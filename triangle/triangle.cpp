#include <GL/glew.h>
#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>

GLuint VBO; //переменная для хранения дескриптора буфера вершин

struct Vector3f
{
    float x;
    float y;
    float z;

    Vector3f()
    {
    }

    Vector3f(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);   //очистка буфера для предустановленных значений

    glEnableVertexAttribArray(0);   //разрешение использования атрибутов вершин
    glBindBuffer(GL_ARRAY_BUFFER, VBO);   //привязка буфера
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);   //параметры данных в буфере

    glDrawArrays(GL_TRIANGLES, 0, 3);   //отрисовки треугольника

    glDisableVertexAttribArray(0);   //отключение атрибутов вершин

    glutSwapBuffers();
}


static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);   //обратный вызов, который отрисовывает 1 кадр
}

static void CreateVertexBuffer()
{
    Vector3f Vertices[3];   //увеличение массива, чтобы он мог содержать 3 вершины
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);   //левая вершина
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);   //средняя верщина
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);   //правая вершина

    glGenBuffers(1, &VBO);  //создание буфера (первый - количество объектов, которое хотим создать, а второй — адрес массива для хранения дескрипторов)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  //привязка объекта именованного буфера, 1 поле - атрибуты вершин
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);  //заполнение объекта данными (1 поле - атрибуты вершин, 4 - GL_STATIC_DRAW, потому что не собираюсь менять содержимое буфера)
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);    //инициализация GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);    //настройка некоторых параметров GLUT
    glutInitWindowSize(1024, 768);    //размер окна
    glutInitWindowPosition(100, 100);   //начальное положение
    glutCreateWindow("Tutorial 03");    //заголовок окна

    InitializeGlutCallbacks();

    //инициализация GLEW и проверка на ошибки
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(1.0f, 0.0f, 1.0f, 0.0f);   //цвет, который будет использоваться при очистке буфера кадра

    CreateVertexBuffer();   //создание буфера вершины

    glutMainLoop();

    return 0;
}
