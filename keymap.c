#include "secrets-default.h"
#include QMK_KEYBOARD_H
#include "quantum.h"
#include "keymap_us_extended.h"
#include "process_tap_dance.h"
#include "timer.h"  // Asegúrate de tener esta línea si no está
bool isWriting = false;
uint16_t last_typing_timer = 0;


extern uint8_t is_master;

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMBERS,
};


#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define NUMBERS MO(_NUMBERS)


enum custom_keycodes {
    PASS1 = SAFE_RANGE,
    PASS2,
    EMAIL1,
    EMAIL2,
    ALT_BSPC,
    ALT_HOLD,
    NEW_SAFE_RANGE  // (opcional, si defines más abajo)
};

// ───── TAP DANCE ENUM ─────
enum {
    TD_A_ACUTE,
    TD_E_ACUTE,
    TD_I_ACUTE,
    TD_O_ACUTE,
    TD_U_ACUTE,
    TD_N_TILDE,
    TD_COMILLAS,
    TD_MAYUSCULAS,
};

void td_a_acute(tap_dance_state_t *state, void *user_data);
void td_e_acute(tap_dance_state_t *state, void *user_data);
void td_i_acute(tap_dance_state_t *state, void *user_data);
void td_o_acute(tap_dance_state_t *state, void *user_data);
void td_u_acute(tap_dance_state_t *state, void *user_data);
void td_n_tilde(tap_dance_state_t *state, void *user_data);
void td_comillas(tap_dance_state_t *state, void *user_data);
void td_mayusculas(tap_dance_state_t *state, void *user_data);
void td_mayusculas_finished(tap_dance_state_t *state, void *user_data);
void td_mayusculas_reset(tap_dance_state_t *state, void *user_data);

