#define LOG_TAG "LedService"

#include <aidl/android/hardware/sslight/ISslight.h>
#include <android/binder_interface_utils.h>
#include <android/binder_manager.h>
#include <android-base/chrono_utils.h>
#include <android/log.h>
#include <binder/IBinder.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <jni.h>
#include "android_runtime/AndroidRuntime.h"
#include <nativehelper/JNIHelp.h>
#include <stdio.h>
#include <utils/Log.h>
#include <utils/misc.h>

namespace android {

using aidl::android::hardware::sslight::ISslight;
using namespace std;

// Shared pointer for HAL interface
static std::shared_ptr<ISslight> ssHal = nullptr;

static int native_ledCtrl(JNIEnv *env, jobject /*obj*/, jint state) {
    int status = 0;

    const std::string sslightInstance = std::string() + ISslight::descriptor + "/default";

    // Get HAL service instance
    std::shared_ptr<ISslight> ssHal = ISslight::fromBinder(
        ndk::SpAIBinder(AServiceManager_waitForService(sslightInstance.c_str()))
    );

    if (ssHal != nullptr) {
        ssHal->ledControl(state, &status);
        __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG,
                            "LED control state sent to SSLight HAL Service (state=%d, status=%d)", state, status);
    } else {
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG,
                            "Failed to acquire SSLight HAL Service instance");
    }

    return status;
}

// JNI method registration
static const JNINativeMethod methods[] = {
    {"native_ledCtrl", "(I)I", (void*)native_ledCtrl},
};

int register_android_server_SslightService(JNIEnv *env) {
    return jniRegisterNativeMethods(env, "com/android/server/SslightService",
                                    methods, NELEM(methods));
}

} // namespace android
