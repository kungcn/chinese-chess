package com.ceres.hao.chinesechess;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class GameActivity extends AppCompatActivity {

    TextView opponentName;
    TextView timeLeft;
    TextView status;
    Button surrender;

    private void findViews() {
        opponentName = (TextView)findViewById(R.id.opponentName);
        timeLeft = (TextView)findViewById(R.id.timeLeft);
        status = (TextView)findViewById(R.id.status);
        surrender = (Button)findViewById(R.id.surrender);
    }

    private void bindViews() {
        surrender.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {


            }
        });
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);
    }
}
