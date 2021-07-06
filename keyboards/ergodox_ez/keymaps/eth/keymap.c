// SPDX-FileCopyrightText: 2021 Ethel Morgan
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "version.h"

#include "eth.h"

static const uint8_t max_led_value = 50;

enum layers {
    _QWERTY,
    _COLEMAK,
    _CONTROLS,
    _SETTINGS,
};

#define Controls_or(kc) LT(_CONTROLS, kc)

#define TabLeft LCMD(LSFT(KC_LBRC))
#define TabRight LCMD(LSFT(KC_RBRC))
#define GoBack LCMD(KC_LBRC)
#define GoForward LCMD(KC_RBRC)

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    RGB_SLD,
    VRSN,
};

// clang-format off
#define LAYOUT_ergodox_pretty_main_( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39  \
  ) \
  LAYOUT_ergodox_pretty( \
    Backslash         ,          K00 , K01 , K02 , K03  , K04 , Del ,     Bksp, K05 , K06  , K07 , K08 , K09          , Tack              , \
    Controls_or(Slash),          K10 , K11 , K12 , K13  , K14 , Tab ,     Tab , K15 , K16  , K17 , K18 , K19          , Controls_or(Equal), \
    LShift_or(Esc)    , LCmd_or (K20), K21 , K22 , K23  , K24 ,                 K25 , K26  , K27 , K28 , RCmd_or(K29) , RShift_or(Esc)    , \
    LAlt_or(Backtick) , LCtrl_or(K30), K31 , K32 , K33  , K34 , ____,     ____, K35 , K36  , K37 , K38 , RCtrl_or(K39), RAlt              , \
    _______           , _______      , ____, ____, Space,                             Space, ____, ____, _______      , MO(_SETTINGS)     , \
                                                                                                                                            \
                                                          ____, ____,     ____, ____,                                                       \
                                                                PgUp,     PgUp,                                                             \
                                                   Enter, Bksp, PgDn,     PgDn, Bksp, Enter                                                 \
  )
// clang-format on

// Expand any macros passed in as arguments.
#define LAYOUT_ergodox_pretty_main(...) LAYOUT_ergodox_pretty_main_(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_ergodox_pretty_main(
        // clang-format off
        NUMBERS_L, NUMBERS_R,
        QWERTY_L1, QWERTY_R1,
        QWERTY_L2, QWERTY_R2,
        QWERTY_L3, QWERTY_R3
        // clang-format on
        ),

    [_COLEMAK] = LAYOUT_ergodox_pretty_main(
        // clang-format off
        NUMBERS_L, NUMBERS_R,
        COLEMAK_L1, COLEMAK_R1,
        COLEMAK_L2, COLEMAK_R2,
        COLEMAK_L3, COLEMAK_R3
        // clang-format on
        ),

    [_CONTROLS] = LAYOUT_ergodox_pretty(
        // clang-format off
        VRSN  , F1   , F2  , F3  , F4  , F5  , ____,     ____, F6  , F7   , F8  , F9      , F10     , F11   ,
        ______, Prev , Next, Play, ____, ____, ____,     ____, Down, Right, ____, LBracket, RBracket, F12   ,
        LShift, LCmd , ____, ____, ____, ____,                 Left, _____, ____, _______ , RCmd    , RShift,
        LAlt  , LCtrl, ____, ____, ____, ____, ____,     ____, Up  , _____, ____, _______ , RCtrl   , RAlt  ,
        ______, _____, ____, ____, ____,                             _____, ____, _______ , _______ , ______,

                                      RgbMode, ____,     RgbToggle, RGB_SLD,
                                               ____,     _______  ,
                            GoBack, GoForward, ____,     _______  , TabLeft, TabRight
        // clang-format on
        ),

    [_SETTINGS] = LAYOUT_ergodox_pretty(
        // clang-format off
        ____, ____, ____, ____, ____, ____, ____,     ____, ____, ______, _______, ____, ____, ____,
        ____, ____, ____, ____, ____, ____, ____,     ____, ____, QWERTY, COLEMAK, ____, ____, ____,
        ____, ____, ____, ____, ____, ____,                 ____, ______, _______, ____, ____, ____,
        ____, ____, ____, ____, ____, ____, ____,     ____, ____, ______, _______, ____, ____, ____,
        ____, ____, ____, ____, ____,                             ______, _______, ____, ____, ____,

                                      ____, ____,     ____, ____,
                                            ____,     ____,
                                ____, ____, ____,     ____, ____, ____
        // clang-format on
        ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case VRSN:
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;

            case RGB_SLD:
#ifdef RGBLIGHT_ENABLE
                rgblight_mode(1);
#endif
                return false;

            case QWERTY:
                ergodox_right_led_2_off();
                set_single_persistent_default_layer(_QWERTY);
                return false;

            case COLEMAK:
                ergodox_right_led_2_on();
                ergodox_right_led_2_set(max_led_value);
                set_single_persistent_default_layer(_COLEMAK);
                return false;
        }
    }
    return true;
}

// Runs once after boot.
void keyboard_post_init_user(void) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    if (IS_LAYER_ON_STATE(state, _SETTINGS)) {
        ergodox_right_led_3_on();
        ergodox_right_led_3_set(max_led_value);
    } else {
        ergodox_right_led_3_off();
    }

    return state;
};
