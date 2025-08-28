#define LOG_TAG "Sslight_HalService"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include "Sslight.h"

using aidl::android::hardware::sslight::Sslight;
using std::string_literals::operator""s;

int main() {

    // Set up binder thread pool
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    ABinderProcess_startThreadPool();

    // Create SSLight service instance
    std::shared_ptr<Sslight> sslight = ndk::SharedRefBase::make<Sslight>();
    const std::string name = Sslight::descriptor + "/default"s;

    // Register service with binder
    if (sslight != nullptr) {
        if(AServiceManager_addService(sslight->asBinder().get(), name.c_str()) != STATUS_OK) {
            ALOGE("%s: Service registration failed", LOG_TAG);
            return EXIT_FAILURE;
        }
    } else {
        ALOGE("%s: ISslight instance not available", LOG_TAG);
        return EXIT_FAILURE;
    }

    ALOGE("%s: Service registered successfully, joining binder service pool", LOG_TAG);
    ABinderProcess_joinThreadPool();

    return EXIT_FAILURE;  // should not reached
}
