/**
 * @file test_emu.c
 *
 */
#include "src/emulation/test_emu.h"
#include "src/emulation/monkey_setup.h"
#include "src/emulation/test_emu_handlers.h"

/**
 * Globals
 */
/* screen */
lv_obj_t * scr_def;
/* background */
lv_obj_t * background;
/* buttons */
lv_obj_t * btns_main_bottom[V_BTN_NUM_MAIN_MENU_BOT];
lv_obj_t * labs_main_bottom[V_BTN_NUM_MAIN_MENU_BOT];
lv_obj_t * btn_main_switch;
lv_obj_t * lab_main_switch;
// LV_SYMBOL_MUTE LV_SYMBOL_EYE_CLOSE
static const char * label_symbols_on[] = { "placeholder", LV_SYMBOL_OK,      LV_SYMBOL_EYE_OPEN,  LV_SYMBOL_WIFI, LV_SYMBOL_VOLUME_MAX, LV_SYMBOL_SETTINGS };
static const char * label_symbols_off[]= { "placeholder", LV_SYMBOL_WARNING, LV_SYMBOL_EYE_CLOSE, LV_SYMBOL_WIFI, LV_SYMBOL_MUTE,       LV_SYMBOL_SETTINGS };
static const char * label_symbols_def[]= { "AD",          LV_SYMBOL_WARNING, LV_SYMBOL_EYE_CLOSE, LV_SYMBOL_WIFI, LV_SYMBOL_MUTE,       LV_SYMBOL_SETTINGS };
// static const char *adult_labels[] = { "AD", LV_SYMBOL_WARNING, LV_SYMBOL_EYE_OPEN, LV_SYMBOL_WIFI, LV_SYMBOL_MUTE, LV_SYMBOL_SETTINGS };
// static const char *fetal_labels[] = { "FET", LV_SYMBOL_CUT, LV_SYMBOL_EYE_CLOSE, LV_SYMBOL_WIFI, LV_SYMBOL_MUTE, LV_SYMBOL_SETTINGS };
// static const char *adult_labels[] = {"Adult", "Trig", "Depth", "WLAN", "Sound", "Settings" };
// static const char *fetal_labels[] = {"Fetal", "Ring", "nDepth", "WLAN", "Sound", "Settings"};
char ** labs_text_main_bottom;


/* btn var for monky-test */
lv_obj_t *btn_monkey[V_BTN_NUM_MAIN_MENU_BOT];

/* styles */
static lv_style_t buttonStyleAdultBotDefault;
static lv_style_t buttonStyleAdultBotActive;
static lv_style_t buttonStyleFetalBotDefault;
static lv_style_t buttonStyleFetalBotActive;
static v_clr_btn_main_bot_menu_t buttonColorMainBot;
static v_btn_set_main_bot_menu_t buttonStateMainBot;

/**
 * code for testsetup, called in main()
 */
void v_test_setup_emulation(void)
{
    scr_def = lv_screen_active();
    v_state_setup_main_menu();
    v_style_setup_main_bottom_buttons();
    v_button_setup_main_bottom(V_BTN_SIZE_MAIN_BOT_WIDTH, 0);
    v_background_setup_main(V_SCR_WIDTH, V_SCR_HEIGHT);
    
    /* monkeytest */
    #ifdef LV_USE_TEST
        #if V_TEST_MONKEYSETUP
            v_test_setup_monkey();
        #endif
    #endif
}

/**
 * state and color setup main menu, start in adult
 */
