/**
 * @file test_emu_handlers.h
 *
 */

#ifndef TEST_EMU_HANDLERS_H
#define TEST_EMU_HANDLERS_H

#ifdef __cplusplus
extern "C" {
#endif

// includes
#include "lvgl.h"
#include "test_emu.h"

// defines

// globals

// headers
void v_event_btn_main_bottom(lv_event_t * e);
void v_event_btn_main_bg(lv_event_t * e);
void v_btn_redraw(v_btn_enum_main_bottom_t btn_id);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*TEST_EMU_HANDLERS_H*/