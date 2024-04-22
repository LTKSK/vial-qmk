#include "quantum.h"
#include "adele_s.h"

// ハードウェアに関する設定はここ。今回はcpiの設定をしている
void pointing_device_init_kb(void) {
    pointing_device_set_cpi(500);
}