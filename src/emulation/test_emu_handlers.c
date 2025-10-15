/**
 * @file test_emu_handlers.c
 *
 */
#include "src/emulation/test_emu_handlers.h"

/**
 * empty event handler for button init without sth happening
 */
void btn_event_cb_empty(lv_event_t * e)
{
    // nothing happens
}

/**
 * Event handler 1 for button clicking
 */
void btn_event_cb_1(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e); // get event code
    lv_obj_t * btn = lv_event_get_target_obj(e); // event object
    switch(code){
        // interaction with the button
        case LV_EVENT_PRESSED || LV_EVENT_CLICKED || LV_EVENT_LONG_PRESSED || LV_EVENT_LONG_PRESSED_REPEAT:
            /*Get the first child of the button which is the label and change its text*/
            lv_obj_set_style_bg_color(btn, lv_color_hex(RED), LV_PART_MAIN);
            break;
        // interaction stopped
        case LV_EVENT_RELEASED:
            lv_obj_set_style_bg_color(btn, lv_color_hex(WHITE), LV_PART_MAIN);
            break;
    }
}