// ───── TAP DANCE ACTIONS ─────
tap_dance_action_t tap_dance_actions[] = {
    [TD_A_ACUTE] = ACTION_TAP_DANCE_FN(td_a_acute),
    [TD_E_ACUTE] = ACTION_TAP_DANCE_FN(td_e_acute),
    [TD_I_ACUTE] = ACTION_TAP_DANCE_FN(td_i_acute),
    [TD_O_ACUTE] = ACTION_TAP_DANCE_FN(td_o_acute),
    [TD_U_ACUTE] = ACTION_TAP_DANCE_FN(td_u_acute),
    [TD_N_TILDE] = ACTION_TAP_DANCE_FN(td_n_tilde),
    [TD_COMILLAS] = ACTION_TAP_DANCE_FN(td_comillas),
    [TD_MAYUSCULAS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_mayusculas_finished, td_mayusculas_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |  1   |  2   |  3   |  4   |  5   |                    |  6   |  7   |  8   |  9   |  0   | ALT← |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |  Q   |  W   |TD_EAC|  R   |  T   |                    |  Y   |TD_UAC|TD_IAC|TD_OAC|  P   |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |TD_MAY|TD_AAC|  S   |  D   |  F   |  G   |-------.    ,-------|  H   |  J   |  K   |  L   |  ;   |TD_QUO|
 * |------+------+------+------+------+------| Home  |    | End   |------+------+------+------+------+------|
 * |LCTRL |  Z   |  X   |  C   |  V   |  B   |-------|    |-------|TD_NYE|  M   |  ,   |  .   |  /   |TD_MAY|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI | Space| /Lower  /       \Raise \  |Space | Enter | RAlt |
 *                   |      |      |      |/       /         \      \ |      |       |      |
 *                   `----------------------------'           '------''---------------------'
 */
[_QWERTY] = LAYOUT(
    KC_ESC,             KC_1,           KC_2,  KC_3,            KC_4,     KC_5,                       KC_6,            KC_7,           KC_8,            KC_9,            KC_0,     ALT_BSPC,
    KC_TAB,             KC_Q,           KC_W,  TD(TD_E_ACUTE),  KC_R,     KC_T,                       KC_Y,            TD(TD_U_ACUTE), TD(TD_I_ACUTE),  TD(TD_O_ACUTE),  KC_P,     KC_MINS,
    TD(TD_MAYUSCULAS),  TD(TD_A_ACUTE), KC_S,  KC_D,            KC_F,     KC_G,                       KC_H,            KC_J,           KC_K,            KC_L,            KC_SCLN,  TD(TD_COMILLAS),
    KC_LCTL,            KC_Z,           KC_X,  KC_C,            KC_V,     KC_B,   KC_LGUI , KC_PSCR,   TD(TD_N_TILDE),  KC_M,           KC_COMM,         KC_DOT,          KC_SLSH,  TD(TD_MAYUSCULAS),
                                               KC_LALT,         KC_APP,  NUMBERS,   LT(LOWER, KC_SPC),  LT(RAISE, KC_SPC),   RAISE,           KC_ENT,         KC_RALT
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  | F1   | F2   | F3   | F4   | F5   |                    |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |PrtScr|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |XXXXX | F6   | F7   | F8   | F9   | F10  |                    |  $   |  [   |   ]  |   +  |   |  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |XXXXX |XXXXX |XXXXX |XXXXX |F11   |F12   |-------.    ,-------|  #   |  (   |   )  |   =  |   &  |  "   |
 * |------+------+------+------+------+------|TRNS   |    |TRNS   |------+------+------+------+------+------|
 * |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |-------|    |-------|  /   |  {   |   }  |   *  |   %  |  \   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |TRNS  |TRNS  |TRNS  | / TRNS  /       \ TRNS \  | TRNS| TRNS | TRNS |
 *                   |      |      |      |/       /         \      \ |     |      |      |
 *                   `----------------------------'           '------''-------------------'
 */
[_LOWER] = LAYOUT(
  KC_TRNS,   KC_F1,   KC_F2,   KC_F3,  KC_F4,  KC_F5,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS,
  XXXXXXX,   KC_F6,   KC_F7,   KC_F8,  KC_F9,  KC_F10,                      KC_DLR,  KC_LBRC, KC_RBRC, KC_PLUS, KC_TILD, KC_TRNS,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_F11, KC_F12,                      KC_HASH, KC_LPRN, KC_RPRN, KC_PEQL, KC_AMPR, KC_TRNS,
  XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU,  KC_TRNS, KC_TRNS,  KC_PSLS, KC_LCBR, KC_RCBR, KC_ASTR, KC_PERC, KC_BSLS,
                             KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS
),



/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |TRNS |XXXXX |XXXXX |XXXXX |XXXXX | XXXXX |                    |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX | <--  |
 * |-----+------+------+------+------+-------|                    |------+------+------+------+------+------|
 * |TRNS |XXXXX |HOME  |XXXXX |END   | XXXXX |                    |ENTER |PgUp  | ↑    |PgDn  |XXXXX |XXXXX |
 * |-----+------+------+------+------+-------|                    |------+------+------+------+------+------|
 * |TRNS |XXXXX |CTRL  |SHIFT |ALT   | XXXXX |-------.    ,-------|XXXXX | ←    | ↓    | →    |XXXXX |XXXXX |
 * |-----+------+------+------+------+-------| TRNS  |    | TRNS  |------+------+------+------+------+------|
 * |TRNS |XXXXX | CUT  | COPY |PASTE | XXXXX |-------|    |-------|XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | TRNS | TRNS | TRNS | / TRNS  /       \ TRNS \ | TRNS | TRNS | TRNS |
 *                   |      |      |      |/       /         \      \|      |      |      |
 *                   `----------------------------'           '------'--------------------'
 */
[_RAISE] = LAYOUT(
  KC_TRNS,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                       XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,      XXXXXXX,  KC_TRNS,
  KC_TRNS,  XXXXXXX,  KC_HOME,  XXXXXXX,  KC_END,   KC_ENT,                       KC_ENT, KC_PAGE_UP, KC_UP,    KC_PAGE_DOWN, XXXXXXX,  XXXXXXX,
  KC_TRNS,  XXXXXXX,  KC_LCTL,  KC_LSFT,  KC_LALT,  ALT_HOLD,                       KC_HOME,   KC_LEFT,    KC_DOWN,  KC_RIGHT,      KC_END,  XXXXXXX,
  KC_TRNS,  XXXXXXX,  LCTL(KC_X),   LCTL(KC_C),  LCTL(KC_V),   XXXXXXX,   KC_TRNS, KC_TRNS,   XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,      XXXXXXX,  XXXXXXX,
                                KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,   ALT_BSPC,  KC_TRNS,    KC_TRNS
),
/* ADJUST
 * ,-----------------------------------------.                    ,---------------------------------------------.
 * |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |                    |XXXXX |XXXXX |XXXXX |XXXXX   |XXXXX  |XXXXX  |
 * |------+------+------+------+------+------|                    |------+------+------+--------+-------+-------|
 * |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |                    |XXXXX |XXXXX |XXXXX |XXXXX   |XXXXX  |XXXXX  |
 * |------+------+------+------+------+------|                    |------+------+------+--------+-------+-------|
 * |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |-------.    ,-------|XXXXX |XXXXX |UG_TOG|UG_HUEU |UG_SATU|UG_VALU|
 * |------+------+------+------+------+------|QK_BOOT|    |QK_RBT |------+------+------+--------+-------+-------|
 * |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |-------|    |-------|XXXXX |XXXXX |UG_NEXT|UG_HUED|UG_SATD|UG_VALD|
 * `-----------------------------------------/       /     \      \---------------------------------------------'
 *                   |TRNS  |TRNS  |TRNS  | / TRNS  /       \ TRNS \ | TRNS | TRNS | TRNS |
 *                   |      |      |      |/       /         \      \|      |      |      |
 *                   `----------------------------'           '-----''-------------------'
 */
[_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, EMAIL1, EMAIL2, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, UG_TOGG, UG_HUEU, UG_SATU, UG_VALU,
  XXXXXXX, PASS1,  PASS2, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, QK_RBT, XXXXXXX, XXXXXXX, UG_NEXT, UG_HUED, UG_SATD, UG_VALD,
                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
),


/* NUMBERS
 * ,-----------------------------------------.                    ,---------------------------------------------.
 * |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |                    |XXXXX |XXXXX |XXXXX |XXXXX   |XXXXX  |XXXXX  |
 * |------+------+------+------+------+------|                    |------+------+------+--------+-------+-------|
 * |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |                    |XXXXX |XXXXX |XXXXX |XXXXX   |XXXXX  |XXXXX  |
 * |------+------+------+------+------+------|                    |------+------+------+--------+-------+-------|
 * |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |-------.    ,-------|XXXXX |XXXXX |UG_TOG|UG_HUEU |UG_SATU|UG_VALU|
 * |------+------+------+------+------+------|QK_BOOT|    |QK_RBT |------+------+------+--------+-------+-------|
 * |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |XXXXX |-------|    |-------|XXXXX |XXXXX |UG_NEXT|UG_HUED|UG_SATD|UG_VALD|
 * `-----------------------------------------/       /     \      \---------------------------------------------'
 *                   |TRNS  |TRNS  |TRNS  | / TRNS  /       \ TRNS \ | TRNS | TRNS | TRNS |
 *                   |      |      |      |/       /         \      \|      |      |      |
 *                   `----------------------------'           '-----''-------------------'
 */
[_NUMBERS] = LAYOUT(
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS,
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
  KC_TRNS, XXXXXXX, XXXXXXX, ALT_HOLD, XXXXXXX, XXXXXXX,                    XXXXXXX, KC_4,    KC_5,    KC_6, XXXXXXX, XXXXXXX,
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS,  XXXXXXX, KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_0,    KC_TRNS, KC_TRNS
),


};







// Tri-layer logic
// ───── FUNCIÓN PARA ACTIVAR _ADJUST ─────
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void td_a_acute(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_A);
    } else {
        tap_code16(US_AACU);
    }
}

void td_e_acute(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_E);
    } else {
        tap_code16(US_EACU);
    }
}

void td_i_acute(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_I);
    } else {
        tap_code16(US_IACU);
    }
}

void td_o_acute(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_O);
    } else {
        tap_code16(US_OACU);
    }
}

void td_u_acute(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_U);
    } else {
        tap_code16(US_UACU);
    }
}

void td_n_tilde(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_N);
    } else {
        tap_code16(US_NTIL);
    }
}




void td_comillas(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(US_QUOT);
        tap_code(KC_SPC);
    } else {
        tap_code16(US_DQUO);
        tap_code(KC_SPC);
    }
}

bool shift_held = false;

void td_mayusculas_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_LSFT);
        shift_held = true;
    } else {
        tap_code(KC_CAPS);
    }
}

void td_mayusculas_reset(tap_dance_state_t *state, void *user_data) {
    if (shift_held) {
        unregister_code(KC_LSFT);
        shift_held = false;
    }
}

void matrix_scan_user(void) {
    if (isWriting && timer_elapsed(last_typing_timer) > 500) {
        isWriting = false;
    }
}

#ifdef OLED_ENABLE

/* 32 * 32 logo */
static void render_logo(void) {
    static const char PROGMEM hell_logo[] = {
        0x00, 0x80, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x1c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x80,
0xe0, 0x78, 0x1e, 0x06, 0x00, 0x0c, 0x1c, 0x18, 0x30, 0x30, 0x60, 0x60, 0xc0, 0xc0, 0x80, 0x00,
0x01, 0x03, 0x07, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x70, 0x60, 0x00, 0xc0, 0xf0, 0x3c, 0x0f,
0x03, 0x00, 0x00, 0x00, 0x00, 0x60, 0x70, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x07, 0x03, 0x01,
0x00, 0xe0, 0xe0, 0x80, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x80,
0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0xe0, 0xe0, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00,
0x00, 0x1f, 0x00, 0x03, 0x0f, 0x1e, 0x1f, 0x00, 0x0c, 0x1e, 0x12, 0x1a, 0x1f, 0x00, 0x00, 0x1f,
0x00, 0x00, 0x1f, 0x1f, 0x06, 0x1f, 0x10, 0x10, 0x1f, 0x1f, 0x06, 0x1f, 0x10, 0x10, 0x1f, 0x06
    };

    oled_write_raw_P(hell_logo, sizeof(hell_logo));
}

/* 32 * 32 logo */
static void render_logo_python(void) {
    static const char PROGMEM hell_logo[] = {
        // 'images', 32x32px
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0x83, 0x99, 0xbd, 0x98, 0x80, 0x80, 0x80,
0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x60, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f,
0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x06, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
0x01, 0x01, 0x01, 0x19, 0xbd, 0x99, 0xc1, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };

    oled_write_raw_P(hell_logo, sizeof(hell_logo));
}

static void render_logo_android(void) {
    static const char PROGMEM hell_logo[] = {
// '14415', 32x32px
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x0f, 0x0e, 0x63, 0x63, 0x03, 0x03, 0x03,
0x03, 0x03, 0x03, 0x63, 0x63, 0x0e, 0x0f, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0x0f, 0x07, 0x07, 0x07, 0xff, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0xff, 0x07, 0x07, 0x07, 0x0f, 0xff, 0xff,
0xff, 0xff, 0xe0, 0xc0, 0xc0, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xe0, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0x80, 0x00, 0x00, 0x80, 0xfc,
0xfc, 0x80, 0x00, 0x00, 0x80, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };

    oled_write_raw_P(hell_logo, sizeof(hell_logo));
}


/* 32 * 14 os logos */
static const char PROGMEM linux_logo[] = {
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x1f, 0x1f,
0x1f, 0x1f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x9f, 0xe0, 0xe9, 0xec,
0xfd, 0xf1, 0xe0, 0x80, 0x1f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xdf, 0xef, 0xe1, 0xde, 0x1f, 0xbf, 0xff, 0xff,
0xff, 0xff, 0xff, 0x1f, 0xc0, 0xc0, 0xc0, 0x83, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xfb, 0xfb, 0xf8, 0xfd, 0xfd,
0xfd, 0xfc, 0xfc, 0xf8, 0xfb, 0xfb, 0xfd, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};


/* KEYBOARD PET START */

/* advanced settings */
#    define ANIM_FRAME_DURATION 200  // how long each frame lasts in ms
#    define ANIM_SIZE           96   // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

/* timers */
uint32_t anim_timer = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
led_t led_usb_state;

bool isSneaking = false;
bool isJumping  = false;
bool showedJump = true;


/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
    /* Sit */
    static const char PROGMEM sit[2][ANIM_SIZE] = {/* 'sit1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'sit2', 32x22px */
                                                   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};


    /* Run */
    static const char PROGMEM run[2][ANIM_SIZE] = {/* 'run1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'run2', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   }};

    /* Bark */
    static const char PROGMEM bark[2][ANIM_SIZE] = {/* 'bark1', 32x22px */
                                                    {
                                                        0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'bark2', 32x22px */
                                                    {
                                                        0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Sneak */
    static const char PROGMEM sneak[2][ANIM_SIZE] = {/* 'sneak1', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
                                                     },

                                                     /* 'sneak2', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                     }};

    /* animation */
    void animate_luna(void) {
        /* jump */
        if (isJumping || !showedJump) {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y + 2);
            oled_write("     ", false);
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            showedJump = true;
        } else {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            oled_write("     ", false);
            oled_set_cursor(LUNA_X, LUNA_Y);
        }
        /* switch frame */
        current_frame = (current_frame + 1) % 2;
        /* current status */
        if (led_usb_state.caps_lock) {
            oled_write_raw_P(bark[current_frame], ANIM_SIZE);
        }else if (isWriting){
            oled_write_raw_P(run[current_frame], ANIM_SIZE);
        } else if (isSneaking) {
            oled_write_raw_P(sneak[current_frame], ANIM_SIZE);
        } else if (!isWriting) {
            oled_write_raw_P(sit[current_frame], ANIM_SIZE);
        } else {
            oled_write_raw_P(run[current_frame], ANIM_SIZE);
        }
    }

#    if OLED_TIMEOUT > 0
    /* the animation prevents the normal timeout from occuring */
    if (last_input_activity_elapsed() > OLED_TIMEOUT && last_led_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return;
    } else {
        oled_on();
    }
#    endif

    /* animation timer */
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_luna();
    }
}

/* KEYBOARD PET END */

static void print_logo_narrow(void) {
    render_logo();
    oled_set_cursor(0, 5);
    render_logo_python();
    oled_set_cursor(0,10);
    render_logo_android();

}

static void print_status_narrow(void) {
    /* Print current mode */
    oled_set_cursor(0, 0);
    oled_write_raw_P(linux_logo, sizeof(linux_logo));
    oled_set_cursor(0, 5);
    /* Print current layer */
    oled_write("Layer", false);
    oled_set_cursor(0, 6);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write("BASE ", true);
            break;
        case _RAISE:
            oled_write("RAISE", true);
            break;
        case _LOWER:
            oled_write("LOWER", true);
            break;
        case _ADJUST:
            oled_write(" ADJ ", true);
            break;
        default:
            oled_write("Undef", false);
    }
    /* caps lock */
    oled_set_cursor(0, 9);
    oled_write("MAYUS", false);
    oled_set_cursor(0, 10);
    if(led_usb_state.caps_lock){
        oled_write(" ON ", true);
    }else{
        oled_write("OFF ", false);
    }
    /* KEYBOARD PET RENDER START */
    render_luna(0, 12);
    /* KEYBOARD PET RENDER END */
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

bool oled_task_user(void) {
    /* KEYBOARD PET VARIABLES START */
    led_usb_state = host_keyboard_led_state();
    /* KEYBOARD PET VARIABLES END */
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        print_logo_narrow();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /* KEYBOARD PET STATUS START */
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
            if (record->event.pressed) {
                isWriting = true;
                last_typing_timer = timer_read();
            }
            break;
        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
            break;
        case KC_SPC:
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;
        case ALT_BSPC:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_ALT) {
                    register_code(KC_DEL);  // Mantiene Delete presionado
                } else {
                    register_code(KC_BSPC);
                }
            } else {
                if (get_mods() & MOD_MASK_ALT) {
                    unregister_code(KC_DEL);  // Libera Delete cuando sueltas ALT_BSPC
                } else {
                    unregister_code(KC_BSPC);
                }
            }
            return false;
        case EMAIL1:
            if (record->event.pressed) {
                SEND_STRING(EMAIL1_STR);
            }
            return false;
        case EMAIL2:
            if (record->event.pressed) {
                SEND_STRING(EMAIL2_STR);
            }
            return false;
        case ALT_HOLD:
            if (record->event.pressed) {
                register_code(KC_LALT);   // Presiona Alt
                tap_code(KC_TAB);
            } else {
                unregister_code(KC_LALT); // Suelta Alt
            }
            return false;
        case PASS1:
            if (record->event.pressed) {
                SEND_STRING(PASS1_STR);
            }
            return false;
        case PASS2:
            if (record->event.pressed) {
                SEND_STRING(PASS2_STR);
            }
            return false;
            /* KEYBOARD PET STATUS END */
    }
    return true;
}

#endif
