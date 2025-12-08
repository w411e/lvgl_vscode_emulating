/**
 * @file main_screen.hpp
 *
 */

#pragma once

#include "lvgl.h"
#include <cstdint>
#include <array>

namespace v_main_screen {

// -----------------------------------------------------------------------------
// Screen configuration
// -----------------------------------------------------------------------------
constexpr uint32_t V_SCR_WIDTH  = 800;
constexpr uint32_t V_SCR_HEIGHT = 480;

// -----------------------------------------------------------------------------
// Button count and statevar
// -----------------------------------------------------------------------------
constexpr uint8_t V_BTN_NUM_MAIN_MENU_BOT = 6;
constexpr uint8_t V_TEST_MONKEYSETUP = 0; // 0 = no monkey - 1 = touch screen anywhere - 2 = only touch buttons

// -----------------------------------------------------------------------------
// Colors
// -----------------------------------------------------------------------------
constexpr uint32_t NACHTBLAU_100  = 0x002841; /* 100 = full color / 100% */
constexpr uint32_t NACHTBLAU_80   = 0x2F475E; /* 80 */
constexpr uint32_t NACHTBLAU_60   = 0x57687C; /* 60 */
constexpr uint32_t NACHTBLAU_40   = 0x7F8B9B; /* 40 */
constexpr uint32_t NACHTBLAU_20   = 0xA8B0BB; /* 20 */
constexpr uint32_t NACHTBLAU_10   = 0xD3D7DD; /* 10 = close to white / 10% */
constexpr uint32_t CYAN_100       = 0x00A0E1;
constexpr uint32_t CYAN_80        = 0x59AFE6;
constexpr uint32_t CYAN_60        = 0x82BFEB;
constexpr uint32_t CYAN_40        = 0xA5CEF0;
constexpr uint32_t CYAN_20        = 0xC4DEF5;
constexpr uint32_t CYAN_10        = 0xE2EFFA;
constexpr uint32_t CYAN_LIGHT_100 = 0x82D2F5;
constexpr uint32_t CYAN_LIGHT_80  = 0x9AD9F7;
constexpr uint32_t CYAN_LIGHT_60  = 0xB0E1F8;
constexpr uint32_t CYAN_LIGHT_40  = 0xC5E8FA;
constexpr uint32_t CYAN_LIGHT_20  = 0xD9F0FC;
constexpr uint32_t CYAN_LIGHT_10  = 0xECF7FD;
constexpr uint32_t ULTRAVIOLET_100= 0xC80078;
constexpr uint32_t ULTRAVIOLET_80 = 0xD54B8D;
constexpr uint32_t ULTRAVIOLET_60 = 0xE173A3;
constexpr uint32_t ULTRAVIOLET_40 = 0xeB97B9;
constexpr uint32_t ULTRAVIOLET_20 = 0xF4BAD0;
constexpr uint32_t ULTRAVIOLET_10 = 0xFADDE7;


// -----------------------------------------------------------------------------
// Menu button background colors
// -----------------------------------------------------------------------------
const lv_color_t V_BTN_BG_CLR_ADULT_DEFAULT = lv_color_hex(CYAN_60);
const lv_color_t V_BTN_BG_CLR_ADULT_ACTIVE  = lv_color_hex(NACHTBLAU_80);
const lv_color_t V_BTN_BG_CLR_FETAL_DEFAULT = lv_color_hex(CYAN_100);
const lv_color_t V_BTN_BG_CLR_FETAL_ACTIVE  = lv_color_hex(NACHTBLAU_80);

// -----------------------------------------------------------------------------
// Menu icon colors
// -----------------------------------------------------------------------------
const lv_color_t V_BTN_ICON_CLR_MAIN_BOT_DEFAULT  = lv_color_hex(0xFFFFFF); /* white */
const lv_color_t V_BTN_ICON_CLR_MAIN_BOT_DISABLED = lv_color_hex(0xADADAD); /* light gray */
const lv_color_t V_BTN_ICON_CLR_MAIN_BOT_WLAN     = lv_color_hex(0xFFB22E); /* yellow/orange */

// -----------------------------------------------------------------------------
// Button default size
// -----------------------------------------------------------------------------
constexpr uint32_t V_BTN_SIZE_MAIN_BOT_RADIUS       = 0;   /* corner size */
constexpr uint32_t V_BTN_SIZE_MAIN_BOT_WIDTH        = 132; /* button width */
constexpr uint32_t V_BTN_SIZE_MAIN_BOT_HEIGHT       = 80;  /* button height */
constexpr uint32_t V_BTN_SIZE_MAIN_BOT_PAD_ALL      = 0;   /* pad on all sides */
constexpr uint32_t V_BTN_SIZE_MAIN_BOT_BORDER_WIDTH = 0;   /* button border width */

// -----------------------------------------------------------------------------
// Enums
// -----------------------------------------------------------------------------
// button id/iteration
enum class v_btn_main_id : uint8_t {
    adult_fetal = 0,
    trigger,
    depth,
    wlan,
    sound,
    settings,
    adfet_switch,
    background
};

// -----------------------------------------------------------------------------
// State Structures
// -----------------------------------------------------------------------------
/* main menu button/icon colors */
struct v_clr_main_bot_menu_t {
    /* button icon colors */
    /* adult fetal button */
    lv_color_t v_btn_adfet{};
    lv_color_t v_btn_adfet_switch{};
    /* trigger button */
    lv_color_t v_btn_trig_on{};
    lv_color_t v_btn_trig_off{};
    /* depth button */
    lv_color_t v_btn_depth_on{};
    lv_color_t v_btn_depth_off{};
    /* wlan button */
    lv_color_t v_btn_wlan_on{};
    lv_color_t v_btn_wlan_off{};
    /* sound button */
    lv_color_t v_btn_sound_on{};
    lv_color_t v_btn_sound_off{};
    /* settings button */
    lv_color_t v_btn_settings{};

