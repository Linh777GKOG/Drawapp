#ifndef DRAWING_ENGINE_H
#define DRAWING_ENGINE_H

#include <vector>
#include <android/log.h>
#include <GLES2/gl2.h>

#define LOG_TAG "CppEngine"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

struct Point {
    float x, y;
};

class DrawingEngine {
public:
    DrawingEngine();
    ~DrawingEngine();

    void onSurfaceCreated();
    void onSurfaceChanged(int width, int height);
    void onTouchDown(float x, float y);
    void onTouchMove(float x, float y);
    void onTouchUp();
    void render();

private:
    int viewportWidth = 0;
    int viewportHeight = 0;

    std::vector<Point> currentStroke;
    std::vector<std::vector<Point>> allStrokes;

    GLuint program;
    GLuint vPositionHandle;

    // Shader code đơn giản
    const char* vertexShaderCode =
        "attribute vec4 vPosition;"
        "void main() {"
        "  gl_Position = vPosition;"
        "}";

    const char* fragmentShaderCode =
        "precision mediump float;"
        "void main() {"
        "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);" // Màu đỏ
        "}";

    GLuint loadShader(GLenum type, const char* shaderCode);
    Point normalize(float x, float y);
};

#endif //DRAWING_ENGINE_H