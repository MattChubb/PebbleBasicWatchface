static TextLayer *s_time_layer;
static TextLayer *s_date_layer;
static GFont s_time_font;
static GFont s_date_font;

static void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  static char time_buffer[] = "0000";
  static char date_buffer[] = "01 Jan 2000";
  
  // Time
  if (clock_is_24h_style() == true) {
    strftime(time_buffer, sizeof("0000"), "%H%M", tick_time);
  } else {
    strftime(time_buffer, sizeof("0000"), "%I%M", tick_time);
  }
  
  // Date
  strftime(date_buffer, sizeof("01 Jan 2000"), "%e %b %Y", tick_time);
  
  text_layer_set_text(s_time_layer, time_buffer);
  text_layer_set_text(s_date_layer, date_buffer);
}

static void create_time_layer() {
  s_time_layer = text_layer_create(GRect(0, 50, 144, 55));
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PERFECT_DOS_VGA_52));
  
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_font(s_time_layer, s_time_font);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
}

static void create_date_layer() {
  s_date_layer = text_layer_create(GRect(0, 25, 144, 25));
  s_date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PERFECT_DOS_VGA_20));
  
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_color(s_date_layer, GColorBlack);
  text_layer_set_font(s_date_layer, s_date_font);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
}

static void datetime_deinit() {
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_date_layer);
  fonts_unload_custom_font(s_time_font);
  fonts_unload_custom_font(s_date_font);
}