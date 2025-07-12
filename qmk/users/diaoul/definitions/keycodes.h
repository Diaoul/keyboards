#pragma once

// Layer-taps
#define NUM_TAB LT(NUM, KC_TAB)
#define NAV_SPC LT(NAV, KC_SPC)
#define SYM_BSPC LT(SYM, KC_BSPC)
#define SYM_ENT LT(SYM, KC_ENT)

// Mod-taps
// Home row mods
#define HR_A LALT_T(KC_A)
#define HR_R LGUI_T(KC_R)
#define HR_S LSFT_T(KC_S)
#define HR_T LCTL_T(KC_T)
#define HR_N RCTL_T(KC_N)
#define HR_E RSFT_T(KC_E)
#define HR_I RGUI_T(KC_I)
#define HR_O LALT_T(KC_O)

// One-shot mods
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
