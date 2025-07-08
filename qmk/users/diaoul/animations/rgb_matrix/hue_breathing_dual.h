#ifdef ENABLE_RGB_MATRIX_HUE_BREATHING_DUAL
RGB_MATRIX_EFFECT(HUE_BREATHING_DUAL)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#        ifndef RGB_MATRIX_HUE_BREATHING_DUAL_DELTA
#            define RGB_MATRIX_HUE_BREATHING_DUAL_DELTA 12
#        endif
#        ifndef RGB_MATRIX_HUE_BREATHING_DUAL_SLAVE_HUE_DISTANCE
#            define RGB_MATRIX_HUE_BREATHING_DUAL_SLAVE_HUE_DISTANCE 128
#        endif
#        ifndef RGB_MATRIX_HUE_BREATHING_DUAL_DIRECTION
#            define RGB_MATRIX_HUE_BREATHING_DUAL_DIRECTION 1
#        endif

hsv_t HUE_BREATHING_DUAL_math(hsv_t hsv, uint8_t i, uint8_t time) {
    if (is_keyboard_master()) {
        hsv.h = hsv.h + RGB_MATRIX_HUE_BREATHING_DUAL_DIRECTION * scale8(abs8(sin8(time / 2) - 128) * 2, RGB_MATRIX_HUE_BREATHING_DUAL_DELTA);
    } else {
        hsv.h = hsv.h + RGB_MATRIX_HUE_BREATHING_DUAL_SLAVE_HUE_DISTANCE - RGB_MATRIX_HUE_BREATHING_DUAL_DIRECTION * scale8(abs8(sin8(time / 2) - 128) * 2, RGB_MATRIX_HUE_BREATHING_DUAL_DELTA);
    }
    return hsv;
}

bool HUE_BREATHING_DUAL(effect_params_t* params) {
    return effect_runner_i(params, &HUE_BREATHING_DUAL_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_HUE_BREATHING_DUAL
