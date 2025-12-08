/**
 * @file main_screen_handlers.hpp
 *
 */

#pragma once

#include "lvgl.h"
#include "main_screen.hpp"     // for v_btn_enum_main_bottom_t and state struct

namespace v_main_screen {

    /* Event handlers */
    void v_event_btn_main_bottom(lv_event_t* e);
    void v_event_btn_main_bg(lv_event_t* e);
    void v_btn_redraw(v_btn_main_id v_btn_id);

} // namespace v_main_screen
