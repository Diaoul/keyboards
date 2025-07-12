#include QMK_KEYBOARD_H

#include "../definitions/layers.h"
#include "oled.h"

#include "action_layer.h"
#include "oled_driver.h"
#include "progmem.h"

void render_user(uint8_t col, uint8_t line) {
    static const char PROGMEM user_1[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0};
    static const char PROGMEM user_2[] = {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0};
    oled_set_cursor(col, line);
    oled_write_P(user_1, false);
    oled_set_cursor(col, line + 1);
    oled_write_P(user_2, false);
}

void render_computer(uint8_t col, uint8_t line) {
    static const char PROGMEM computer_1[] = {0x98, 0x99, 0x9a, 0};
    static const char PROGMEM computer_2[] = {0xb8, 0xb9, 0xba, 0};
    static const char PROGMEM computer_3[] = {0xd8, 0xd9, 0xda, 0};

    oled_set_cursor(col, line);
    oled_write_P(computer_1, false);
    oled_set_cursor(col, line + 1);
    oled_write_P(computer_2, false);
    oled_set_cursor(col, line + 2);
    oled_write_P(computer_3, false);
}

void render_layer_state(uint8_t col, uint8_t line) {
    static const char PROGMEM layer_1[]   = {0x93, 0x94, 0x95, 0x96, 0x97, 0};
    static const char PROGMEM layer_2_1[] = {0xb3, 0};
    static const char PROGMEM layer_2_2[] = {0xb7, 0};
    static const char PROGMEM layer_3[]   = {0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0};
    static const char PROGMEM arrows[]    = {0x1b, 0x12, 0x1a, 0};

    oled_set_cursor(col, line);
    oled_write_P(layer_1, false);
    oled_set_cursor(col, line + 1);
    oled_write_P(layer_2_1, false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case NAV:
            oled_write_P(arrows, false);
            break;
        case SYM:
            oled_write_P(PSTR("#$%"), false);
            break;
        case NUM:
            oled_write_P(PSTR("123"), false);
            break;
        case FUN:
            oled_write_P(PSTR("fun"), false);
            break;
        case SYS:
            oled_write_P(PSTR("sys"), false);
            break;
        default:
            oled_write_P(PSTR("abc"), false);
    }
    oled_write_P(layer_2_2, false);
    oled_set_cursor(col, line + 2);
    oled_write_P(layer_3, false);
}

void render_mod_status_alt_gui(uint8_t modifiers, uint8_t col, uint8_t line) {
    static const char PROGMEM alt_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM alt_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM alt_on_1[]  = {0x8d, 0x8e, 0};
    static const char PROGMEM alt_on_2[]  = {0xad, 0xae, 0};

    static const char PROGMEM gui_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM gui_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM gui_on_1[]  = {0x8f, 0x90, 0};
    static const char PROGMEM gui_on_2[]  = {0xaf, 0xb0, 0};

    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    oled_set_cursor(col, line);
    if (modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if ((modifiers & MOD_MASK_ALT) && (modifiers & MOD_MASK_GUI)) {
        oled_write_P(on_on_1, false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(on_off_1, false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if (modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    oled_set_cursor(col, line + 1);
    if (modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }

    if ((modifiers & MOD_MASK_ALT) && (modifiers & MOD_MASK_GUI)) {
        oled_write_P(on_on_2, false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(on_off_2, false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }
}

void render_mod_status_shift_ctrl(uint8_t modifiers, bool is_caps_word_on, uint8_t col, uint8_t line) {
    static const char PROGMEM shift_off_1[]    = {0x89, 0x8a, 0};
    static const char PROGMEM shift_off_2[]    = {0xa9, 0xaa, 0};
    static const char PROGMEM shift_on_1[]     = {0x91, 0x92, 0};
    static const char PROGMEM shift_on_2[]     = {0xb1, 0xb2, 0};
    static const char PROGMEM caps_word_on_1[] = {0xc0, 0xc1, 0};
    static const char PROGMEM caps_word_on_2[] = {0xc2, 0xc3, 0};

    static const char PROGMEM ctrl_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM ctrl_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM ctrl_on_1[]  = {0xcd, 0xce, 0};
    static const char PROGMEM ctrl_on_2[]  = {0xcf, 0xd0, 0};

    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    oled_set_cursor(col, line);
    if ((modifiers & MOD_MASK_SHIFT) || is_caps_word_on) {
        if (is_caps_word_on) {
            oled_write_P(caps_word_on_1, false);
        } else {
            oled_write_P(shift_on_1, false);
        }
    } else {
        oled_write_P(shift_off_1, false);
    }

    if (((modifiers & MOD_MASK_SHIFT) || is_caps_word_on) && (modifiers & MOD_MASK_CTRL)) {
        oled_write_P(on_on_1, false);
    } else if ((modifiers & MOD_MASK_SHIFT) || is_caps_word_on) {
        oled_write_P(on_off_1, false);
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    oled_set_cursor(col, line + 1);
    if ((modifiers & MOD_MASK_SHIFT) || is_caps_word_on) {
        if (is_caps_word_on) {
            oled_write_P(caps_word_on_2, false);
        } else {
            oled_write_P(shift_on_2, false);
        }
    } else {
        oled_write_P(shift_off_2, false);
    }

    if (((modifiers & MOD_MASK_SHIFT) || is_caps_word_on) && (modifiers & MOD_MASK_CTRL)) {
        oled_write_P(on_on_2, false);
    } else if ((modifiers & MOD_MASK_SHIFT) || is_caps_word_on) {
        oled_write_P(on_off_2, false);
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }
}
