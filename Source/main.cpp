#include "../Headers/GameManager.h"

int main(int argc, char **argv) {
  if (!al_init()) { // initialize Allegro
    return -1;
  }
  if (!al_init_image_addon()) {
    return -1;
  }
  if (!al_init_acodec_addon()) {
    return -1;
  }
  if (!al_install_audio()) {
    return -1;
  }
  if (!al_init_font_addon()) {
    return -1;
  }
  if (!al_init_ttf_addon()) {
    return -1;
  }
  int screenWidth = pixel * 37;  // w
  int screenHeight = pixel * 24; // h
  ALLEGRO_BITMAP *buffer;
  buffer = al_create_bitmap(screenWidth, screenHeight);
  if (!buffer) {
    cout << "Fatal error, unable to create a buffer";
    return -1;
  }
  al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
  ALLEGRO_DISPLAY *display = al_create_display(screenWidth, screenHeight);

  if (!display) {
    cout << "Fatal error, unable to create a display";
    return -1;
  }

  int windowHeight = al_get_display_height(display);
  int windowWidth = al_get_display_width(display);
  float sx = windowWidth / float(screenWidth);
  float sy = windowHeight / float(screenHeight);
  int scale = std::min(sx, sy);
  int scaleW = screenWidth * scale;
  int scaleH = screenHeight * scale;
  int scaleX = (windowWidth - scaleW) / 2;
  int scaleY = (windowHeight - scaleH) / 2;
  al_set_target_bitmap(buffer);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_install_keyboard();

  GameManager *game;
  game = new GameManager(display, buffer, scaleW, scaleH, scaleX, scaleY);
  al_reserve_samples(1);
  game->Menu();
  game->gioco();

  al_destroy_display(display);
  al_destroy_bitmap(buffer);
  al_uninstall_keyboard();
  delete game;

  return 0;
}