void v_state_setup_main_menu(void)
{
    /* startup states of buttons */
    buttonStateMainBot.btn_adult_active       = true;  /* default start in adult */
    buttonStateMainBot.btn_switch_active      = false; /* default start no switch btn */
    buttonStateMainBot.btn_trig_adult_active  = false; /* default start trigger off */
    buttonStateMainBot.btn_trig_fetal_active  = false; /* default start trigger off */
    buttonStateMainBot.btn_depth_adult_active = false; /* default start depth off */
    buttonStateMainBot.btn_depth_fetal_active = false; /* default start depth off */
    buttonStateMainBot.btn_WLAN_active        = false; /* default start WLAN not connected */
    buttonStateMainBot.btn_sound_active       = false; /* default start sound off */
    buttonStateMainBot.btn_settings_active    = false; /* default not in settings menu */
    
    /* button color settings */
    buttonColorMainBot.btn_ADFET        = lv_color_hex(V_CLR_MAIN_BOT_DEFAULT_ICON);
    buttonColorMainBot.btn_AFSwitch     = lv_color_hex(V_CLR_MAIN_BOT_DEFAULT_ICON);
    buttonColorMainBot.btn_trig_on      = lv_color_hex(V_CLR_MAIN_BOT_DEFAULT_ICON);
    buttonColorMainBot.btn_trig_off     = lv_color_hex(V_CLR_MAIN_BOT_DISABLED_ICON);
    buttonColorMainBot.btn_depth_on     = lv_color_hex(V_CLR_MAIN_BOT_DEFAULT_ICON);
    buttonColorMainBot.btn_depth_off    = lv_color_hex(V_CLR_MAIN_BOT_DISABLED_ICON);
    buttonColorMainBot.btn_WLAN_on      = lv_color_hex(V_CLR_MAIN_BOT_WLAN_ICON);
    buttonColorMainBot.btn_WLAN_off     = lv_color_hex(V_CLR_MAIN_BOT_WLAN_ICON);
    buttonColorMainBot.btn_sound_on     = lv_color_hex(V_CLR_MAIN_BOT_DEFAULT_ICON);
    buttonColorMainBot.btn_sound_off    = lv_color_hex(V_CLR_MAIN_BOT_DISABLED_ICON);
    buttonColorMainBot.btn_settings     = lv_color_hex(V_CLR_MAIN_BOT_DEFAULT_ICON);
    buttonColorMainBot.btn_bg_adult_def = lv_color_hex(V_BTN_ADULT_MAIN_BOT_BG);
    buttonColorMainBot.btn_bg_adult_act = lv_color_hex(V_BTN_ACTIVE_MAIN_BOT_BG);
    buttonColorMainBot.btn_bg_fetal_def = lv_color_hex(V_BTN_FETAL_MAIN_BOT_BG);
    buttonColorMainBot.btn_bg_fetal_act = lv_color_hex(V_BTN_ACTIVE_MAIN_BOT_BG);
}

/**
 * style setup main menu bottom buttons
 */
void v_style_setup_main_bottom_buttons(void)
{
    /* buttons bottom line adult style */        
    lv_style_init(&buttonStyleAdultBotDefault);
    lv_style_set_radius(&buttonStyleAdultBotDefault, V_BTN_SIZE_MAIN_BOT_RADIUS);
    lv_style_set_width(&buttonStyleAdultBotDefault, V_BTN_SIZE_MAIN_BOT_WIDTH);
    lv_style_set_height(&buttonStyleAdultBotDefault, V_BTN_SIZE_MAIN_BOT_HEIGHT);
    lv_style_set_pad_all(&buttonStyleAdultBotDefault, V_BTN_SIZE_MAIN_BOT_PAD_ALL);
    lv_style_set_border_width(&buttonStyleAdultBotDefault, V_BTN_SIZE_MAIN_BOT_BORDER_WIDTH);
    lv_style_set_bg_color(&buttonStyleAdultBotDefault, buttonColorMainBot.btn_bg_adult_def);
    lv_style_set_border_color(&buttonStyleAdultBotDefault, buttonColorMainBot.btn_bg_adult_def);
    lv_style_set_text_color(&buttonStyleAdultBotDefault, buttonColorMainBot.btn_settings);
    lv_style_set_text_font(&buttonStyleAdultBotDefault, &lv_font_montserrat_32);
    lv_style_set_bg_opa(&buttonStyleAdultBotDefault, LV_OPA_COVER);

    /* active main menu button styles */
    lv_style_init(&buttonStyleAdultBotActive);
    lv_style_set_bg_color(&buttonStyleAdultBotActive, buttonColorMainBot.btn_bg_adult_act);
    lv_style_set_border_color(&buttonStyleAdultBotActive, buttonColorMainBot.btn_bg_adult_act);
    lv_style_set_text_font(&buttonStyleAdultBotActive, &lv_font_montserrat_32);

    /* buttons bottom line fetal style */
    lv_style_init(&buttonStyleFetalBotDefault);
    lv_style_set_radius(&buttonStyleFetalBotDefault, V_BTN_SIZE_MAIN_BOT_RADIUS);
    lv_style_set_width(&buttonStyleFetalBotDefault, V_BTN_SIZE_MAIN_BOT_WIDTH);
    lv_style_set_height(&buttonStyleFetalBotDefault, V_BTN_SIZE_MAIN_BOT_HEIGHT);
    lv_style_set_pad_all(&buttonStyleFetalBotDefault, V_BTN_SIZE_MAIN_BOT_PAD_ALL);
    lv_style_set_border_width(&buttonStyleFetalBotDefault, V_BTN_SIZE_MAIN_BOT_BORDER_WIDTH);
    lv_style_set_bg_color(&buttonStyleFetalBotDefault, buttonColorMainBot.btn_bg_fetal_def);
    lv_style_set_border_color(&buttonStyleFetalBotDefault, buttonColorMainBot.btn_bg_fetal_def);
    lv_style_set_text_color(&buttonStyleFetalBotDefault, buttonColorMainBot.btn_settings);
    lv_style_set_text_font(&buttonStyleFetalBotDefault, &lv_font_montserrat_32);
    lv_style_set_bg_opa(&buttonStyleFetalBotDefault, LV_OPA_COVER);

    /* active main menu button styles */
    lv_style_init(&buttonStyleFetalBotActive);
    lv_style_set_bg_color(&buttonStyleFetalBotActive, buttonColorMainBot.btn_bg_fetal_act);
    lv_style_set_border_color(&buttonStyleFetalBotActive, buttonColorMainBot.btn_bg_fetal_act);
    lv_style_set_text_font(&buttonStyleFetalBotActive, &lv_font_montserrat_32);
}


