#define KEY_TEMPERATURE 0
#define KEY_CONDITIONS 1
#define weather_font_resource RESOURCE_ID_FONT_PERFECT_DOS_VGA_20
  
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
  s_weather_layer = text_layer_create(GRect(0, 148, 144, 20));
  s_weather_font = fonts_load_custom_font(resource_get_handle(weather_font_resource));
  
  text_layer_set_background_color(s_weather_layer, GColorClear);
  text_layer_set_text_color(s_weather_layer, GColorBlack);
  text_layer_set_font(s_weather_layer, s_weather_font);
  text_layer_set_text(s_weather_layer, "Loading...");
  text_layer_set_text_alignment(s_weather_layer, GTextAlignmentLeft);
}

static void weather_deinit() {
  text_layer_destroy(s_weather_layer);
  fonts_unload_custom_font(s_weather_font);
}