#include <jni.h>
#include <string>
#include "DrawingEngine.h"

// Khởi tạo Engine
DrawingEngine* engine = new DrawingEngine();

extern "C" JNIEXPORT void JNICALL
Java_com_example_drawapp_CanvasView_nativeSurfaceCreated(JNIEnv* env, jobject /* this */) {
    engine->onSurfaceCreated();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_drawapp_CanvasView_nativeSurfaceChanged(JNIEnv* env, jobject /* this */, jint width, jint height) {
    engine->onSurfaceChanged(width, height);
}

// Lưu ý: Tôi thêm hàm Render này để gọi từ onDrawFrame của Kotlin
extern "C" JNIEXPORT void JNICALL
Java_com_example_drawapp_CanvasView_nativeRender(JNIEnv* env, jobject /* this */) {
    engine->render();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_drawapp_CanvasView_nativeOnTouch(JNIEnv* env, jobject /* this */, jint action, jfloat x, jfloat y) {
    switch (action) {
        case 0: engine->onTouchDown(x, y); break; // DOWN
        case 1: engine->onTouchUp(); break;       // UP
        case 2: engine->onTouchMove(x, y); break; // MOVE
    }
}