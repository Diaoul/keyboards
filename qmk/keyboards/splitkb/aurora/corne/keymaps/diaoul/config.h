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
#define RGB_MATRIX_HUE_BREATHING_DUAL_RIGHT_HUE_DISTANCE 190
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_HUE_BREATHING_DUAL

// OLED (https://docs.qmk.fm/features/oled_driver)
#define QMK_VERSION_HOLD_TIME 1000 // in ms
#define EXHAUST_PARTICLES 40
#define EXHAUST_FRAME_INTERVAL 50 // in ms

// Split (https://docs.qmk.fm/features/split_keyboard)
// Status OLED and RGB follow the side, not the USB half, so the other half needs this state
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_WPM_ENABLE
#define SPLIT_ACTIVITY_ENABLE
#define CAPS_WORD_SPLIT_SYNC
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_CAPS_WORD
