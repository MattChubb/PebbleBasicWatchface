#include <pebble.h>
#include <datetime.h>
#include <weather.h>
#include <battery.h>
#include <bluetooth.h>
#include <ctype.h>

#define watchface_background_colour GColorBlack

static Window *s_main_window;

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
  
  if ( tick_time->tm_min == 0 ) {
    update_weather();
  }
}


static void main_window_load(Window *window) {
  window_set_background_color(window, watchface_background_colour);
    
  create_time_layer();
  create_date_layer();
  create_day_layer();
  create_weather_layer();
  create_battery_layer();
  create_bt_icon_layer();
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_weather_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_battery_layer));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_bt_icon_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_day_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
}

static void main_window_unload(Window *window) {}


static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  static char temperature_buffer[8];
  static char conditions_buffer[32];
  static char weather_layer_buffer[32];
  
  Tuple *t = dict_read_first(iterator);

  while(t != NULL) {
    switch(t->key) {
    case KEY_TEMPERATURE:
      snprintf(temperature_buffer, sizeof(temperature_buffer), "%dC", (int)t->value->int32);
      break;
    case KEY_CONDITIONS:
      snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
      break;
    case KEY_SEPARATOR:
      snprintf(time_separator,  sizeof(time_separator), "%s", t->value->cstring);
    default:
      APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
      break;
    }

    t = dict_read_next(iterator);
  }
  
  snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s, %s", temperature_buffer, conditions_buffer);
  text_layer_set_text(s_weather_layer, weather_layer_buffer);
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}
static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}
static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}


static void init() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Initialising...");
 
  // Main window
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Loading main window...");
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(s_main_window, true);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Main window loaded.");
  
  // Callbacks
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Setting up callbacks...");
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Callbacks configured successfully.");
 
  // Libraries
  battery_init();
  bluetooth_init();
  // Time
  update_time();
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  update_weather();
}

static void deinit() {
  window_destroy(s_main_window);

  datetime_deinit();
  weather_deinit();
  battery_deinit();
  bluetooth_deinit();
}


int main(void) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Starting up...");
  init();
  app_event_loop();
  deinit();
}