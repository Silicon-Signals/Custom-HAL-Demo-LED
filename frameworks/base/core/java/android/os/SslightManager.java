package android.os;

import android.annotation.Nullable;
import android.annotation.SystemApi;
import android.annotation.SystemService;
import android.app.ActivityThread;
import android.content.Context;
import android.os.Handler;
import android.os.IBinder;
import android.os.ISslightService;
import android.os.Message;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.util.Log;

import java.util.HashSet;
import java.util.Set;

@SystemService(Context.SSLIGHT_SERVICE)
public class SslightManager {

    private static final String TAG = "SslightManager";

    /** Error code returned when LED control operation fails */
    public static final int LED_CONTROL_FAILED = -1;

    private final Context mContext;
    private ISslightService mSslightService = null;

    /** {@hide} **/
    public SslightManager(Context context) {
        this.mContext = context;
    }

    private ISslightService getService() {
        if (mSslightService != null) {
            return mSslightService;
        }
        try {
            IBinder binder = ServiceManager.getService(Context.SSLIGHT_SERVICE);
            mSslightService = ISslightService.Stub.asInterface(binder);
            Log.d(TAG, "Successfully connected to SSLight service");
        } catch (Exception e) {
            Log.e(TAG, "Failed to connect to SSLight service", e);
        }
        return mSslightService;
    }

    public int ledControl(int state) {
        try {
            return getService().ledControl(state);
        } catch (Exception e) {
            Log.e(TAG, "LED control operation failed (state=" + state + ")", e);
        }
        return LED_CONTROL_FAILED;
    }
}
