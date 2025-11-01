#include <glad/glad.h> // for initializing OpenGL functions
#include <GLFW/glfw3.h> // make window
#include <iostream> // cout & endl
#include <string> // string
#include <glm/glm.hpp> // matrix stuff
#include <glm/gtc/matrix_transform.hpp> // matrix stuff
#include <chrono> // deltaTime
#include "input.h"
#include "global.h"


// fix the stuff wrong with global and the cube in global



using std::string;

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

long long lastTime = 0;
long long currentTime = 0;

int main() {
    glfwInit(); // initialize glfw
    // tell glfw which version of opengl is being used
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // tell glfw we are using the core profile of opengl, so only the modern "core" functions





    // test if glm is working
    glm::vec2 a(1.0f, 2.0f);
    glm::vec2 b(3.0f, 4.0f);
    auto c = a + b;
    std::cout << c.x << ", " << c.y << "\n";


    // full screen quad
    GLfloat vertices[] = {
        -1, -1, 0,
        1, 1, 0,
        -1, 1, 0,

        -1, -1, 0,
        1, -1, 0,
        1, 1, 0,
    };



    int windowWidth = 1280;
    int windowHeight = 720;
    
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "glfw window", NULL, NULL);

    if (!window) {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }



    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // make it so the mouse gets locked to the window
    if (glfwRawMouseMotionSupported()) glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE); // if its supported, use the raw mouse motion
    glfwSetCursorPosCallback(window, cursorPositionCallback);


    glfwMakeContextCurrent(window);




    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // after creating the current context, load GLAD (to load all the OpenGL functions) and check if it loaded correctly
        std::cout << "Failed to init GLAD\n";
        return -1;
    }


    cube = new Cube();


    
    glViewport(0, 0, windowWidth, windowHeight); // specify the viewport of OpenGL in the window


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    GLuint modelMatrixLocation = glGetUniformLocation(shaderProgram, "modelMatrix"); // GLint or GLuint?
    GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");



    //GLuint VAO, VBO; // create reference containers for a VAO and a VBO

    //// generate the VAO and VBO with one object each
    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);

    //glBindVertexArray(VAO); // make VAO the current Vertex Array Object by binding it (always bind the vao before anything else and unbind it after everything else (everything besides EBO, EBO always last))

    //glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind the VBO specifying that its a GL_ARRAY_BUFFER
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // add the vertices to the VBO
    //
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // tell opengl how to read the vertices from the buffer
    //glEnableVertexAttribArray(0); // enable the attribute so that opengl knows to use it (0 for location = 0)

    //// unbind everything
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    camera = Camera();

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f), // camera position
        glm::vec3(0.0f, 0.0f, 0.0f), // look at
        glm::vec3(0.0f, 1.0f, 0.0f)  // up vector
    );
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0), (double)(windowWidth) / (double)(windowHeight), 0.1, 1000.0);


    double fpsMilliseconds = 1000 / 60;
    while (!glfwWindowShouldClose(window)) {
        // deltaTime stuff
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        long long currentTime = milliseconds.count();
        deltaTime = currentTime - lastTime;



        // drawing and updating
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // clear the back buffer and assign the new color to it

        glUseProgram(shaderProgram);
        //glBindVertexArray(VAO); // bind the vao so that opengl knows to use it for drawing
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

        modelMatrix = glm::rotate(modelMatrix, glm::radians(0.1f * deltaTime), glm::vec3(2.0f, 5.0f, .0f));

        cube->draw();

        keyHandler(window);

        camera.updateCamera();

        viewMatrix = glm::lookAt(
            camera.position,
            camera.position + camera.front,
            camera.up
        );


        glfwSwapBuffers(window); // swap the back and front buffers
        glfwPollEvents(); // take care of all the glfw events

        lastTime = currentTime;
    }


    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}