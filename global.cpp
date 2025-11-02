#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "global.h"
#include "camera.h"
#include "cube.h"
#include <iostream>

using std::string;

Camera camera;
Cube* cube;

double mousePosX;
double mousePosY;

float deltaTime = 0;


const string vertexShaderSourceString = R"(#version 330 core
    in vec3 position;
    in vec4 color;

    //uniform mat4 modelMatrix;
    uniform mat4 viewMatrix;
    uniform mat4 projectionMatrix;

    out vec4 colorData;
    
    void main() {
        gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);
        //gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
        colorData = color;
    }
)";
const string fragmentShaderSourceString = R"(#version 330 core
    in vec4 colorData;

    out vec4 outColor;
    
    void main() {
        //outColor = vec4(0.0, 1.0, 1.0, 1.0);

        outColor = vec4(gl_FragCoord.xy/800.0, 1.0, 1.0);
        outColor = colorData;
    }
)";
const GLchar* vertexShaderSource = vertexShaderSourceString.c_str();
const GLchar* fragmentShaderSource = fragmentShaderSourceString.c_str();

GLuint shaderProgram;

GLuint positionAttributeLocation; // remember to put declarations for new attributes to allocate memory for them
GLuint colorAttributeLocation;

GLuint modelMatrixLocation;
GLuint viewMatrixLocation;
GLuint projectionMatrixLocation;



void initShaders() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    positionAttributeLocation = glGetAttribLocation(shaderProgram, "position");
    colorAttributeLocation = glGetAttribLocation(shaderProgram, "color");

    modelMatrixLocation = glGetUniformLocation(shaderProgram, "modelMatrix"); // GLint or GLuint?
    viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
    projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
}