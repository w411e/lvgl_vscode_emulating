#include "../inc/main_screen_c_api.h"
#include "../inc/main_screen.hpp"
#include <memory>

namespace v_main_screen{
    std::unique_ptr<v_smart_sync_gui> g_gui;
} // namespace v_main_screen

extern "C" {

void v_main_screen_gui_destroy(void) {
    v_main_screen::g_gui.reset();
}

void v_main_screen_gui_init(void) {
    if (!v_main_screen::g_gui) {
        v_main_screen::g_gui = std::make_unique<v_main_screen::v_smart_sync_gui>();
    }
}

} // extern "C"s