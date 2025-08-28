package com.android.server;

import android.content.Context;
import android.os.ISslightService;
import android.os.RemoteException;
import android.util.Log;

public class SslightService extends ISslightService.Stub {

    private static final String TAG = "SslightService";

    public SslightService(Context context) {
        // Context can be stored if needed later
    }

    /** Calls native code to perform Sslight hardware service control */
    @Override
    public int ledControl(int state) throws RemoteException {
        Log.i(TAG, "Processing LED control request with state=" + state);
        return native_ledCtrl(state);
    }

    private static native int native_ledCtrl(int state);
}
