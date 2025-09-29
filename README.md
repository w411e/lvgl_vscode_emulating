# Testing lv_init Properties

<details open>
<summary><b>Testcases:</b></summary>

1. [x]lv_draw_sw_init(): complex vs. simple drawing
2. [x]SDL: active vs. non-active (further testing needed)
3. [x]lv_sysmon_builtin_init(): Performance testing
4. [x]Builtin memory tests: Performance testing with/without (further testing needed)
5. [x]Cache size: Performance testing (further testing needed)

</details>

# Testing sdl_hal_init()

<details>
<summary><b>Testcases:</b></summary>

1. [ ]SDL_GetTicks (duration 49 days) vs. SDL_GetTicks64: 64 recommended, might not work
2. [ ]lv_display_create: Performance/Visual testing
      1. [ ]LV_DPI_DEF
      2. [ ]Antialiazing
      3. [ ]Color depth

</details>

# Restults lv_init Properties

<details>
<summary><b>Testutilities LVGL lv_sysmon_builtin_init():</b></summary>

1. In lv_conf.h set LV_USE_SYSMON and LV_USE_PERF_MONITOR to '1'.  
![FPS monitored in example program.](/screenshots/FPS-Monitor.PNG?raw=true "FPS Monitor")
2. as 1. but also set LV_USE_MEM_MONITOR to '1'. Make sure you dont change the STDLIB setting, to use LVGL's.  
![RAM usage monitored in example program.](/screenshots/RAM-Monitor.PNG?raw=true "RAM Monitor")

</details><br>

| Testcase | Outcome |
|:---------|:--------|
| Complex vs. Simple Drawing<br>lv_draw_sw_init() | Simple can't compile because of dependencies. Other Testprogram needed. |
| SDL active vs. non-active<br>lv_conf.h LV_USE_DRAW_SDL<br>CMakeLists.txt LV_USE_DRAW_SDL OFF | No significant differences detected in idle after starting the program:<br>SDL-Caching EN:<br>![SDL Caching EN CPU and RAM usage.](/screenshots/SDL-caching-en-small.PNG?raw=true "SDL Caching EN")<br>SDL-Caching DEN:<br>![SDL Caching DEN CPU and RAM usage.](/screenshots/SDL-caching-den-small.PNG?raw=true "SDL Caching DEN")<br>**Conclusion**: Further testing needed, e.g. benchmarking example |
| Dis-/Enabled builtin memory tests in lv_conf.h **LV_USE_ASSERT**_...<br>...**STYLE** and ...**OBJ** combined on/off for LVGL performance<br>...**MEM_INTEGRITY** on/off for RAM usage | STYLE/OBJ on: about 5s startuptime, min. FPS 22<br>STYLE/OBJ off: about 4.5s startuptime, min FPS 25<br>MEM_INTEGRITY on: upto 10% RAM usage (~98.9kB)<br>MEM_INTEGRITY off: upto 10% RAM usage (~98.5kB) no significant difference<br>**Conclusion**: Further testing needed, e.g. benchmarking example |
| Cache size for filesystem lv_fs_read()<br>LV_FS_STDIO_CACHE_SIZE 0<br>LV_FS_STDIO_CACHE_SIZE 512 | Cachesize 0 Bytes: upto 10% RAM, upto 87% CPU<br>Cachesize 512 Bytes: upto 10% RAM, upto 90% CPU <br>**Conclusion**: Further testing needed, e.g. benchmarking example |  

Trying out and testing the prebuilt benchmark TBD.

# Results sdl_hal_init()

**TBD**