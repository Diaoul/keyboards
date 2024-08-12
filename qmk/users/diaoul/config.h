#pragma once

// Tap hold (see https://docs.qmk.fm/tap_hold)
#define TAPPING_TERM 220
#define QUICK_TAP_TERM 0
#define PERMISSIVE_HOLD
#define ONESHOT_TIMEOUT 1000

// Combos (see https://docs.qmk.fm/features/combos)
#define COMBO_TERM 30
#define EXTRA_SHORT_COMBOS
#define COMBO_STRICT_TIMER

// Caps Word (see https://docs.qmk.fm/features/caps_word)
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 1000

// Repeat key (see https://docs.qmk.fm/features/repeat_key)
#define NO_ALT_REPEAT_KEY

// Firmware size optimizations (see https://docs.qmk.fm/squeezing_avr)
#define LAYER_STATE_8BIT

// Custom OLED font
#ifdef OLED_ENABLE
#    ifdef OLED_FONT_H
#        undef OLED_FONT_H
#    endif
#    define OLED_FONT_H "users/diaoul/glcdfont.c"
#endif
