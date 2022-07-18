package uk.lgl.modmenu;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Align;
import android.graphics.Paint.Style;
import android.graphics.PorterDuff;
import android.graphics.PorterDuff.Mode;
import android.os.Process;
import android.util.Log;
import android.view.View;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

import uk.lgl.modmenu.FloatingModMenuService;

public class NepEsp extends View implements Runnable {
        Paint mStrokePaint;
        Paint mFilledPaint;
        Paint mTextPaint;
        Thread mThread;
        int FPS = 60;
        long sleepTime;
        Date time;
        SimpleDateFormat formatter;


        public NepEsp(Context context) {
                super(context, null, 0);
                InitializePaints();
                setFocusableInTouchMode(false);
                setBackgroundColor(Color.TRANSPARENT);
                time = new Date();
                formatter = new SimpleDateFormat("HH:mm:ss", Locale.getDefault());
                sleepTime = 1000 / FPS;
                mThread = new Thread(this);
                mThread.start();
            }

        @Override
        protected void onDraw(Canvas canvas) {
                if (canvas != null && getVisibility() == VISIBLE) {
                        ClearCanvas(canvas);
                        time.setTime(System.currentTimeMillis());
                        FloatingModMenuService.DrawOn(this, canvas);
                    }
            }

        @Override
        public void run() {
                android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_BACKGROUND);
                while (mThread.isAlive() && !mThread.isInterrupted()) {
                        try {
                                long t1 = System.currentTimeMillis();
                                postInvalidate();
                                long td = System.currentTimeMillis() - t1;
                                Thread.sleep(Math.max(Math.min(0, sleepTime - td), sleepTime));
                            } catch (InterruptedException it) {
                                Log.e("OverlayThread", it.getMessage());
                            }
                    }
            }

        public void InitializePaints() {
                mStrokePaint = new Paint();
                mStrokePaint.setStyle(Paint.Style.STROKE);
                mStrokePaint.setAntiAlias(true);
                mStrokePaint.setColor(Color.rgb(0, 0, 0));

                mFilledPaint = new Paint();
                mFilledPaint.setStyle(Paint.Style.FILL);
                mFilledPaint.setAntiAlias(true);
                mFilledPaint.setColor(Color.rgb(0, 0, 0));

                mTextPaint = new Paint();
                mTextPaint.setStyle(Paint.Style.FILL_AND_STROKE);
                mTextPaint.setAntiAlias(true);
                mTextPaint.setColor(Color.rgb(0, 0, 0));
                mTextPaint.setTextAlign(Paint.Align.CENTER);
                mTextPaint.setStrokeWidth(1.1f);
            }

        public void ClearCanvas(Canvas cvs) {
                cvs.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR);
            }

        public void DrawLine(Canvas cvs, int a, int r, int g, int b, float lineWidth, float fromX, float fromY, float toX, float toY) {
                mStrokePaint.setColor(Color.rgb(r, g, b));
                mStrokePaint.setAlpha(a);
                mStrokePaint.setStrokeWidth(lineWidth);
                cvs.drawLine(fromX, fromY, toX, toY, mStrokePaint);
            }

        public void DrawText(Canvas cvs, int a, int r, int g, int b, String txt, float posX, float posY, float size) {
                mTextPaint.setColor(Color.rgb(r, g, b));
                mTextPaint.setAlpha(a);

                if (getRight() > 1920 || getBottom() > 1920)
                    mTextPaint.setTextSize(4 + size);
                else if (getRight() == 1920 || getBottom() == 1920)
                    mTextPaint.setTextSize(2 + size);
                else
                    mTextPaint.setTextSize(size);
                cvs.drawText(txt, posX, posY, mTextPaint);
            }

        public void DrawCircle(Canvas cvs, int a, int r, int g, int b, float stroke, float posX, float posY, float radius) {
                mStrokePaint.setColor(Color.rgb(r, g, b));
                mStrokePaint.setAlpha(a);
                mStrokePaint.setStrokeWidth(stroke);
                cvs.drawCircle(posX, posY, radius, mStrokePaint);
            }

        public void DrawFilledCircle(Canvas cvs, int a, int r, int g, int b, float posX, float posY, float radius) {
                mFilledPaint.setColor(Color.rgb(r, g, b));
                mFilledPaint.setAlpha(a);
                cvs.drawCircle(posX, posY, radius, mFilledPaint);
            }

        public void DrawRect(Canvas cvs, int a, int r, int g, int b, int stroke, float x, float y, float width, float height) {
                mStrokePaint.setStrokeWidth(stroke);
                mStrokePaint.setColor(Color.rgb(r, g, b));
                mStrokePaint.setAlpha(a);
                cvs.drawRect(x, y, x + width, y + height, mStrokePaint);
            }

        public void DrawFilledRect(Canvas cvs, int a, int r, int g, int b, float x, float y, float width, float height) {
                mFilledPaint.setColor(Color.rgb(r, g, b));
                mFilledPaint.setAlpha(a);
                cvs.drawRect(x, y, x + width, y + height, mFilledPaint);
            }
    }
