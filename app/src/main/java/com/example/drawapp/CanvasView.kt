package com.example.drawapp

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.view.MotionEvent
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class CanvasView(context: Context, attrs: AttributeSet) : GLSurfaceView(context, attrs), GLSurfaceView.Renderer {

    init {
        setEGLContextClientVersion(2)
        setRenderer(this)

        // Rất quan trọng: Báo cho Android biết chúng ta chỉ vẽ lại màn hình khi cần thiết (giúp tiết kiệm pin)
        renderMode = RENDERMODE_WHEN_DIRTY
    }

    external fun nativeSurfaceCreated()
    external fun nativeSurfaceChanged(width: Int, height: Int)
    external fun nativeRender()

    // Thêm hàm này
    external fun nativeOnTouch(action: Int, x: Float, y: Float)

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        nativeSurfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        nativeSurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        nativeRender()
    }

    // Thêm khối xử lý cảm ứng này
    override fun onTouchEvent(event: MotionEvent): Boolean {
        // Chuyển đổi action của Android thành số nguyên đơn giản cho C++ (0: Chạm, 1: Nhấc, 2: Di chuyển)
        val action = when (event.actionMasked) {
            MotionEvent.ACTION_DOWN -> 0
            MotionEvent.ACTION_UP -> 1
            MotionEvent.ACTION_MOVE -> 2
            else -> -1
        }

        if (action != -1) {
            // Đẩy ngay lập tức tọa độ X, Y xuống C++
            nativeOnTouch(action, event.x, event.y)

            // Ra lệnh cho GPU vẽ lại khung hình mới ngay lập tức
            requestRender()
        }
        return true
    }

    companion object {
        init {
            System.loadLibrary("drawapp")
        }
    }
}