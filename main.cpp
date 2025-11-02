#include <glad/glad.h> // for initializing OpenGL functions
#include <GLFW/glfw3.h> // make window
#include <iostream> // cout & endl
#include <string> // string
#include <glm/glm.hpp> // matrix stuff
#include <glm/gtc/matrix_transform.hpp> // matrix stuff
#include <chrono> // deltaTime
#include "input.h"
#include "global.h"
#include "chunk.h"
#include "world.h"



long long lastTime = 0;
long long currentTime = 0;

void checkGLErrors() { // delete later
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        // log error
        std::cerr << "OpenGL Error: " << err << std::endl;
    }
}


int main() {
    glfwInit(); // initialize glfw
    // tell glfw which version of opengl is being used
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // tell glfw we are using the core profile of opengl, so only the modern "core" functions

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    //int windowWidth = mode->width;
    //int windowHeight = mode->height;
    int windowWidth = 1600;
    int windowHeight = 900;


    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    //GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "glfw window", monitor, NULL);
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "glfw window", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    //glfwSetWindowPos(window, 0 + (mode->width - windowWidth) / 2, 0 + (mode->height - windowHeight) / 2);
    glfwSetWindowPos(window, 50, 50);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // make it so the mouse gets locked to the window
    if (glfwRawMouseMotionSupported()) glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE); // if its supported, use the raw mouse motion
    glfwSetCursorPosCallback(window, cursorPositionCallback);


    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // after creating the current context, load GLAD (to load all the OpenGL functions) and check if it loaded correctly
        std::cout << "Failed to init GLAD\n";
        return -1;
    }

    glViewport(0, 0, windowWidth, windowHeight); // specify the viewport of OpenGL in the window
    initShaders(); // make sure to run this BEFORE any classes that have constructors that contain shader/drawing stuff



    Chunk* chunks = new Chunk[25];
    for (int z = 0; z < 5; z++) {
        for (int x = 0; x < 5; x++) {
            chunks[z * 5 + x * 1].init(glm::vec3((float)x * 10.0f, (float)x * (float)z * 0.0f, (float)z * 10.0f));
            chunks[z * 5 + x * 1].buildMesh();
        }
    }
    //World world = World();
    //world.buildWorldMesh();


    camera = Camera();

    //glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f), // camera position
        glm::vec3(0.0f, 0.0f, 0.0f), // look at
        glm::vec3(0.0f, 1.0f, 0.0f)  // up vector
    );
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0), (double)(windowWidth) / (double)(windowHeight), 0.1, 1000.0);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //double fpsMilliseconds = 1000 / 60; // dont specify an fps, just use deltaTime
    while (!glfwWindowShouldClose(window)) {
        // deltaTime stuff
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        long long currentTime = milliseconds.count();
        deltaTime = currentTime - lastTime;


        // drawing and updating
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the back buffer and assign the new color to it

        glUseProgram(shaderProgram);

        keyHandler(window);
        camera.updateCamera();
        viewMatrix = glm::lookAt(camera.position, camera.position + camera.front, camera.up);

        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);


        //world.draw();
        for (int z = 0; z < 5; z++) {
            for (int x = 0; x < 5; x++) {
                chunks[z * 5 + x * 1].draw();
            }
        }


        checkGLErrors();

        glfwSwapBuffers(window); // swap the back and front buffers
        glfwPollEvents(); // take care of all the glfw events

        lastTime = currentTime;
    }


    glDeleteProgram(shaderProgram);

    //delete[] chunks;

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}