#include QMK_KEYBOARD_H

/* Macros for layer (use these for transparent keys etc.) */
#define XXXXXXX KC_NO     // No key
#define _______ KC_TRNS   // Transparent (fall through to lower layer)

enum custom_keycodes {
    EMOJI = SAFE_RANGE,
    COPY,
    PASTE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Layer 0 */
    [0] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,------------------------------------------------------.
         KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    EMOJI,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+---------|
         KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,  KC_SCLN, KC_MINS,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------+--------|
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT,  KC_SLSH, KC_LALT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------+--------|
                                     LT(1, KC_LNG2),  KC_SPC, KC_LGUI,    KC_LCTL, KC_BSPC, LT(2, KC_LNG1)
                                        //`--------------------------'  `--------------------------'
    ),

/* Layer 1 */
    [1] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-------------------------------------------------------.
        XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------+---------|
        XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,     KC_0,   KC_F12,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------+---------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT,  XXXXXXX,  XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------+---------|
                                            _______, _______, _______,     KC_DEL,  KC_ENT,   MO(3)
                                        //`--------------------------'  `--------------------------'
    ),

/* Layer 2 */
    [2] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-------------------------------------------------------.
        XXXXXXX, KC_EXLM, KC_QUOT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_PIPE,  KC_TILD,  XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------+---------|
        XXXXXXX, XXXXXXX, KC_LBRC,   KC_LT, KC_LCBR, KC_LPRN,                      KC_RPRN, KC_RCBR,   KC_GT, KC_RBRC,  XXXXXXX,  XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------+---------|
        XXXXXXX, XXXXXXX, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS,                      KC_PEQL, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------+---------|
                                              MO(3),   KC_AT, S(KC_QUOT), _______, _______, _______
                                        //`--------------------------'  `--------------------------'
    ),

/* Layer 3 */
    [3] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-------------------------------------------------------.
        XXXXXXX, XXXXXXX, XXXXXXX,   MS_UP, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------+---------|
        XXXXXXX, XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT,    COPY,                        PASTE, MS_BTN1, MS_WHLU, MS_BTN2,  XXXXXXX,  XXXXXXX,  
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------+---------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, MS_WHLD, XXXXXXX,  XXXXXXX,  XXXXXXX,  
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------+---------|
                                            _______, _______, _______,    _______, _______, _______
                                        //`--------------------------'  `--------------------------'
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case COPY:
                register_mods(MOD_BIT(KC_LGUI));
                tap_code(KC_C);
                unregister_mods(MOD_BIT(KC_LGUI));
                return false;
            case PASTE:
                register_mods(MOD_BIT(KC_LGUI));
                tap_code(KC_V);
                unregister_mods(MOD_BIT(KC_LGUI));
                return false;
            case EMOJI:
                if (record->event.pressed) {
                    // Control + Command + Space を送信
                    register_code(KC_LCTL);
                    register_code(KC_LGUI);
                    register_code(KC_SPC);
                    unregister_code(KC_SPC);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LCTL);
                }
                return false;
        }
    }
    return true;
}