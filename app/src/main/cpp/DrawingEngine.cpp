#include "DrawingEngine.h"

DrawingEngine::DrawingEngine() {}

DrawingEngine::~DrawingEngine() {}

GLuint DrawingEngine::loadShader(GLenum type, const char* shaderCode) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    return shader;
}

void DrawingEngine::onSurfaceCreated() {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderCode);
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    vPositionHandle = glGetAttribLocation(program, "vPosition");
    LOGI("OpenGL initialized");
}

void DrawingEngine::onSurfaceChanged(int width, int height) {
    viewportWidth = width;
    viewportHeight = height;
    glViewport(0, 0, width, height);
}

Point DrawingEngine::normalize(float x, float y) {
    // Chuyển từ tọa độ Screen (0 -> Width) sang OpenGL (-1 -> 1)
    float nx = (x / viewportWidth) * 2.0f - 1.0f;
    float ny = -((y / viewportHeight) * 2.0f - 1.0f); // Đảo trục Y
    return {nx, ny};
}

void DrawingEngine::onTouchDown(float x, float y) {
    currentStroke.clear();
    currentStroke.push_back(normalize(x, y));
}

void DrawingEngine::onTouchMove(float x, float y) {
    currentStroke.push_back(normalize(x, y));
}

void DrawingEngine::onTouchUp() {
    allStrokes.push_back(currentStroke);
    currentStroke.clear();
}

void DrawingEngine::render() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Nền trắng
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glEnableVertexAttribArray(vPositionHandle);

    // Vẽ các nét vẽ cũ
    for (const auto& stroke : allStrokes) {
        if (stroke.size() < 2) continue;
        glVertexAttribPointer(vPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, stroke.data());
        glDrawArrays(GL_LINE_STRIP, 0, stroke.size());
    }

    // Vẽ nét vẽ hiện tại
    if (currentStroke.size() >= 2) {
        glVertexAttribPointer(vPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, currentStroke.data());
        glDrawArrays(GL_LINE_STRIP, 0, currentStroke.size());
    }

    glDisableVertexAttribArray(vPositionHandle);
}