#define KEY_TEMPERATURE 0
#define KEY_CONDITIONS 1
#define weather_font_resource RESOURCE_ID_FONT_NEUROPOLITICAL_20
#define weather_colour GColorRed
#define weather_position GRect(0, 0, 144, 24)
#define weather_alignment GTextAlignmentLeft
//#define weather_position GRect(0, 148, 144, 20)
//#define weather_alignment GTextAlignmentRight
  
static TextLayer *s_weather_layer;
static GFont s_weather_font;

static void update_weather() {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  // Add a key-value pair
  dict_write_uint8(iter, 0, 0);

  app_message_outbox_send();
}

static void create_weather_layer() {
  s_weather_layer = text_layer_create(weather_position);
  s_weather_font = fonts_load_custom_font(resource_get_handle(weather_font_resource));
  
  text_layer_set_background_color(s_weather_layer, GColorClear);
  text_layer_set_text_color(s_weather_layer, weather_colour);
  text_layer_set_font(s_weather_layer, s_weather_font);
  text_layer_set_text(s_weather_layer, "Loading...");
  text_layer_set_text_alignment(s_weather_layer, weather_alignment);
}

static void weather_deinit() {
  text_layer_destroy(s_weather_layer);
  fonts_unload_custom_font(s_weather_font);
}