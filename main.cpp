#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>

const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;

static const char *vertexShader = "#version 330\nlayout(location=0) in vec 3 pos;\n void main(){ gl_Position = vec4(0.4*pos.x,0.4*pos.y,pos.z,1.0); }";
static const char *fragmentShader = "#version 330\nout vec4 colour;\n void main(){ colour = vec4(1.0,0.0,0.0,1.0); }";

void CreateTriangle()
{
  GLFloat vertices[] = {
      -1.0f,
      -1.0f,
      0.0f,
      1.0f,
      -1.0f,
      0.0f,
      0.0f,
      1.0f,
      0.0f,
  };
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glGenBuffers(1, &VBO);
  glbindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glenablevertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void AddShader(GLuint p_program, const char *p_code, GLenum p_type)
{
  return;
}

void CompileShaders()
{
  shader = glCreateProgram();
  if (!shader)
  {
    printf("Error creating shader program!\n");
    return;
  }
  AddShader(shader, vertexShader, GL_VERTEX_SHADER);
  AddShader(shader, fragmentShader, GL_FRAGMENT_SHADER);
  GLint result = 0;
  GLchar eLog[1024] = {0};
  glLinkProgram(shader);
}

int main()
{
  if (!glfwInit())
  {
    printf("GLFW initialisations failed!");
    glfwTerminate();
    return 1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Window", NULL, NULL);
  if (!mainWindow)
  {
    printf("GLFW window creation failed!");
    glfwTerminate();
    return 1;
  }
  int bufferHeight, bufferWidth;
  glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
  glfwMakeContextCurrent(mainWindow);
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
    printf("GLEW initialisation failed");
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    return 1;
  }
  glViewport(0, 0, bufferWidth, bufferHeight);
  while (!glfwWindowShouldClose(mainWindow))
  {
    glfwPollEvents();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(mainWindow);
  }
  return 0;
}