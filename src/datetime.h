static TextLayer *s_time_layer;
static TextLayer *s_date_layer;
static TextLayer *s_day_layer;
static GFont s_time_font;
static GFont s_date_font;
static GFont s_day_font;

#define main_clock_font_resource RESOURCE_ID_FONT_SFAUTO_70
#define date_font_resource RESOURCE_ID_FONT_NEUROPOLITICAL_20
#define day_font_resource RESOURCE_ID_FONT_NEUROPOLITICAL_20
#define main_clock_position GRect(0, 20, 144, 70)
#define date_position GRect(0, 0, 144, 25)
#define day_position GRect(0, 110, 144, 25)
#define main_clock_colour GColorRed
#define date_colour GColorCyan
#define day_colour GColorCyan
#define main_clock_background_colour GColorClear

static void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  static char time_buffer[] = "2222";
  static char date_buffer[] = "01 Jan 2000";
  static char day_buffer[] = "Wednesday";
  
  // Time
  if (clock_is_24h_style() == true) {
//    strftime(time_buffer, sizeof("0000"), "%H%M", tick_time);
  } else {
    strftime(time_buffer, sizeof("0000"), "%I%M", tick_time);
  }
  
  // Date
  strftime(date_buffer, sizeof("01 Jan 2000"), "%e %b %Y", tick_time);
  
  // Day
  strftime(day_buffer, sizeof("Wednesday"), "%A", tick_time);
  
  text_layer_set_text(s_time_layer, time_buffer);
  text_layer_set_text(s_date_layer, date_buffer);
  text_layer_set_text(s_day_layer, day_buffer);
}

static void create_time_layer() {
  s_time_layer = text_layer_create(main_clock_position);
  s_time_font = fonts_load_custom_font(resource_get_handle(main_clock_font_resource));
  
  text_layer_set_background_color(s_time_layer, main_clock_background_colour);
  text_layer_set_text_color(s_time_layer, main_clock_colour);
  text_layer_set_font(s_time_layer, s_time_font);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
}

static void create_date_layer() {
  s_date_layer = text_layer_create(date_position);
  s_date_font = fonts_load_custom_font(resource_get_handle(date_font_resource));
  
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_color(s_date_layer, date_colour);
  text_layer_set_font(s_date_layer, s_date_font);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
}

static void create_day_layer() {
  s_day_layer = text_layer_create(day_position);
  s_day_font = fonts_load_custom_font(resource_get_handle(day_font_resource));
  
  text_layer_set_background_color(s_day_layer, GColorClear);
  text_layer_set_text_color(s_day_layer, day_colour);
  text_layer_set_font(s_day_layer, s_day_font);
  text_layer_set_text_alignment(s_day_layer, GTextAlignmentCenter);
}

static void datetime_deinit() {
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_day_layer);
  fonts_unload_custom_font(s_time_font);
  fonts_unload_custom_font(s_date_font);
  fonts_unload_custom_font(s_day_font);
}