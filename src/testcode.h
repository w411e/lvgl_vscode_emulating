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
#define RED     0xFF0000
#define GREEN   0x00FF00
#define BLUE    0x0000FF
#define WHITE   0xFFFFFF
#define BLACK   0x000000
#define YELLOW  0xFFFF00
#define FOREST  0x008000
#define TEAL    0x008080
#define MAGENTA 0xFF00FF

// globals
typedef struct {
    char buttonName[9];
    uint8_t cnt;
} button;

//lv_obj_t * screen_def, screen_2;

// headers here
static void btn_event_cb_mod(lv_event_t * e);
static void btn_event_cb_2(lv_event_t * e);
static void btn_event_cb_sw_src(lv_event_t * e);
void lv_example_get_started_2_mod(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*TESTCODE_H*/