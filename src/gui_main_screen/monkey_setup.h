/**
 * @file monkey_setup.h
 *
 */

#ifndef MONKEY_SETUP_H
#define MONKEY_SETUP_H

#ifdef __cplusplus
extern "C" {
#endif

// includes
#include "lvgl.h"


void v_test_setup_monkey(void)
{
    #if V_TEST_MONKEYSETUP
        lv_monkey_config_t mconfig;
        lv_monkey_t * monkey;
        lv_indev_t* indev;
    #endif
    lv_obj_t *labMonkey = lv_label_create(lv_screen_active());

    #if V_TEST_MONKEYSETUP == 0
        lv_label_set_text(labMonkey, "Monkeyvers: Not activated");
        lv_obj_set_style_text_color(labMonkey, lv_color_hex(V_CLR_BLACK), LV_PART_MAIN);
        lv_obj_set_pos(labMonkey, 5, 280);
    #endif

    /* Monkeytest setup screen */
    #if V_TEST_MONKEYSETUP == 1
        lv_label_set_text(labMonkey, "Monkeyvers: Anywhere");
        lv_monkey_config_init(&mconfig);
        mconfig.type = LV_INDEV_TYPE_POINTER;
        mconfig.period_range.min = 10;
        mconfig.period_range.max = 50;
        mconfig.input_range.min = 0;
        mconfig.input_range.max = 350;
        monkey = lv_monkey_create(&mconfig);
        indev = lv_monkey_get_indev(monkey);
    #endif

    #if V_TEST_MONKEYSETUP == 2
        lv_label_set_text(labMonkey, "Monkeyvers: Buttonhits");
        lv_point_t btn_mon_arr[BTNNUM];
        lv_monkey_config_init(&mconfig);
        mconfig.type = LV_INDEV_TYPE_POINTER;
        mconfig.period_range.min = 10;
        mconfig.period_range.max = 50;
        mconfig.input_range.min = 0;
        mconfig.input_range.max = sizeof(btn_mon_arr) / sizeof(lv_point_t) - 1;
        monkey = lv_monkey_create(&mconfig);

        for(int i = 0; i < BTNNUM; i++) {
            lv_area_t area;
            lv_obj_get_coords(btn_monkey[i], &area);
            btn_mon_arr[i].x = ((area.x2-area.x1) / 2) + area.x1;
            btn_mon_arr[i].y = ((area.y2-area.y1) / 2) + area.y1;
        }
        indev = lv_monkey_get_indev(monkey);
        lv_indev_set_button_points(indev, btn_mon_arr);
    #endif
    /* monkey start */
    #if V_TEST_MONKEYSETUP
        lv_obj_set_style_text_color(labMonkey, lv_color_hex(V_CLR_BLACK), LV_PART_MAIN);
        lv_obj_set_pos(labMonkey, 15, 280);
        lv_indev_set_display(indev, lv_disp_get_default());
        lv_monkey_set_enable(monkey, true);
    #endif
}

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*MONKEY_SETUP_H*/