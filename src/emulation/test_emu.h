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
#include "test_emu_handlers.h"

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
#define DEF     0x27C2F5
#define DEF_2   0x8FDFFA

// globals

// headers here
void test_emulation_setup(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*TEST_EMU_H*/