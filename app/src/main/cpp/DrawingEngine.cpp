#include "DrawingEngine.h"

// Shader tính toán tọa độ (Vertex)
const char* vertexShaderCode =
        "attribute vec4 vPosition;"
        "void main() {"
        "  gl_Position = vPosition;"
        "}";

// Shader tô màu (Fragment) - Ở đây đang set màu Cam (Đỏ 1.0, Xanh lá 0.5, Xanh dương 0.0)
const char* fragmentShaderCode =
        "precision mediump float;"
        "void main() {"
        "  gl_FragColor = vec4(1.0, 0.5, 0.0, 1.0);"
        "}";

DrawingEngine::DrawingEngine() : screenWidth(0), screenHeight(0), shaderProgram(0) {}
DrawingEngine::~DrawingEngine() {}

GLuint DrawingEngine::loadShader(GLenum type, const char *shaderCode) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    return shader;
}

void DrawingEngine::onSurfaceCreated() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Nền xám đen

    // Biên dịch và khởi tạo Shader
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderCode);
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
}

void DrawingEngine::onSurfaceChanged(int width, int height) {
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, width, height);
}

// Khi vừa chạm ngón tay xuống màn hình
void DrawingEngine::onTouchDown(float x, float y) {
    lineVertices.clear(); // Xóa nét cũ đi để vẽ nét mới
    onTouchMove(x, y);
}

// Khi lướt ngón tay
void DrawingEngine::onTouchMove(float x, float y) {
    if (screenWidth == 0 || screenHeight == 0) return;

    // Chuyển đổi tọa độ Pixel của điện thoại sang tọa độ OpenGL (-1 đến 1)
    float glX = (x / (float)screenWidth) * 2.0f - 1.0f;
    float glY = -((y / (float)screenHeight) * 2.0f - 1.0f); // Trục Y của OpenGL ngược với Android

    lineVertices.push_back(glX);
    lineVertices.push_back(glY);
}

void DrawingEngine::onTouchUp() {
    // Nhấc tay lên (hiện tại chưa cần xử lý thêm)
}

void DrawingEngine::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (lineVertices.empty()) return;

    glUseProgram(shaderProgram);

    // Kích hoạt biến vPosition trong Vertex Shader
    GLuint positionHandle = glGetAttribLocation(shaderProgram, "vPosition");
    glEnableVertexAttribArray(positionHandle);

    // Đẩy dữ liệu tọa độ từ C++ lên GPU
    glVertexAttribPointer(positionHandle, 2, GL_FLOAT, GL_FALSE, 0, lineVertices.data());

    // Yêu cầu GPU vẽ các điểm thành một đường liền mạch (LINE_STRIP)
    glDrawArrays(GL_LINE_STRIP, 0, lineVertices.size() / 2);

    glDisableVertexAttribArray(positionHandle);
}