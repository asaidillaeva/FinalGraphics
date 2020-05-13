package com.example.finalgrapgics3;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.EditText;
import android.widget.Button;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

public class MainActivity extends Activity {
    ImageView moveUp;
    ImageView moveDown;
    ImageView moveRight;
    ImageView moveLeft;
    ImageView heart1;
    ImageView heart2;
    ImageView smile;
    ImageView smile2;
    ImageView sound;
    BluetoothAdapter mBluetoothAdapter;
    BluetoothSocket mmSocket;
    BluetoothDevice mmDevice;
    OutputStream mmOutputStream;
    InputStream mmInputStream;
    Thread workerThread;
    byte[] readBuffer;
    int readBufferPosition;
    volatile boolean stopWorker;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initViews();
        initOnCkicks();
        try {
            findBT();
            openBT();
        }
        catch (IOException ex) { }


    }

    private void initOnCkicks() {
        moveUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    String message = "Going to Forward";
                    sendData(message);
                }
                catch (IOException ex) {
                    showMessage("SEND FAILED");
                }
            }
        });
        moveDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    String message = "Going to Back";
                    sendData(message);
                }
                catch (IOException ex) {
                    showMessage("SEND FAILED");
                }
            }
        });
        moveRight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    String message = "Going to Right";
                    sendData(message);
                }
                catch (IOException ex) {
                    showMessage("SEND FAILED");
                }
            }
        });
        moveLeft.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    String message = "Going to Left";
                    sendData(message);
                }
                catch (IOException ex) {
                    showMessage("SEND FAILED");
                }
            }
        });
        heart1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    String message = "Hello I am Romo";
                    sendData(message);
                }
                catch (IOException ex) {
                    showMessage("SEND FAILED");
                }
            }
        });
        heart2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    String message = "I am a Pet Robot";
                    sendData(message);
                }
                catch (IOException ex) {
                    showMessage("SEND FAILED");
                }
            }
        });
        smile.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    String message = "Pls! Connect Me";
                    sendData(message);
                }
                catch (IOException ex) {
                    showMessage("SEND FAILED");
                }
            }
        });
        smile2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    String message = "Feeling Relax";
                    sendData(message);
                }
                catch (IOException ex) {
                    showMessage("SEND FAILED");
                }
            }
        });
        sound.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    String message = "Music Time";
                    sendData(message);
                }
                catch (IOException ex) {
                    showMessage("SEND FAILED");
                }
            }
        });
    }

    private void initViews() {
        moveUp = findViewById(R.id.moveUp);
        moveDown = findViewById(R.id.moveDown);
        moveRight = findViewById(R.id.moveRight);
        moveLeft = findViewById(R.id.moveLeft);
        heart1 = findViewById(R.id.heart1);
        heart2 = findViewById(R.id.heart2);
        smile = findViewById(R.id.smile);
        smile2 = findViewById(R.id.smile2);
        sound = findViewById(R.id.sound);
    }

    void findBT() {
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if(mBluetoothAdapter == null) {
            showMessage("No bluetooth adapter available");

        }

        if(!mBluetoothAdapter.isEnabled()) {
            Intent enableBluetooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBluetooth, 0);
        }

        Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
        if(pairedDevices.size() > 0) {
            for(BluetoothDevice device : pairedDevices) {
                if(device.getName().equals("FireFly-108B")) {
                    mmDevice = device;
                    break;
                }
            }
        }
        showMessage("Bluetooth Device Found");

    }

    void openBT() throws IOException {
        UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");
        mmSocket = mmDevice.createRfcommSocketToServiceRecord(uuid);
        mmSocket.connect();
        mmOutputStream = mmSocket.getOutputStream();
        mmInputStream = mmSocket.getInputStream();
        beginListenForData();
        showMessage("Bluetooth Opened");

    }

    void beginListenForData() {
        final Handler handler = new Handler();
        final byte delimiter = 10; //This is the ASCII code for a newline character

        stopWorker = false;
        readBufferPosition = 0;
        readBuffer = new byte[1024];
        workerThread = new Thread(new Runnable() {
            public void run() {
                while(!Thread.currentThread().isInterrupted() && !stopWorker) {
                    try {
                        int bytesAvailable = mmInputStream.available();
                        if(bytesAvailable > 0) {
                            byte[] packetBytes = new byte[bytesAvailable];
                            mmInputStream.read(packetBytes);
                            for(int i=0;i<bytesAvailable;i++) {
                                byte b = packetBytes[i];
                                if(b == delimiter) {
                                    byte[] encodedBytes = new byte[readBufferPosition];
                                    System.arraycopy(readBuffer, 0, encodedBytes, 0, encodedBytes.length);
                                    final String data = new String(encodedBytes, "US-ASCII");
                                    readBufferPosition = 0;

                                    handler.post(new Runnable() {
                                        public void run() {
                                            showMessage(data);

                                        }
                                    });
                                }
                                else {
                                    readBuffer[readBufferPosition++] = b;
                                }
                            }
                        }
                    }
                    catch (IOException ex) {
                        stopWorker = true;
                    }
                }
            }
        });

        workerThread.start();
    }

    void sendData(String msg) throws IOException {
        mmOutputStream.write(msg.getBytes());
//        mmOutputStream.write('A');
        showMessage("Data Sent");

    }

//    void closeBT() throws IOException {
//        stopWorker = true;
//        mmOutputStream.close();
//        mmInputStream.close();
//        mmSocket.close();
//        showMessage("Bluetooth Closed");
//    }

    private void showMessage(String theMsg) {
        Toast msg = Toast.makeText(getBaseContext(),
                theMsg, (Toast.LENGTH_LONG)/160);
        msg.show();
    }
}

