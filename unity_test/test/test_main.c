#include "unity.h"
#include "src/emulation/test_emu.h"
#include "lvgl.h"
#include "hal/hal.h"

/* external vars */
extern lv_obj_t* btn1; 
extern lv_obj_t* btn2;
extern lv_obj_t* btn3;
extern lv_obj_t* btn4;

void setUp(void) {
    lv_init();  // initialize LVGL
    sdl_hal_init(200, 350);
    test_emulation_setup();
}

void tearDown(void) {
    // optional: free LVGL resources
}

void test_buttons_created(void) {
    btn1 = lv_obj_get_child(lv_screen_active(), 0);
    btn2 = lv_obj_get_child(lv_screen_active(), 1);
    btn3 = lv_obj_get_child(lv_screen_active(), 2);
    btn4 = lv_obj_get_child(lv_screen_active(), 3);
    TEST_ASSERT_NOT_NULL(btn1);
    TEST_ASSERT_NOT_NULL(btn2);
    TEST_ASSERT_NOT_NULL(btn3);
    TEST_ASSERT_NOT_NULL(btn4);

    const char* name1 = lv_obj_get_name(btn1);
    TEST_ASSERT_EQUAL_STRING("btn_1", name1);
    const char* name2 = lv_obj_get_name(btn2);
    TEST_ASSERT_EQUAL_STRING("btn_2", name2);
    const char* name3 = lv_obj_get_name(btn3);
    TEST_ASSERT_EQUAL_STRING("btn_3", name3);
    const char* name4 = lv_obj_get_name(btn4);
    TEST_ASSERT_EQUAL_STRING("btn_4", name4);
}

void test_button_event_cb(void) {
    test_emulation_setup();

    btn1 = lv_obj_get_child(lv_screen_active(), 0);
    
    lv_obj_send_event(btn1, LV_EVENT_PRESSED, NULL);
    lv_color_t color = lv_obj_get_style_bg_color(btn1, LV_PART_MAIN);
    uint32_t hexcolor = lv_color_to_u32(color);
    hexcolor &= 0x00FFFFFF;
    TEST_ASSERT_EQUAL_HEX32(0xFF0000, hexcolor);  // RED

    lv_obj_send_event(btn1, LV_EVENT_RELEASED, NULL);
    color = lv_obj_get_style_bg_color(btn1, LV_PART_MAIN);
    hexcolor = lv_color_to_u32(color);
    hexcolor &= 0x00FFFFFF;
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFF, hexcolor);  // WHITE
}