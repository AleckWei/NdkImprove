package com.wwj.ndkimprove;

import android.os.Bundle;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

/**
 * @author WWJ
 * @detail:
 * @date: 2023/11/1 15:23
 */
public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    static {
        System.loadLibrary("ndkimprove");
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView stringFromJniTv = findViewById(R.id.tv_from_jni);
        stringFromJniTv.setText(stringFromJni());
    }

    /**
     * 调用jni中的获取
     *
     * @return jni方法中处理的字符串
     */
    private native String stringFromJni();
}
