# Testing lv_init Properties

**Testcases:**
1. lv_draw_sw_init(): complex vs. simple drawing
2. SDL: active vs. non-active
3. lv_sysmon_builtin_init(): Performance testing
4. Builtin memory tests: Performance testing with/without
5. Cache size: Performance testing, maybe

# Testing sdl_hal_init()

**Testcases:**
1. SDL_GetTicks vs. SDL_GetTicks64: 64 recommended, might not work
2. lv_display_create: Performance/Visual testing
      1. LV_DPI_DEF
      2. Antialiazing
      3. Color depth

# Restults lv_init Properties

1. .
2. .
3. FPS Monitor:
   1. In lv_conf.h set LV_USE_SYSMON and LV_USE_PERF_MONITOR to '1'.  ![FPS monitored in example program.](/screenshots/FPS-Monitor.PNG?raw=true "FPS Monitor")
   2. as 1. but also set LV_USE_MEM_MONITOR to '1'. Make sure you dont change the STDLIB setting, to use LVGL's.  ![RAM usage monitored in example program.](/screenshots/RAM-Monitor.PNG?raw=true "RAM Monitor")
# Results sdl_hal_init()

**TBD**