/**
 * button setup main menu bottom row adult and fetal for startup
 * @param x_offset offset for the buttons on x-axis (alignment bottom left)
 * @param y_offset offset for the buttons on y-axis (alignment bottom left (+down/-up))
 */
void v_button_setup_main_bottom(uint32_t x_offset, uint32_t y_offset)
{
    /* middle gap bottom main menu bottons is rest of width */
    static uint32_t v_bottom_mid_gap = V_SCR_WIDTH - (V_BTN_NUM_MAIN_MENU_BOT) * V_BTN_SIZE_MAIN_BOT_WIDTH;
    labs_text_main_bottom = (char **) label_symbols_def;
    
    /* setting up the buttons bottom row */
    for(int i = 0; i < V_BTN_NUM_MAIN_MENU_BOT; i++)
    {
        /* adult create buttons */
        btns_main_bottom[i] = lv_button_create(scr_def);
        labs_main_bottom[i] = lv_label_create(btns_main_bottom[i]);
        lv_obj_remove_style_all(btns_main_bottom[i]);
        /* position, style */
        lv_obj_align(btns_main_bottom[i], LV_ALIGN_BOTTOM_LEFT, x_offset, y_offset);
        if(i < (V_BTN_NUM_MAIN_MENU_BOT) / 2) /* left half of buttons */
            lv_obj_set_pos(btns_main_bottom[i], (i) * x_offset, y_offset);
        else /* right half of buttons */
            lv_obj_set_pos(btns_main_bottom[i], (i) * x_offset + v_bottom_mid_gap, y_offset);
        lv_obj_add_style(btns_main_bottom[i], &buttonStyleAdultBotDefault, 0);
        lv_obj_add_style(btns_main_bottom[i], &buttonStyleAdultBotActive, LV_PART_MAIN | LV_STATE_PRESSED);
        /* label setup for the buttons */
        lv_label_set_text(labs_main_bottom[i], labs_text_main_bottom[i]);
        lv_obj_center(labs_main_bottom[i]);
        /* color settings for startup */
        switch(i){
            case 0: /* Adult / Fetal selector */
                break; // default color
            case 1: /* trigger selector */
                lv_obj_set_style_text_color(labs_main_bottom[i], buttonColorMainBot.btn_trig_off, LV_PART_MAIN);
                break;
            case 2: /* depth selector */
                lv_obj_set_style_text_color(labs_main_bottom[i], buttonColorMainBot.btn_depth_off, LV_PART_MAIN);
                break;
            case 3: /* WLAN status */
                lv_obj_set_style_text_color(labs_main_bottom[i], buttonColorMainBot.btn_WLAN_off, LV_PART_MAIN);
                break;
            case 4: /* sound selector */
                lv_label_set_text(labs_main_bottom[i], LV_SYMBOL_MUTE);
                lv_obj_center(labs_main_bottom[i]);
                lv_obj_set_style_text_color(labs_main_bottom[i], buttonColorMainBot.btn_sound_off, LV_PART_MAIN);
                break;
            case 5: /* settings menu */
                break; // default color
        }
        /* register event handler to buttons */
        lv_obj_add_event_cb(btns_main_bottom[i], v_event_btn_main_bottom, LV_EVENT_ALL, (void*)(intptr_t)i);

        #ifdef LV_USE_TEST
            char btnname[6] = "\0";
            lv_snprintf(btnname, sizeof(btnname), "btn_%d", i+1);
            lv_obj_set_name(btns_main_bottom[i], btnname);
            btn_monkey[i] = btns_main_bottom[i];
        #endif
    }
}

