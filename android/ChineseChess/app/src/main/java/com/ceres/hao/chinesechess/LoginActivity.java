package com.ceres.hao.chinesechess;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class LoginActivity extends AppCompatActivity {

    Button loginButton;
    EditText username;
    SharedPreferences mSharedPreferences;
    SharedPreferences.Editor mEditor;

    private void findViews() {
        loginButton = (Button)findViewById(R.id.loginButton);
        username = (EditText)findViewById(R.id.username);
        mSharedPreferences = getSharedPreferences("UserData", Context.MODE_PRIVATE);
        mEditor = mSharedPreferences.edit();

    }

    private void bindViews() {
        loginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mEditor.putString("USERNAME", username.getText().toString());
                Intent intent = new Intent();
                intent.setClass(LoginActivity.this, LobbyActivity.class);
                startActivity(intent);
            }
        });
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
    }
}
