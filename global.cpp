#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "global.h"
#include "camera.h"
#include "cube.h"

using std::string;

Camera camera;
Cube* cube;

double mousePosX;
double mousePosY;

float deltaTime = 0;


const string vertexShaderSourceString = R"(#version 330 core
    layout (location = 0) in vec3 aPos;

    uniform mat4 modelMatrix;
    uniform mat4 viewMatrix;
    uniform mat4 projectionMatrix;
    
    void main() {
        gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
    }
)";
const string fragmentShaderSourceString = R"(#version 330 core
    out vec4 outColor;
    
    void main() {
        //outColor = vec4(0.0, 1.0, 1.0, 1.0);

        outColor = vec4(gl_FragCoord.xy/800.0, 1.0, 1.0);
    }
)";
const GLchar* vertexShaderSource = vertexShaderSourceString.c_str();
const GLchar* fragmentShaderSource = fragmentShaderSourceString.c_str();

GLuint shaderProgram;
GLuint modelMatrixLocation;
GLuint viewMatrixLocation;
GLuint projectionMatrixLocation;

void initShaders() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    modelMatrixLocation = glGetUniformLocation(shaderProgram, "modelMatrix"); // GLint or GLuint?
    viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
    projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
}