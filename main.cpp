//Alumno: Hector Felipe Idme Apaza
//Curso: Computacion Grafica - CCOMP7-1
//NOTA: Copiar carpeta resources, shaders, Rubik-solver en:  carpeta_donde_almacena_proyecto-> \GLFW_GLAD_GLUT_GLEW_cmake_project\build\mak.vc16\x64\src\Cubo_Rubik_Hector


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "std_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "texture.h"
#include "rubikCube.h"

#include <iostream>
#include <vector>

#define PI 3.14159265

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(const char* path);

void propuesta(Shader shaderc, glm::mat4& view,int op);
void menu_main(vector<string> options);

void use_camera(int cam, Shader shaderc);
void keyboard_camera(int& cam, Shader shaderc, glm::mat4& view);
void moveCamera(Camera& cam, int op, bool& flag);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


vector<string> option_menu = {
                              "Camara Arriba (W)", "Camara Abajo (S)",
                              "Camara Izquierda (A)", "Camara Derecha (D)",
                              "Camara Adelante (Q)", "Camara Atras (E)",
                              "Camada 1 Horizontal Horario (Z+1)","Camada 1 Horizontal Antiorario (Z)",
                              "Camada 2 Horizontal Horario (X+1)","Camada 2 Horizontal Antiorario (X)",
                              "Camada 3 Horizontal Horario (C+1)","Camada 3 Horizontal Antiorario (C)",
                              "Camada 1 Vertical Horario (V+1)","Camada 1 Vertical Antiorario (V)",
                              "Camada 2 Vertical Horario (B+1)","Camada 2 Vertical Antiorario (B)",
                              "Camada 3 Vertical Horario (N+1)","Camada 3 Vertical Antiorario (N)",
                              "Camada 1 Vertical Horizontal Horario (J)","Camada 1 Vertical Horizontal Antiorario (J+1)",
                              "Camada 2 Vertical Horizontal Horario (K)","Camada 2 Vertical Horizontal Antiorario (K+1)",
                              "Camada 3 Vertical Horizontal Horario (L)","Camada 3 Vertical Horizontal Antiorario (L+1)",
                              "Proyeccion Ortogonal (T)","Proyeccion Perspectiva (Y)","Solucionar Cubo (P)",
                              "Apagar Linterna (F+1)", "Prender Linterna (F)",
                              "Propuesta  (1)","Cambiar Textura (2)",
                              "Salir (ESC)" };


bool change_texture = 0;
bool apagar_linterna = 1;



float angulo_proj = 35.0f;
float angulo_proj_ort = 35.0f;
float anguloPROJ = 35.0f;
float anguloPROJORT = 100.0;

int camara_op = 0;
int camada_giro = 0;

int cmd_giro = 0;
bool g_hor = 1;

float angulo = 0;
float ang = 0.0;
float angx = 0.0;
bool giro_horario = 1;
bool solCube = 0;

bool op_projection = 1;

/// VARIABLES DE PROPUESTA /// 

int propuesta_op = 0;
float y_pos = 0.0;
float alejar_camara = 0.0;
bool sol_cube = 0;
bool casm_op = 0;
int cara_apuntada = 0;