/**
 * setting up background clickable object to handle clicks that are not on widgets
 * @param width screenwidth
 * @param height screenheight
 */
void v_background_setup_main(uint32_t width, uint32_t height)
{
    /* setting up clickable background object */
    background = lv_obj_create(scr_def);
    lv_obj_remove_style_all(background);
    lv_obj_set_size(background, width, height);
    lv_obj_clear_flag(background, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(background, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_move_background(background);
    /* register event handler to background */
    lv_obj_add_event_cb(background, v_event_btn_main_bg, LV_EVENT_CLICKED, (void*)(intptr_t)BTN_BG);
}

/**
 * updating the button styles and texts depending on their state flags
 * @param buttonStates the array of flags for the current button states
 */
void v_button_update_main_bottom(v_btn_set_main_bot_menu_t *buttonStates)
{
    /* assign label text adult or fetal */
    // if (buttonStates->btn_adult_active)
    //     labs_text_main_bottom = (char **) adult_labels;
    // else
    //     labs_text_main_bottom = (char **) fetal_labels;
    lv_color_t currentColorState;

    for(int i = 0; i < V_BTN_NUM_MAIN_MENU_BOT; i++)
    {
        /* switching to adult mode */
        if(buttonStates->btn_adult_active){
            lv_obj_remove_style(btns_main_bottom[i], &buttonStyleFetalBotDefault, 0);
            lv_obj_remove_style(btns_main_bottom[i], &buttonStyleFetalBotActive, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_add_style(btns_main_bottom[i], &buttonStyleAdultBotDefault, 0);
            lv_obj_add_style(btns_main_bottom[i], &buttonStyleAdultBotActive, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        /* switching to fetal mode */
        else{
            lv_obj_remove_style(btns_main_bottom[i], &buttonStyleAdultBotDefault, 0);
            lv_obj_remove_style(btns_main_bottom[i], &buttonStyleAdultBotActive, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_add_style(btns_main_bottom[i], &buttonStyleFetalBotDefault, 0);
            lv_obj_add_style(btns_main_bottom[i], &buttonStyleFetalBotActive, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        /* color settings reload after changes */
        switch(i){
            /* button switch between fetal / adult mode */
            case 0: /* nothing to do always white */
                if(buttonStates->btn_adult_active){
                    lv_label_set_text(labs_main_bottom[i], "AD");
                    currentColorState = buttonColorMainBot.btn_ADFET;
                }
                else{
                    lv_label_set_text(labs_main_bottom[i], "FET");
                    currentColorState = buttonColorMainBot.btn_ADFET;
                }
                break;
            /* button trigger selector */
            case 1:
                if(buttonStates->btn_adult_active){
                    if(buttonStates->btn_trig_adult_active){ /* adult - trigger on */
                        lv_label_set_text(labs_main_bottom[i], label_symbols_on[i]);
                        currentColorState = buttonColorMainBot.btn_trig_on;
                    }
                    else{ /* adult - trigger off */
                        lv_label_set_text(labs_main_bottom[i], label_symbols_off[i]);
                        currentColorState = buttonColorMainBot.btn_trig_off;
                    }
                }
                else{
                    if(buttonStates->btn_trig_fetal_active){ /* fetal - trigger on */
                        lv_label_set_text(labs_main_bottom[i], label_symbols_on[i]);
                        currentColorState = buttonColorMainBot.btn_trig_on;
                    }
                    else{ /* fetal - trigger off */
                        lv_label_set_text(labs_main_bottom[i], label_symbols_off[i]);
                        currentColorState = buttonColorMainBot.btn_trig_off;
                    }
                }
                break;
            /* button depth selector */
            case 2:
                if(buttonStates->btn_adult_active){
                    if(buttonStates->btn_depth_adult_active){ /* adult - depth on */
                        lv_label_set_text(labs_main_bottom[i], label_symbols_on[i]);
                        currentColorState = buttonColorMainBot.btn_depth_on;
                    }
                    else{ /* adult - depth off */
                        lv_label_set_text(labs_main_bottom[i], label_symbols_off[i]);
                        currentColorState = buttonColorMainBot.btn_depth_off;
                    }
                }
                else{
                    if(buttonStates->btn_depth_fetal_active){ /* fetal - depth on */
                        lv_label_set_text(labs_main_bottom[i], label_symbols_on[i]);
                        currentColorState = buttonColorMainBot.btn_depth_on;
                    }
                    else{ /* fetal - depth off */
                        lv_label_set_text(labs_main_bottom[i], label_symbols_off[i]);
                        currentColorState = buttonColorMainBot.btn_depth_off;
                    }
                }
                break;
            /* button WLAN status */
            case 3: /* stays yellow, might buttonStates->btn_adult_active in the future */
                if(buttonStates->btn_WLAN_active){
                    lv_label_set_text(labs_main_bottom[i], label_symbols_on[i]);
                    currentColorState = buttonColorMainBot.btn_WLAN_on;
                }
                else{
                    lv_label_set_text(labs_main_bottom[i], label_symbols_off[i]);
                    currentColorState = buttonColorMainBot.btn_WLAN_off;
                }
                break;
            /* button sound status */
            case 4:
                if(buttonStates->btn_sound_active){
                    lv_label_set_text(labs_main_bottom[i], label_symbols_on[i]);
                    currentColorState = buttonColorMainBot.btn_sound_on;
                }
                else{
                    lv_label_set_text(labs_main_bottom[i], label_symbols_off[i]);
                    currentColorState = buttonColorMainBot.btn_sound_off;
                }
                break;
            /* button settings */
            case 5: /* stays white with screen buttonStates->btn_adult_active, might buttonStates->btn_adult_active in the future */
                if(buttonStates->btn_settings_active){
                    lv_label_set_text(labs_main_bottom[i], label_symbols_on[i]);
                    currentColorState = buttonColorMainBot.btn_settings;
                }
                else{
                    lv_label_set_text(labs_main_bottom[i], label_symbols_off[i]);
                    currentColorState = buttonColorMainBot.btn_settings;
                }
                break;
        }
        /* update text color for current button */
        lv_obj_set_style_text_color(labs_main_bottom[i], currentColorState, LV_PART_MAIN);

        #ifdef LV_USE_TEST
            char btnname[6] = "\0";
            lv_snprintf(btnname, sizeof(btnname), "btn_%d", i+1);
            lv_obj_set_name(btns_main_bottom[i], btnname);
            btn_monkey[i] = btns_main_bottom[i];
        #endif
    }
}

/**
 * creating/removing/handling the switch button and switching between modes
 * @param buttonStates the array of flags for the current button states
 * @param btn_id the current button, which fired the event
 */
void v_button_update_main_switch(v_btn_set_main_bot_menu_t *buttonStates, v_btn_enum_main_bottom_t btn_id)
{
    /* switch button active */
    if (buttonStates->btn_switch_active)
    {
        /* switch from/to adult/fetal */
        if(btn_id == BTN_ADFET_SWITCH)
            buttonStates->btn_adult_active = !buttonStates->btn_adult_active;
        lv_obj_delete(btn_main_switch);
        buttonStates->btn_switch_active = false;
    }
    /* switch button not active */
    else
    {
        /* creating switch button */
        if(btn_id == BTN_ADULT_FETAL){
            /* button, label and style setup */
            btn_main_switch = lv_button_create(scr_def);
            lab_main_switch = lv_label_create(btn_main_switch);
            lv_obj_remove_style_all(btn_main_switch);
            lv_obj_align(btn_main_switch, LV_ALIGN_BOTTOM_LEFT, 0, - V_BTN_SIZE_MAIN_BOT_HEIGHT);
            /* currently in adult mode */
            if(buttonStates->btn_adult_active)
            {
                lv_obj_add_style(btn_main_switch, &buttonStyleAdultBotDefault, 0);
                lv_obj_add_style(btn_main_switch, &buttonStyleAdultBotActive, LV_PART_MAIN | LV_STATE_PRESSED);
                lv_label_set_text(lab_main_switch, "FET");
            }
            /* currently in fetal mode */
            else
            {
                lv_obj_add_style(btn_main_switch, &buttonStyleFetalBotDefault, 0);
                lv_obj_add_style(btn_main_switch, &buttonStyleFetalBotActive, LV_PART_MAIN | LV_STATE_PRESSED);
                lv_label_set_text(lab_main_switch, "AD");
            }
            lv_obj_center(lab_main_switch);
            /* register event handler to buttons */
            lv_obj_add_event_cb(btn_main_switch, v_event_btn_main_bottom, LV_EVENT_ALL, (void*)(intptr_t) BTN_ADFET_SWITCH);
            buttonStates->btn_switch_active = true;
        }
        else{ /* nothing happens */
            buttonStates->btn_switch_active = false;
        }
    }
}

/**
 * return the current state flags of the button array
 */
v_btn_set_main_bot_menu_t *get_buttonStateMainBot(void) {
    return &buttonStateMainBot;
}