    /* button background colors */
    lv_color_t v_btn_bg_adult_default{};
    lv_color_t v_btn_bg_adult_active{};
    lv_color_t v_btn_bg_fetal_default{};
    lv_color_t v_btn_bg_fetal_active{};
};

/* main menu button states active/non active */
struct v_btn_state_t {
    bool v_btn_adult_active{};      /* switching between adult/fetal menu */
    bool v_btn_switch_active{};     /* extra button to switch between ad and fet */
    bool v_btn_trig_adult_active{}; /* trigger options adult */
    bool v_btn_trig_fetal_active{}; /* trigger options fetal */
    bool v_btn_depth_adult_active{};/* depth option */
    bool v_btn_depth_fetal_active{};/* depth option */
    bool v_btn_wlan_active{};       /* WLAN/connection option */
    bool v_btn_sound_active{};      /* sound options */
    bool v_btn_settings_active{};   /* general settings menu */
};

// -----------------------------------------------------------------------------
// Main class
// -----------------------------------------------------------------------------
class v_smart_sync_gui {
public:
    /* constructor */
    v_smart_sync_gui();

    /* functions */
    // void v_test_setup_emulation();
    void v_state_setup_main_menu();
    void v_style_setup_main_bottom_buttons();
    void v_button_setup_main_bottom(uint32_t x_offset, uint32_t y_offset);
    void v_background_setup_main(uint32_t width, uint32_t height);
    void v_button_update_main_bottom(v_btn_state_t* state);
    void v_button_update_main_switch(v_btn_state_t* state, v_btn_main_id btn);
    v_btn_state_t* v_get_button_state_main_bottom(void);

    /* deconstructor */
    ~v_smart_sync_gui();

private:
    lv_obj_t* v_scr_main_ = nullptr;
    lv_obj_t* v_scr_main_background_ = nullptr;

    std::array<lv_obj_t*, V_BTN_NUM_MAIN_MENU_BOT> v_btns_main_bottom_{};
    std::array<lv_obj_t*, V_BTN_NUM_MAIN_MENU_BOT> v_labs_main_bottom_{};

    lv_obj_t* v_btn_main_switch_ = nullptr;
    lv_obj_t* v_lab_main_switch_ = nullptr;

    lv_style_t v_style_adult_default_{};
    lv_style_t v_style_adult_active_{};
    lv_style_t v_style_fetal_default_{};
    lv_style_t v_style_fetal_active_{};

    v_clr_main_bot_menu_t v_button_color_main_bot_{};
    v_btn_state_t v_button_state_main_bot_{};

    /* btn var for monky-test */
    
    #ifdef LV_USE_TEST
    #if V_TEST_MONKEYSETUP
        lv_obj_t *btn_monkey[V_BTN_NUM_MAIN_MENU_BOT];
    #endif
    #endif

    /* active icons */
    inline static const std::array<const char*, V_BTN_NUM_MAIN_MENU_BOT> v_icons_on_ {
        "placeholder",
        LV_SYMBOL_OK,
        LV_SYMBOL_EYE_OPEN,
        LV_SYMBOL_WIFI,
        LV_SYMBOL_VOLUME_MAX,
        LV_SYMBOL_SETTINGS
    };
    /* non-active icons */
    inline static const std::array<const char*, V_BTN_NUM_MAIN_MENU_BOT> v_icons_off_{
        "placeholder",
        LV_SYMBOL_WARNING,
        LV_SYMBOL_EYE_CLOSE,
        LV_SYMBOL_WIFI,
        LV_SYMBOL_MUTE,
        LV_SYMBOL_SETTINGS
    };
    /* default startup icons */
    inline static const std::array<const char*, V_BTN_NUM_MAIN_MENU_BOT> v_icons_start_{ 
        "AD",
        LV_SYMBOL_WARNING,
        LV_SYMBOL_EYE_CLOSE,
        LV_SYMBOL_WIFI,
        LV_SYMBOL_MUTE,
        LV_SYMBOL_SETTINGS 
    };
};
} // namespace v_main_screen