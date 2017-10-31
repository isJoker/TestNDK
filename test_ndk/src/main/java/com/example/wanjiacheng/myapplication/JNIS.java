package com.example.wanjiacheng.myapplication;

import android.content.Context;
import android.widget.Toast;

/**
 * Created by ${JokerWan} on 2017/10/30.
 * WeChat: wjc398556712
 * Function:
 */

public class JNIS {

    private Context mContext;

    public JNIS(Context context) {
        this.mContext = context;
    }

    public JNIS() {
    }

    static {
        System.loadLibrary("HelloJni");
    }

    public native String helloJNI();

    public native String sayHello(String s);

    public native int[] increaseArrayEles(int[] intArray);

    public native void callbackShowToast();

    public void showToast(){
        Toast.makeText(mContext, "C调用Java更新UI", Toast.LENGTH_SHORT).show();
    }
}