int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cubo de Rubik", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    Shader lightingShader("shaders/light_casters.vs", "shaders/light_casters.fs");
    //Shader shaderText("shaders/default.vert", "shaders/default01.frag");  //cube-textures
    //Shader shaderColor("shaders/default02.vert", "shaders/default02.frag"); //cube-colors



    float vertices[] = {
        //positions             //normals             //texture coords
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,

         0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 1.0f
    };

    float vertices_cubi[] = {
        //positions             //normals             //texture coords
        -1.5f, -1.5f, -1.5f,    0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
         1.5f, -1.5f, -1.5f,    0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
         1.5f,  1.5f, -1.5f,    0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
         1.5f,  1.5f, -1.5f,    0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
        -1.5f,  1.5f, -1.5f,    0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
        -1.5f, -1.5f, -1.5f,    0.0f,  0.0f, -1.0f,   1.0f, 0.0f,

        -1.5f, -1.5f,  1.5f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
         1.5f, -1.5f,  1.5f,    0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
         1.5f,  1.5f,  1.5f,    0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
         1.5f,  1.5f,  1.5f,    0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
        -1.5f,  1.5f,  1.5f,    0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
        -1.5f, -1.5f,  1.5f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f,

        -1.5f, -1.5f, -1.5f,    -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -1.5f, -1.5f,  1.5f,    -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -1.5f,  1.5f,  1.5f,    -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -1.5f,  1.5f,  1.5f,    -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -1.5f,  1.5f, -1.5f,    -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -1.5f, -1.5f, -1.5f,    -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,

         1.5f, -1.5f,  1.5f,    1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
         1.5f, -1.5f, -1.5f,    1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
         1.5f,  1.5f, -1.5f,    1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
         1.5f,  1.5f, -1.5f,    1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
         1.5f,  1.5f,  1.5f,    1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
         1.5f, -1.5f,  1.5f,    1.0f,  0.0f,  0.0f,   0.0f, 0.0f,

        -1.5f, -1.5f, -1.5f,    0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
         1.5f, -1.5f, -1.5f,    0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
         1.5f, -1.5f,  1.5f,    0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
         1.5f, -1.5f,  1.5f,    0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
        -1.5f, -1.5f,  1.5f,    0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
        -1.5f, -1.5f, -1.5f,    0.0f, -1.0f,  0.0f,   0.0f, 1.0f,

        -1.5f,  1.5f, -1.5f,    0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
         1.5f,  1.5f, -1.5f,    0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
         1.5f,  1.5f,  1.5f,    0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
         1.5f,  1.5f,  1.5f,    0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
        -1.5f,  1.5f,  1.5f,    0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
        -1.5f,  1.5f, -1.5f,    0.0f,  1.0f,  0.0f,   0.0f, 1.0f
    };



    float vert_table[] = {
        -10.5f, -0.5f, -7.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
         10.5f, -0.5f, -7.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
         10.5f,  0.5f, -7.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
         10.5f,  0.5f, -7.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
        -10.5f,  0.5f, -7.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
        -10.5f, -0.5f, -7.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,

        -10.5f, -0.5f,  7.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
         10.5f, -0.5f,  7.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
         10.5f,  0.5f,  7.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
         10.5f,  0.5f,  7.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
        -10.5f,  0.5f,  7.5f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
        -10.5f, -0.5f,  7.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,

        -10.5f,  0.5f,  7.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
        -10.5f,  0.5f, -7.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
        -10.5f, -0.5f, -7.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
        -10.5f, -0.5f, -7.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
        -10.5f, -0.5f,  7.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
        -10.5f,  0.5f,  7.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

         10.5f,  0.5f,  7.5f,  1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
         10.5f,  0.5f, -7.5f,  1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
         10.5f, -0.5f, -7.5f,  1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
         10.5f, -0.5f, -7.5f,  1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
         10.5f, -0.5f,  7.5f,  1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
         10.5f,  0.5f,  7.5f,  1.0f,  0.0f,  0.0f,    1.0f, 0.0f,

        -10.5f, -0.5f, -7.5f,  0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
         10.5f, -0.5f, -7.5f,  0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
         10.5f, -0.5f,  7.5f,  0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
         10.5f, -0.5f,  7.5f,  0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
        -10.5f, -0.5f,  7.5f,  0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
        -10.5f, -0.5f, -7.5f,  0.0f, -1.0f,  0.0f,    0.0f, 1.0f,

        -10.5f,  0.5f, -7.5f,  0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
         10.5f,  0.5f, -7.5f,  0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
         10.5f,  0.5f,  7.5f,  0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
         10.5f,  0.5f,  7.5f,  0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
        -10.5f,  0.5f,  7.5f,  0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
        -10.5f,  0.5f, -7.5f,  0.0f,  1.0f,  0.0f,    0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(-7.6f, -23.3f, 0.3f),
        glm::vec3(7.5f, -23.3f, -5.5f),
        glm::vec3(-7.6f,  -23.3f, 3.2f)
    };


    ///////////////////////////////////////
    ///// CUBE

    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    ///////////////////////////////////////
    ///// TABLE

    unsigned int VBO1, tableVAO;
    glGenVertexArrays(1, &tableVAO);
    glGenBuffers(1, &VBO1);


    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert_table), vert_table, GL_STATIC_DRAW);

    glBindVertexArray(tableVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    ///////////////////////////////////////
    ///// MINECRAFT GRASS

    unsigned int grassVAO,VBO2;
    glGenVertexArrays(1, &grassVAO);
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cubi), vertices_cubi, GL_STATIC_DRAW);
    glBindVertexArray(grassVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    ///////////////////////////////////////
    ///// LIGHT-CUBE

    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    ///////////////////////
    ///TEXTURES////////////

    unsigned int textures[60];
    unsigned int textures_colors[60];

    vector<string> images = { "resources/blue.jpg","resources/green.jpg","resources/orange.jpg",
                              "resources/white.jpg","resources/red.jpg","resources/yellow.jpg",
                              "resources/hidden.jpg","resources/container.jpg","resources/awesomeface.png",
                               "resources/table00.jpg","resources/body_grass.jpg","resources/up_grass.png"
    };

    vector<string> letraU = {
        "resources/letras/letraU/U11.png",
        "resources/letras/letraU/U12.png",
        "resources/letras/letraU/U13.png",
        "resources/letras/letraU/U21.png",
        "resources/letras/letraU/U22.png",
        "resources/letras/letraU/U23.png",
        "resources/letras/letraU/U31.png",
        "resources/letras/letraU/U32.png",
        "resources/letras/letraU/U33.png"
    };

    vector<string> letraC1 = {
        "resources/letras/letraC1/C1_11.png",
        "resources/letras/letraC1/C1_12.png",
        "resources/letras/letraC1/C1_13.png",
        "resources/letras/letraC1/C1_21.png",
        "resources/letras/letraC1/C1_22.png",
        "resources/letras/letraC1/C1_23.png",
        "resources/letras/letraC1/C1_31.png",
        "resources/letras/letraC1/C1_32.png",
        "resources/letras/letraC1/C1_33.png"
    };

    vector<string> letraS = {
        "resources/letras/letraS/S11.png",
        "resources/letras/letraS/S12.png",
        "resources/letras/letraS/S13.png",
        "resources/letras/letraS/S21.png",
        "resources/letras/letraS/S22.png",
        "resources/letras/letraS/S23.png",
        "resources/letras/letraS/S31.png",
        "resources/letras/letraS/S32.png",
        "resources/letras/letraS/S33.png"
    };

    vector<string> letraP = {
        "resources/letras/letraP/P11.png",
        "resources/letras/letraP/P12.png",
        "resources/letras/letraP/P13.png",
        "resources/letras/letraP/P21.png",
        "resources/letras/letraP/P22.png",
        "resources/letras/letraP/P23.png",
        "resources/letras/letraP/P31.png",
        "resources/letras/letraP/P32.png",
        "resources/letras/letraP/P33.png"
    };

    vector<string> letraC2 = {
        "resources/letras/letraC2/C2_11.png",
        "resources/letras/letraC2/C2_12.png",
        "resources/letras/letraC2/C2_13.png",
        "resources/letras/letraC2/C2_21.png",
        "resources/letras/letraC2/C2_22.png",
        "resources/letras/letraC2/C2_23.png",
        "resources/letras/letraC2/C2_31.png",
        "resources/letras/letraC2/C2_32.png",
        "resources/letras/letraC2/C2_33.png"
    };

    vector<string> letraG = {
        "resources/letras/letraG/G11.png",
        "resources/letras/letraG/G12.png",
        "resources/letras/letraG/G13.png",
        "resources/letras/letraG/G21.png",
        "resources/letras/letraG/G22.png",
        "resources/letras/letraG/G23.png",
        "resources/letras/letraG/G31.png",
        "resources/letras/letraG/G32.png",
        "resources/letras/letraG/G33.png"
    };


    //TEXTURES: FRONT - RIGHT - UP - LEFT - DOWN - BACK

    /// Fill textures with letters

    for (int i = 0, j = 0; i < 9; i++, j++)
        textures[i] = loadTexture(letraU[j].c_str());

    for (int i = 9, j = 0; i < 18; i++, j++)
        textures[i] = loadTexture(letraC1[j].c_str());

    for (int i = 18, j = 0; i < 27; i++, j++)
        textures[i] = loadTexture(letraS[j].c_str());

    for (int i = 27, j = 0; i < 36; i++, j++)
        textures[i] = loadTexture(letraP[j].c_str());

    for (int i = 36, j = 0; i < 45; i++, j++)
        textures[i] = loadTexture(letraC2[j].c_str());

    for (int i = 45, j = 0; i < 54; i++, j++)
        textures[i] = loadTexture(letraG[j].c_str());

    textures[54] = loadTexture(images[6].c_str()); //hidden


    /// Fill textures with colors

    for (int i = 0, j = 0; i < 9; i++, j++)
        textures_colors[i] = loadTexture(images[1].c_str());

    for (int i = 9, j = 0; i < 18; i++, j++)
        textures_colors[i] = loadTexture(images[4].c_str());

    for (int i = 18, j = 0; i < 27; i++, j++)
        textures_colors[i] = loadTexture(images[3].c_str());

    for (int i = 27, j = 0; i < 36; i++, j++)
        textures_colors[i] = loadTexture(images[2].c_str());

    for (int i = 36, j = 0; i < 45; i++, j++)
        textures_colors[i] = loadTexture(images[5].c_str());

    for (int i = 45, j = 0; i < 54; i++, j++)
        textures_colors[i] = loadTexture(images[0].c_str());

    textures_colors[54] = loadTexture(images[6].c_str()); //hidden

    /////////////////////////////////////////////

    
    textures[55] = loadTexture(images[9].c_str()); //table00
    textures[56] = loadTexture(images[10].c_str()); //table00
    textures[57] = loadTexture(images[11].c_str()); //table00


    vector<unsigned int> texturas;
    for (int i = 0; i < 55; i++)
        texturas.push_back(textures[i]);

    vector<unsigned int> texturas_colors;
    for (int i = 0; i < 55; i++)
        texturas_colors.push_back(textures_colors[i]);
    


    RubikCube rubikCube(texturas);
    rubikCube.setTexturasCors(texturas_colors);

    menu_main(option_menu);

    // shader configuration
    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);

    string solution_mov;
    string mov_prop = "ZVJ";

    while (!glfwWindowShouldClose(window)){
        
        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        lightingShader.use();
        lightingShader.setVec3("light.position", camera.Position);
        lightingShader.setVec3("light.direction", camera.Front);
        lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
        lightingShader.setVec3("viewPos", camera.Position);

        // light properties
        lightingShader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
        
        if (apagar_linterna) {
            lightingShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else {
            lightingShader.setVec3("light.diffuse", 0.0f, 0.0f, 0.0f);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

  
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("light.constant", 1.0f);
        lightingShader.setFloat("light.linear", 0.09f);
        //lightingShader.setFloat("light.quadratic", 0.032f);
        lightingShader.setFloat("light.quadratic", 0.0032f);

        // material properties
        lightingShader.setFloat("material.shininess", 32.0f);


        // view/projection transformations
        //glm::mat4 projection = glm::perspective(glm::radians(35.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);


        
        //Cubo de Rubik
        
        if (!op_projection) projection = glm::ortho(-(float)SCR_WIDTH / anguloPROJORT,
            (float)SCR_WIDTH / anguloPROJORT, -(float)SCR_HEIGHT / anguloPROJORT, (float)SCR_HEIGHT / anguloPROJORT, 0.1f, 100.0f);
        else projection = glm::perspective(glm::radians(anguloPROJ), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);
        

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(cubeVAO);
        if (propuesta_op) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_UNAVAILABLE);
            if ((int)alejar_camara != 80) {
                alejar_camara += 0.1;
                propuesta(lightingShader, view, 1);
            }

            else {
                if (apagar_linterna == 1) apagar_linterna = 0;
                
                else if (y_pos >= -22.5) {
                    y_pos -= 0.04;
                    propuesta(lightingShader, view, 0);
                }
            }

            rubikCube.drawCubeRubik_(lightingShader, 1, glm::vec3(0.0, y_pos, 0.0));
            if (y_pos < -22.5) {
                if ((int)camera.Pitch > -55) {
                    camera.Pitch -= 0.2;
                    camera.updateCameraVectors();
                }
                else {
                    propuesta_op = 0;
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                }
            
            }

      

        }


        else if (change_texture) {
            rubikCube.changeTextures();
            change_texture = 0;
        }


        else {
            rubikCube.solutionCube(solCube, solution_mov);

            if (solution_mov.size()) {
                rubikCube.parser_mov(cmd_giro, g_hor, solution_mov,cara_apuntada);
                moveCamera(camera, cara_apuntada, casm_op);
                casm_op = 0;
            }
            else {
                if (casm_op==0) while(casm_op == 0) moveCamera(camera, 2, casm_op);
                rubikCube.rotCamada(camada_giro, giro_horario);
            }

         
            rubikCube.drawCubeRubik_(lightingShader, 1, glm::vec3(0.0, y_pos, 0.0));
        }

        

        // Table
        glBindVertexArray(tableVAO);
        glm::mat4 model_table = glm::mat4(1.0f);
        model_table = glm::translate(model_table, glm::vec3(0.0,-25.0,-1.0));
        lightingShader.setMat4("model", model_table);
        glBindTexture(GL_TEXTURE_2D, textures[55]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        

        //Minecraft Grass
        glBindVertexArray(grassVAO);
        for (unsigned int i = 0; i < 3; i++){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            lightingShader.setMat4("model", model);
            glBindTexture(GL_TEXTURE_2D, textures[56]);
            glDrawArrays(GL_TRIANGLES, 0, 24);
            glBindTexture(GL_TEXTURE_2D, textures[57]);
            glDrawArrays(GL_TRIANGLES, 24, 12);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(60, textures);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}





void processInput(GLFWwindow* window){

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(UP_, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN_, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);


    else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) giro_horario = 0;
        else giro_horario = 1;
        camada_giro = 1;
    }
        
    else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) giro_horario = 0;
        else giro_horario = 1;
        camada_giro = 2;
    }

    else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) giro_horario = 0;
        else giro_horario = 1;
        camada_giro = 3;
    }

    else if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) giro_horario = 0;
        else giro_horario = 1;
        camada_giro = 4;
    }

    else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) giro_horario = 0;
        else giro_horario = 1;
        camada_giro = 5;
    }

    else if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) giro_horario = 0;
        else giro_horario = 1;
        camada_giro = 6;
    }

    else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) giro_horario = 0;
        else giro_horario = 1;
        camada_giro = 7;
    }

    else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) giro_horario = 0;
        else giro_horario = 1;
        camada_giro = 8;
    }

    else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) giro_horario = 0;
        else giro_horario = 1;
        camada_giro = 9;
    }

    else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        op_projection = 0;
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) anguloPROJORT += 0.01;
        else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) anguloPROJORT -= 0.01;
        else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) anguloPROJORT = angulo_proj_ort;
    }

    else if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        op_projection = 1;
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) anguloPROJ += 0.01;
        else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) anguloPROJ -= 0.01;
        else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) anguloPROJ = angulo_proj;
    }



    else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        solCube = 1;

    else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        propuesta_op = 1;

    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        change_texture = 1;

    else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) apagar_linterna = 0;
        else apagar_linterna = 1;
    }


}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}


