#include "unity.h"
#include "src/emulation/test_emu.h"
#include "lvgl.h"
#include <time.h>

/* LVGL Test module includes */
#include "lvgl/src/others/test/lv_test_display.h"
// #include "lvgl/src/drivers/sdl/lv_sdl_window.h"
#include "lvgl/src/misc/lv_timer.h"
#include "lvgl/src/others/test/lv_test_indev.h"
#include "lvgl/src/others/test/lv_test_screenshot_compare.h"
#include "lvgl/src/others/test/lv_test_helpers.h"

/**
 * Info: to get a log of PASS-ed tests call: ./test_ui.exe > textfilename.txt
 */

#define UNITY_
#ifndef REF_IMGS_PATH
    #define REF_IMGS_PATH "A:/bin/screenshots"
#endif

#define BTNNUM 4
#define WAIT 30
#define MONKEYTIME 20000 // ms time for monkeytest

/* functions */
void refresh_win_scr(void);
bool file_exists(const char *path);
void screenshot_name(void);
void run_screenshot_compare(void);
void timer_start(void);
void timer_get_time(void);
void timer_finish(void);

/* External objects and screen */
static lv_display_t * test_display;
lv_obj_t *btn_arr[BTNNUM];
lv_display_t* disp;
lv_obj_t* scr;
extern lv_obj_t* btn1;
extern lv_obj_t* btn2;
extern lv_obj_t* btn3;
extern lv_obj_t* btn4;

/* Time header for textfile */
bool timeHeader = false;
time_t rawtime;
struct tm * timeinfo;
static uint32_t time_start = 0;
static uint32_t time_stamp = 0;

/* Vars */
uint32_t screenshot_cnt = 1; // amount of screencompares for naming
char png_name [25] = {0}; // name of screenshot
char name_template[] = "/screentest_"; // prefix
lv_monkey_config_t mconfig;
lv_monkey_t * monkey;


/* Set up LVGL emulated environment */
void setUp(void) 
{
    timer_start();
    lv_init();
    printf("\nsetUp begin...\n");

    /* Create an in-memory display for testing */
    // disp = lv_sdl_window_create(480, 320); // width x height
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
    /* Initialize your UI */
    test_emulation_setup();

    printf("setUp finished...\n");
}

/* Tear down LVGL environment */
void tearDown(void) 
{
    // LVGL objects will be cleaned up when display is deleted
    printf("\n--------------------------------------------\n");
    printf("tearDown...\n\nTest result: ");
}

/* Test button creation */
void test_testscreen(void) 
{
    bool result; // screenshot compare

    printf("test_testscreen begin...\n");
    btn_arr[0] = btn1;
    btn_arr[1] = btn2;
    btn_arr[2] = btn3;
    btn_arr[3] = btn4;

    for(int i = 0; i < BTNNUM; i++)
    {
        btn_arr[i] = lv_obj_get_child(scr, i);
    }

    refresh_win_scr();

    printf("\n--------------------------------------------\n");
    printf("Buttons created test:\n");
    for(int i = 0; i < BTNNUM; i++)
    {
        TEST_ASSERT_NOT_NULL(btn_arr[i]);
        printf("Button btn_%d:\t\t\t\tPASS\n", i+1);

        /* Screenshot compare block start */
        run_screenshot_compare();
        /* Screenshot compare block end */
    }
    timer_get_time();

    printf("\n--------------------------------------------\n");
    printf("Button label test:\n");
    refresh_win_scr();
    for(int i = 0; i < BTNNUM; i++)
    {
        char btn_name[6] = "\0";
        lv_snprintf(btn_name, sizeof(btn_name), "btn_%d", i+1);
        TEST_ASSERT_EQUAL_STRING(btn_name, lv_obj_get_name(btn_arr[i]));
        printf("Label btn_%d:\t\t\t\tPASS\n", i+1);

        /* Screenshot compare block start */
        run_screenshot_compare();
        /* Screenshot compare block end */
    }
    timer_get_time();

    printf("\n--------------------------------------------\n");
    printf("Button event tests:\n");
    for(int i = 0; i < BTNNUM; i++)
    {
        lv_obj_send_event(btn_arr[i], LV_EVENT_PRESSED, NULL);
        refresh_win_scr();
        
        uint32_t color = lv_color_to_u32(lv_obj_get_style_bg_color(btn_arr[i], LV_PART_MAIN)) & 0x00FFFFFF;
        TEST_ASSERT_EQUAL_HEX32(0xFF0000, color); // RED
        printf("Event PRESSED, clr RED btn_%d:\t\tPASS\n", i+1);

        /* Screenshot compare block start */
        run_screenshot_compare();
        /* Screenshot compare block end */

        lv_obj_send_event(btn_arr[i], LV_EVENT_RELEASED, NULL);
        refresh_win_scr();

        color = lv_color_to_u32(lv_obj_get_style_bg_color(btn_arr[i], LV_PART_MAIN)) & 0x00FFFFFF;
        TEST_ASSERT_EQUAL_HEX32(0xFFFFFF, color); // WHITE
        printf("Event RELEASED, clr WHITE btn_%d:\tPASS\n", i+1);

        /* Screenshot compare block start */
        run_screenshot_compare();
        /* Screenshot compare block end */
    }
    timer_get_time();
}

