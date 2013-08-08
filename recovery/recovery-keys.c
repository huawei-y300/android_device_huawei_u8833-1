#include <linux/input.h>

#include "recovery_ui.h"
#include "common.h"
#include "extendedcommands.h"


int device_toggle_display(volatile char* key_pressed, int key_code) {
    int alt = key_pressed[KEY_LEFTALT] || key_pressed[KEY_RIGHTALT];
    if (alt && key_code == KEY_L)
        return 1;
    // allow toggling of the display if the correct key is pressed, and the display toggle is allowed or the display is currently off
    if (ui_get_showing_back_button()) {
        return 0;
        //return get_allow_toggle_display() && (key_code == KEY_HOME || key_code == KEY_MENU || key_code == KEY_END);
    }
    return get_allow_toggle_display() && (key_code == KEY_MENU);
}

int device_handle_key(int key_code, int visible) {
    if (visible) {
        switch (key_code) {
            case KEY_MENU:
            case KEY_VOLUMEDOWN:
                return HIGHLIGHT_DOWN;
                    
            case KEY_VOLUMEUP:
                return HIGHLIGHT_UP;

            case KEY_HOME:
            case KEY_POWER:
                return SELECT_ITEM;
            
            case 330:
            case KEY_BACK:
                if (!ui_root_menu) {
                    return GO_BACK;
                }
        }
    }

    return NO_ACTION;
}
