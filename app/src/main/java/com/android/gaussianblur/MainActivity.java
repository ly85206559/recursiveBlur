package com.android.gaussianblur;

import android.databinding.DataBindingUtil;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.SeekBar;

import com.android.gaussianblur.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity implements SeekBar.OnSeekBarChangeListener {

    private static final String TAG = MainActivity.class.getName();

    private ActivityMainBinding mBinding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mBinding = DataBindingUtil.setContentView(this, R.layout.activity_main);

        mBinding.seekBar.setOnSeekBarChangeListener(this);
    }

    @Override
    protected void onDestroy() {
        mBinding.unbind();
        super.onDestroy();
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        if (progress < 1) {
            progress = 1;
        }

        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inPreferredConfig = Bitmap.Config.ARGB_8888;
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.test, options);
        Bitmap img;
        long time = System.currentTimeMillis();
        long costTime = 0;
        img = GaussianBlur.recursiveBlurNatively(bitmap, progress, false);
        costTime = System.currentTimeMillis() - time;
        Log.d(TAG, "RecursiveBlur 耗时:" + costTime);
        mBinding.tvRecursiveTime.setText("耗时：" + costTime);
        mBinding.ivOtherBlur.setImageBitmap(img);

        time = System.currentTimeMillis();
        img = GaussianBlur.gaussBlurNatively(
                bitmap, progress, false);
        costTime = System.currentTimeMillis() - time;
        Log.d(TAG, "GaussianBlur 耗时:" + costTime);
        mBinding.tvGaussTime.setText("耗时：" + costTime);
        mBinding.ivBlur.setImageBitmap(img);

        mBinding.tvRadius.setText(String.valueOf(progress));
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {

    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {

    }
}
