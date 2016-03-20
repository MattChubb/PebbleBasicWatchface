static TextLayer *s_time_layer;
static TextLayer *s_date_layer;
static TextLayer *s_day_layer;
static GFont s_time_font;
static GFont s_date_font;
static GFont s_day_font;
static char time_separator[] = ":";

#define KEY_SEPARATOR 2
#define main_clock_font_resource RESOURCE_ID_FONT_BEBASNEUE_75
#define date_font_resource RESOURCE_ID_FONT_NEUROPOLITICAL_20
#define day_font_resource RESOURCE_ID_FONT_NEUROPOLITICAL_20
#define main_clock_position GRect(0, 25, 144, 85)

#define day_position GRect(0, 124, 144, 24)
#define date_position GRect(0, 148, 144, 20)
#define date_alignment GTextAlignmentRight
#define day_alignment GTextAlignmentRight
//#define day_position GRect(0, 20, 144, 24)
//#define date_position GRect(0, 0, 144, 20)
//#define date_alignment GTextAlignmentLeft
//#define day_alignment GTextAlignmentLeft

#define main_clock_colour GColorWhite
#define date_colour GColorRed
#define day_colour GColorRed
#define main_clock_background_colour GColorClear

static void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  static char time_buffer[] = "20:58";
  static char date_buffer[] = "01 Jan 2000";
  static char day_buffer[] = "Wednesday";
  char time_format[5] = "";

  // Time
  if (clock_is_24h_style() == true) {
    strcat(time_format, "%H");
  } else {
    strcat(time_format, "%I");
  }
  strcat(time_format, time_separator);
  strcat(time_format, "%M");
  strftime(time_buffer, sizeof("00:00"), time_format, tick_time);
  
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
  text_layer_set_text_alignment(s_date_layer, date_alignment);
}

static void create_day_layer() {
  s_day_layer = text_layer_create(day_position);
  s_day_font = fonts_load_custom_font(resource_get_handle(day_font_resource));
  
  text_layer_set_background_color(s_day_layer, GColorClear);
  text_layer_set_text_color(s_day_layer, day_colour);
  text_layer_set_font(s_day_layer, s_day_font);
  text_layer_set_text_alignment(s_day_layer, day_alignment);
}

static void datetime_deinit() {
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_day_layer);
  fonts_unload_custom_font(s_time_font);
  fonts_unload_custom_font(s_date_font);
  fonts_unload_custom_font(s_day_font);
}