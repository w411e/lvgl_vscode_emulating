/**
 * @file test_emu.c
 *
 */
#include "src/emulation/test_emu.h"

/**
 * Globals (must do for testing)
 */
lv_obj_t *scr_def;
lv_obj_t *btn1;
lv_obj_t *btn2;
lv_obj_t *btn3;
lv_obj_t *btn4;

/**
 * code for testsetup, called in main()
 */
void test_emulation_setup(void)
{
    // get starting screen
    scr_def = lv_screen_active();
    // button style
    static lv_style_t bst;
    lv_style_init(&bst);
    lv_style_set_radius(&bst, 5);
    lv_style_set_width(&bst, 100);
    lv_style_set_height(&bst, 50);
    lv_style_set_pad_all(&bst, 5);
    // init buttons and labels
    btn1 = lv_button_create(scr_def);
    btn2 = lv_button_create(scr_def);
    btn3 = lv_button_create(scr_def);
    btn4 = lv_button_create(scr_def);
    lv_obj_t *lab1 = lv_label_create(btn1);
    lv_obj_t *lab2 = lv_label_create(btn2);
    lv_obj_t *lab3 = lv_label_create(btn3);
    lv_obj_t *lab4 = lv_label_create(btn4);

    #ifdef TEST
        lv_obj_set_name(btn1, "btn_1");
        lv_obj_set_name(btn2, "btn_2");
        lv_obj_set_name(btn3, "btn_3");
        lv_obj_set_name(btn4, "btn_4");
    #endif

    // setup
    lv_obj_set_style_bg_color(btn1, lv_color_hex(WHITE), LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn2, lv_color_hex(WHITE), LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn3, lv_color_hex(WHITE), LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn4, lv_color_hex(WHITE), LV_PART_MAIN);
    lv_obj_set_pos(btn1, 10, 10);
    lv_obj_set_pos(btn2, 10, 70);
    lv_obj_set_pos(btn3, 10, 130);
    lv_obj_set_pos(btn4, 10, 190);
    lv_obj_add_style(btn1, &bst, 0);
    lv_obj_add_style(btn2, &bst, 0);
    lv_obj_add_style(btn3, &bst, 0);
    lv_obj_add_style(btn4, &bst, 0);
    lv_label_set_text(lab1, "Button 1");
    lv_label_set_text(lab2, "Button 2");
    lv_label_set_text(lab3, "Button 3");
    lv_label_set_text(lab4, "Button 4");
    lv_obj_set_style_text_color(lab1, lv_color_hex(DEF), LV_PART_MAIN);
    lv_obj_set_style_text_color(lab2, lv_color_hex(DEF), LV_PART_MAIN);
    lv_obj_set_style_text_color(lab3, lv_color_hex(DEF), LV_PART_MAIN);
    lv_obj_set_style_text_color(lab4, lv_color_hex(DEF), LV_PART_MAIN);
    lv_obj_center(lab1);
    lv_obj_center(lab2);
    lv_obj_center(lab3);
    lv_obj_center(lab4);
    // events
    lv_obj_add_event_cb(btn1, btn_event_cb_1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(btn2, btn_event_cb_1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(btn3, btn_event_cb_1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(btn4, btn_event_cb_1, LV_EVENT_ALL, NULL);
}