#define WDL_IMPLEMENTATION
#define WDL_NO_XDG
#include "../../WDL.h"

#include <string.h>
#include <stdint.h>

#define TEST_WL_INTERFACE_NAME(interface, expected, count, passed) \
    printf("[Test #%u] Tested %s.name, expected: %s, actual: %s, passed: %s\x1b[0m\n", \
        count, #interface, expected, interface.name, strcmp(interface.name, expected) ? "\x1b[0;31mno" : (passed++, "\x1b[0;32myes"));

// #define TEST_WL_INTERFACE_NAME(interface, expected, count, passed) printf("%s[Test #%u] Tested %s.name, expected: %s, actual: %s, passed: %s\x1b[0m\n", strcmp(interface.name, expected) ? "\x1b[0;31m" : "\x1b[0;32m",count, #interface, expected, interface.name, strcmp(interface.name, expected) ? "no" : (passed++, "yes"));

int main() {;
    WDL_init();

    uint32_t count = 0;
    uint32_t passed = 0;


    TEST_WL_INTERFACE_NAME(wl_display_interface, "wl_display", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_registry_interface, "wl_registry", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_callback_interface, "wl_callback", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_compositor_interface, "wl_compositor", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_shm_pool_interface, "wl_shm_pool", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_shm_interface, "wl_shm", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_buffer_interface, "wl_buffer", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_data_offer_interface, "wl_data_offer", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_data_source_interface, "wl_data_source", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_data_device_interface, "wl_data_device", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_data_device_manager_interface, "wl_data_device_manager", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_shell_interface, "wl_shell", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_shell_surface_interface, "wl_shell_surface", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_surface_interface, "wl_surface", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_seat_interface, "wl_seat", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_pointer_interface, "wl_pointer", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_keyboard_interface, "wl_keyboard", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_touch_interface, "wl_touch", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_output_interface, "wl_output", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_region_interface, "wl_region", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_subcompositor_interface, "wl_subcompositor", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_subsurface_interface, "wl_subsurface", count++, passed)
    TEST_WL_INTERFACE_NAME(wl_fixes_interface, "wl_fixes", count++, passed)

    printf("\n%sPassed: %u/%u\x1b[0m\n", !(passed == count) ?  "\x1b[0;31m" : "\x1b[0;32m",  passed, count);

    WDL_deinit();

    return (passed == count) ? 0 : 1;
}