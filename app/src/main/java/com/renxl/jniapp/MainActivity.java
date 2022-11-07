package com.renxl.jniapp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        JniUtils jniUtils = new JniUtils();

        TextView hello = findViewById(R.id.hello);
        hello.setText(JniUtils.getJniString());

        TextView accessField = findViewById(R.id.access_field);
        String s = jniUtils.accessField();
        accessField.setText(s);

        TextView accessStaticField = findViewById(R.id.access_static_field);
        JniUtils.accessStaticField();
        accessStaticField.setText("修改后的值：" + JniUtils.accessedStaticIntField);

        TextView accessMethod = findViewById(R.id.access_method);
        String s1 = jniUtils.accessMethod();
        accessMethod.setText(s1);

        TextView accessStaticMethod = findViewById(R.id.access_static_method);
        String s2 = JniUtils.accessStaticMethod();
        accessStaticMethod.setText(s2);

        TextView accessParentMethod = findViewById(R.id.access_parent_method);
        try {
            String s3 = jniUtils.accessParentMethod();
            accessParentMethod.setText(s3);
        } catch (Error e) {
            Log.i("Error", "catch 到了 Error");
        } catch (Throwable throwable) {
            Log.i("Throwable", "catch 到了 Throwable");
        }
    }
}
