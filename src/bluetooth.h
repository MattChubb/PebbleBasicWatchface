static BitmapLayer *s_bt_icon_layer;
static GBitmap *s_bt_icon_bitmap;


static void bluetooth_handler(bool connected) {
  layer_set_hidden(bitmap_layer_get_layer(s_bt_icon_layer), connected);

  if(!connected) {
    vibes_double_pulse();
  }
}


static void create_bt_icon_layer() {
  s_bt_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_ICON);

  s_bt_icon_layer = bitmap_layer_create(GRect(114, 0, 30, 30));
  bitmap_layer_set_bitmap(s_bt_icon_layer, s_bt_icon_bitmap);
}


static void bluetooth_init() {
  bluetooth_connection_service_subscribe(bluetooth_handler);
  bluetooth_handler(bluetooth_connection_service_peek());
}

static void bluetooth_deinit() {
  gbitmap_destroy(s_bt_icon_bitmap);
  bitmap_layer_destroy(s_bt_icon_layer);
}