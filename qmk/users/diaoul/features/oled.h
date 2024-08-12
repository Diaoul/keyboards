#pragma once

#include QMK_KEYBOARD_H

void render_user(uint8_t col, uint8_t line);
void render_computer(uint8_t col, uint8_t line);
void render_layer_state(uint8_t col, uint8_t line);
void render_mod_status_alt_gui(uint8_t modifiers, uint8_t col, uint8_t line);
void render_mod_status_shift_ctrl(uint8_t modifiers, bool is_caps_word_on, uint8_t col, uint8_t line);
