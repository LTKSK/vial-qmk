#include "quantum.h"
#include <math.h>
#include "adele_t.h"
#include "wait.h"// keyboardレイヤでのinitialize

// ハードウェアに関する設定はここ。今回はcpiの設定をしている
void pointing_device_init_kb(void) {
    pointing_device_set_cpi(500);
}