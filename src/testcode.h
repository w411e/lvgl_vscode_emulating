/**
 * @file testcode.h
 *
 */

#ifndef TESTCODE_H
#define TESTCODE_H

#ifdef __cplusplus
extern "C" {
#endif

// includes
#include "lvgl.h"

// defines
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

// globals
typedef struct {
    char buttonName[9];
    uint8_t cnt;
} button;

// lv_style_t * style_default;

//lv_obj_t * screen_def, screen_2;

// headers here
static void btn_event_cb_mod(lv_event_t * e);
static void btn_event_cb_2(lv_event_t * e);
static void btn_event_cb_sw_src(lv_event_t * e);
static void init_custom_style(lv_style_t * style);
void lv_example_get_started_2_mod(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*TESTCODE_H*/