void test_monkey_random_input(void)
{
    TEST_IGNORE();
    printf("Starting Monkey Random Interaction Test...\n");
    
    /* Monkeytest setup */
    lv_monkey_config_init(&mconfig);
    mconfig.type = LV_INDEV_TYPE_POINTER;
    mconfig.period_range.min = 0;
    mconfig.period_range.max = 20;
    mconfig.input_range.min = 0;
    mconfig.input_range.max = 320;
    monkey = lv_monkey_create(&mconfig);
    lv_monkey_set_enable(monkey, true);
    refresh_win_scr();

    uint32_t end = lv_tick_get() + MONKEYTIME; // 3 seconds
    uint32_t scr_shot_time = 0;
    while(lv_tick_get() < end) {
        lv_timer_handler();
        lv_test_wait(10);
        if (scr_shot_time == 500){
            scr_shot_time = 0;
            run_screenshot_compare();
        }
        scr_shot_time+=10;
    }

    /* Screenshot compare block start */
    run_screenshot_compare();
    /* Screenshot compare block end */

    printf("Monkey interaction done.\n");
}

void refresh_win_scr(void)
{
    lv_obj_invalidate(scr);
    lv_test_wait(WAIT);
    lv_refr_now(NULL);
}

bool file_exists(const char *path)
{
    lv_fs_file_t f;
    lv_fs_res_t res;
    res = lv_fs_open(&f, path, LV_FS_MODE_RD);
    if(res == LV_FS_RES_OK)
    {
        lv_fs_close(&f);
        return true;
    }
    return false;
}

void screenshot_name(void)
{
    /* build name */
    lv_snprintf(png_name, sizeof(png_name), "%s%d.png", name_template, screenshot_cnt);
    char fn_ref_full[256];
    lv_snprintf(fn_ref_full, sizeof(fn_ref_full), "%s%s", REF_IMGS_PATH, png_name);
    /* create file if non existent */
    if(!file_exists(fn_ref_full))
    {
        refresh_win_scr();
        lv_test_screenshot_compare(png_name);
        refresh_win_scr();
    }
    screenshot_cnt++;
}

void run_screenshot_compare(void)
{
    /* Screenshot compare block start */
    lv_test_wait(WAIT);
    screenshot_name();
    bool result = lv_test_screenshot_compare(png_name);
    TEST_ASSERT_TRUE(result);
    printf("Screen compare:\t\t\t\tPASS\n");
    /* Screenshot compare block end */
}

void timer_start(void)
{
    if(!timeHeader)
    {
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        printf("Test starting time: %s\n", asctime(timeinfo));
        printf("--------------------------------------------\n\n");
        timeHeader = true;
        time_start = lv_tick_get();
        time_stamp = time_start;
    }
}

void timer_get_time(void)
{
    uint32_t time_curr = lv_tick_get();
    printf("\nTickcount:\t\t\t\t%d\n", time_curr - time_stamp);
    printf("Ticks since start: \t\t\t%d\n", time_curr);
    time_stamp = time_curr;
}

void timer_finish(void)
{
    /**
     * Maybe future use
     */
}