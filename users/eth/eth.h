// SPDX-FileCopyrightText: 2021 Ethel Morgan
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// clang-format off
#define NUMBERS_L   KC_1, KC_2, KC_3, KC_4, KC_5
#define NUMBERS_R   KC_6, KC_7, KC_8, KC_9, KC_0
// clang-format on

// clang-format off
#define QWERTY_L1   KC_Q, KC_W, KC_E   , KC_R  , KC_T
#define QWERTY_L2   KC_A, KC_S, KC_D   , KC_F  , KC_G
#define QWERTY_L3   KC_Z, KC_X, KC_C   , KC_V  , KC_B
#define QWERTY_R1   KC_Y, KC_U, KC_I   , KC_O  , KC_P
#define QWERTY_R2   KC_H, KC_J, KC_K   , KC_L  , KC_SCLN
#define QWERTY_R3   KC_N, KC_M, KC_COMM, KC_DOT, KC_QUOT
// clang-format on

// clang-format off
#define COLEMAK_L1  KC_Q, KC_W, KC_F   , KC_P  , KC_G
#define COLEMAK_L2  KC_A, KC_R, KC_S   , KC_T  , KC_D
#define COLEMAK_L3  KC_Z, KC_X, KC_C   , KC_V  , KC_B
#define COLEMAK_R1  KC_J, KC_L, KC_U   , KC_I  , KC_SCLN
#define COLEMAK_R2  KC_H, KC_N, KC_E   , KC_I  , KC_O
#define COLEMAK_R3  KC_K, KC_M, KC_COMM, KC_DOT, KC_QUOT
// clang-format on

// These are set elsewhere in ChibiOS, so we'll unset them for the keymap.
#undef F1
#undef F2
#undef F3
#undef F4
#undef F5
#undef F6
#undef F7
#undef F8
#undef F9
#undef F10
#undef F11
#undef F12

// clang-format off
#define F1  KC_F1
#define F2  KC_F2
#define F3  KC_F3
#define F4  KC_F4
#define F5  KC_F5
#define F6  KC_F6
#define F7  KC_F7
#define F8  KC_F8
#define F9  KC_F9
#define F10 KC_F10
#define F11 KC_F11
#define F12 KC_F12
// clang-format on

#define N0 KC_0
#define N1 KC_1
#define N2 KC_2
#define N3 KC_3
#define N4 KC_4
#define N5 KC_5
#define N6 KC_6
#define N7 KC_7
#define N8 KC_8
#define N9 KC_9

// clang-format off
#define AudioOff  AU_OFF
#define AudioOn   AU_ON
#define Backslash KC_BSLS
#define Backtick  KC_GRV
#define Bksp      KC_BSPC
#define Del       KC_DEL
#define Down      KC_DOWN
#define Enter     KC_ENT
#define Equal     KC_EQL
#define Esc       KC_ESC
#define HueDn     RGB_HUD
#define HueUp     RGB_HUI
#define LAlt      KC_LALT
#define LBracket  KC_LBRC
#define LCmd      KC_LCMD
#define LCtrl     KC_LCTL
#define LShift    KC_LSFT
#define Left      KC_LEFT
#define MidiOff   MI_OFF
#define MidiOn    MI_ON
#define MusicMode MU_MOD
#define MusicOff  MU_OFF
#define MusicOn   MU_ON
#define Next      KC_MNXT
#define PgDn      KC_PGDN
#define PgUp      KC_PGUP
#define Play      KC_MPLY
#define Prev      KC_MPRV
#define RAlt      KC_RALT
#define RBracket  KC_RBRC
#define RCmd      KC_RCMD
#define RCtrl     KC_RCTL
#define RShift    KC_RSFT
#define RgbMode   RGB_MOD
#define RgbToggle RGB_TOG
#define Right     KC_RGHT
#define SatDn     RGB_SAD
#define SatUp     RGB_SAI
#define Slash     KC_SLSH
#define Space     KC_SPC
#define Tab       KC_TAB
#define Tack      KC_MINS
#define Up        KC_UP
#define ValDn     RGB_VAI
#define ValUp     RGB_VAI
#define VoiceDn   MUV_DE
#define VoiceUp   MUV_IN
#define VolDn     KC_VOLD
#define VolUp     KC_VOLU
// clang-format on

// clang-format off
#define ___       KC_TRNS
#define ____      KC_TRNS
#define _____     KC_TRNS
#define ______    KC_TRNS
#define _______   KC_TRNS
#define ________  KC_TRNS
// clang-format on

// clang-format off
#define LAlt_or(kc)   LALT_T(kc)
#define LCmd_or(kc)   LCMD_T(kc)
#define LCtrl_or(kc)  LCTL_T(kc)
#define LShift_or(kc) LSFT_T(kc)
#define RAlt_or(kc)   RALT_T(kc)
#define RCmd_or(kc)   RCMD_T(kc)
#define RCtrl_or(kc)  RCTL_T(kc)
#define RShift_or(kc) RSFT_T(kc)
// clang-format on