void moveCamera(Camera& cam, int op, bool& flag) {

    float veloc = 1.0;

    int posx, posy, posz;
    int  upx, upy, upz;
    int yaw_, pitch_;

    if (op == 2) { //FRENTE
        posx = 0, posy = 0, posz = 10;
        yaw_ = -90, pitch_ = 0;
    }

    else if (op == 4) { //ATRAS
        posx = 0, posy = 0, posz = -10;
        yaw_ = 90, pitch_ = 0;
    }

    else if (op == 1) { //IZQUIERDA
        posx = -10, posy = 0, posz = 0;
        yaw_ = 0, pitch_ = 0;
    }

    else if (op == 3) { //DERECHA
        posx = 10, posy = 0, posz = 0;
        yaw_ = 0, pitch_ = 0;
    }

    else if (op == 0) { //ARRIBA
        posx = 0, posy = 10, posz = 0;
        yaw_ = -90, pitch_ = -89;
    }

    else if (op == 5) { //ABAJO
        posx = 0, posy = -10, posz = 0;
        yaw_ = -90, pitch_ = 89;
    }

    else {
        posx = 0, posy = 0, posz = 10;
        yaw_ = -90, pitch_ = 0;
    }


    if ((int)cam.Position.x > posx)
        cam.Position.x -= veloc;
    if ((int)cam.Position.x < posx)
        cam.Position.x += veloc;
    if ((int)cam.Position.y > posy)
        cam.Position.y -= veloc;
    if ((int)cam.Position.y < posy)
        cam.Position.y += veloc;
    if ((int)cam.Position.z > posz)
        cam.Position.z -= veloc;
    if ((int)cam.Position.z < posz)
        cam.Position.z += veloc;
    if ((int)cam.Yaw > yaw_)
        cam.Yaw -= veloc;
    if ((int)cam.Yaw < yaw_)
        cam.Yaw += veloc;
    if ((int)cam.Pitch > pitch_)
        cam.Pitch -= veloc;
    if ((int)cam.Pitch < pitch_)
        cam.Pitch += veloc;

    if ((int)cam.Pitch == pitch_ && (int)cam.Yaw == yaw_ && (int)cam.Position.x == posx && (int)cam.Position.y == posy && (int)cam.Position.z == posz)
        flag = 1;

    cam.updateCameraVectors();
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera.ProcessMouseScroll(yoffset);
}

