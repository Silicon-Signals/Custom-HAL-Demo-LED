#pragma once

#include <aidl/android/hardware/sslight/BnSslight.h>

namespace aidl {
namespace android {
namespace hardware {
namespace sslight {

class Sslight : public BnSslight {
    public:
        ndk::ScopedAStatus ledControl(int32_t in_state, int32_t* _aidl_return);
};

}  // namespace sslight
}  // namespace hardware
}  // namespace android
}  // namespace aidl
