/**
 * @file test_emu_handlers.c
 *
 */
#include "src/emulation/test_emu_handlers.h"

/**
 * Event handler for button clicks in main menu
 * @param e fired event, triggered by registered objects
 */
void v_event_btn_main_bottom(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e); // get event code
    v_btn_enum_main_bottom_t btn_id = (v_btn_enum_main_bottom_t)(intptr_t)lv_event_get_user_data(e);
    lv_obj_t * btn = lv_event_get_target_obj(e); // event object
    switch(code){
        case LV_EVENT_PRESSED:
        /* nothing happens here (for now) */
            switch (btn_id) {
                case BTN_ADULT_FETAL:
                case BTN_TRIGGER:
                case BTN_DEPTH:
                case BTN_WLAN:
                case BTN_SOUND:
                case BTN_SETTINGS:
                case BTN_ADFET_SWITCH:
                    break;
                default:
                    break;
            }
            break;
        case LV_EVENT_CLICKED:
        /* all buttons handled by same function (for now) */
            switch (btn_id) {
                case BTN_ADULT_FETAL:
                case BTN_TRIGGER:
                case BTN_DEPTH:
                case BTN_WLAN:
                case BTN_SOUND:
                case BTN_SETTINGS:
                case BTN_ADFET_SWITCH:
                    v_btn_redraw(btn_id);
                    break;
                default:
                    break;
            }
            break;
    }
}

/**
 * Event handler for clicks, that are not onto a widget
 * @param e fired event, triggered by registered objects
 */
void v_event_btn_main_bg(lv_event_t * e)
{
    v_btn_enum_main_bottom_t btn_id = (v_btn_enum_main_bottom_t)(intptr_t)lv_event_get_user_data(e);
    v_btn_set_main_bot_menu_t * state = get_buttonStateMainBot();
    v_button_update_main_switch(state, btn_id);
}

/**
 * redrawing the main menu depending on fetal/adult mode and their settings
 * @param btn_id currently activated button
 */
void v_btn_redraw(v_btn_enum_main_bottom_t btn_id)
{
    v_btn_set_main_bot_menu_t * state = get_buttonStateMainBot();
    /* adult mode */
    if(state->btn_adult_active)
    {
        switch (btn_id) {
            case BTN_ADULT_FETAL:
                /* changing mode to fetal */
                break;
            case BTN_TRIGGER:
                state->btn_trig_adult_active = !state->btn_trig_adult_active;
                break;
            case BTN_DEPTH:
                state->btn_depth_adult_active = !state->btn_depth_adult_active;
                break;
            case BTN_WLAN:
                state->btn_WLAN_active = !state->btn_WLAN_active;
                break;
            case BTN_SOUND:
                state->btn_sound_active = !state->btn_sound_active;
                break;
            case BTN_SETTINGS:
                break;
            default:
                break;
        }
    }
    /* fetal mode */
    else
    {
        switch (btn_id) {
            case BTN_ADULT_FETAL:
                /* changing mode to adult */
                break;
            case BTN_TRIGGER:
                state->btn_trig_fetal_active = !state->btn_trig_fetal_active;
                break;
            case BTN_DEPTH:
                state->btn_depth_fetal_active = !state->btn_depth_fetal_active;
                break;
            case BTN_WLAN:
                state->btn_WLAN_active = !state->btn_WLAN_active;
                break;
            case BTN_SOUND:
                state->btn_sound_active = !state->btn_sound_active;
                break;
            case BTN_SETTINGS:
                break;
            default:
                break;
        }
    }
    /* updating the menu buttons */
    v_button_update_main_switch(state, btn_id);
    v_button_update_main_bottom(state);
}

/**
 * Event handler 1 for button clicking
 * @param e fired event, triggered by registered objects
 */
void btn_event_cb_1(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e); // get event code
    lv_obj_t * btn = lv_event_get_target_obj(e); // event object
    switch(code){
        // interaction with the button
        case LV_EVENT_PRESSED:
            /*Get the first child of the button which is the label and change its text*/
            // lv_obj_set_style_bg_color(btn, lv_color_hex(V_CLR_RED), LV_PART_MAIN);
            break;
        // interaction stopped
        case LV_EVENT_RELEASED:
            // lv_obj_set_style_bg_color(btn, lv_color_hex(V_CLR_WHITE), LV_PART_MAIN);
            break;
    }
}