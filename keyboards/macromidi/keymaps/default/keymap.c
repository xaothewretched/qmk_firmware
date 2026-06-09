// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "print.h"
#include "joystick.h"
#include "analog.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_PGUP,
        KC_PPLS,   KC_MUTE,   KC_VOLD,   KC_VOLU,   KC_PGDN,
        KC_ESC,   MS_BTN1,   KC_UP,   MS_BTN2,   KC_MINS,
        KC_LEFT,   KC_DOWN,   KC_RIGHT,
        MO(0),   KC_LALT,   KC_LCTL
    ),

    [1] = LAYOUT(
        KC_A,   KC_B,   KC_C,   KC_D,   KC_E,
        KC_F,   KC_G,   KC_H,   KC_I,   KC_J,
        KC_K,   KC_L,   KC_M,   KC_N,   KC_O,
        KC_P,   KC_Q,   KC_R,
        KC_S,   KC_T,   KC_U
    )
};


static uint16_t joy_x = 0;
static uint16_t joy_y = 0;

void matrix_scan_user(void) {
    joy_x = adc_read(F7);
    joy_y = adc_read(F6);
}

// joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
//     JOYSTICK_AXIS_VIRTUAL,
//     JOYSTICK_AXIS_VIRTUAL
// };

#ifdef OLED_ENABLE

bool oled_task_user(void) {
    oled_clear();

    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("0"), false);
            break;

        default:
            oled_write_ln_P(PSTR("?"), false);
            break;
    }

    char buf[24];

    snprintf(buf, sizeof(buf), "X:%4u", joy_x);
    oled_write_ln(buf, false);

    snprintf(buf, sizeof(buf), "Y:%4u", joy_y);
    oled_write_ln(buf, false);

    return false;
}

#endif
