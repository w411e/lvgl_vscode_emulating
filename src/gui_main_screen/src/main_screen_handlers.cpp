/**
 * @file main_screen_handlers.c
 *
 */
#include <memory>
#include "../inc/main_screen_handlers.hpp"
#include "../inc/main_screen.hpp"

namespace v_main_screen {

/* screen instance */
extern std::unique_ptr<v_main_screen::v_smart_sync_gui> g_gui;

/**
 * Event handler for button clicks in main menu
 * @param e fired event, triggered by registered objects
 */
void v_event_btn_main_bottom(lv_event_t* e)
{
    const lv_event_code_t v_code = lv_event_get_code(e);
    const auto v_btn_id = static_cast<v_btn_main_id>(reinterpret_cast<intptr_t>(lv_event_get_user_data(e)));
    lv_obj_t* v_btn = lv_event_get_target_obj(e);
    switch (v_code){
        case LV_EVENT_PRESSED:
            switch (v_btn_id) {
                case v_btn_main_id::adult_fetal:
                case v_btn_main_id::trigger:
                case v_btn_main_id::depth:
                case v_btn_main_id::wlan:
                case v_btn_main_id::sound:
                case v_btn_main_id::settings:
                case v_btn_main_id::adfet_switch:
                    break;
                default:
                    break;
            }
        break;

        case LV_EVENT_CLICKED:
            switch (v_btn_id) {
                case v_btn_main_id::adult_fetal:
                case v_btn_main_id::trigger:
                case v_btn_main_id::depth:
                case v_btn_main_id::wlan:
                case v_btn_main_id::sound:
                case v_btn_main_id::settings:
                case v_btn_main_id::adfet_switch:
                    v_btn_redraw(v_btn_id);
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
void v_event_btn_main_bg(lv_event_t* e)
{
    auto* v_state = g_gui->v_get_button_state_main_bottom(); // call normal member function
    v_btn_main_id v_btn_id = static_cast<v_btn_main_id>(reinterpret_cast<intptr_t>(lv_event_get_user_data(e)));
    g_gui->v_button_update_main_switch(v_state, v_btn_id);
}

/**
 * redrawing the main menu depending on fetal/adult mode and their settings
 * @param v_btn_id currently activated button
 */
void v_btn_redraw(v_btn_main_id v_btn_id)
{
    auto* v_state = g_gui->v_get_button_state_main_bottom();
    /* Adult mode */
    if (v_state->v_btn_adult_active)
    {
        switch (v_btn_id) {
            case v_btn_main_id::adult_fetal:
                /* changing to fetal mode */
                break;
            case v_btn_main_id::trigger:
                v_state->v_btn_trig_adult_active = !v_state->v_btn_trig_adult_active;
                break;
            case v_btn_main_id::depth:
                v_state->v_btn_depth_adult_active = !v_state->v_btn_depth_adult_active;
                break;
            case v_btn_main_id::wlan:
                v_state->v_btn_wlan_active = !v_state->v_btn_wlan_active;
                break;
            case v_btn_main_id::sound:
                v_state->v_btn_sound_active = !v_state->v_btn_sound_active;
                break;
            case v_btn_main_id::settings:
                break;
            default:
                break;
        }
    }
    /* Fetal mode */
    else
    {
        switch (v_btn_id)
        {
            case v_btn_main_id::adult_fetal:
                /* changing to adult mode */
                break;
            case v_btn_main_id::trigger:
                v_state->v_btn_trig_fetal_active = !v_state->v_btn_trig_fetal_active;
                break;
            case v_btn_main_id::depth:
                v_state->v_btn_depth_fetal_active = !v_state->v_btn_depth_fetal_active;
                break;
            case v_btn_main_id::wlan:
                v_state->v_btn_wlan_active = !v_state->v_btn_wlan_active;
                break;
            case v_btn_main_id::sound:
                v_state->v_btn_sound_active = !v_state->v_btn_sound_active;
                break;
            case v_btn_main_id::settings:
                break;
            default:
                break;
        }
    }
    /* update menu buttons */
    g_gui->v_button_update_main_switch(v_state, v_btn_id);
    g_gui->v_button_update_main_bottom(v_state);
}

/**
 * Event handler 1 for button clicking
 * @param e fired event, triggered by registered objects
 */
void v_btn_event_cb_1(lv_event_t* e)
{
    const lv_event_code_t v_code = lv_event_get_code(e);
    lv_obj_t* v_btn = lv_event_get_target_obj(e);
    switch (v_code){
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

} // namespace v_main_screen
