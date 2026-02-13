package com.example.drawapp // Đã sửa đúng package

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.view.MotionEvent
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class CanvasView(context: Context, attrs: AttributeSet) : GLSurfaceView(context, attrs), GLSurfaceView.Renderer {

    init {
        // Cấu hình OpenGL ES 2.0
        setEGLContextClientVersion(2)
        setRenderer(this)
        // Chỉ vẽ lại khi có lệnh (tiết kiệm pin), thay vì vẽ liên tục
        renderMode = RENDERMODE_WHEN_DIRTY
    }

    // --- Khai báo hàm JNI khớp với native-lib.cpp ---
    external fun nativeSurfaceCreated()
    external fun nativeSurfaceChanged(width: Int, height: Int)
    external fun nativeRender()
    external fun nativeOnTouch(action: Int, x: Float, y: Float)

    // --- GLSurfaceView.Renderer Implementation ---
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        nativeSurfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        nativeSurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        nativeRender()
    }

    // --- Xử lý cảm ứng ---
    override fun onTouchEvent(event: MotionEvent): Boolean {
        // Gửi tọa độ xuống C++
        nativeOnTouch(event.actionMasked, event.x, event.y)

        // Yêu cầu vẽ lại màn hình ngay lập tức
        requestRender()
        return true
    }

    companion object {
        init {
            // Load thư viện tên "drawapp" khớp với CMakeLists
            System.loadLibrary("drawapp")
        }
    }
}