#ifndef DRAWING_ENGINE_H
#define DRAWING_ENGINE_H

#include <GLES2/gl2.h>
#include <vector>

class DrawingEngine {
public:
    DrawingEngine();
    ~DrawingEngine();

    void onSurfaceCreated();
    void onSurfaceChanged(int width, int height);
    void render();

    // Thêm các hàm xử lý cảm ứng
    void onTouchDown(float x, float y);
    void onTouchMove(float x, float y);
    void onTouchUp();

private:
    int screenWidth;
    int screenHeight;
    GLuint shaderProgram; // Chương trình tô màu của card đồ họa

    // Mảng lưu tọa độ các điểm đi qua (X, Y, X, Y...)
    std::vector<float> lineVertices;

    GLuint loadShader(GLenum type, const char* shaderCode);
};

#endif //DRAWING_ENGINE_H