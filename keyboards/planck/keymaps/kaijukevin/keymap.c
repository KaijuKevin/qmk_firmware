/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "planck.h"
#include "action_layer.h"
#include "muse.h"
#include "wait.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _GAMING,
  _LOWER,
  _RAISE,
  _NUMPAD,
  _FNKEYS,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  GAMING,
  LOWER,
  RAISE,
  NUMPAD,
  FNKEYS
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define GAMING MO(_GAMING)
#define NUMPAD MO(_NUMPAD)
#define FNKEYS MO(_FNKEYS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:  |  ' " |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  /?  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  |Numpad|Lower |    Space    |Raise |FNKeys|  xx  | Mute |Enter |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,   KC_Q,    KC_W,    KC_E,       KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,   KC_A,    KC_S,    KC_D,       KC_F,    KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,       KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LCTL,  KC_LALT, KC_LGUI, TT(NUMPAD), LOWER,   KC_SPC, KC_SPC, RAISE,   FNKEYS,  _______, KC_MUTE, KC_RSFT
),

/* Gaming
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:  |  ' " |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  up  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  |Numpad|Lower |    Space    |Raise |FNKeys| left | down | right|
 * `-----------------------------------------------------------------------------------'
 */
[_GAMING] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_E,       KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,       KC_F,    KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,       KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_ENT,
    KC_LCTL, KC_LALT, KC_LGUI, TT(NUMPAD), LOWER,   KC_SPC, KC_SPC, RAISE,   FNKEYS,  KC_LEFT, KC_DOWN, KC_RIGHT
),

//  LOWERV2
//  * ,-----------------------------------------------------------------------------------.
//  * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * |      |SelAll| Save |      |      |  xx  |  xx  |   _  |   +  |   {  |   }  |  |   |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * | CAPS |      | Cut  | Copy | Paste|  xx  |      |      |      |      |      |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      |      |      |      |      |
//  * `-----------------------------------------------------------------------------------'
 
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, LCTL(KC_A), LCTL(KC_S), _______,    _______,    XXXXXXX, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    KC_CAPS, _______,    LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), XXXXXXX, _______, _______, _______, _______, _______, _______,
    _______, _______,    _______,    _______,    _______,    _______, _______, RAISE,   _______, _______, _______, _______
),


//  RAISE
//  * ,-----------------------------------------------------------------------------------.
//  * |   `  |      |      |  up  |      |      |      |      |      |      |      |      |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * |      |      | left | down | right|      | xxxx |   -  |   =  |   [  |   ]  |  \   |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * |      |      |      |      |      |      |      |      |      |      |      |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      |      |      |      |      |
//  * `-----------------------------------------------------------------------------------'
 
[_RAISE] = LAYOUT_planck_grid(
    KC_TILD, _______, _______, KC_UP,   _______,  _______, _______,  _______, _______, _______, _______, _______,
    _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, XXXXXXX,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, _______, _______, _______,  _______, _______,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, LOWER,    _______, _______,  _______, _______, _______, _______, LGUI(KC_PSCR)
),


// Numpad
//  * ,-----------------------------------------------------------------------------------.
//  * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * |      |      |      |      |      |      |      |   4  |   5  |   6  |   +  |   -  |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * |      |      |      |      |      |      |      |   1  |   2  |   3  |   *  |   /  |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |   0  |   ,  |   .  |   =  | Enter|
//  * `-----------------------------------------------------------------------------------'

[_NUMPAD] = LAYOUT_planck_grid(
    _______, KC_1,    KC_2,    KC_3,        KC_4,     KC_5,    KC_6,  KC_7, KC_8,    KC_9,   KC_0,     KC_BSPC,
    _______, _______, _______, _______,    _______, _______, _______, KC_4, KC_5,    KC_6,   KC_PLUS,  KC_MINUS,
    _______, _______, _______, _______,    _______, _______, _______, KC_1, KC_2,    KC_3,   KC_ASTR,  KC_SLASH,
    _______, _______, _______, TT(NUMPAD), _______, _______, _______, KC_0, KC_COMM, KC_DOT, KC_EQUAL, KC_ENTER
),

//  FNKEYS
//  * ,-----------------------------------------------------------------------------------.
//  * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * | F13  | F14  | F15  | F16  | F17  | F18  | F19  | F20  | F21  | F22  | F23  | F24  |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * |      |      |      |      |      |      |      |      |      |      |      |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      |      |      |      |      |
//  * `-----------------------------------------------------------------------------------'

[_FNKEYS] = LAYOUT_planck_grid(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|      |Colemk|Dvorak|Plover|Qwerty|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______,  _______, _______, QWERTY,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, GAMING,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)


};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
      case GAMING:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_GAMING);
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_song);
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
   }
}

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
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}


//  empty
//  * ,-----------------------------------------------------------------------------------.
//  * |      |      |      |      |      |      |      |      |      |      |      |      |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * |      |      |      |      |      |      |      |      |      |      |      |      |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * |      |      |      |      |      |      |      |      |      |      |      |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      |      |      |      |      |
//  * `-----------------------------------------------------------------------------------'
 
// [_EMPTY] = LAYOUT_planck_grid(
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
// ),



 // Lower
 // * ,-----------------------------------------------------------------------------------.
 // * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 // * |------+------+------+------+------+-------------+------+------+------+------+------|
 // * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 // * |------+------+------+------+------+------|------+------+------+------+------+------|
 // * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 // * |------+------+------+------+------+------+------+------+------+------+------+------|
 // * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 // * `-----------------------------------------------------------------------------------'
 

// [_LOWER] = LAYOUT_planck_grid(
//     KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
//     KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
//     _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
//     _______, _______, _______, _______, _______, _______, _______, RAISE,      KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
// ),


//  Raise
//  * ,-----------------------------------------------------------------------------------.
//  * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * | Del  | left | down |  up  | right|  xx  |  xx  |   -  |   =  |   [  |   ]  |  \   |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * |      |  xx  |  xx  |  xx  |  xxx |  xxx |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
//  * `-----------------------------------------------------------------------------------'
 
// [_RAISE] = LAYOUT_planck_grid(
//     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
//     KC_DEL,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, _______,
//     _______, _______, _______, _______, _______, _______, _______,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______,  KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
// ),


// HOW TO FLASH THE KEYBOARD:
//  go to the parent directory and do this:
//  make planck/rev6:kaijukevin:dfu-util

