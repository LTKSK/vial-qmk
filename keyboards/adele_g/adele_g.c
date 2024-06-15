#include "quantum.h"
#include "ltjoy.h"
#include "custom_joystick.h"

typedef union {
  uint32_t raw;

  struct {
    // int16_t to_clickable_time; // // この秒数(千分の一秒)、WAITING状態ならクリックレイヤーが有効になる。  For this number of seconds (milliseconds), if in WAITING state, the click layer is activated.
    int16_t joystick_ratio;
  };
} user_config_t;

user_config_t user_config;

const uint16_t click_layer = 8;   // マウス入力が可能になった際に有効になるレイヤー。Layers enabled when mouse input is enabled

void eeconfig_init_kb(void) {
    user_config.raw = 0;
    user_config.joystick_ratio = 170;

    eeconfig_update_kb(user_config.raw);
}

void keyboard_post_init_kb(void) {
    user_config.raw = eeconfig_read_kb();
    joystick_ratio = user_config.joystick_ratio;
}

layer_state_t layer_state_set_user(layer_state_t state){
    // 8がマウスレイヤー
    if (layer_state_cmp(state, click_layer)) {
        // マウスレイヤーに入ったら速度を下げる。クリックの直前とかで押す想定
        joystick_ratio = 170;
        user_config.joystick_ratio = joystick_ratio;
        eeconfig_update_kb(user_config.raw);
    } else {
        // 他のレイヤーにいるときは速度を上げる
        joystick_ratio = 170;
        user_config.joystick_ratio = joystick_ratio;
        eeconfig_update_kb(user_config.raw);
    }
    return state;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    return process_record_user(keycode, record);
}


report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    return mouse_report;
}