/**
 * @file main_screen.cpp
 *
 */

#include "../inc/main_screen.hpp"
// #include "monkey_setup.hpp"
#include "../inc/main_screen_handlers.hpp"

namespace v_main_screen {

v_smart_sync_gui* g_gui_instance = nullptr;

/**
 * contructor main menu gui
 */
v_smart_sync_gui::v_smart_sync_gui()
{
    // store active screen
    v_scr_main_ = lv_screen_active();

    // accessor for btn states
    g_gui_instance = this;

    // setup initial state, styles and UI
    v_state_setup_main_menu();
    v_style_setup_main_bottom_buttons();
    v_button_setup_main_bottom(V_BTN_SIZE_MAIN_BOT_WIDTH, 0);
    v_background_setup_main(V_SCR_WIDTH, V_SCR_HEIGHT);

    // optional monkey setup if enabled
    #ifdef LV_USE_TEST
        #if V_TEST_MONKEYSETUP
            v_test_setup_monkey();
        #endif
    #endif
}

/**
 * destructor main menu gui
 */
v_smart_sync_gui::~v_smart_sync_gui()
{
    /* destruct any objects, that might exist */
    for (auto &b : v_btns_main_bottom_) {
        if (b) lv_obj_del(b);
    }
    if (v_btn_main_switch_) lv_obj_del(v_btn_main_switch_);
    if (v_scr_main_background_) lv_obj_del(v_scr_main_background_);
}

/**
 * state and color setup main menu, start in adult
 */
void v_smart_sync_gui::v_state_setup_main_menu()
{
    /* Initialize button states */
    v_button_state_main_bot_.v_btn_adult_active      = true;  /* default start in adult */
    v_button_state_main_bot_.v_btn_switch_active     = false; /* default start no switch btn */
    v_button_state_main_bot_.v_btn_trig_adult_active = false; /* default start trigger off */
    v_button_state_main_bot_.v_btn_trig_fetal_active = false; /* default start trigger off */
    v_button_state_main_bot_.v_btn_depth_adult_active= false; /* default start depth off */
    v_button_state_main_bot_.v_btn_depth_fetal_active= false; /* default start depth off */
    v_button_state_main_bot_.v_btn_wlan_active       = false; /* default start WLAN not connected */
    v_button_state_main_bot_.v_btn_sound_active      = false; /* default start sound off */
    v_button_state_main_bot_.v_btn_settings_active   = false; /* default not in settings menu */

    /* Initialize colors */
    v_button_color_main_bot_.v_btn_adfet        = V_BTN_ICON_CLR_MAIN_BOT_DEFAULT;
    v_button_color_main_bot_.v_btn_adfet_switch = V_BTN_ICON_CLR_MAIN_BOT_DEFAULT;
    v_button_color_main_bot_.v_btn_trig_on      = V_BTN_ICON_CLR_MAIN_BOT_DEFAULT;
    v_button_color_main_bot_.v_btn_trig_off     = V_BTN_ICON_CLR_MAIN_BOT_DISABLED;
    v_button_color_main_bot_.v_btn_depth_on     = V_BTN_ICON_CLR_MAIN_BOT_DEFAULT;
    v_button_color_main_bot_.v_btn_depth_off    = V_BTN_ICON_CLR_MAIN_BOT_DISABLED;
    v_button_color_main_bot_.v_btn_wlan_on      = V_BTN_ICON_CLR_MAIN_BOT_WLAN;
    v_button_color_main_bot_.v_btn_wlan_off     = V_BTN_ICON_CLR_MAIN_BOT_WLAN;
    v_button_color_main_bot_.v_btn_sound_on     = V_BTN_ICON_CLR_MAIN_BOT_DEFAULT;
    v_button_color_main_bot_.v_btn_sound_off    = V_BTN_ICON_CLR_MAIN_BOT_DISABLED;
    v_button_color_main_bot_.v_btn_settings     = V_BTN_ICON_CLR_MAIN_BOT_DEFAULT;
    v_button_color_main_bot_.v_btn_bg_adult_default  = V_BTN_BG_CLR_ADULT_DEFAULT;
    v_button_color_main_bot_.v_btn_bg_adult_active   = V_BTN_BG_CLR_ADULT_ACTIVE;
    v_button_color_main_bot_.v_btn_bg_fetal_default  = V_BTN_BG_CLR_FETAL_DEFAULT;
    v_button_color_main_bot_.v_btn_bg_fetal_active   = V_BTN_BG_CLR_FETAL_ACTIVE;
}

/**
 * style setup main menu bottom buttons
 */
void v_smart_sync_gui::v_style_setup_main_bottom_buttons()
{
    /* buttons adult style default */
    lv_style_init(&v_style_adult_default_);
    lv_style_set_radius(&v_style_adult_default_, V_BTN_SIZE_MAIN_BOT_RADIUS);
    lv_style_set_width(&v_style_adult_default_, V_BTN_SIZE_MAIN_BOT_WIDTH);
    lv_style_set_height(&v_style_adult_default_, V_BTN_SIZE_MAIN_BOT_HEIGHT);
    lv_style_set_pad_all(&v_style_adult_default_, V_BTN_SIZE_MAIN_BOT_PAD_ALL);
    lv_style_set_border_width(&v_style_adult_default_, V_BTN_SIZE_MAIN_BOT_BORDER_WIDTH);
    lv_style_set_bg_color(&v_style_adult_default_, v_button_color_main_bot_.v_btn_bg_adult_default);
    lv_style_set_border_color(&v_style_adult_default_, v_button_color_main_bot_.v_btn_bg_adult_default);
    lv_style_set_text_color(&v_style_adult_default_, v_button_color_main_bot_.v_btn_settings);
    lv_style_set_text_font(&v_style_adult_default_, &lv_font_montserrat_32);
    lv_style_set_bg_opa(&v_style_adult_default_, LV_OPA_COVER);

    /* buttons adult style active */
    lv_style_init(&v_style_adult_active_);
    lv_style_set_bg_color(&v_style_adult_active_, v_button_color_main_bot_.v_btn_bg_adult_active);
    lv_style_set_border_color(&v_style_adult_active_, v_button_color_main_bot_.v_btn_bg_adult_active);
    lv_style_set_text_font(&v_style_adult_active_, &lv_font_montserrat_32);

    /* buttons fetal style default */
    lv_style_init(&v_style_fetal_default_);
    lv_style_set_radius(&v_style_fetal_default_, V_BTN_SIZE_MAIN_BOT_RADIUS);
    lv_style_set_width(&v_style_fetal_default_, V_BTN_SIZE_MAIN_BOT_WIDTH);
    lv_style_set_height(&v_style_fetal_default_, V_BTN_SIZE_MAIN_BOT_HEIGHT);
    lv_style_set_pad_all(&v_style_fetal_default_, V_BTN_SIZE_MAIN_BOT_PAD_ALL);
    lv_style_set_border_width(&v_style_fetal_default_, V_BTN_SIZE_MAIN_BOT_BORDER_WIDTH);
    lv_style_set_bg_color(&v_style_fetal_default_, v_button_color_main_bot_.v_btn_bg_fetal_default);
    lv_style_set_border_color(&v_style_fetal_default_, v_button_color_main_bot_.v_btn_bg_fetal_default);
    lv_style_set_text_color(&v_style_fetal_default_, v_button_color_main_bot_.v_btn_settings);
    lv_style_set_text_font(&v_style_fetal_default_, &lv_font_montserrat_32);
    lv_style_set_bg_opa(&v_style_fetal_default_, LV_OPA_COVER);

    /* buttons fetal style active */
    lv_style_init(&v_style_fetal_active_);
    lv_style_set_bg_color(&v_style_fetal_active_, v_button_color_main_bot_.v_btn_bg_fetal_active);
    lv_style_set_border_color(&v_style_fetal_active_, v_button_color_main_bot_.v_btn_bg_fetal_active);
    lv_style_set_text_font(&v_style_fetal_active_, &lv_font_montserrat_32);
}

/**
 * button setup main menu bottom row adult and fetal for startup
 * @param x_offset offset for the buttons on x-axis (alignment bottom left)
 * @param y_offset offset for the buttons on y-axis (alignment bottom left (+down/-up))
 */
void v_smart_sync_gui::v_button_setup_main_bottom(uint32_t x_offset, uint32_t y_offset)
{
    /* middle gap bottom main menu bottons is rest of width */
    const uint32_t v_bottom_mid_gap = V_SCR_WIDTH - (V_BTN_NUM_MAIN_MENU_BOT * V_BTN_SIZE_MAIN_BOT_WIDTH);

    /* setting up the buttons bottom row */
    for(uint8_t i = 0; i < V_BTN_NUM_MAIN_MENU_BOT; ++i) {
        /* adult create buttons */
        v_btns_main_bottom_[i] = lv_button_create(v_scr_main_);
        v_labs_main_bottom_[i] = lv_label_create(v_btns_main_bottom_[i]);
        lv_obj_remove_style_all(v_btns_main_bottom_[i]);

        /* position, style */
        lv_obj_align(v_btns_main_bottom_[i], LV_ALIGN_BOTTOM_LEFT, x_offset, y_offset);
        if(i < static_cast<int>(V_BTN_NUM_MAIN_MENU_BOT) / 2) { /* left half of buttons */
            lv_obj_set_pos(v_btns_main_bottom_[i], (i) * x_offset, y_offset);
        } else { /* right half of buttons */
            lv_obj_set_pos(v_btns_main_bottom_[i], (i) * x_offset + v_bottom_mid_gap, y_offset);
        }
        lv_obj_add_style(v_btns_main_bottom_[i], &v_style_adult_default_, 0);
        lv_obj_add_style(v_btns_main_bottom_[i], &v_style_adult_active_, LV_PART_MAIN | LV_STATE_PRESSED);
        /* label setup for the buttons */
        const char * txt = v_icons_start_[i];
        lv_label_set_text(v_labs_main_bottom_[i], txt);
        lv_obj_center(v_labs_main_bottom_[i]);
        /* initial color settings */
        /* button setups in functions */
        switch(i) {
            case 0: /* Adult / Fetal selector */
                break; // default color
            case 1: /* trigger selector */
                lv_obj_set_style_text_color(v_labs_main_bottom_[i], v_button_color_main_bot_.v_btn_trig_off, LV_PART_MAIN);
                break;
            case 2: /* depth selector */
                lv_obj_set_style_text_color(v_labs_main_bottom_[i], v_button_color_main_bot_.v_btn_depth_off, LV_PART_MAIN);
                break;
            case 3: /* WLAN status */
                lv_obj_set_style_text_color(v_labs_main_bottom_[i], v_button_color_main_bot_.v_btn_wlan_off, LV_PART_MAIN);
                break;
            case 4: /* sound selector */
                lv_label_set_text(v_labs_main_bottom_[i], LV_SYMBOL_MUTE);
                lv_obj_center(v_labs_main_bottom_[i]);
                lv_obj_set_style_text_color(v_labs_main_bottom_[i], v_button_color_main_bot_.v_btn_sound_off, LV_PART_MAIN);
                break;
            case 5: /* settings menu */
                break; // default color
        }
        /* register event handler to buttons */
        lv_obj_add_event_cb(v_btns_main_bottom_[i], v_event_btn_main_bottom, LV_EVENT_ALL, reinterpret_cast<void*>(static_cast<intptr_t>(i)));

        /* naming buttons if testing active */
        // #ifdef LV_USE_TEST
        //     char btnname[6] = "\0";
        //     lv_snprintf(btnname, sizeof(btnname), "btn_%d", i+1);
        //     lv_obj_set_name(v_btns_main_bottom_[i], btnname);
        // #endif
    }
}

/**
 * setting up background clickable object to handle clicks that are not on widgets
 * @param width screenwidth
 * @param height screenheight
 */
void v_smart_sync_gui::v_background_setup_main(uint32_t width, uint32_t height)
{
    v_scr_main_background_ = lv_obj_create(v_scr_main_);
    lv_obj_remove_style_all(v_scr_main_background_);
    lv_obj_set_size(v_scr_main_background_, width, height);
    lv_obj_clear_flag(v_scr_main_background_, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(v_scr_main_background_, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_move_background(v_scr_main_background_);

    // user_data uses enum value background -> cast to integer
    // static_cast<intptr_t> converts the enum value to an integer type guaranteed to hold a pointer (intptr_t).
    lv_obj_add_event_cb(v_scr_main_background_, v_event_btn_main_bg, LV_EVENT_CLICKED,
                        reinterpret_cast<void*>(static_cast<intptr_t>(v_btn_main_id::background)));
}

/**
 * updating the button styles and texts depending on their state flags
 * @param buttonStates the array of flags for the current button states
 */
void v_smart_sync_gui::v_button_update_main_bottom(v_btn_state_t* buttonStates)
{
    lv_color_t currentColorState;

    for(uint8_t i = 0; i < V_BTN_NUM_MAIN_MENU_BOT; ++i) {
        /* switching to adult mode */
        if(buttonStates->v_btn_adult_active) {
            lv_obj_remove_style(v_btns_main_bottom_[i], &v_style_fetal_default_, 0);
            lv_obj_remove_style(v_btns_main_bottom_[i], &v_style_fetal_active_, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_add_style(v_btns_main_bottom_[i], &v_style_adult_default_, 0);
            lv_obj_add_style(v_btns_main_bottom_[i], &v_style_adult_active_, LV_PART_MAIN | LV_STATE_PRESSED);
        /* switching to fetal mode */
        } else {
            lv_obj_remove_style(v_btns_main_bottom_[i], &v_style_adult_default_, 0);
            lv_obj_remove_style(v_btns_main_bottom_[i], &v_style_adult_active_, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_add_style(v_btns_main_bottom_[i], &v_style_fetal_default_, 0);
            lv_obj_add_style(v_btns_main_bottom_[i], &v_style_fetal_active_, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        /* color settings reload after changes */
        switch(i) {
            case 0: /* button switch between fetal / adult mode */
                if(buttonStates->v_btn_adult_active) {
                    lv_label_set_text(v_labs_main_bottom_[i], "AD");
                    currentColorState = v_button_color_main_bot_.v_btn_adfet;
                } else {
                    lv_label_set_text(v_labs_main_bottom_[i], "FET");
                    currentColorState = v_button_color_main_bot_.v_btn_adfet;
                }
                break;

            case 1: /* button trigger selector */
                if(buttonStates->v_btn_adult_active) {
                    if(buttonStates->v_btn_trig_adult_active) {
                        lv_label_set_text(v_labs_main_bottom_[i], v_icons_on_[i]);
                        currentColorState = v_button_color_main_bot_.v_btn_trig_on;
                    } else {
                        lv_label_set_text(v_labs_main_bottom_[i], v_icons_off_[i]);
                        currentColorState = v_button_color_main_bot_.v_btn_trig_off;
                    }
                } else {
                    if(buttonStates->v_btn_trig_fetal_active) {
                        lv_label_set_text(v_labs_main_bottom_[i], v_icons_on_[i]);
                        currentColorState = v_button_color_main_bot_.v_btn_trig_on;
                    } else {
                        lv_label_set_text(v_labs_main_bottom_[i], v_icons_off_[i]);
                        currentColorState = v_button_color_main_bot_.v_btn_trig_off;
                    }
                }
                break;

            case 2: /* button depth selector */
                if(buttonStates->v_btn_adult_active) {
                    if(buttonStates->v_btn_depth_adult_active) {
                        lv_label_set_text(v_labs_main_bottom_[i], v_icons_on_[i]);
                        currentColorState = v_button_color_main_bot_.v_btn_depth_on;
                    } else {
                        lv_label_set_text(v_labs_main_bottom_[i], v_icons_off_[i]);
                        currentColorState = v_button_color_main_bot_.v_btn_depth_off;
                    }
                } else {
                    if(buttonStates->v_btn_depth_fetal_active) {
                        lv_label_set_text(v_labs_main_bottom_[i], v_icons_on_[i]);
                        currentColorState = v_button_color_main_bot_.v_btn_depth_on;
                    } else {
                        lv_label_set_text(v_labs_main_bottom_[i], v_icons_off_[i]);
                        currentColorState = v_button_color_main_bot_.v_btn_depth_off;
                    }
                }
                break;

            case 3: /* button WLAN status */
                if(buttonStates->v_btn_wlan_active) {
                    lv_label_set_text(v_labs_main_bottom_[i], v_icons_on_[i]);
                    currentColorState = v_button_color_main_bot_.v_btn_wlan_on;
                } else {
                    lv_label_set_text(v_labs_main_bottom_[i], v_icons_off_[i]);
                    currentColorState = v_button_color_main_bot_.v_btn_wlan_off;
                }
                break;

            case 4: /* button sound status */
                if(buttonStates->v_btn_sound_active) {
                    lv_label_set_text(v_labs_main_bottom_[i], v_icons_on_[i]);
                    currentColorState = v_button_color_main_bot_.v_btn_sound_on;
                } else {
                    lv_label_set_text(v_labs_main_bottom_[i], v_icons_off_[i]);
                    currentColorState = v_button_color_main_bot_.v_btn_sound_off;
                }
                break;

            case 5: /* button settings */
                if(buttonStates->v_btn_settings_active) {
                    lv_label_set_text(v_labs_main_bottom_[i], v_icons_on_[i]);
                    currentColorState = v_button_color_main_bot_.v_btn_settings;
                } else {
                    lv_label_set_text(v_labs_main_bottom_[i], v_icons_off_[i]);
                    currentColorState = v_button_color_main_bot_.v_btn_settings;
                }
                break;
        }
        /* update text color for current button */
        lv_obj_set_style_text_color(v_labs_main_bottom_[i], currentColorState, LV_PART_MAIN);
    }
}

/**
 * creating/removing/handling the switch button and switching between modes
 * @param buttonStates the array of flags for the current button states
 * @param btn_id the current button, which fired the event
 */
void v_smart_sync_gui::v_button_update_main_switch(v_btn_state_t* buttonStates, v_btn_main_id btn_id)
{
    // If the switch button currently exists -> remove it and toggle mode if requested
    if(buttonStates->v_btn_switch_active) {
        // if user clicked the switch entry, toggle adult/fetal
        if(btn_id == v_btn_main_id::adfet_switch) {
            buttonStates->v_btn_adult_active = !buttonStates->v_btn_adult_active;
        }
        if(v_btn_main_switch_) {
            lv_obj_del(v_btn_main_switch_);
            v_btn_main_switch_ = nullptr;
            v_lab_main_switch_ = nullptr;
        }
        buttonStates->v_btn_switch_active = false;
        return;
    }

    // No switch active -> create one if the adult/fetal button was pressed
    if(btn_id == v_btn_main_id::adult_fetal) {
        v_btn_main_switch_ = lv_button_create(v_scr_main_);
        v_lab_main_switch_ = lv_label_create(v_btn_main_switch_);
        lv_obj_remove_style_all(v_btn_main_switch_);

        // position: above the main bottom area (use negative height offset)
        lv_obj_align(v_btn_main_switch_, LV_ALIGN_BOTTOM_LEFT, 0, -static_cast<int>(V_BTN_SIZE_MAIN_BOT_HEIGHT));

        // apply style relative to current mode
        if(buttonStates->v_btn_adult_active) {
            lv_obj_add_style(v_btn_main_switch_, &v_style_adult_default_, 0);
            lv_obj_add_style(v_btn_main_switch_, &v_style_adult_active_, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_label_set_text(v_lab_main_switch_, "FET");
        } else {
            lv_obj_add_style(v_btn_main_switch_, &v_style_fetal_default_, 0);
            lv_obj_add_style(v_btn_main_switch_, &v_style_fetal_active_, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_label_set_text(v_lab_main_switch_, "AD");
        }

        lv_obj_center(v_lab_main_switch_);

        // hook event callback; user_data identifies switch enum value
        // static_cast<intptr_t> converts the enum value to an integer type guaranteed to hold a pointer (intptr_t).
        lv_obj_add_event_cb(v_btn_main_switch_, v_event_btn_main_bottom, LV_EVENT_ALL,
                            reinterpret_cast<void*>(static_cast<intptr_t>(v_btn_main_id::adfet_switch)));

        buttonStates->v_btn_switch_active = true;
    } else {
        // clicked something else
        buttonStates->v_btn_switch_active = false;
    }
}

/**
 * return the current state flags of the button array
 */
v_btn_state_t* v_smart_sync_gui::v_get_button_state_main_bottom(void) 
{ 
    return &v_button_state_main_bot_;
}

} // namespace v_main_screen
