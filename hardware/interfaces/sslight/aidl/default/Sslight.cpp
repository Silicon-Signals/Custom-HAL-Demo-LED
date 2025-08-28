#include <utils/Log.h>
#include <iostream>
#include <fstream>
#include "Sslight.h"

namespace aidl {
namespace android {
namespace hardware {
namespace sslight {

#define TAG "SSLightHAL"

// LED values as macros
#define LED_HIGH_VALUE  "1"
#define LED_LOW_VALUE "0"

ndk::ScopedAStatus Sslight::ledControl(int32_t in_state, int32_t* _aidl_return) {
    constexpr char LED_FILE_PATH[] = "/sys/class/leds/sslight/brightness";

    int fd = open(LED_FILE_PATH, O_WRONLY);
    if (fd < 0) {
        ALOGE("%s: Failed to open LED node %s", TAG, LED_FILE_PATH);
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    } else {
        ALOGI("%s: LED node %s opened successfully", TAG, LED_FILE_PATH);
    }

    int ret = 0;
    if (in_state > 0) {
        ret = write(fd, LED_HIGH_VALUE, sizeof(LED_HIGH_VALUE) - 1); // Write "HIGH" (LED ON)
    } else {
        ret = write(fd, LED_LOW_VALUE, sizeof(LED_LOW_VALUE) - 1); // Write "LOW" (LED OFF)
    }

    close(fd);

    if (ret < 0) {
        ALOGE("%s: Write operation failed for LED node: %s", TAG, LED_FILE_PATH);
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    }

    *_aidl_return = true;
    return ndk::ScopedAStatus::ok();
}

}  // namespace sslight
}  // namespace hardware
}  // namespace android
}
