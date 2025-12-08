/**
 * @file gtest_main_menu.cpp
 * 
 */
/* gtest */
#include <gtest/gtest.h>
/* lvgl */
#include "lvgl.h"
#include "lvgl/src/others/test/lv_test_indev.h"
#include "lvgl/src/others/test/lv_test_screenshot_compare.h"
#include "lvgl/src/others/test/lv_test_helpers.h"
#include "lvgl/src/others/test/lv_test_display.h"
#include "lvgl/src/misc/lv_timer.h"
/* gui */
#include "src/gui_main_screen/inc/main_screen.hpp"
/* custom */
/* tbd */

/* constexpr */

/* variables */

extern "C" int SDL_main(int argc, char** argv) {
    return 0;
}


using namespace v_main_screen;

namespace gtest_main_menu {

class LVGLMainMenuTest : public ::testing::Test {
protected:
    lv_display_t* disp;
    lv_obj_t* scr;

    void setUp()
    {
        // timer_start();
        lv_init();

        /* Create an in-memory display for testing */
        disp = lv_test_display_create(480, 320);
        lv_display_set_default(disp);
        lv_display_set_color_format(disp, LV_COLOR_FORMAT_XRGB8888);
        lv_display_set_render_mode(disp, LV_DISPLAY_RENDER_MODE_PARTIAL);
        lv_display_set_antialiasing(disp, false);
        lv_display_flush_ready(disp);
        
        /* Create test input devices: pointer, keypad, encoder */
        lv_test_indev_create_all();
        scr = lv_screen_active();
        lv_obj_invalidate(scr);
    }

    void TearDown() {
        lv_disp_remove(disp);
        lv_deinit();
    }
    }; /* class end */

    /* very small test if it works */
    TEST_F(LVGLMainMenuTest, CreatesButtonsOnConstruction) {
        setUp();
        v_smart_sync_gui gui;
        std::vector<lv_obj_t*> buttonsToTest(V_BTN_NUM_MAIN_MENU_BOT);
        /* buttons created? */
        for(int i = 0; i < V_BTN_NUM_MAIN_MENU_BOT; i++){
            buttonsToTest[i] = lv_obj_get_child(scr, i);
            EXPECT_NE(buttonsToTest[i], nullptr) << "Button " << i << " was not created.";
        }
    }

} /* gtest_main_menu end */
