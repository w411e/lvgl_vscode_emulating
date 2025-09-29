#include "hal.h"


lv_display_t * sdl_hal_init(int32_t w, int32_t h)
{

  lv_group_set_default(lv_group_create()); // collects focusable objects, best for testing, might need changes for final board, if just touchscreen maybe unused

  lv_display_t * disp = lv_sdl_window_create(w, h);

  lv_indev_t * mouse = lv_sdl_mouse_create();       // mouse input device
  lv_indev_set_group(mouse, lv_group_get_default());// set the default group for the mouse input device
  lv_indev_set_display(mouse, disp);                // bind the mouse input device to the display
  lv_display_set_default(disp);                     // set the created display as the default display
  /*Declare the image file. (c file: src\mouse_cursor_icon.c )*/
  LV_IMAGE_DECLARE(mouse_cursor_icon); 
  lv_obj_t * cursor_obj;
  /*Create an image object for the cursor on the active screen*/
  cursor_obj = lv_image_create(lv_screen_active()); 
  /*Set the image source to cursor icon*/
  lv_image_set_src(cursor_obj, &mouse_cursor_icon);           
  /*Connect the image  object to the driver, cursor image to mouse input device*/
  lv_indev_set_cursor(mouse, cursor_obj);             

  lv_indev_t * mousewheel = lv_sdl_mousewheel_create();   // mousewheel input device
  lv_indev_set_display(mousewheel, disp);                 // bind the mousewheel input device to the display
  lv_indev_set_group(mousewheel, lv_group_get_default()); // set the default group for the mousewheel input device

  lv_indev_t * kb = lv_sdl_keyboard_create();     // keyboard input device
  lv_indev_set_display(kb, disp);                 // bind the keyboard input device to the display
  lv_indev_set_group(kb, lv_group_get_default()); // set the default group for the keyboard input device

  return disp;
}
