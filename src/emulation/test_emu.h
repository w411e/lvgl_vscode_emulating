/**
 * @file test_emu.h
 *
 */

#ifndef TEST_EMU_H
#define TEST_EMU_H

#ifdef __cplusplus
extern "C" {
#endif

// includes
#include "lvgl.h"

// defines
/* screen size */
#define V_SCR_WIDTH 800
#define V_SCR_HEIGHT 480
// Main Menu Labels
#define V_BTN_NUM_MAIN_MENU_BOT 6 /* buttonnumber bottom row buttons adult/fetal*/
// Main Menu Button BG Colors
#define V_BTN_ADULT_MAIN_BOT_BG          0x8FCDF2 /* soft blue */
#define V_BTN_FETAL_MAIN_BOT_BG          0x1B9AE4 /* strong blue */
#define V_BTN_ACTIVE_MAIN_BOT_BG         0x167FBB /* strong dark blue */
// Icon Colors
#define V_CLR_MAIN_BOT_DEFAULT_ICON      0xFFFFFF /* white */
#define V_CLR_MAIN_BOT_DISABLED_ICON     0xADADAD /* light gray */
#define V_CLR_MAIN_BOT_WLAN_ICON         0xFFB22E /* yellow/orange */
// main menu bottom buttons sizes
#define V_BTN_SIZE_MAIN_BOT_RADIUS       0   /* corner size */
#define V_BTN_SIZE_MAIN_BOT_WIDTH        132 /* button width */
#define V_BTN_SIZE_MAIN_BOT_HEIGHT       80  /* button height */
#define V_BTN_SIZE_MAIN_BOT_PAD_ALL      0   /* pad on all sides */
#define V_BTN_SIZE_MAIN_BOT_BORDER_WIDTH 0   /* button border width */

/* predefined colors */
#define V_CLR_RED     0xFF0000
#define V_CLR_GREEN   0x00FF00
#define V_CLR_BLUE    0x0000FF
#define V_CLR_WHITE   0xFFFFFF
#define V_CLR_BLACK   0x000000
#define V_CLR_YELLOW  0xFFFF00
#define V_CLR_FOREST  0x008000
#define V_CLR_TEAL    0x008080
#define V_CLR_MAGENTA 0xFF00FF
#define V_CLR_DEF     0x27C2F5
#define V_CLR_DEF_2   0x8FDFFA
#define V_CLR_GRAY    0x808080

#define BTNNUM  4 // Buttonnumber for testscreen

#define V_TEST_MONKEYSETUP 0 // 0 = no monkey - 1 = touch screen anywhere - 2 = only touch buttons

// structs
typedef struct
{
    lv_color_t btn_ADFET;        /* color adult/fetal menu */
    lv_color_t btn_AFSwitch;     /* color switch button adult/fetal */
    lv_color_t btn_trig_on;      /* color trigger options */
    lv_color_t btn_trig_off;     /* color trigger options */
    lv_color_t btn_depth_on;     /* color depth option */
    lv_color_t btn_depth_off;    /* color depth option */
    lv_color_t btn_WLAN_on;      /* color WLAN/connection */
    lv_color_t btn_WLAN_off;     /* color WLAN/connection */
    lv_color_t btn_sound_on;     /* color sound options */
    lv_color_t btn_sound_off;    /* color sound options */
    lv_color_t btn_settings;     /* color general settings menu */
    lv_color_t btn_bg_adult_def; /* bottom row default color adult */
    lv_color_t btn_bg_adult_act; /* bottom row "active" color adult */
    lv_color_t btn_bg_fetal_def; /* bottom row default color fetal */
    lv_color_t btn_bg_fetal_act; /* bottom row "active" color fetal */
} v_clr_btn_main_bot_menu_t;

typedef struct
{
    bool btn_adult_active;      /* switching between adult/fetal menu */
    bool btn_switch_active;     /* extra button to switch between ad and fet */
    bool btn_trig_adult_active; /* trigger options adult */
    bool btn_trig_fetal_active; /* trigger options fetal */
    bool btn_depth_adult_active;/* depth option */
    bool btn_depth_fetal_active;/* depth option */
    bool btn_WLAN_active;       /* WLAN/connection option */
    bool btn_sound_active;      /* sound options */
    bool btn_settings_active;   /* general settings menu */
} v_btn_set_main_bot_menu_t;

typedef enum {
    BTN_ADULT_FETAL = 0,
    BTN_TRIGGER,
    BTN_DEPTH,
    BTN_WLAN,
    BTN_SOUND,
    BTN_SETTINGS,
    BTN_ADFET_SWITCH,
    BTN_BG
} v_btn_enum_main_bottom_t;

// functions
void v_test_setup_emulation(void);
void v_state_setup_main_menu(void);
void v_style_setup_main_bottom_buttons(void);
void v_button_setup_main_bottom(uint32_t x_offset, uint32_t y_offset);
void v_background_setup_main(uint32_t width, uint32_t height);
void v_button_update_main_bottom(v_btn_set_main_bot_menu_t *buttonStates);
void v_button_update_main_switch(v_btn_set_main_bot_menu_t *buttonStates, v_btn_enum_main_bottom_t btn_id);
v_btn_set_main_bot_menu_t *get_buttonStateMainBot(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*TEST_EMU_H*/