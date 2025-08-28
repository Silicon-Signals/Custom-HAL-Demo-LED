package com.android.ledcontrol;

import android.content.Context;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import android.os.ServiceManager;
import android.os.SslightManager;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "Sslight_apk";
    private static final int LED_HIGH = 1;
    private static final int LED_LOW = 0;

    private SslightManager mManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mManager = (SslightManager) getSystemService(Context.SSLIGHT_SERVICE);
        if (mManager == null) {
            Log.e(TAG, "Error: SslightManager service is null");
            Toast.makeText(this, "LED service not available", Toast.LENGTH_SHORT).show();
            return;
        }

        Button buttonOn = findViewById(R.id.buttonOn);
        Button buttonOff = findViewById(R.id.buttonOff);

        buttonOn.setOnClickListener(v -> {
            Log.i(TAG, "LED Turning ON");
            turnOnLED();
            Toast.makeText(MainActivity.this, "LED ON", Toast.LENGTH_SHORT).show();
        });

        buttonOff.setOnClickListener(v -> {
            Log.i(TAG, "LED Turning OFF");
            turnOffLED();
            Toast.makeText(MainActivity.this, "LED OFF", Toast.LENGTH_SHORT).show();
        });
    }

    private void turnOnLED() {
        if (mManager != null) mManager.ledControl(LED_HIGH);
    }

    private void turnOffLED() {
        if (mManager != null) mManager.ledControl(LED_LOW);
    }
}
