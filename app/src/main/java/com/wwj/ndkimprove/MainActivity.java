package com.wwj.ndkimprove;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.wwj.ndkimprove.bean.JniOperateBean;

/**
 * @author WWJ
 * @detail:
 * @date: 2023/11/1 15:23
 */
public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivityNDK";

    static {
        System.loadLibrary("ndkimprove");
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView stringFromJniTv = findViewById(R.id.tv_from_jni);
        stringFromJniTv.setText(stringFromJni());

        String stringFromDimaLoad = JniInterfaceUtil.getsInstance().getString();
        Log.d(TAG, "stringFromDimaLoad： " + stringFromDimaLoad);

        // jni操作对象中的属性：
        JniOperateBean jniOperateBean = new JniOperateBean();
        int numPlusOne = jniOperateBean.getNumPlusOne();
        Log.d(TAG, "操作后的属性： " + numPlusOne);

        Log.d(TAG, "操作前静态name： " + JniOperateBean.name);
        jniOperateBean.operatorStaticName();
        Log.d(TAG, "操作后静态name： " + JniOperateBean.name);

        jniOperateBean.accessPrivateNum();
        Log.d(TAG, "设置私有属性后的值： " + jniOperateBean.getNum());

        String output = jniOperateBean.accessPrivateMethod();
        Log.d(TAG, "调用object方法： " + output);
    }

    /**
     * 调用jni中的获取
     *
     * @return jni方法中处理的字符串
     */
    private native String stringFromJni();
}
