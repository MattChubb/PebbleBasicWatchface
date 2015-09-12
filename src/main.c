#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_time_layer;
static GFont s_time_font;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;


static void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  static char buffer[] = "0000";
  
  if (clock_is_24h_style() == true) {
    strftime(buffer, sizeof("0000"), "%H%M", tick_time);
  } else {
    strftime(buffer, sizeof("0000"), "%I%M", tick_time);
  }
  
  text_layer_set_text(s_time_layer, buffer);
}


static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}


static void main_window_load(Window *window) {
  // Background
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BASIC_BACKGROUND);
  s_background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  
  // Time
  s_time_layer = text_layer_create(GRect(0, 50, 144, 55));
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PERFECT_DOS_VGA_52));
  
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_font(s_time_layer, s_time_font);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  
  // Putting it all together
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_background_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
}

static void main_window_unload(Window *window) {
  text_layer_destroy(s_time_layer);
}


static void init() {
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(s_main_window, true);
  
  update_time();
  
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
  window_destroy(s_main_window);
  fonts_unload_custom_font(s_time_font);
  gbitmap_destroy(s_background_bitmap);
  bitmap_layer_destroy(s_background_layer);
}


int main(void) {
  init();
  app_event_loop();
  deinit();
}


