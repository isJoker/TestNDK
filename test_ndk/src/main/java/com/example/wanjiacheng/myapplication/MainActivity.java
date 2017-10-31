package com.example.wanjiacheng.myapplication;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        JNIS jnis = new JNIS(this);
        String s = jnis.helloJNI();
        Log.e("TAG", "-------->    "+s);

        String s1 = jnis.sayHello("hahahaha");
        Log.e("TAG",  s1);

        int[] increaseArray = jnis.increaseArrayEles(new int[]{10, 20, 30});
        for (int i : increaseArray) {
            Log.e("TAG", i+"");
        }

        jnis.callbackShowToast();
    }
}
