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
void btn_event_cb_empty(lv_event_t * e);
void btn_event_cb_1(lv_event_t * e);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*TEST_EMU_HANDLERS_H*/