// SPDX-FileCopyrightText: 2021 Ethel Morgan
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "muse.h"

#include "eth.h"

enum planck_layers {
    _QWERTY,
    _COLEMAK,
    _CONTROLS,
    _NUMBERS,
    _SETTINGS,
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
};

#define Controls_or(kc) LT(_CONTROLS, kc)
#define Numbers_or(kc) LT(_NUMBERS, kc)

// clang-format off
#define LAYOUT_planck_mit_main_( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29  \
  ) \
  LAYOUT_planck_mit( \
    Controls_or(Slash),          K00 , K01 , K02 , K03              , K04 , K05 , K06              , K07 , K08 ,          K09 , Controls_or(Tack), \
    LShift_or(Esc)    , LCmd_or (K10), K11 , K12 , K13              , K14 , K15 , K16              , K17 , K18 , RCmd_or (K19), RShift_or(Esc)   , \
    LAlt_or(Backtick) , LCtrl_or(K20), K21 , K22 , K23              , K24 , K25 , K26              , K27 , K28 , RCtrl_or(K29), RAlt_or(Slash)   , \
    ________          , _______      , ____, ____, Numbers_or(Space),   Enter   , Numbers_or(Space), Bksp, ____, _______      , MO(_SETTINGS)      \
  )
// clang-format on

// Expand any macros passed in as arguments.
#define LAYOUT_planck_mit_main(...) LAYOUT_planck_mit_main_(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_planck_mit_main(
        // clang-format off
        QWERTY_L1, QWERTY_R1,
        QWERTY_L2, QWERTY_R2,
        QWERTY_L3, QWERTY_R3
        // clang-format on
        ),

    [_COLEMAK] = LAYOUT_planck_mit_main(
        // clang-format off
        COLEMAK_L1, COLEMAK_R1,
        COLEMAK_L2, COLEMAK_R2,
        COLEMAK_L3, COLEMAK_R3
        // clang-format on
        ),

    [_CONTROLS] = LAYOUT_planck_mit(
        // clang-format off
        ______, _____, Prev, Next, Play, Tab , Down, Right, _____, _____, _____, ______,
        LShift, LCmd , ____, ____, ____, ____, Left, _____, _____, _____, RCmd , RShift,
        LCtrl , LCtrl, ____, ____, ____, ____, Up  , _____, _____, _____, RCtrl, RAlt  ,
        ______, _____, ____, ____, ____,  _______  , _____, _____, _____, _____, ______
        // clang-format on
        ),

    [_NUMBERS] = LAYOUT_planck_mit(
        // clang-format off
        Backslash       , N1          , N2 , N3 , N4  , N5  , N6  , N7  , N8      , N9      , N0           , Tack,
        LShift_or(Slash), LCmd_or(F1) , F2 , F3 , F4  , F5  , Bksp, PgUp, LBracket, RBracket, RCmd_or(PgDn), RShift_or(Equal),
        LAlt            , LCtrl_or(F7), F8 , F9 , F10 , F11 , F12 , ____, _______ , _______ , RCtrl        , RAlt,
        _______         , _______     , ___, ___, ____,  _______  , ____, _______ , VolDn   , VolUp        , _______
        // clang-format on
        ),

    [_SETTINGS] = LAYOUT_planck_mit(
        // clang-format off
        ____, RESET  , DEBUG    , RgbToggle, RgbMode , HueUp , HueDn  , SatUp , SatDn  , ValUp, ValDn, ____,
        ____, ______ , MusicMode, AudioOn  , AudioOff, ______, _______, QWERTY, COLEMAK, _____, _____, ____,
        ____, VoiceDn, VoiceUp  , MusicOn  , MusicOff, MidiOn, MidiOff, ______, _______, _____, _____, ____,
        ____, ______ , ______   , _______  , _______ ,    _______     , ______, _______, _____, _____, ____
        // clang-format on
        ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;

        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
    }
    return true;
}

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case MO(_SETTINGS):
            return false;
        default:
            return true;
    }
}
