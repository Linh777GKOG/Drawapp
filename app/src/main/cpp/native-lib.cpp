#include <jni.h>
#include "DrawingEngine.h"

DrawingEngine* engine = new DrawingEngine();

extern "C" JNIEXPORT void JNICALL
Java_com_example_drawapp_CanvasView_nativeSurfaceCreated(JNIEnv* env, jobject /* this */) {
    engine->onSurfaceCreated();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_drawapp_CanvasView_nativeSurfaceChanged(JNIEnv* env, jobject /* this */, jint width, jint height) {
    engine->onSurfaceChanged(width, height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_drawapp_CanvasView_nativeRender(JNIEnv* env, jobject /* this */) {
    engine->render();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_drawapp_CanvasView_nativeOnTouch(JNIEnv* env, jobject /* this */, jint action, jfloat x, jfloat y) {
    // action: 0 = DOWN, 1 = UP, 2 = MOVE
    switch (action) {
        case 0: engine->onTouchDown(x, y); break;
        case 1: engine->onTouchUp(); break;
        case 2: engine->onTouchMove(x, y); break;
    }
}