#pragma once

#include QMK_KEYBOARD_H

enum layers {
    _COLEMAK_DH = 0,
    _NAV,
    _SYM,
};
// Layers
#define COLEMAK DF(_COLEMAK_DH)
#define QWERTY DF(_QWERTY)

// Layer keys
#define NAV_TAB LT(_NAV, KC_TAB)
#define NAV_SPC LT(_NAV, KC_SPC)
#define SYM_ENT LT(_SYM, KC_ENT)
#define SYM_BSPC LT(_SYM, KC_BSPC)

// Compose key
#define COMPOSE KC_RALT

// Home row mods
#define HC_A LALT_T(KC_A)
#define HC_R LSFT_T(KC_R)
#define HC_S LGUI_T(KC_S)
#define HC_T LCTL_T(KC_T)
#define HC_O LALT_T(KC_O)
#define HC_I RSFT_T(KC_I)
#define HC_E RGUI_T(KC_E)
#define HC_N RCTL_T(KC_N)

// One shot shifts
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
