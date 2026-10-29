// Copyright 2026 Antoine Bertin (@Diaoul)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// RGB Lighting (https://docs.qmk.fm/features/rgblight)
#define RGBLIGHT_SPLIT

// RGB Matrix (https://docs.qmk.fm/features/rgb_matrix)
#define ENABLE_RGB_MATRIX_HUE_BREATHING_DUAL
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define RGB_MATRIX_DEFAULT_HUE 208
#define RGB_MATRIX_HUE_BREATHING_DUAL_SLAVE_HUE_DISTANCE 190
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_HUE_BREATHING_DUAL

// OLED (https://docs.qmk.fm/features/oled_driver)
#define ART_DRIFT_INTERVAL 10000
#define QMK_VERSION_HOLD_TIME 1000
#define EXHAUST_PARTICLES 40
#define EXHAUST_FRAME_INTERVAL 50
#define MAX_STARS 16
#define STAR_PULSE 1000 // one rise and fade at the slowest speed, in ms
#define STAR_MAX_SPEED 20 // fastest star's speed, in 1/8
#define STAR_DENSITY 26 // share of pulse slots in which a star twinkles, out of 256
#define STAR_DIP_CHANCE 10 // share of the other slots in which a star dips, out of 256
#define STAR_DIP_TIME 150
#define METEOR_FRAME_INTERVAL 40
#define METEOR_TAIL 5
#define METEOR_MIN_WAIT 15000
#define METEOR_MAX_WAIT 60000
#define AURORA_FRAME_INTERVAL 100
#define AURORA_PHASE_STEP 4 // a ripple takes 256 / step frames to pass
#define AURORA_LEVEL 9 // lit share of solid aurora, out of 16
#define AURORA_SHIMMER 2 // levels the ripple adds or removes

// Split (https://docs.qmk.fm/features/split_keyboard)
// Status OLED and RGB follow the side, not the USB half, so the other half needs this state
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_WPM_ENABLE
#define SPLIT_ACTIVITY_ENABLE
#define CAPS_WORD_SPLIT_SYNC
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_CAPS_WORD