unsigned int loadTexture(char const* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void propuesta(Shader shaderc, glm::mat4& view,int op) {

    if(op)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    else 
        camera.ProcessKeyboard(DOWN_, 0.006);
    
    shaderc.setMat4("view", view);
}

void menu_main(vector<string> options) {

    cout << "\n\tMENU\n";
    for (int i = 0; i < options.size(); i++) cout << i + 1 << " " << options[i] << "\n";
}

void use_camera(int cam, Shader shaderc) {
    glm::mat4 view = glm::mat4(1.0f);
    float radius = 10.0f;
    float tmp = PI / 180.0;

    float camX = sin(angulo * tmp) * radius;
    float camZ = cos(angulo * tmp) * radius;
    angulo += 0.1;

    if (cam == 0) {
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
    }
    else if (cam == 1) {
        view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    else if (cam == 2) {
        view = glm::lookAt(glm::vec3(-camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    shaderc.setMat4("view", view);
}

void keyboard_camera(int& cam, Shader shaderc, glm::mat4& view) {
    float radius = 10.0f;
    float tmp = PI / 180.0;
    float fraction = 0.7f;

    if (cam == 1) {
        ang -= 0.1;
        view = glm::lookAt(glm::vec3(0.0, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::rotate(view, glm::radians(ang) * fraction, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    else if (cam == 2) {
        ang += 0.1;
        view = glm::lookAt(glm::vec3(0.0, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::rotate(view, glm::radians(ang) * fraction, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    else if (cam == 3) {
        angx -= 0.1;
        view = glm::lookAt(glm::vec3(0.0, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::rotate(view, glm::radians(angx) * fraction, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    else if (cam == 4) {
        angx += 0.1;
        view = glm::lookAt(glm::vec3(0.0, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::rotate(view, glm::radians(angx) * fraction, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    shaderc.setMat4("view", view);
    cam = 0;
}


