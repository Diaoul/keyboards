#pragma once

// Tap hold (see https://docs.qmk.fm/tap_hold)
#define TAPPING_TERM 240
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM_PER_KEY
#define FLOW_TAP_TERM 100
#define CHORDAL_HOLD
#define SPECULATIVE_HOLD
#define SPECULATIVE_HOLD_FLOW_TERM 100
#define SPECULATIVE_HOLD_ONE_KEY

// One-shot keys (see https://docs.qmk.fm/one_shot_keys)
#define ONESHOT_TIMEOUT 1000

// Combos (see https://docs.qmk.fm/features/combo)
#define COMBO_TERM 30
#define COMBO_STRICT_TIMER

// Caps Word (see https://docs.qmk.fm/features/caps_word)
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 3000

// Repeat key (see https://docs.qmk.fm/features/repeat_key)
#define NO_ALT_REPEAT_KEY

// Firmware size optimizations (see https://docs.qmk.fm/squeezing_avr)
#define LAYER_STATE_8BIT
#define EXTRA_SHORT_COMBOS

// RGB (https://docs.qmk.fm/features/rgblight#configuration)
#define RGBLIGHT_HUE_STEP 4
#define RGBLIGHT_SLEEP

// RGB Matrix (https://docs.qmk.fm/features/rgb_matrix#additional-config-h-options)
#define RGB_MATRIX_SLEEP
// RGB_MATRIX_TIMEOUT blinks the half without USB (https://github.com/qmk/qmk_firmware/issues/26544), see diaoul.c
#define RGB_IDLE_TIMEOUT 300000 // in ms

// OLED (https://docs.qmk.fm/features/oled_driver)
#ifdef OLED_ENABLE
#    ifdef OLED_FONT_H
#        undef OLED_FONT_H
#    endif
#    define OLED_FONT_H "users/diaoul/glcdfont.c"
#    define OLED_BRIGHTNESS 100
#endif
