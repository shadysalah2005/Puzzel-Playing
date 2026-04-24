#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

const int WIDTH = 540;
const int HEIGHT = 540;

const int N = 9;
float cell = WIDTH / (float)N;

std::string symbols[] = {"+", "-", "*", "/", "7", "3", "9", "2", "5", "8"};

std::string getRandomSymbol(int i, int j) {
    return symbols[(i * 7 + j * 3) % 10]; // شبه عشوائي ثابت
}

void drawRect(float x, float y, float w, float h) {
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

void drawText(float x, float y) {
    // OpenGL classic ما بيدعمش text مباشرة
    // هنستخدم placeholder بسيط (نرسم نقطة صغيرة بدل النص)
    glPointSize(4);
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
}

// المربع الأوسط 3x3
bool isCenter(int i, int j) {
    return (i >= 3 && i <= 5 && j >= 3 && j <= 5);
}

int main() {

    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "AI Puzzle Grid OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.02f, 0.04f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ===== GRID CELLS =====
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {

                float x = j * cell;
                float y = i * cell;

                bool active = isCenter(i, j);

                // لون Neon / مطفي
                if (active) {
                    glColor3f(0.0f, 0.9f, 1.0f); // cyan neon
                } else {
                    glColor3f(0.02f, 0.1f, 0.15f); // dark
                }

                drawRect(x, y, cell - 2, cell - 2);

                // ===== TEXT / SYMBOL (fake) =====
                if (active) {
                    glColor3f(0.0f, 1.0f, 1.0f);
                } else {
                    glColor3f(0.0f, 0.3f, 0.4f);
                }

                float cx = x + cell / 2;
                float cy = y + cell / 2;

                drawText(cx, cy);
            }
        }

        // ===== BIG 3x3 LINES =====
        for (int i = 0; i <= N; i++) {

            if (i % 3 == 0)
                glColor3f(0.0f, 1.0f, 1.0f);
            else
                glColor3f(0.0f, 0.2f, 0.3f);

            glBegin(GL_LINES);

            // vertical
            glVertex2f(i * cell, 0);
            glVertex2f(i * cell, HEIGHT);

            // horizontal
            glVertex2f(0, i * cell);
            glVertex2f(WIDTH, i * cell);

            glEnd();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}