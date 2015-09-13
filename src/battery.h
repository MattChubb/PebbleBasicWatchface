static TextLayer *s_battery_layer;
static GFont s_battery_font;

#define battery_font_resource RESOURCE_ID_FONT_NEUROPOLITICAL_15
#define battery_colour GColorWhite

static void battery_handler(BatteryChargeState state) {
  static char battery_buffer[4] = "100%";
  snprintf(battery_buffer, sizeof(battery_buffer), "%d%%", state.charge_percent);
  text_layer_set_text(s_battery_layer, battery_buffer);
}

static void create_battery_layer() {
  s_battery_layer = text_layer_create(GRect(0, 148, 144, 20));
  s_battery_font = fonts_load_custom_font(resource_get_handle(battery_font_resource));
  
  text_layer_set_background_color(s_battery_layer, GColorClear);
  text_layer_set_text_color(s_battery_layer, battery_colour);
  text_layer_set_font(s_battery_layer, s_battery_font);
  text_layer_set_text_alignment(s_battery_layer, GTextAlignmentRight);
}

static void battery_init() {
  battery_state_service_subscribe(battery_handler);
  battery_handler(battery_state_service_peek());
}

static void battery_deinit() {
  text_layer_destroy(s_battery_layer);
  fonts_unload_custom_font(s_battery_font);
}