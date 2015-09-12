static int s_battery_level;
static TextLayer *s_battery_layer;
static GFont s_battery_font;

static void battery_callback(BatteryChargeState state) {
  static char battery_buffer[] = "100%";
  s_battery_level = state.charge_percent;
  snprintf(battery_buffer, sizeof(battery_buffer), "%d", s_battery_level);
  text_layer_set_text(s_battery_layer, battery_buffer);
}

static void create_battery_layer() {
  s_battery_layer = text_layer_create(GRect(14, 54, 115, 2));
  text_layer_set_text(s_battery_layer, "---%");
}

static void battery_init() {
  battery_callback(battery_state_service_peek());
  battery_state_service_subscribe(battery_callback);
}

static void battery_deinit() {
  text_layer_destroy(s_battery_layer);
  fonts_unload_custom_font(s_battery_font);
}