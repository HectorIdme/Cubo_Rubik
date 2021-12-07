#ifndef RUBIKCUBE_H
#define RUBIKCUBE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>


#include "shader.h"
#include "std_image.h"
#include "texture.h"
#include <string>
#include <iostream>
#include <queue>
#include <algorithm>
#include <utility>
#include <deque>
#include <vector>
#include <stdlib.h>
#include <fstream>

#define distCub 1.3

using namespace std;


glm::vec3 cubePositions[] = {
    glm::vec3(-1.3f, 1.3f, 0.0f),
    glm::vec3(0.0f, 1.3f, 0.0f),
    glm::vec3(1.3f, 1.3f, 0.0f),
    glm::vec3(-1.3f, 0.0f, 0.0f),
    glm::vec3(1.3f, 0.0f, 0.0f),
    glm::vec3(-1.3f, -1.3f, 0.0f),
    glm::vec3(0.0f, -1.3f, 0.0f),
    glm::vec3(1.3f, -1.3f, 0.0f),

    glm::vec3(-1.3f, 1.3f, 1.3f),
    glm::vec3(0.0f, 1.3f, 1.3f),
    glm::vec3(1.3f, 1.3f, 1.3f),
    glm::vec3(-1.3f, 0.0f, 1.3f),
    glm::vec3(0.0f, 0.0f, 1.3f),
    glm::vec3(1.3f, 0.0f, 1.3f),
    glm::vec3(-1.3f, -1.3f, 1.3f),
    glm::vec3(0.0f, -1.3f, 1.3f),
    glm::vec3(1.3f, -1.3f, 1.3f),

    glm::vec3(-1.3f, 1.3f, -1.3f),
    glm::vec3(0.0f, 1.3f, -1.3f),
    glm::vec3(1.3f, 1.3f, -1.3f),
    glm::vec3(-1.3f, 0.0f, -1.3f),
    glm::vec3(0.0f, 0.0f, -1.3f),
    glm::vec3(1.3f, 0.0f, -1.3f),
    glm::vec3(-1.3f, -1.3f, -1.3f),
    glm::vec3(0.0f, -1.3f, -1.3f),
    glm::vec3(1.3f, -1.3f, -1.3f),

    glm::vec3(0.0f, 0.0f, 0.0f)
};

vector<glm::vec3> cubePositionsH = {
    glm::vec3(-distCub, 0.0f, 0.0f),
    glm::vec3(0.0f, distCub, 0.0f),
    glm::vec3(distCub, 0.0f, 0.0f),
    glm::vec3(-distCub, 0.0f, 0.0f),
    glm::vec3(distCub, 0.0f, 0.0f),
    glm::vec3(-distCub, 0.0f, 0.0f),
    glm::vec3(0.0f, -distCub, 0.0f),
    glm::vec3(distCub, 0.0f, 0.0f),


    glm::vec3(-distCub, 0.0f, distCub),
    glm::vec3(0.0f, 0.0f, distCub),
    glm::vec3(distCub, 0.0f, distCub),
    glm::vec3(-distCub, 0.0f, distCub),
    glm::vec3(0.0f, 0.0f, distCub),
    glm::vec3(distCub, 0.0f, distCub),
    glm::vec3(-distCub, 0.0f, distCub),
    glm::vec3(0.0f, 0.0f, distCub),
    glm::vec3(distCub, 0.0f, distCub),


    glm::vec3(-distCub, 0.0f, -distCub),
    glm::vec3(0.0f, 0.0f, -distCub),
    glm::vec3(distCub, 0.0f, -distCub),
    glm::vec3(-distCub, 0.0f, -distCub),
    glm::vec3(0.0f, 0.0f, -distCub),
    glm::vec3(distCub, 0.0f, -distCub),
    glm::vec3(-distCub, 0.0f, -distCub),
    glm::vec3(0.0f, 0.0f, -distCub),
    glm::vec3(distCub, 0.0f, -distCub),

    glm::vec3(0.0f, 0.0f, 0.0f)
};

vector<glm::vec3> cubePositionsV = {
    glm::vec3(0.0f, distCub, 0.0f),
    glm::vec3(0.0f, distCub, 0.0f),
    glm::vec3(0.0f, distCub, 0.0f),
    glm::vec3(-distCub, 0.0f, 0.0f),
    glm::vec3(distCub, 0.0f, 0.0f),
    glm::vec3(0.0f, -distCub, 0.0f),
    glm::vec3(0.0f, -distCub, 0.0f),
    glm::vec3(0.0f, -distCub, 0.0f),


    glm::vec3(0.0f, distCub, distCub),
    glm::vec3(0.0f, distCub, distCub),
    glm::vec3(0.0f, distCub, distCub),
    glm::vec3(0.0f, 0.0f, distCub),
    glm::vec3(0.0f, 0.0f, distCub),
    glm::vec3(0.0f, 0.0f, distCub),
    glm::vec3(0.0f, -distCub, distCub),
    glm::vec3(0.0f, -distCub, distCub),
    glm::vec3(0.0f, -distCub, distCub),

    glm::vec3(0.0f, distCub, -distCub),
    glm::vec3(0.0f, distCub, -distCub),
    glm::vec3(0.0f, distCub, -distCub),
    glm::vec3(0.0f, 0.0f, -distCub),
    glm::vec3(0.0f, 0.0f, -distCub),
    glm::vec3(0.0f, 0.0f, -distCub),
    glm::vec3(0.0f, -distCub, -distCub),
    glm::vec3(0.0f, -distCub, -distCub),
    glm::vec3(0.0f, -distCub, -distCub),

    glm::vec3(0.0f, 0.0f, 0.0f)
};

vector<glm::vec3> cubePositionsV2 = {
    glm::vec3(-distCub, distCub, 0.0f),
    glm::vec3(0.0f, distCub, 0.0f),
    glm::vec3(distCub, distCub, 0.0f),
    glm::vec3(-distCub, 0.0f, 0.0f),
    glm::vec3(distCub, 0.0f, 0.0f),
    glm::vec3(-distCub, -distCub, 0.0f),
    glm::vec3(0.0f, -distCub, 0.0f),
    glm::vec3(distCub, -distCub, 0.0f),



    glm::vec3(-distCub, distCub, 0.0f),
    glm::vec3(0.0f, distCub, 0.0f),
    glm::vec3(distCub, distCub, 0.0f),
    glm::vec3(-distCub, 0.0f, 0.0f),

    glm::vec3(0.0f, 0.0f, distCub),

    glm::vec3(distCub, 0.0f, 0.0f),
    glm::vec3(-distCub, -distCub, 0.0f),
    glm::vec3(0.0f, -distCub, 0.0f),
    glm::vec3(distCub, -distCub, 0.0f),



    glm::vec3(-distCub, distCub, 0.0f),
    glm::vec3(0.0f, distCub, 0.0f),
    glm::vec3(distCub, distCub, 0.0f),
    glm::vec3(-distCub, 0.0f, 0.0f),

    glm::vec3(0.0f, 0.0f, -distCub),

    glm::vec3(distCub, 0.0f, 0.0f),
    glm::vec3(-distCub, -distCub, 0.0f),
    glm::vec3(0.0f, -distCub, 0.0f),
    glm::vec3(distCub, -distCub, 0.0f),

    glm::vec3(0.0f, 0.0f, 0.0f)

};



struct NodeCube {

    ///COLORS
    ////orange(izq/0) - green(frente/1) - white(arriba/2) - blue(atras/3) 
    ///- yellow(abajo/4) - red(der/5) - black(hidden/6)
    vector<vector<float>> cors = {
                {1,0.552,0.121}, {0,0.678,0.019},{1,1,1},
                { 0.003,0.266,0.756 }, {0.960,0.843,0} , {1, 0.078, 0.133},{0,0,0}
    };


    vector<unsigned int> text_ref;



    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 model_text = glm::mat4(1.0f);
    glm::vec3 cubePosition;
    vector<unsigned int> cube_textures;  //ATRAS - FRENTE - IZQ - DER - ABAJO - ARRIBA
    vector<vector<float>> colors; //ATRAS - FRENTE - IZQ - DER - ABAJO - ARRIBA
    int ID;


    void setPos(glm::vec3 pos) {
        cubePosition = pos;
        model =  glm::translate(model, cubePosition);
    }

    void setModel(glm::mat4 model_) {
        model = model_;
    }

    void setModelText(glm::mat4 model_) {
        model_text = model_;
    }

    glm::mat4 getModel() {
        return model;
    }

    void setTex(vector<unsigned int> text) {
        cube_textures = text;
    }

    void setTexRef(vector<unsigned int> text) {
        text_ref = text;
    }

    void setColor(vector<vector<float>> cor) {
        colors = cor;
    }

    void setID(int id) {
        ID = id;
    }

    char getCorCara_(int cara) {
        char cor='-';
        
        if (cara == 0) {
            if (colors[0] == cors[0]) cor = 'o';
            else if (colors[0] == cors[1]) cor = 'g';
            else if (colors[0] == cors[2]) cor = 'w';
            else if (colors[0] == cors[3]) cor = 'l';
            else if (colors[0] == cors[4]) cor = 'y';
            else if (colors[0] == cors[5]) cor = 'r';
            else if (colors[0] == cors[6]) cor = '-';
        }
        
        else if (cara == 1) {
            if (colors[1] == cors[0]) cor = 'o';
            else if (colors[1] == cors[1]) cor = 'g';
            else if (colors[1] == cors[2]) cor = 'w';
            else if (colors[1] == cors[3]) cor = 'l';
            else if (colors[1] == cors[4]) cor = 'y';
            else if (colors[1] == cors[5]) cor = 'r';
            else if (colors[1] == cors[6]) cor = '-';
        }
        
        else if (cara == 2) {
            if (colors[2] == cors[0]) cor = 'o';
            else if (colors[2] == cors[1]) cor = 'g';
            else if (colors[2] == cors[2]) cor = 'w';
            else if (colors[2] == cors[3]) cor = 'l';
            else if (colors[2] == cors[4]) cor = 'y';
            else if (colors[2] == cors[5]) cor = 'r';
            else if (colors[2] == cors[6]) cor = '-';
        }
       
        else if (cara == 3) {
            if (colors[3] == cors[0]) cor = 'o';
            else if (colors[3] == cors[1]) cor = 'g';
            else if (colors[3] == cors[2]) cor = 'w';
            else if (colors[3] == cors[3]) cor = 'l';
            else if (colors[3] == cors[4]) cor = 'y';
            else if (colors[3] == cors[5]) cor = 'r';
            else if (colors[3] == cors[6]) cor = '-';
        }
        
        else if (cara == 4) {
            if (colors[4] == cors[0]) cor = 'o';
            else if (colors[4] == cors[1]) cor = 'g';
            else if (colors[4] == cors[2]) cor = 'w';
            else if (colors[4] == cors[3]) cor = 'l';
            else if (colors[4] == cors[4]) cor = 'y';
            else if (colors[4] == cors[5]) cor = 'r';
            else if (colors[4] == cors[6]) cor = '-';
        }
        
        else if (cara == 5) {
            if (colors[5] == cors[0]) cor = 'o';
            else if (colors[5] == cors[1]) cor = 'g';
            else if (colors[5] == cors[2]) cor = 'w';
            else if (colors[5] == cors[3]) cor = 'l';
            else if (colors[5] == cors[4]) cor = 'y';
            else if (colors[5] == cors[5]) cor = 'r';
            else if (colors[5] == cors[6]) cor = '-';
        }

        return cor;

    }

    ///

    bool searchText(unsigned int text,int textura_cara) {

        //letra U
        if (textura_cara == 0) {
            for (int i = 0; i < 9; i++) 
                if (text == text_ref[i]) return true;
        }

        //letra C1
        else if (textura_cara == 1) {
            for (int i = 9; i < 18; i++)
                if (text == text_ref[i]) return true;
        }

        //letra S
        else if (textura_cara ==2) {
            for (int i = 18; i < 27; i++)
                if (text == text_ref[i]) return true;
        }

        //letra P
        else if (textura_cara == 3) {
            for (int i = 27; i < 36; i++)
                if (text == text_ref[i]) return true;
        }

        //letra C2
        else if (textura_cara == 4) {
            for (int i = 36; i < 45; i++)
                if (text == text_ref[i]) return true;
        }

        //letra G
        else if (textura_cara == 5) {
            for (int i = 45; i < 55; i++)
                if (text == text_ref[i]) return true;
        }

        return false;

    } 


    char getCorCara(int cara) {
        char cor = '-';

        if (cara == 0) {
            if (searchText(cube_textures[0], 3)) cor = 'o';
            else if (searchText(cube_textures[0], 0)) cor = 'g';
            else if (searchText(cube_textures[0], 2)) cor = 'w';
            else if (searchText(cube_textures[0], 5)) cor = 'l';
            else if (searchText(cube_textures[0], 4)) cor = 'y';
            else if (searchText(cube_textures[0], 1)) cor = 'r';
            else  cor = '-';
        }
        
        else if (cara == 1) {
            if (searchText(cube_textures[1], 3)) cor = 'o';
            else if (searchText(cube_textures[1], 0)) cor = 'g';
            else if (searchText(cube_textures[1], 2)) cor = 'w';
            else if (searchText(cube_textures[1], 5)) cor = 'l';
            else if (searchText(cube_textures[1], 4)) cor = 'y';
            else if (searchText(cube_textures[1], 1)) cor = 'r';
            else  cor = '-';
        }

        else if (cara == 2) {
            if (searchText(cube_textures[2], 3)) cor = 'o';
            else if (searchText(cube_textures[2], 0)) cor = 'g';
            else if (searchText(cube_textures[2], 2)) cor = 'w';
            else if (searchText(cube_textures[2], 5)) cor = 'l';
            else if (searchText(cube_textures[2], 4)) cor = 'y';
            else if (searchText(cube_textures[2], 1)) cor = 'r';
            else  cor = '-';
        }

        else if (cara == 3) {
            if (searchText(cube_textures[3], 3)) cor = 'o';
            else if (searchText(cube_textures[3], 0)) cor = 'g';
            else if (searchText(cube_textures[3], 2)) cor = 'w';
            else if (searchText(cube_textures[3], 5)) cor = 'l';
            else if (searchText(cube_textures[3], 4)) cor = 'y';
            else if (searchText(cube_textures[3], 1)) cor = 'r';
            else  cor = '-';
        }

        else if (cara == 4) {
            if (searchText(cube_textures[4], 3)) cor = 'o';
            else if (searchText(cube_textures[4], 0)) cor = 'g';
            else if (searchText(cube_textures[4], 2)) cor = 'w';
            else if (searchText(cube_textures[4], 5)) cor = 'l';
            else if (searchText(cube_textures[4], 4)) cor = 'y';
            else if (searchText(cube_textures[4], 1)) cor = 'r';
            else  cor = '-';
        }

        else if (cara == 5) {
            if (searchText(cube_textures[5], 3)) cor = 'o';
            else if (searchText(cube_textures[5], 0)) cor = 'g';
            else if (searchText(cube_textures[5], 2)) cor = 'w';
            else if (searchText(cube_textures[5], 5)) cor = 'l';
            else if (searchText(cube_textures[5], 4)) cor = 'y';
            else if (searchText(cube_textures[5], 1)) cor = 'r';
            else  cor = '-';
        }

        return cor;
    }
   

    glm::mat4 getModelMatrix(bool op = 0) {
        if (op)return model;
        else  return glm::translate(model, cubePosition);
    }

    glm::mat4 getModelText() {
        return model_text;
    }


    void drawCubeText() {
        for (int i = 0; i < 6; i++) {
            glBindTexture(GL_TEXTURE_2D, cube_textures[i]);
            glDrawArrays(GL_TRIANGLES, i*6, 6);
        }
    }

    void drawCubeColors(Shader shaderc) {
        for (int i = 0; i < 6; i++) {
            shaderc.setVec3("ourColor", colors[i][0], colors[i][1], colors[i][2]);
            glDrawArrays(GL_TRIANGLES, i * 6, 6);
        }
    }


};


struct Camada {

    vector<NodeCube> cubos;
    vector<glm::vec3> cubePos;
    glm::mat4 model_center = glm::mat4(1.0f);
    glm::mat4 model_camada = glm::mat4(1.0f);
    glm::mat4 model_text_ref = glm::mat4(1.0f);

    int ID;
    int orientation;
    bool animation = 0;

    float ang_ = 0;
    bool girar = 0;
    float speed = 0.25;

    void setID(int id) {
        ID = id;
    }

    void setCamada(vector<NodeCube> grupo) {
        cubos = grupo;
    }

    void setCubePos(vector<glm::vec3> cubePos_) {
        cubePos = cubePos_;
    }

    void setOr(int or ) {
        orientation = or;

        if (orientation == 1) cubePos = cubePositionsV;
        else if (orientation == 2) cubePos = cubePositionsV2;
        else cubePos = cubePositionsH;

        getPos_Center();
    }

    void getPos_Center() {

        if (ID == 0) model_center = glm::translate(model_center, cubePos[1]);
        else if(ID == 1) model_center = glm::translate(model_center, cubePos[26]);
        else if (ID == 2) model_center = glm::translate(model_center, cubePos[6]);
        else if (ID == 3) model_center = glm::translate(model_center, cubePos[3]);
        else if (ID == 4) model_center = glm::translate(model_center, cubePos[26]);
        else if (ID == 5) model_center = glm::translate(model_center, cubePos[4]);
        else if (ID == 6) model_center = glm::translate(model_center, cubePos[12]);
        else if (ID == 7) model_center = glm::translate(model_center, cubePos[26]);
        else if (ID == 8) model_center = glm::translate(model_center, cubePos[21]);

    }

    void printPos() {
        cout << "\nCamada " << ID << " orientation " << orientation << "\n";
        for (int i = 0; i < cubePos.size(); i++) {
            cout << i << " " << to_string(this->cubePos[i]) << "\n";
        }cout << "\n";
    }

    void set_cubes_rot(bool rotation) {
        glm::vec3 direction;
        glm::vec3 direction_;

        if (animation) {

            if (orientation == 0) {
                if (rotation) {
                    direction = glm::vec3(0.0f, 1.0f, 0.0f);
                    direction_ = glm::vec3(0.0f, -1.0f, 0.0f);
                }
                else {
                    direction = glm::vec3(0.0f, -1.0f, 0.0f);
                    direction_ = glm::vec3(0.0f, 1.0f, 0.0f);
                }
            }
            else if(orientation == 1){
                if (rotation) {
                    direction = glm::vec3(1.0f, 0.0f, 0.0f);
                    direction_ = glm::vec3(-1.0f, 0.0f, 0.0f);
                }
                else {
                    direction = glm::vec3(-1.0f, 0.0f, 0.0f);
                    direction_ = glm::vec3(1.0f, 0.0f, 0.0f);
                }
            }
            else if (orientation == 2) {
                if (!rotation) {
                    direction = glm::vec3(0.0f, 0.0f, 1.0f);
                    direction_ = glm::vec3(0.0f, 0.0f, -1.0f);
                }
                else { 
                    direction = glm::vec3(0.0f, 0.0f, -1.0f);
                    direction_ = glm::vec3(0.0f, 0.0f, 1.0f);
                }
            }


            if (girar) {
                model_center = glm::rotate(model_center, (float)(glm::radians(speed)), direction);
                model_text_ref = glm::rotate(model_text_ref, (float)(glm::radians(speed)), direction_);
                ang_ += speed;
            }

            model_camada = model_center;
            cubos[4].setModel(model_center);
            cubos[4].setModelText(model_text_ref);

        }
           
    }

};



struct RubikCube {

    vector<char> stateCube;
    vector<int> camada_mas_complet;

    NodeCube cubos[27];
    Camada camadas[9];
    string sol_movs;

    bool  flag_sol = 0;
    bool borr;
    string m;


    ///COLORS
    ////orange(izq/0) - green(frente/1) - white(arriba/2) - blue(atras/3) 
    ///- yellow(abajo/4) - red(der/5) - black(hidden/6)
    vector<vector<float>> colors = { 
                {1,0.552,0.121}, {0,0.678,0.019},{1,1,1},
                { 0.003,0.266,0.756 }, {0.960,0.843,0} , {1, 0.078, 0.133},{0,0,0}
    };

    vector<unsigned int> texturas;
    vector<unsigned int> texturas_colors;


    void fileStateCube() {

        ofstream myFile("stateCub.dat");

        for (int i = 0; i < stateCube.size(); i++) {
            myFile << stateCube[i] << " ";
            if ((i + 1) % 9 == 0) myFile << "\n";
        }
        myFile.close();

    }


    RubikCube(vector<unsigned int> text) {

        texturas = text;

        //CREANDO CUBOS

        //COLORS
        /*
        for (int i = 0; i < 27; i++) {
            cubos[i].setPos(cubePositions[i]);
            cubos[i].setID(i);

            switch (i) {  //ATRAS - FRENTE - IZQ - DER - ABAJO - ARRIBA
            ////PRIMERA FILA 1
            case 0:
                cubos[0].setColor({ colors[6],colors[6],colors[0],colors[6],colors[6],colors[2] });
                break;
            case 1:
                cubos[1].setColor({ colors[6],colors[6],colors[6],colors[6],colors[6],colors[2] });
                break;
            case 2:
                cubos[2].setColor({ colors[6],colors[6],colors[6],colors[5],colors[6],colors[2] });
                break;
                ////SEGUNDA FILA 1
            case 3:
                cubos[3].setColor({ colors[6],colors[6],colors[0],colors[6],colors[6],colors[6] });
                break;
            case 4:
                cubos[4].setColor({ colors[6],colors[6],colors[6],colors[5],colors[6],colors[6] });
                break;
                ////TERCERA FILA 1
            case 5:
                cubos[5].setColor({ colors[6],colors[6],colors[0],colors[6],colors[4],colors[6] });
                break;
            case 6:
                cubos[6].setColor({ colors[6],colors[6],colors[6],colors[6],colors[4],colors[6] });
                break;
            case 7:
                cubos[7].setColor({ colors[6],colors[6],colors[6],colors[5],colors[4],colors[6] });
                break;


                ////PRIMERA FILA 0
            case 8:
                cubos[8].setColor({ colors[6],colors[1],colors[0],colors[6],colors[6],colors[2] });
                break;
            case 9:
                cubos[9].setColor({ colors[6],colors[1],colors[6],colors[6],colors[6],colors[2] });
                break;
            case 10:
                cubos[10].setColor({ colors[6],colors[1],colors[6],colors[5],colors[6],colors[2] });
                break;
                ////SEGUNDA FILA 0
            case 11:
                cubos[11].setColor({ colors[6],colors[1],colors[0],colors[6],colors[6],colors[6] });
                break;
            case 12:
                cubos[12].setColor({ colors[6],colors[1],colors[6],colors[6],colors[6],colors[6] });
                break;
            case 13:
                cubos[13].setColor({ colors[6],colors[1],colors[6],colors[5],colors[6],colors[6] });
                break;
                ////TERCERA FILA 0
            case 14:
                cubos[14].setColor({ colors[6],colors[1],colors[0],colors[6],colors[4],colors[6] });
                break;
            case 15:
                cubos[15].setColor({ colors[6],colors[1],colors[6],colors[6],colors[4],colors[6] });
                break;
            case 16:
                cubos[16].setColor({ colors[6],colors[1],colors[6],colors[5],colors[4],colors[6] });
                break;


                ////PRIMERA FILA 2
            case 17:
                cubos[17].setColor({ colors[3],colors[6],colors[0],colors[6],colors[6],colors[2] });
                break;
            case 18:
                cubos[18].setColor({ colors[3],colors[6],colors[6],colors[6],colors[6],colors[2] });
                break;
            case 19:
                cubos[19].setColor({ colors[3],colors[6],colors[6],colors[5],colors[6],colors[2] });
                break;
                ////SEGUNDA FILA 2
            case 20:
                cubos[20].setColor({ colors[3],colors[6],colors[0],colors[6],colors[6],colors[6] });
                break;
            case 21:
                cubos[21].setColor({ colors[3],colors[6],colors[6],colors[6],colors[6],colors[6] });
                break;
            case 22:
                cubos[22].setColor({ colors[3],colors[6],colors[6],colors[5],colors[6],colors[6] });
                break;
                ////TERCERA FILA 2
            case 23:
                cubos[23].setColor({ colors[3],colors[6],colors[0],colors[6],colors[4],colors[6] });
                break;
            case 24:
                cubos[24].setColor({ colors[3],colors[6],colors[6],colors[6],colors[4],colors[6] });
                break;
            case 25:
                cubos[25].setColor({ colors[3],colors[6],colors[6],colors[5],colors[4],colors[6] });
                break;
            }

        }
        */

        //TEXTURES
        for (int i = 0; i < 27; i++) {
            cubos[i].setPos(cubePositions[i]);
            cubos[i].setID(i);
            cubos[i].setTexRef(texturas);

            switch (i) {  //ATRAS - FRENTE - IZQ - DER - ABAJO - ARRIBA
            ////PRIMERA FILA 1
            case 0:
                cubos[0].setTex({ texturas[54],texturas[54],texturas[28],texturas[54],texturas[54],texturas[21] });
                break;
            case 1:
                cubos[1].setTex({ texturas[54],texturas[54],texturas[54],texturas[54],texturas[54],texturas[22] });
                break;
            case 2:
                cubos[2].setTex({ texturas[54],texturas[54],texturas[54],texturas[10],texturas[54],texturas[23] });
                break;
                ////SEGUNDA FILA 1
            case 3:
                cubos[3].setTex({ texturas[54],texturas[54],texturas[31],texturas[54],texturas[54],texturas[54] });
                break;
            case 4:
                cubos[4].setTex({ texturas[54],texturas[54],texturas[54],texturas[13],texturas[54],texturas[54] });
                break;
                ////TERCERA FILA 1
            case 5:
                cubos[5].setTex({ texturas[54],texturas[54],texturas[34],texturas[54],texturas[39],texturas[54] });
                break;
            case 6:
                cubos[6].setTex({ texturas[54],texturas[54],texturas[54],texturas[54],texturas[40],texturas[54] });
                break;
            case 7:
                cubos[7].setTex({ texturas[54],texturas[54],texturas[54],texturas[16],texturas[41],texturas[54] });
                break;


                ////PRIMERA FILA 0
            case 8:
                cubos[8].setTex({ texturas[54],texturas[0],texturas[29],texturas[54],texturas[54],texturas[24] });
                break;
            case 9:
                cubos[9].setTex({ texturas[54],texturas[1],texturas[54],texturas[54],texturas[54],texturas[25] });
                break;
            case 10:
                cubos[10].setTex({ texturas[54],texturas[2],texturas[54],texturas[9],texturas[54],texturas[26] });
                break;
                ////SEGUNDA FILA 0
            case 11:
                cubos[11].setTex({ texturas[54],texturas[3],texturas[32],texturas[54],texturas[54],texturas[54] });
                break;
            case 12:
                cubos[12].setTex({ texturas[54],texturas[4],texturas[54],texturas[54],texturas[54],texturas[54] });
                break;
            case 13:
                cubos[13].setTex({ texturas[54],texturas[5],texturas[54],texturas[12],texturas[54],texturas[54] });
                break;
                ////TERCERA FILA 0
            case 14:
                cubos[14].setTex({ texturas[54],texturas[6],texturas[35],texturas[54],texturas[42],texturas[54] });
                break;
            case 15:
                cubos[15].setTex({ texturas[54],texturas[7],texturas[54],texturas[54],texturas[43],texturas[54] });
                break;
            case 16:
                cubos[16].setTex({ texturas[54],texturas[8],texturas[54],texturas[15],texturas[44],texturas[54] });
                break;


                ////PRIMERA FILA 2
            case 17:
                cubos[17].setTex({ texturas[47],texturas[54],texturas[27],texturas[54],texturas[54],texturas[18] });
                break;
            case 18:
                cubos[18].setTex({ texturas[46],texturas[54],texturas[54],texturas[54],texturas[54],texturas[19] });
                break;
            case 19:
                cubos[19].setTex({ texturas[45],texturas[54],texturas[54],texturas[11],texturas[54],texturas[20] });
                break;
                ////SEGUNDA FILA 2
            case 20:
                cubos[20].setTex({ texturas[50],texturas[54],texturas[30],texturas[54],texturas[54],texturas[54] });
                break;
            case 21:
                cubos[21].setTex({ texturas[49],texturas[54],texturas[54],texturas[54],texturas[54],texturas[54] });
                break;
            case 22:
                cubos[22].setTex({ texturas[48],texturas[54],texturas[54],texturas[14],texturas[54],texturas[54] });
                break;
                ////TERCERA FILA 2
            case 23:
                cubos[23].setTex({ texturas[53],texturas[54],texturas[33],texturas[54],texturas[36],texturas[54] });
                break;
            case 24:
                cubos[24].setTex({ texturas[52],texturas[54],texturas[54],texturas[54],texturas[37],texturas[54] });
                break;
            case 25:
                cubos[25].setTex({ texturas[51],texturas[54],texturas[54],texturas[17],texturas[38],texturas[54] });
                break;
            }

        }


        //CREANDO CAMADAS
        camadas[0].setID(0);
        camadas[0].setOr(0);
        camadas[0].setCamada({ cubos[17],cubos[18], cubos[19],
                               cubos[0],cubos[1], cubos[2],
                               cubos[8],cubos[9], cubos[10] });

        camadas[1].setID(1);
        camadas[1].setOr(0);
        camadas[1].setCamada({ cubos[20],cubos[21], cubos[22], 
                                cubos[3],cubos[26],cubos[4], 
                                cubos[11],cubos[12], cubos[13]});
        
        camadas[2].setID(2);
        camadas[2].setOr(0);
        camadas[2].setCamada({ cubos[23],cubos[24], cubos[25],
                                cubos[5],cubos[6], cubos[7],
                                cubos[14],cubos[15], cubos[16] });
                                    

        camadas[3].setID(3);
        camadas[3].setOr(1);
        camadas[3].setCamada({ cubos[17], cubos[0],cubos[8], 
                                cubos[20],cubos[3], cubos[11], 
                                cubos[23],cubos[5],cubos[14] });
        

        camadas[4].setID(4);
        camadas[4].setOr(1);
        camadas[4].setCamada({ cubos[18],cubos[1], cubos[9],
                                    cubos[21],cubos[26],cubos[12],
                                    cubos[24],cubos[6], cubos[15] });


        camadas[5].setID(5);
        camadas[5].setOr(1);
        camadas[5].setCamada({ cubos[19],cubos[2], cubos[10],
                                    cubos[22],cubos[4], cubos[13],
                                    cubos[25],cubos[7], cubos[16] });

        camadas[6].setID(6);
        camadas[6].setOr(2);
        camadas[6].setCamada({ cubos[8], cubos[9],cubos[10],
                                cubos[11],cubos[12], cubos[13],
                                cubos[14],cubos[15],cubos[16] });


        camadas[7].setID(7);
        camadas[7].setOr(2);
        camadas[7].setCamada({ cubos[0],cubos[1], cubos[2],
                                    cubos[3],cubos[26],cubos[4],
                                    cubos[5],cubos[6], cubos[7] });


        camadas[8].setID(8);
        camadas[8].setOr(2);
        camadas[8].setCamada({ cubos[17],cubos[18], cubos[19],
                                    cubos[20],cubos[21], cubos[22],
                                    cubos[23],cubos[24], cubos[25] });


        
        //ATRAS - FRENTE - IZQ - DER - ABAJO - ARRIBA (colores)
        // 
        //CAMADAS PARA SOLVER: ARRIBA - IZQ - FRENTE - DER - ATRAS - ABAJO

        
        //ARRIBA
        for (int i = 0; i <9; i++) stateCube.push_back(camadas[0].cubos[i].getCorCara(5));
        
        //IZQ
        for (int i = 0; i <9; i++) stateCube.push_back(camadas[3].cubos[i].getCorCara(2));
        
        //FRENTE
        for (int i = 0; i < 9; i++) stateCube.push_back(camadas[6].cubos[i].getCorCara(1));

        //DER
        stateCube.push_back(camadas[5].cubos[2].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[1].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[0].getCorCara(3));

        stateCube.push_back(camadas[5].cubos[5].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[4].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[3].getCorCara(3));

        stateCube.push_back(camadas[5].cubos[8].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[7].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[6].getCorCara(3));

        //ATRAS
        stateCube.push_back(camadas[8].cubos[2].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[1].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[0].getCorCara(0));

        stateCube.push_back(camadas[8].cubos[5].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[4].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[3].getCorCara(0));

        stateCube.push_back(camadas[8].cubos[8].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[7].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[6].getCorCara(0));

        //ABAJO
        stateCube.push_back(camadas[2].cubos[6].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[7].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[8].getCorCara(4));

        stateCube.push_back(camadas[2].cubos[3].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[4].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[5].getCorCara(4));

        stateCube.push_back(camadas[2].cubos[0].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[1].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[2].getCorCara(4));
        

        cout << "Estado Cubo\n";
        for (int i = 0; i < stateCube.size(); i++) {
            cout << stateCube[i] << " ";
            if ((i + 1) % 9 == 0) cout << "\n";
        }cout << "\n";

        fileStateCube();
        
    }

    NodeCube getCube(int id) {
        for (int i = 0; i < 27; i++) {
            if (cubos[i].ID == id) return cubos[i];
        }
    }

    void setTexturasCors(vector<unsigned int> textCor) {
        texturas_colors = textCor;
    }

    void changeTextures() {

        //TEXTURES
        for (int i = 0; i < 27; i++) {
            cubos[i].setTexRef(texturas_colors);
            
            switch (i) {  //ATRAS - FRENTE - IZQ - DER - ABAJO - ARRIBA
            ////PRIMERA FILA 1
            case 0:
                cubos[0].setTex({ texturas_colors[54],texturas_colors[54],texturas_colors[28],texturas_colors[54],texturas_colors[54],texturas_colors[21] });
                break;
            case 1:
                cubos[1].setTex({ texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[22] });
                break;
            case 2:
                cubos[2].setTex({ texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[10],texturas_colors[54],texturas_colors[23] });
                break;
                ////SEGUNDA FILA 1
            case 3:
                cubos[3].setTex({ texturas_colors[54],texturas_colors[54],texturas_colors[31],texturas_colors[54],texturas_colors[54],texturas_colors[54] });
                break;
            case 4:
                cubos[4].setTex({ texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[13],texturas_colors[54],texturas_colors[54] });
                break;
                ////TERCERA FILA 1
            case 5:
                cubos[5].setTex({ texturas_colors[54],texturas_colors[54],texturas_colors[34],texturas_colors[54],texturas_colors[39],texturas_colors[54] });
                break;
            case 6:
                cubos[6].setTex({ texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[40],texturas_colors[54] });
                break;
            case 7:
                cubos[7].setTex({ texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[16],texturas_colors[41],texturas_colors[54] });
                break;


                ////PRIMERA FILA 0
            case 8:
                cubos[8].setTex({ texturas_colors[54],texturas_colors[0],texturas_colors[29],texturas_colors[54],texturas_colors[54],texturas_colors[24] });
                break;
            case 9:
                cubos[9].setTex({ texturas_colors[54],texturas_colors[1],texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[25] });
                break;
            case 10:
                cubos[10].setTex({ texturas_colors[54],texturas_colors[2],texturas_colors[54],texturas_colors[9],texturas_colors[54],texturas_colors[26] });
                break;
                ////SEGUNDA FILA 0
            case 11:
                cubos[11].setTex({ texturas_colors[54],texturas_colors[3],texturas_colors[32],texturas_colors[54],texturas_colors[54],texturas_colors[54] });
                break;
            case 12:
                cubos[12].setTex({ texturas_colors[54],texturas_colors[4],texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[54] });
                break;
            case 13:
                cubos[13].setTex({ texturas_colors[54],texturas_colors[5],texturas_colors[54],texturas_colors[12],texturas_colors[54],texturas_colors[54] });
                break;
                ////TERCERA FILA 0
            case 14:
                cubos[14].setTex({ texturas_colors[54],texturas_colors[6],texturas_colors[35],texturas_colors[54],texturas_colors[42],texturas_colors[54] });
                break;
            case 15:
                cubos[15].setTex({ texturas_colors[54],texturas_colors[7],texturas_colors[54],texturas_colors[54],texturas_colors[43],texturas_colors[54] });
                break;
            case 16:
                cubos[16].setTex({ texturas_colors[54],texturas_colors[8],texturas_colors[54],texturas_colors[15],texturas_colors[44],texturas_colors[54] });
                break;


                ////PRIMERA FILA 2
            case 17:
                cubos[17].setTex({ texturas_colors[47],texturas_colors[54],texturas_colors[27],texturas_colors[54],texturas_colors[54],texturas_colors[18] });
                break;
            case 18:
                cubos[18].setTex({ texturas_colors[46],texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[19] });
                break;
            case 19:
                cubos[19].setTex({ texturas_colors[45],texturas_colors[54],texturas_colors[54],texturas_colors[11],texturas_colors[54],texturas_colors[20] });
                break;
                ////SEGUNDA FILA 2
            case 20:
                cubos[20].setTex({ texturas_colors[50],texturas_colors[54],texturas_colors[30],texturas_colors[54],texturas_colors[54],texturas_colors[54] });
                break;
            case 21:
                cubos[21].setTex({ texturas_colors[49],texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[54] });
                break;
            case 22:
                cubos[22].setTex({ texturas_colors[48],texturas_colors[54],texturas_colors[54],texturas_colors[14],texturas_colors[54],texturas_colors[54] });
                break;
                ////TERCERA FILA 2
            case 23:
                cubos[23].setTex({ texturas_colors[53],texturas_colors[54],texturas_colors[33],texturas_colors[54],texturas_colors[36],texturas_colors[54] });
                break;
            case 24:
                cubos[24].setTex({ texturas_colors[52],texturas_colors[54],texturas_colors[54],texturas_colors[54],texturas_colors[37],texturas_colors[54] });
                break;
            case 25:
                cubos[25].setTex({ texturas_colors[51],texturas_colors[54],texturas_colors[54],texturas_colors[17],texturas_colors[38],texturas_colors[54] });
                break;
            }

        }


        //CREANDO CAMADAS
        camadas[0].setCamada({ cubos[17],cubos[18], cubos[19],
                               cubos[0],cubos[1], cubos[2],
                               cubos[8],cubos[9], cubos[10] });

        camadas[1].setCamada({ cubos[20],cubos[21], cubos[22],
                                cubos[3],cubos[26],cubos[4],
                                cubos[11],cubos[12], cubos[13] });

        camadas[2].setCamada({ cubos[23],cubos[24], cubos[25],
                                cubos[5],cubos[6], cubos[7],
                                cubos[14],cubos[15], cubos[16] });

        camadas[3].setCamada({ cubos[17], cubos[0],cubos[8],
                                cubos[20],cubos[3], cubos[11],
                                cubos[23],cubos[5],cubos[14] });

        camadas[4].setCamada({ cubos[18],cubos[1], cubos[9],
                                    cubos[21],cubos[26],cubos[12],
                                    cubos[24],cubos[6], cubos[15] });

        camadas[5].setCamada({ cubos[19],cubos[2], cubos[10],
                                    cubos[22],cubos[4], cubos[13],
                                    cubos[25],cubos[7], cubos[16] });

        camadas[6].setCamada({ cubos[8], cubos[9],cubos[10],
                                cubos[11],cubos[12], cubos[13],
                                cubos[14],cubos[15],cubos[16] });

        camadas[7].setCamada({ cubos[0],cubos[1], cubos[2],
                                    cubos[3],cubos[26],cubos[4],
                                    cubos[5],cubos[6], cubos[7] });

        camadas[8].setCamada({ cubos[17],cubos[18], cubos[19],
                                    cubos[20],cubos[21], cubos[22],
                                    cubos[23],cubos[24], cubos[25] });




        //ATRAS - FRENTE - IZQ - DER - ABAJO - ARRIBA (colores)
        //CAMADAS PARA SOLVER: ARRIBA - IZQ - FRENTE - DER - ATRAS - ABAJO

        //ARRIBA
        for (int i = 0; i < 9; i++) stateCube.push_back(camadas[0].cubos[i].getCorCara(5));

        //IZQ
        for (int i = 0; i < 9; i++) stateCube.push_back(camadas[3].cubos[i].getCorCara(2));

        //FRENTE
        for (int i = 0; i < 9; i++) stateCube.push_back(camadas[6].cubos[i].getCorCara(1));

        //DER
        stateCube.push_back(camadas[5].cubos[2].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[1].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[0].getCorCara(3));

        stateCube.push_back(camadas[5].cubos[5].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[4].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[3].getCorCara(3));

        stateCube.push_back(camadas[5].cubos[8].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[7].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[6].getCorCara(3));

        //ATRAS
        stateCube.push_back(camadas[8].cubos[2].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[1].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[0].getCorCara(0));

        stateCube.push_back(camadas[8].cubos[5].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[4].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[3].getCorCara(0));

        stateCube.push_back(camadas[8].cubos[8].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[7].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[6].getCorCara(0));

        //ABAJO
        stateCube.push_back(camadas[2].cubos[6].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[7].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[8].getCorCara(4));

        stateCube.push_back(camadas[2].cubos[3].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[4].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[5].getCorCara(4));

        stateCube.push_back(camadas[2].cubos[0].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[1].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[2].getCorCara(4));


        fileStateCube();
        
    }


    int getCamadaMasCompleta() {

        int no_cor = 0;

        //ARRIBA
        for (int i = 0; i < 9; i++)
            if (camadas[0].cubos[i].getCorCara(5) != 'w') no_cor++;

        camada_mas_complet.push_back(no_cor);
        no_cor = 0;

        //IZQ
        for (int i = 0; i < 9; i++)
            if (camadas[3].cubos[i].getCorCara(2) != 'o') no_cor++;

        camada_mas_complet.push_back(no_cor);
        no_cor = 0;

        //FRENTE
        for (int i = 0; i < 9; i++) 
            if (camadas[6].cubos[i].getCorCara(1) != 'g') no_cor++;

        camada_mas_complet.push_back(no_cor);
        no_cor = 0;

        //DER
        if (camadas[5].cubos[2].getCorCara(3) != 'r') no_cor++;
        if (camadas[5].cubos[1].getCorCara(3) != 'r') no_cor++;
        if (camadas[5].cubos[0].getCorCara(3) != 'r') no_cor++;

        if (camadas[5].cubos[5].getCorCara(3) != 'r') no_cor++;
        if (camadas[5].cubos[4].getCorCara(3) != 'r') no_cor++;
        if (camadas[5].cubos[3].getCorCara(3) != 'r') no_cor++;

        if (camadas[5].cubos[8].getCorCara(3) != 'r') no_cor++;
        if (camadas[5].cubos[7].getCorCara(3) != 'r') no_cor++;
        if (camadas[5].cubos[6].getCorCara(3) != 'r') no_cor++;

        camada_mas_complet.push_back(no_cor);
        no_cor = 0;

        //ATRAS
        if (camadas[8].cubos[2].getCorCara(0) != 'l') no_cor++;
        if (camadas[8].cubos[1].getCorCara(0) != 'l') no_cor++;
        if (camadas[8].cubos[0].getCorCara(0) != 'l') no_cor++;

        if (camadas[8].cubos[5].getCorCara(0) != 'l') no_cor++;
        if (camadas[8].cubos[4].getCorCara(0) != 'l') no_cor++;
        if (camadas[8].cubos[3].getCorCara(0) != 'l') no_cor++;

        if (camadas[8].cubos[8].getCorCara(0) != 'l') no_cor++;
        if (camadas[8].cubos[7].getCorCara(0) != 'l') no_cor++;
        if (camadas[8].cubos[6].getCorCara(0) != 'l') no_cor++;

        camada_mas_complet.push_back(no_cor);
        no_cor = 0;

        //ABAJO
        if (camadas[2].cubos[6].getCorCara(4) != 'y') no_cor++;
        if (camadas[2].cubos[7].getCorCara(4) != 'y') no_cor++;
        if (camadas[2].cubos[8].getCorCara(4) != 'y') no_cor++;

        if (camadas[2].cubos[3].getCorCara(4) != 'y') no_cor++;
        if (camadas[2].cubos[4].getCorCara(4) != 'y') no_cor++;
        if (camadas[2].cubos[5].getCorCara(4) != 'y') no_cor++;

        if (camadas[2].cubos[0].getCorCara(4) != 'y') no_cor++;
        if (camadas[2].cubos[1].getCorCara(4) != 'y') no_cor++;
        if (camadas[2].cubos[2].getCorCara(4) != 'y') no_cor++;
        
        camada_mas_complet.push_back(no_cor);
        no_cor = 0;

        pair<int, int> mini = { camada_mas_complet[0],0};
        for (int i = 0; i < camada_mas_complet.size(); i++) {
            if (camada_mas_complet[i] < mini.first) {
                mini = { camada_mas_complet[i] ,i};
            }
        }

        camada_mas_complet.clear();

        return mini.second;

    }


    void updateStateCubo(Camada camadas[9]) {
        stateCube.clear();

        //CAMADAS PARA SOLVER: ARRIBA - IZQ - FRENTE - DER - ATRAS - ABAJO

        //ARRIBA
        for (int i = 0; i < 9; i++) stateCube.push_back(camadas[0].cubos[i].getCorCara(5));

        //IZQ
        for (int i = 0; i < 9; i++) stateCube.push_back(camadas[3].cubos[i].getCorCara(2));

        //FRENTE
        for (int i = 0; i < 9; i++) stateCube.push_back(camadas[6].cubos[i].getCorCara(1));

        //DER
        stateCube.push_back(camadas[5].cubos[2].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[1].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[0].getCorCara(3));

        stateCube.push_back(camadas[5].cubos[5].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[4].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[3].getCorCara(3));

        stateCube.push_back(camadas[5].cubos[8].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[7].getCorCara(3));
        stateCube.push_back(camadas[5].cubos[6].getCorCara(3));

        //ATRAS
        stateCube.push_back(camadas[8].cubos[2].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[1].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[0].getCorCara(0));

        stateCube.push_back(camadas[8].cubos[5].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[4].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[3].getCorCara(0));

        stateCube.push_back(camadas[8].cubos[8].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[7].getCorCara(0));
        stateCube.push_back(camadas[8].cubos[6].getCorCara(0));

        //ABAJO
        stateCube.push_back(camadas[2].cubos[6].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[7].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[8].getCorCara(4));

        stateCube.push_back(camadas[2].cubos[3].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[4].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[5].getCorCara(4));

        stateCube.push_back(camadas[2].cubos[0].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[1].getCorCara(4));
        stateCube.push_back(camadas[2].cubos[2].getCorCara(4));


        fileStateCube();

    }
   

    //UPDATE COLORS HORIZONTAL

    void updateCh(vector<vector<float>>& a) {
        vector<vector<float>> b;
        queue<vector<float>> q;
        q.push(a[0]);
        b.push_back(a[3]);

        q.push(a[1]);
        b.push_back(a[2]);

        b.push_back(q.front());
        q.pop();
        b.push_back(q.front());
        q.pop();

        b.push_back(a[4]);
        b.push_back(a[5]);

        a.clear();
        a = b;
    }

    void updateChA(vector<vector<float>>& a) {
        vector<vector<float>> b;
        deque<vector<float>> q;
        q.push_back(a[0]);
        b.push_back(a[2]);

        q.push_back(a[1]);
        b.push_back(a[3]);

        b.push_back(q.back());
        q.pop_back();
        b.push_back(q.back());
        q.pop_back();

        b.push_back(a[4]);
        b.push_back(a[5]);

        a.clear();
        a = b;
    }

    //UPDATE COLORS VERTICAL

    void updateCh2(vector<vector<float>>& a) {
        vector<vector<float>> b;
        deque<vector<float>> q;

        q.push_back(a[0]);
        b.push_back(a[4]);

        q.push_back(a[1]);
        b.push_back(a[5]);

        b.push_back(a[2]);
        b.push_back(a[3]);

        b.push_back(q.back());
        q.pop_back();
        b.push_back(q.back());
        q.pop_back();

        a.clear();
        a = b;
    }

    void updateCh2A(vector<vector<float>>& a) {
        vector<vector<float>> b;
        queue<vector<float>> q;

        q.push(a[0]);
        b.push_back(a[5]);

        q.push(a[1]);
        b.push_back(a[4]);

        b.push_back(a[2]);
        b.push_back(a[3]);

        b.push_back(q.front());
        q.pop();
        b.push_back(q.front());
        q.pop();

        a.clear();
        a = b;
    }

    //UPDATE COLORS VERTICAL-HORIZONTAL

    void updateCh3(vector<vector<float>>& a) {
        vector<vector<float>> b;
        deque<vector<float>> q;

        b.push_back(a[0]);
        b.push_back(a[1]);

        q.push_back(a[2]);
        b.push_back(a[4]);

        q.push_back(a[3]);
        b.push_back(a[5]);

        b.push_back(q.back());
        q.pop_back();
        b.push_back(q.back());
        q.pop_back();

        a.clear();
        a = b;
    }

    void updateCh3A(vector<vector<float>>& a) {
        vector<vector<float>> b;
        queue<vector<float>> q;

        b.push_back(a[0]);
        b.push_back(a[1]);

        q.push(a[2]);
        b.push_back(a[5]);

        q.push(a[3]);
        b.push_back(a[4]);

        b.push_back(q.front());
        q.pop();
        b.push_back(q.front());
        q.pop();

        a.clear();
        a = b;
    }

    

    void changeCubes(NodeCube &cubOrigen, vector<vector<float>> cubRefCor, bool cor ,int or, bool rot) {

        cubOrigen.model = glm::mat4(1.0f);
        cubOrigen.model = glm::translate(cubOrigen.model, cubOrigen.cubePosition);

        if (cor) {
            if (or == 0) {
                if(rot) updateCh(cubRefCor);
                else  updateChA(cubRefCor);
            }
            else if (or == 1) {
                if (rot) updateCh2(cubRefCor);
                else  updateCh2A(cubRefCor);
            }
            else if (or == 2) {
                if (rot) updateCh3(cubRefCor);
                else  updateCh3A(cubRefCor);
            }

            cubOrigen.colors = cubRefCor;
        }

    }

    void updatefinalCamadas_Cors(int idx,int or, bool rotation) {

        ///punto de modificacion y estado

        vector<NodeCube> tmp;
        if (or == 0) {
            if (rotation) {

                tmp.push_back(camadas[idx].cubos[2]);
                tmp.push_back(camadas[idx].cubos[5]);
                tmp.push_back(camadas[idx].cubos[8]);

                tmp.push_back(camadas[idx].cubos[1]);
                tmp.push_back(camadas[idx].cubos[4]);
                tmp.push_back(camadas[idx].cubos[7]);

                tmp.push_back(camadas[idx].cubos[0]);
                tmp.push_back(camadas[idx].cubos[3]);
                tmp.push_back(camadas[idx].cubos[6]);

            }
            else {

                tmp.push_back(camadas[idx].cubos[6]);
                tmp.push_back(camadas[idx].cubos[3]);
                tmp.push_back(camadas[idx].cubos[0]);

                tmp.push_back(camadas[idx].cubos[7]);
                tmp.push_back(camadas[idx].cubos[4]);
                tmp.push_back(camadas[idx].cubos[1]);

                tmp.push_back(camadas[idx].cubos[8]);
                tmp.push_back(camadas[idx].cubos[5]);
                tmp.push_back(camadas[idx].cubos[2]);
            }

        }

        else if (or == 1) {

            if (rotation) {
                tmp.push_back(camadas[idx].cubos[6]);
                tmp.push_back(camadas[idx].cubos[3]);
                tmp.push_back(camadas[idx].cubos[0]);

                tmp.push_back(camadas[idx].cubos[7]);
                tmp.push_back(camadas[idx].cubos[4]);
                tmp.push_back(camadas[idx].cubos[1]);

                tmp.push_back(camadas[idx].cubos[8]);
                tmp.push_back(camadas[idx].cubos[5]);
                tmp.push_back(camadas[idx].cubos[2]);
            }
            else {
                tmp.push_back(camadas[idx].cubos[2]);
                tmp.push_back(camadas[idx].cubos[5]);
                tmp.push_back(camadas[idx].cubos[8]);

                tmp.push_back(camadas[idx].cubos[1]);
                tmp.push_back(camadas[idx].cubos[4]);
                tmp.push_back(camadas[idx].cubos[7]);

                tmp.push_back(camadas[idx].cubos[0]);
                tmp.push_back(camadas[idx].cubos[3]);
                tmp.push_back(camadas[idx].cubos[6]);
            }

        }

        else if (or == 2) {

            if (rotation) {
                tmp.push_back(camadas[idx].cubos[6]);
                tmp.push_back(camadas[idx].cubos[3]);
                tmp.push_back(camadas[idx].cubos[0]);

                tmp.push_back(camadas[idx].cubos[7]);
                tmp.push_back(camadas[idx].cubos[4]);
                tmp.push_back(camadas[idx].cubos[1]);

                tmp.push_back(camadas[idx].cubos[8]);
                tmp.push_back(camadas[idx].cubos[5]);
                tmp.push_back(camadas[idx].cubos[2]);
            }
            else {
                tmp.push_back(camadas[idx].cubos[2]);
                tmp.push_back(camadas[idx].cubos[5]);
                tmp.push_back(camadas[idx].cubos[8]);

                tmp.push_back(camadas[idx].cubos[1]);
                tmp.push_back(camadas[idx].cubos[4]);
                tmp.push_back(camadas[idx].cubos[7]);

                tmp.push_back(camadas[idx].cubos[0]);
                tmp.push_back(camadas[idx].cubos[3]);
                tmp.push_back(camadas[idx].cubos[6]);
            }

        }


        ///CAMADA HORIZONTAL

        if (idx == 0) {

            changeCubes(cubos[8], tmp[6].colors,1,0, rotation);
            changeCubes(cubos[9], tmp[7].colors, 1, 0, rotation);
            changeCubes(cubos[10], tmp[8].colors, 1, 0, rotation);

            changeCubes(cubos[0], tmp[3].colors, 1, 0, rotation);
            changeCubes(cubos[1], tmp[4].colors, 1, 0, rotation);
            changeCubes(cubos[2], tmp[5].colors, 1, 0, rotation);

            changeCubes(cubos[17], tmp[0].colors, 1, 0, rotation);
            changeCubes(cubos[18], tmp[1].colors, 1, 0, rotation);
            changeCubes(cubos[19], tmp[2].colors, 1, 0, rotation);

        }

        else if (idx == 1) {

            changeCubes(cubos[11], tmp[6].colors, 1, 0, rotation);
            changeCubes(cubos[12], tmp[7].colors, 1, 0, rotation);
            changeCubes(cubos[13], tmp[8].colors, 1, 0, rotation);

            changeCubes(cubos[3], tmp[3].colors, 1, 0, rotation);
            changeCubes(cubos[26], tmp[4].colors,0,0, rotation);
            changeCubes(cubos[4], tmp[5].colors, 1, 0, rotation);

            changeCubes(cubos[20], tmp[0].colors, 1, 0, rotation);
            changeCubes(cubos[21], tmp[1].colors, 1, 0, rotation);
            changeCubes(cubos[22], tmp[2].colors, 1, 0, rotation);

        }

        else if (idx == 2) {

            changeCubes(cubos[14], tmp[6].colors, 1, 0, rotation);
            changeCubes(cubos[15], tmp[7].colors, 1, 0, rotation);
            changeCubes(cubos[16], tmp[8].colors, 1, 0, rotation);

            changeCubes(cubos[5], tmp[3].colors, 1, 0, rotation);
            changeCubes(cubos[6], tmp[4].colors, 1, 0, rotation);
            changeCubes(cubos[7], tmp[5].colors, 1, 0, rotation);

            changeCubes(cubos[23], tmp[0].colors, 1, 0, rotation);
            changeCubes(cubos[24], tmp[1].colors, 1, 0, rotation);
            changeCubes(cubos[25], tmp[2].colors, 1, 0, rotation);

        }

        ///CAMADA VERTICAL

        else if (idx == 3) {
            
            changeCubes(cubos[23], tmp[6].colors, 1, 1, rotation);
            changeCubes(cubos[5], tmp[7].colors, 1, 1, rotation);
            changeCubes(cubos[14], tmp[8].colors, 1, 1, rotation);

            changeCubes(cubos[20], tmp[3].colors, 1, 1, rotation);
            changeCubes(cubos[3], tmp[4].colors, 1, 1, rotation);
            changeCubes(cubos[11], tmp[5].colors, 1, 1, rotation);

            changeCubes(cubos[17], tmp[0].colors, 1, 1, rotation);
            changeCubes(cubos[0], tmp[1].colors, 1, 1, rotation);
            changeCubes(cubos[8], tmp[2].colors, 1, 1, rotation);

        }

        else if (idx == 4) {

            changeCubes(cubos[9], tmp[2].colors, 1, 1, rotation);
            changeCubes(cubos[12], tmp[5].colors, 1, 1, rotation);
            changeCubes(cubos[15], tmp[8].colors, 1, 1, rotation);

            changeCubes(cubos[1], tmp[1].colors, 1, 1, rotation);
            changeCubes(cubos[26], tmp[4].colors,0,1, rotation);
            changeCubes(cubos[6], tmp[7].colors, 1, 1, rotation);

            changeCubes(cubos[18], tmp[0].colors, 1, 1, rotation);
            changeCubes(cubos[21], tmp[3].colors, 1, 1, rotation);
            changeCubes(cubos[24], tmp[6].colors, 1, 1, rotation);

        }

        else if (idx == 5) {

            changeCubes(cubos[10], tmp[2].colors, 1, 1, rotation);
            changeCubes(cubos[13], tmp[5].colors, 1, 1, rotation);
            changeCubes(cubos[16], tmp[8].colors, 1, 1, rotation);

            changeCubes(cubos[2], tmp[1].colors, 1, 1, rotation);
            changeCubes(cubos[4], tmp[4].colors, 1, 1, rotation);
            changeCubes(cubos[7], tmp[7].colors, 1, 1, rotation);

            changeCubes(cubos[19], tmp[0].colors, 1, 1, rotation);
            changeCubes(cubos[22], tmp[3].colors, 1, 1, rotation);
            changeCubes(cubos[25], tmp[6].colors, 1, 1, rotation);

        }

        ///CAMADA VERTICAL-HORIZONTAL

        else if (idx == 6) {

            changeCubes(cubos[10], tmp[2].colors, 1, 2, rotation);
            changeCubes(cubos[13], tmp[5].colors, 1, 2, rotation);
            changeCubes(cubos[16], tmp[8].colors, 1, 2, rotation);

            changeCubes(cubos[9], tmp[1].colors, 1, 2, rotation);
            changeCubes(cubos[12], tmp[4].colors, 1, 2, rotation);
            changeCubes(cubos[15], tmp[7].colors, 1, 2, rotation);

            changeCubes(cubos[8], tmp[0].colors, 1, 2, rotation);
            changeCubes(cubos[11], tmp[3].colors, 1, 2, rotation);
            changeCubes(cubos[14], tmp[6].colors, 1, 2, rotation);

        }

        else if (idx == 7) {

            changeCubes(cubos[2], tmp[2].colors, 1, 2, rotation);
            changeCubes(cubos[4], tmp[5].colors, 1, 2, rotation);
            changeCubes(cubos[7], tmp[8].colors, 1, 2, rotation);

            changeCubes(cubos[1], tmp[1].colors, 1, 2, rotation);
            changeCubes(cubos[26], tmp[4].colors,0,2, rotation);
            changeCubes(cubos[6], tmp[7].colors, 1, 2, rotation);

            changeCubes(cubos[0], tmp[0].colors, 1, 2, rotation);
            changeCubes(cubos[3], tmp[3].colors, 1, 2, rotation);
            changeCubes(cubos[5], tmp[6].colors, 1, 2, rotation);

        }

        else if (idx == 8) {

            changeCubes(cubos[19], tmp[2].colors, 1, 2, rotation);
            changeCubes(cubos[22], tmp[5].colors, 1, 2, rotation);
            changeCubes(cubos[25], tmp[8].colors, 1, 2, rotation);

            changeCubes(cubos[18], tmp[1].colors, 1, 2, rotation);
            changeCubes(cubos[21], tmp[4].colors, 1, 2, rotation);
            changeCubes(cubos[24], tmp[7].colors, 1, 2, rotation);

            changeCubes(cubos[17], tmp[0].colors, 1, 2, rotation);
            changeCubes(cubos[20], tmp[3].colors, 1, 2, rotation);
            changeCubes(cubos[23], tmp[6].colors, 1, 2, rotation);

        }
        
        //////////////////
        
        //actualizando camadas

        camadas[0].setCamada({ cubos[17],cubos[18], cubos[19],
                               cubos[0],cubos[1], cubos[2],
                               cubos[8],cubos[9], cubos[10] });


        camadas[1].setCamada({ cubos[20],cubos[21], cubos[22],
                                cubos[3],cubos[26],cubos[4],
                                cubos[11],cubos[12], cubos[13] });


        camadas[2].setCamada({ cubos[23],cubos[24], cubos[25],
                                cubos[5],cubos[6], cubos[7],
                                cubos[14],cubos[15], cubos[16] });


        camadas[3].setCamada({ cubos[17], cubos[0],cubos[8],
                                cubos[20],cubos[3], cubos[11],
                                cubos[23],cubos[5],cubos[14] });


        camadas[4].setCamada({ cubos[18],cubos[1], cubos[9],
                                    cubos[21],cubos[26],cubos[12],
                                    cubos[24],cubos[6], cubos[15] });


        camadas[5].setCamada({ cubos[19],cubos[2], cubos[10],
                                    cubos[22],cubos[4], cubos[13],
                                    cubos[25],cubos[7], cubos[16] });


        camadas[6].setCamada({ cubos[8], cubos[9],cubos[10],
                                cubos[11],cubos[12], cubos[13],
                                cubos[14],cubos[15],cubos[16] });


        camadas[7].setCamada({ cubos[0],cubos[1], cubos[2],
                                    cubos[3],cubos[26],cubos[4],
                                    cubos[5],cubos[6], cubos[7] });


        camadas[8].setCamada({ cubos[17],cubos[18], cubos[19],
                                    cubos[20],cubos[21], cubos[22],
                                    cubos[23],cubos[24], cubos[25] });



        //ATRAS - FRENTE - IZQ - DER - ABAJO - ARRIBA
        updateStateCubo(camadas);
     
    }



    //UPDATE TEXTURES HORIZONTAL

    void updateCh(vector<unsigned int>& a) {
        vector<unsigned int> b;
        queue<unsigned int> q;
        q.push(a[0]);
        b.push_back(a[3]);

        q.push(a[1]);
        b.push_back(a[2]);

        b.push_back(q.front());
        q.pop();
        b.push_back(q.front());
        q.pop();

        b.push_back(a[4]);
        b.push_back(a[5]);

        a.clear();
        a = b;
    }

    void updateChA(vector<unsigned int>& a) {
        vector<unsigned int> b;
        deque<unsigned int> q;
        q.push_back(a[0]);
        b.push_back(a[2]);

        q.push_back(a[1]);
        b.push_back(a[3]);

        b.push_back(q.back());
        q.pop_back();
        b.push_back(q.back());
        q.pop_back();

        b.push_back(a[4]);
        b.push_back(a[5]);

        a.clear();
        a = b;
    }

    //UPDATE TEXTURES VERTICAL

    void updateCh2(vector<unsigned int>& a) {
        vector<unsigned int> b;
        deque<unsigned int> q;

        q.push_back(a[0]);
        b.push_back(a[4]);

        q.push_back(a[1]);
        b.push_back(a[5]);

        b.push_back(a[2]);
        b.push_back(a[3]);

        b.push_back(q.back());
        q.pop_back();
        b.push_back(q.back());
        q.pop_back();

        a.clear();
        a = b;
    }

    void updateCh2A(vector<unsigned int>& a) {
        vector<unsigned int> b;
        queue<unsigned int> q;

        q.push(a[0]);
        b.push_back(a[5]);

        q.push(a[1]);
        b.push_back(a[4]);

        b.push_back(a[2]);
        b.push_back(a[3]);

        b.push_back(q.front());
        q.pop();
        b.push_back(q.front());
        q.pop();

        a.clear();
        a = b;
    }

    //UPDATE TEXTURES VERTICAL-HORIZONTAL

    void updateCh3(vector<unsigned int>& a) {
        vector<unsigned int> b;
        deque<unsigned int> q;

        b.push_back(a[0]);
        b.push_back(a[1]);

        q.push_back(a[2]);
        b.push_back(a[4]);

        q.push_back(a[3]);
        b.push_back(a[5]);

        b.push_back(q.back());
        q.pop_back();
        b.push_back(q.back());
        q.pop_back();

        a.clear();
        a = b;
    }

    void updateCh3A(vector<unsigned int>& a) {
        vector<unsigned int> b;
        queue<unsigned int> q;

        b.push_back(a[0]);
        b.push_back(a[1]);

        q.push(a[2]);
        b.push_back(a[5]);

        q.push(a[3]);
        b.push_back(a[4]);

        b.push_back(q.front());
        q.pop();
        b.push_back(q.front());
        q.pop();

        a.clear();
        a = b;
    }



    void changeCubes(NodeCube& cubOrigen, vector<unsigned int> cubRefCor, bool cor, int or , bool rot) {

        cubOrigen.model = glm::mat4(1.0f);
        cubOrigen.model = glm::translate(cubOrigen.model, cubOrigen.cubePosition);

        if (cor) {
            if (or == 0) {
                if (rot) updateCh(cubRefCor);
                else  updateChA(cubRefCor);
            }
            else if (or == 1) {
                if (rot) updateCh2(cubRefCor);
                else  updateCh2A(cubRefCor);
            }
            else if (or == 2) {
                if (rot) updateCh3(cubRefCor);
                else  updateCh3A(cubRefCor);
            }

            cubOrigen.cube_textures = cubRefCor;
        }

    }


    void updatefinalCamadas(int idx, int or , bool rotation, int& mov_cam) {

        ///punto de modificacion y estado

        vector<NodeCube> tmp;
        if (or == 0) {
            if (rotation) {

                tmp.push_back(camadas[idx].cubos[2]);
                tmp.push_back(camadas[idx].cubos[5]);
                tmp.push_back(camadas[idx].cubos[8]);

                tmp.push_back(camadas[idx].cubos[1]);
                tmp.push_back(camadas[idx].cubos[4]);
                tmp.push_back(camadas[idx].cubos[7]);

                tmp.push_back(camadas[idx].cubos[0]);
                tmp.push_back(camadas[idx].cubos[3]);
                tmp.push_back(camadas[idx].cubos[6]);

            }
            else {

                tmp.push_back(camadas[idx].cubos[6]);
                tmp.push_back(camadas[idx].cubos[3]);
                tmp.push_back(camadas[idx].cubos[0]);

                tmp.push_back(camadas[idx].cubos[7]);
                tmp.push_back(camadas[idx].cubos[4]);
                tmp.push_back(camadas[idx].cubos[1]);

                tmp.push_back(camadas[idx].cubos[8]);
                tmp.push_back(camadas[idx].cubos[5]);
                tmp.push_back(camadas[idx].cubos[2]);
            }

        }

        else if (or == 1) {

            if (rotation) {
                tmp.push_back(camadas[idx].cubos[6]);
                tmp.push_back(camadas[idx].cubos[3]);
                tmp.push_back(camadas[idx].cubos[0]);

                tmp.push_back(camadas[idx].cubos[7]);
                tmp.push_back(camadas[idx].cubos[4]);
                tmp.push_back(camadas[idx].cubos[1]);

                tmp.push_back(camadas[idx].cubos[8]);
                tmp.push_back(camadas[idx].cubos[5]);
                tmp.push_back(camadas[idx].cubos[2]);
            }
            else {
                tmp.push_back(camadas[idx].cubos[2]);
                tmp.push_back(camadas[idx].cubos[5]);
                tmp.push_back(camadas[idx].cubos[8]);

                tmp.push_back(camadas[idx].cubos[1]);
                tmp.push_back(camadas[idx].cubos[4]);
                tmp.push_back(camadas[idx].cubos[7]);

                tmp.push_back(camadas[idx].cubos[0]);
                tmp.push_back(camadas[idx].cubos[3]);
                tmp.push_back(camadas[idx].cubos[6]);
            }

        }

        else if (or == 2) {

            if (rotation) {
                tmp.push_back(camadas[idx].cubos[6]);
                tmp.push_back(camadas[idx].cubos[3]);
                tmp.push_back(camadas[idx].cubos[0]);

                tmp.push_back(camadas[idx].cubos[7]);
                tmp.push_back(camadas[idx].cubos[4]);
                tmp.push_back(camadas[idx].cubos[1]);

                tmp.push_back(camadas[idx].cubos[8]);
                tmp.push_back(camadas[idx].cubos[5]);
                tmp.push_back(camadas[idx].cubos[2]);
            }
            else {
                tmp.push_back(camadas[idx].cubos[2]);
                tmp.push_back(camadas[idx].cubos[5]);
                tmp.push_back(camadas[idx].cubos[8]);

                tmp.push_back(camadas[idx].cubos[1]);
                tmp.push_back(camadas[idx].cubos[4]);
                tmp.push_back(camadas[idx].cubos[7]);

                tmp.push_back(camadas[idx].cubos[0]);
                tmp.push_back(camadas[idx].cubos[3]);
                tmp.push_back(camadas[idx].cubos[6]);
            }

        }


        ///CAMADA HORIZONTAL

        if (idx == 0) {

            changeCubes(cubos[8], tmp[6].cube_textures, 1, 0, rotation);
            changeCubes(cubos[9], tmp[7].cube_textures, 1, 0, rotation);
            changeCubes(cubos[10], tmp[8].cube_textures, 1, 0, rotation);

            changeCubes(cubos[0], tmp[3].cube_textures, 1, 0, rotation);
            changeCubes(cubos[1], tmp[4].cube_textures, 1, 0, rotation);
            changeCubes(cubos[2], tmp[5].cube_textures, 1, 0, rotation);

            changeCubes(cubos[17], tmp[0].cube_textures, 1, 0, rotation);
            changeCubes(cubos[18], tmp[1].cube_textures, 1, 0, rotation);
            changeCubes(cubos[19], tmp[2].cube_textures, 1, 0, rotation);

        }

        else if (idx == 1) {

            changeCubes(cubos[11], tmp[6].cube_textures, 1, 0, rotation);
            changeCubes(cubos[12], tmp[7].cube_textures, 1, 0, rotation);
            changeCubes(cubos[13], tmp[8].cube_textures, 1, 0, rotation);

            changeCubes(cubos[3], tmp[3].cube_textures, 1, 0, rotation);
            changeCubes(cubos[26], tmp[4].cube_textures, 0, 0, rotation);
            changeCubes(cubos[4], tmp[5].cube_textures, 1, 0, rotation);

            changeCubes(cubos[20], tmp[0].cube_textures, 1, 0, rotation);
            changeCubes(cubos[21], tmp[1].cube_textures, 1, 0, rotation);
            changeCubes(cubos[22], tmp[2].cube_textures, 1, 0, rotation);

        }

        else if (idx == 2) {

            changeCubes(cubos[14], tmp[6].cube_textures, 1, 0, rotation);
            changeCubes(cubos[15], tmp[7].cube_textures, 1, 0, rotation);
            changeCubes(cubos[16], tmp[8].cube_textures, 1, 0, rotation);

            changeCubes(cubos[5], tmp[3].cube_textures, 1, 0, rotation);
            changeCubes(cubos[6], tmp[4].cube_textures, 1, 0, rotation);
            changeCubes(cubos[7], tmp[5].cube_textures, 1, 0, rotation);

            changeCubes(cubos[23], tmp[0].cube_textures, 1, 0, rotation);
            changeCubes(cubos[24], tmp[1].cube_textures, 1, 0, rotation);
            changeCubes(cubos[25], tmp[2].cube_textures, 1, 0, rotation);

        }

        ///CAMADA VERTICAL

        else if (idx == 3) {

            changeCubes(cubos[23], tmp[6].cube_textures, 1, 1, rotation);
            changeCubes(cubos[5], tmp[7].cube_textures, 1, 1, rotation);
            changeCubes(cubos[14], tmp[8].cube_textures, 1, 1, rotation);

            changeCubes(cubos[20], tmp[3].cube_textures, 1, 1, rotation);
            changeCubes(cubos[3], tmp[4].cube_textures, 1, 1, rotation);
            changeCubes(cubos[11], tmp[5].cube_textures, 1, 1, rotation);

            changeCubes(cubos[17], tmp[0].cube_textures, 1, 1, rotation);
            changeCubes(cubos[0], tmp[1].cube_textures, 1, 1, rotation);
            changeCubes(cubos[8], tmp[2].cube_textures, 1, 1, rotation);


        }

        else if (idx == 4) {

            changeCubes(cubos[9], tmp[2].cube_textures, 1, 1, rotation);
            changeCubes(cubos[12], tmp[5].cube_textures, 1, 1, rotation);
            changeCubes(cubos[15], tmp[8].cube_textures, 1, 1, rotation);

            changeCubes(cubos[1], tmp[1].cube_textures, 1, 1, rotation);
            changeCubes(cubos[26], tmp[4].cube_textures, 0, 1, rotation);
            changeCubes(cubos[6], tmp[7].cube_textures, 1, 1, rotation);

            changeCubes(cubos[18], tmp[0].cube_textures, 1, 1, rotation);
            changeCubes(cubos[21], tmp[3].cube_textures, 1, 1, rotation);
            changeCubes(cubos[24], tmp[6].cube_textures, 1, 1, rotation);

        }

        else if (idx == 5) {

            changeCubes(cubos[10], tmp[2].cube_textures, 1, 1, rotation);
            changeCubes(cubos[13], tmp[5].cube_textures, 1, 1, rotation);
            changeCubes(cubos[16], tmp[8].cube_textures, 1, 1, rotation);

            changeCubes(cubos[2], tmp[1].cube_textures, 1, 1, rotation);
            changeCubes(cubos[4], tmp[4].cube_textures, 1, 1, rotation);
            changeCubes(cubos[7], tmp[7].cube_textures, 1, 1, rotation);

            changeCubes(cubos[19], tmp[0].cube_textures, 1, 1, rotation);
            changeCubes(cubos[22], tmp[3].cube_textures, 1, 1, rotation);
            changeCubes(cubos[25], tmp[6].cube_textures, 1, 1, rotation);

        }

        ///CAMADA VERTICAL-HORIZONTAL

        else if (idx == 6) {

            changeCubes(cubos[10], tmp[2].cube_textures, 1, 2, rotation);
            changeCubes(cubos[13], tmp[5].cube_textures, 1, 2, rotation);
            changeCubes(cubos[16], tmp[8].cube_textures, 1, 2, rotation);

            changeCubes(cubos[9], tmp[1].cube_textures, 1, 2, rotation);
            changeCubes(cubos[12], tmp[4].cube_textures, 1, 2, rotation);
            changeCubes(cubos[15], tmp[7].cube_textures, 1, 2, rotation);

            changeCubes(cubos[8], tmp[0].cube_textures, 1, 2, rotation);
            changeCubes(cubos[11], tmp[3].cube_textures, 1, 2, rotation);
            changeCubes(cubos[14], tmp[6].cube_textures, 1, 2, rotation);

            
            cubos[10].model_text = camadas[idx].model_text_ref;
            cubos[13].model_text = camadas[idx].model_text_ref;
            cubos[16].model_text = camadas[idx].model_text_ref;
            cubos[9].model_text = camadas[idx].model_text_ref;
            cubos[12].model_text = camadas[idx].model_text_ref;
            cubos[15].model_text = camadas[idx].model_text_ref;
            cubos[8].model_text = camadas[idx].model_text_ref;
            cubos[11].model_text = camadas[idx].model_text_ref;
            cubos[14].model_text = camadas[idx].model_text_ref;

            
            
        }

        else if (idx == 7) {

            changeCubes(cubos[2], tmp[2].cube_textures, 1, 2, rotation);
            changeCubes(cubos[4], tmp[5].cube_textures, 1, 2, rotation);
            changeCubes(cubos[7], tmp[8].cube_textures, 1, 2, rotation);

            changeCubes(cubos[1], tmp[1].cube_textures, 1, 2, rotation);
            changeCubes(cubos[26], tmp[4].cube_textures, 0, 2, rotation);
            changeCubes(cubos[6], tmp[7].cube_textures, 1, 2, rotation);

            changeCubes(cubos[0], tmp[0].cube_textures, 1, 2, rotation);
            changeCubes(cubos[3], tmp[3].cube_textures, 1, 2, rotation);
            changeCubes(cubos[5], tmp[6].cube_textures, 1, 2, rotation);


        }

        else if (idx == 8) {

            changeCubes(cubos[19], tmp[2].cube_textures, 1, 2, rotation);
            changeCubes(cubos[22], tmp[5].cube_textures, 1, 2, rotation);
            changeCubes(cubos[25], tmp[8].cube_textures, 1, 2, rotation);

            changeCubes(cubos[18], tmp[1].cube_textures, 1, 2, rotation);
            changeCubes(cubos[21], tmp[4].cube_textures, 1, 2, rotation);
            changeCubes(cubos[24], tmp[7].cube_textures, 1, 2, rotation);

            changeCubes(cubos[17], tmp[0].cube_textures, 1, 2, rotation);
            changeCubes(cubos[20], tmp[3].cube_textures, 1, 2, rotation);
            changeCubes(cubos[23], tmp[6].cube_textures, 1, 2, rotation);

            /*
            cubos[19].model_text = camadas[idx].model_text_ref;
            cubos[22].model_text = camadas[idx].model_text_ref;
            cubos[25].model_text = camadas[idx].model_text_ref;
            cubos[18].model_text = camadas[idx].model_text_ref;
            cubos[21].model_text = camadas[idx].model_text_ref;
            cubos[24].model_text = camadas[idx].model_text_ref;
            cubos[17].model_text = camadas[idx].model_text_ref;
            cubos[20].model_text = camadas[idx].model_text_ref;
            cubos[23].model_text = camadas[idx].model_text_ref;
            */

        }

        //////////////////

        //actualizando camadas

        camadas[0].setCamada({ cubos[17],cubos[18], cubos[19],
                               cubos[0],cubos[1], cubos[2],
                               cubos[8],cubos[9], cubos[10] });


        camadas[1].setCamada({ cubos[20],cubos[21], cubos[22],
                                cubos[3],cubos[26],cubos[4],
                                cubos[11],cubos[12], cubos[13] });


        camadas[2].setCamada({ cubos[23],cubos[24], cubos[25],
                                cubos[5],cubos[6], cubos[7],
                                cubos[14],cubos[15], cubos[16] });


        camadas[3].setCamada({ cubos[17], cubos[0],cubos[8],
                                cubos[20],cubos[3], cubos[11],
                                cubos[23],cubos[5],cubos[14] });


        camadas[4].setCamada({ cubos[18],cubos[1], cubos[9],
                                    cubos[21],cubos[26],cubos[12],
                                    cubos[24],cubos[6], cubos[15] });


        camadas[5].setCamada({ cubos[19],cubos[2], cubos[10],
                                    cubos[22],cubos[4], cubos[13],
                                    cubos[25],cubos[7], cubos[16] });


        camadas[6].setCamada({ cubos[8], cubos[9],cubos[10],
                                cubos[11],cubos[12], cubos[13],
                                cubos[14],cubos[15],cubos[16] });


        camadas[7].setCamada({ cubos[0],cubos[1], cubos[2],
                                    cubos[3],cubos[26],cubos[4],
                                    cubos[5],cubos[6], cubos[7] });


        camadas[8].setCamada({ cubos[17],cubos[18], cubos[19],
                                    cubos[20],cubos[21], cubos[22],
                                    cubos[23],cubos[24], cubos[25] });



        //ATRAS - FRENTE - IZQ - DER - ABAJO - ARRIBA
        updateStateCubo(camadas);

        mov_cam = getCamadaMasCompleta();
        //cout << "Camada mas completa: " << mov_cam << endl;

    }



    void updateCamadas(int idx) {

        if (camadas[idx].animation){

            if (idx == 0) {

                camadas[0].model_camada = camadas[0].model_center;
                camadas[0].model_camada = glm::translate(camadas[0].model_camada, camadas[0].cubePos[0]);
                camadas[0].cubos[3].setModel(camadas[0].model_camada);

                camadas[0].model_camada = camadas[0].model_center;
                camadas[0].model_camada = glm::translate(camadas[0].model_camada, camadas[0].cubePos[2]);
                camadas[0].cubos[5].setModel(camadas[0].model_camada);

                camadas[0].model_camada = camadas[0].model_center;
                camadas[0].model_camada = glm::translate(camadas[0].model_camada, camadas[0].cubePos[8]);
                camadas[0].cubos[6].setModel(camadas[0].model_camada);

                camadas[0].model_camada = camadas[0].model_center;
                camadas[0].model_camada = glm::translate(camadas[0].model_camada, camadas[0].cubePos[9]);
                camadas[0].cubos[7].setModel(camadas[0].model_camada);

                camadas[0].model_camada = camadas[0].model_center;
                camadas[0].model_camada = glm::translate(camadas[0].model_camada, camadas[0].cubePos[10]);
                camadas[0].cubos[8].setModel(camadas[0].model_camada);

                camadas[0].model_camada = camadas[0].model_center;
                camadas[0].model_camada = glm::translate(camadas[0].model_camada, camadas[0].cubePos[17]);
                camadas[0].cubos[0].setModel(camadas[0].model_camada);

                camadas[0].model_camada = camadas[0].model_center;
                camadas[0].model_camada = glm::translate(camadas[0].model_camada, camadas[0].cubePos[18]);
                camadas[0].cubos[1].setModel(camadas[0].model_camada);

                camadas[0].model_camada = camadas[0].model_center;
                camadas[0].model_camada = glm::translate(camadas[0].model_camada, camadas[0].cubePos[19]);
                camadas[0].cubos[2].setModel(camadas[0].model_camada);

                
                cubos[8].model = camadas[idx].cubos[6].model;
                cubos[9].model = camadas[idx].cubos[7].model;
                cubos[10].model = camadas[idx].cubos[8].model;

                cubos[0].model = camadas[idx].cubos[3].model;
                cubos[1].model = camadas[idx].cubos[4].model;
                cubos[2].model = camadas[idx].cubos[5].model;

                cubos[17].model = camadas[idx].cubos[0].model;
                cubos[18].model = camadas[idx].cubos[1].model;
                cubos[19].model = camadas[idx].cubos[2].model;
                
            }

            else if (idx == 1) {

                camadas[1].model_camada = camadas[1].model_center;
                camadas[1].model_camada = glm::translate(camadas[1].model_camada, camadas[1].cubePos[3]);
                camadas[1].cubos[3].setModel(camadas[1].model_camada);

                camadas[1].model_camada = camadas[1].model_center;
                camadas[1].model_camada = glm::translate(camadas[1].model_camada, camadas[1].cubePos[4]);
                camadas[1].cubos[5].setModel(camadas[1].model_camada);

                camadas[1].model_camada = camadas[1].model_center;
                camadas[1].model_camada = glm::translate(camadas[1].model_camada, camadas[1].cubePos[11]);
                camadas[1].cubos[6].setModel(camadas[1].model_camada);

                camadas[1].model_camada = camadas[1].model_center;
                camadas[1].model_camada = glm::translate(camadas[1].model_camada, camadas[1].cubePos[12]);
                camadas[1].cubos[7].setModel(camadas[1].model_camada);

                camadas[1].model_camada = camadas[1].model_center;
                camadas[1].model_camada = glm::translate(camadas[1].model_camada, camadas[1].cubePos[13]);
                camadas[1].cubos[8].setModel(camadas[1].model_camada);

                camadas[1].model_camada = camadas[1].model_center;
                camadas[1].model_camada = glm::translate(camadas[1].model_camada, camadas[1].cubePos[20]);
                camadas[1].cubos[0].setModel(camadas[1].model_camada);

                camadas[1].model_camada = camadas[1].model_center;
                camadas[1].model_camada = glm::translate(camadas[1].model_camada, camadas[1].cubePos[21]);
                camadas[1].cubos[1].setModel(camadas[1].model_camada);

                camadas[1].model_camada = camadas[1].model_center;
                camadas[1].model_camada = glm::translate(camadas[1].model_camada, camadas[1].cubePos[22]);
                camadas[1].cubos[2].setModel(camadas[1].model_camada);

                cubos[11].model = camadas[idx].cubos[6].model;
                cubos[12].model = camadas[idx].cubos[7].model;
                cubos[13].model = camadas[idx].cubos[8].model;

                cubos[3].model = camadas[idx].cubos[3].model;
                cubos[26].model = camadas[idx].cubos[4].model;
                cubos[4].model = camadas[idx].cubos[5].model;

                cubos[20].model = camadas[idx].cubos[0].model;
                cubos[21].model = camadas[idx].cubos[1].model;
                cubos[22].model = camadas[idx].cubos[2].model;
            }

            else if (idx == 2) {

                camadas[2].model_camada = camadas[2].model_center;
                camadas[2].model_camada = glm::translate(camadas[2].model_camada, camadas[2].cubePos[5]);
                camadas[2].cubos[3].setModel(camadas[2].model_camada);

                camadas[2].model_camada = camadas[2].model_center;
                camadas[2].model_camada = glm::translate(camadas[2].model_camada, camadas[2].cubePos[7]);
                camadas[2].cubos[5].setModel(camadas[2].model_camada);

                camadas[2].model_camada = camadas[2].model_center;
                camadas[2].model_camada = glm::translate(camadas[2].model_camada, camadas[2].cubePos[14]);
                camadas[2].cubos[6].setModel(camadas[2].model_camada);

                camadas[2].model_camada = camadas[2].model_center;
                camadas[2].model_camada = glm::translate(camadas[2].model_camada, camadas[2].cubePos[15]);
                camadas[2].cubos[7].setModel(camadas[2].model_camada);

                camadas[2].model_camada = camadas[2].model_center;
                camadas[2].model_camada = glm::translate(camadas[2].model_camada, camadas[2].cubePos[16]);
                camadas[2].cubos[8].setModel(camadas[2].model_camada);

                camadas[2].model_camada = camadas[2].model_center;
                camadas[2].model_camada = glm::translate(camadas[2].model_camada, camadas[2].cubePos[23]);
                camadas[2].cubos[0].setModel(camadas[2].model_camada);

                camadas[2].model_camada = camadas[2].model_center;
                camadas[2].model_camada = glm::translate(camadas[2].model_camada, camadas[2].cubePos[24]);
                camadas[2].cubos[1].setModel(camadas[2].model_camada);

                camadas[2].model_camada = camadas[2].model_center;
                camadas[2].model_camada = glm::translate(camadas[2].model_camada, camadas[2].cubePos[25]);
                camadas[2].cubos[2].setModel(camadas[2].model_camada);

                cubos[14].model = camadas[idx].cubos[6].model;
                cubos[15].model = camadas[idx].cubos[7].model;
                cubos[16].model = camadas[idx].cubos[8].model;

                cubos[5].model = camadas[idx].cubos[3].model;
                cubos[6].model = camadas[idx].cubos[4].model;
                cubos[7].model = camadas[idx].cubos[5].model;

                cubos[23].model = camadas[idx].cubos[0].model;
                cubos[24].model = camadas[idx].cubos[1].model;
                cubos[25].model = camadas[idx].cubos[2].model;
            }

            else if (idx == 3) {

                camadas[3].model_camada = camadas[3].model_center;
                camadas[3].model_camada = glm::translate(camadas[3].model_camada, camadas[3].cubePos[0]);
                camadas[3].cubos[1].setModel(camadas[3].model_camada);

                camadas[3].model_camada = camadas[3].model_center;
                camadas[3].model_camada = glm::translate(camadas[3].model_camada, camadas[3].cubePos[5]);
                camadas[3].cubos[7].setModel(camadas[3].model_camada);

                camadas[3].model_camada = camadas[3].model_center;
                camadas[3].model_camada = glm::translate(camadas[3].model_camada, camadas[3].cubePos[8]);
                camadas[3].cubos[2].setModel(camadas[3].model_camada);

                camadas[3].model_camada = camadas[3].model_center;
                camadas[3].model_camada = glm::translate(camadas[3].model_camada, camadas[3].cubePos[11]);
                camadas[3].cubos[5].setModel(camadas[3].model_camada);

                camadas[3].model_camada = camadas[3].model_center;
                camadas[3].model_camada = glm::translate(camadas[3].model_camada, camadas[3].cubePos[14]);
                camadas[3].cubos[8].setModel(camadas[3].model_camada);

                camadas[3].model_camada = camadas[3].model_center;
                camadas[3].model_camada = glm::translate(camadas[3].model_camada, camadas[3].cubePos[17]);
                camadas[3].cubos[0].setModel(camadas[3].model_camada);

                camadas[3].model_camada = camadas[3].model_center;
                camadas[3].model_camada = glm::translate(camadas[3].model_camada, camadas[3].cubePos[20]);
                camadas[3].cubos[3].setModel(camadas[3].model_camada);

                camadas[3].model_camada = camadas[3].model_center;
                camadas[3].model_camada = glm::translate(camadas[3].model_camada, camadas[3].cubePos[23]);
                camadas[3].cubos[6].setModel(camadas[3].model_camada);

                cubos[8].model = camadas[idx].cubos[2].model;
                cubos[11].model = camadas[idx].cubos[5].model;
                cubos[14].model = camadas[idx].cubos[8].model;

                cubos[0].model = camadas[idx].cubos[1].model;
                cubos[3].model = camadas[idx].cubos[4].model;
                cubos[5].model = camadas[idx].cubos[7].model;

                cubos[17].model = camadas[idx].cubos[0].model;
                cubos[20].model = camadas[idx].cubos[3].model;
                cubos[23].model = camadas[idx].cubos[6].model;


            }

            else if (idx == 4) {

                camadas[4].model_camada = camadas[4].model_center;
                camadas[4].model_camada = glm::translate(camadas[4].model_camada, camadas[4].cubePos[1]);
                camadas[4].cubos[1].setModel(camadas[4].model_camada);

                camadas[4].model_camada = camadas[4].model_center;
                camadas[4].model_camada = glm::translate(camadas[4].model_camada, camadas[4].cubePos[6]);
                camadas[4].cubos[7].setModel(camadas[4].model_camada);

                camadas[4].model_camada = camadas[4].model_center;
                camadas[4].model_camada = glm::translate(camadas[4].model_camada, camadas[4].cubePos[9]);
                camadas[4].cubos[2].setModel(camadas[4].model_camada);

                camadas[4].model_camada = camadas[4].model_center;
                camadas[4].model_camada = glm::translate(camadas[4].model_camada, camadas[4].cubePos[12]);
                camadas[4].cubos[5].setModel(camadas[4].model_camada);

                camadas[4].model_camada = camadas[4].model_center;
                camadas[4].model_camada = glm::translate(camadas[4].model_camada, camadas[4].cubePos[15]);
                camadas[4].cubos[8].setModel(camadas[4].model_camada);

                camadas[4].model_camada = camadas[4].model_center;
                camadas[4].model_camada = glm::translate(camadas[4].model_camada, camadas[4].cubePos[18]);
                camadas[4].cubos[0].setModel(camadas[4].model_camada);

                camadas[4].model_camada = camadas[4].model_center;
                camadas[4].model_camada = glm::translate(camadas[4].model_camada, camadas[4].cubePos[21]);
                camadas[4].cubos[3].setModel(camadas[4].model_camada);

                camadas[4].model_camada = camadas[4].model_center;
                camadas[4].model_camada = glm::translate(camadas[4].model_camada, camadas[4].cubePos[24]);
                camadas[4].cubos[6].setModel(camadas[4].model_camada);

                cubos[9].model = camadas[idx].cubos[2].model;
                cubos[12].model = camadas[idx].cubos[5].model;
                cubos[15].model = camadas[idx].cubos[8].model;

                cubos[1].model = camadas[idx].cubos[1].model;
                cubos[26].model = camadas[idx].cubos[4].model;
                cubos[6].model = camadas[idx].cubos[7].model;

                cubos[18].model = camadas[idx].cubos[0].model;
                cubos[21].model = camadas[idx].cubos[3].model;
                cubos[24].model = camadas[idx].cubos[6].model;
            }

            else if (idx == 5) {

                camadas[5].model_camada = camadas[5].model_center;
                camadas[5].model_camada = glm::translate(camadas[5].model_camada, camadas[5].cubePos[2]);
                camadas[5].cubos[1].setModel(camadas[5].model_camada);

                camadas[5].model_camada = camadas[5].model_center;
                camadas[5].model_camada = glm::translate(camadas[5].model_camada, camadas[5].cubePos[7]);
                camadas[5].cubos[7].setModel(camadas[5].model_camada);

                camadas[5].model_camada = camadas[5].model_center;
                camadas[5].model_camada = glm::translate(camadas[5].model_camada, camadas[5].cubePos[10]);
                camadas[5].cubos[2].setModel(camadas[5].model_camada);

                camadas[5].model_camada = camadas[5].model_center;
                camadas[5].model_camada = glm::translate(camadas[5].model_camada, camadas[5].cubePos[13]);
                camadas[5].cubos[5].setModel(camadas[5].model_camada);

                camadas[5].model_camada = camadas[5].model_center;
                camadas[5].model_camada = glm::translate(camadas[5].model_camada, camadas[5].cubePos[16]);
                camadas[5].cubos[8].setModel(camadas[5].model_camada);

                camadas[5].model_camada = camadas[5].model_center;
                camadas[5].model_camada = glm::translate(camadas[5].model_camada, camadas[5].cubePos[19]);
                camadas[5].cubos[0].setModel(camadas[5].model_camada);

                camadas[5].model_camada = camadas[5].model_center;
                camadas[5].model_camada = glm::translate(camadas[5].model_camada, camadas[5].cubePos[22]);
                camadas[5].cubos[3].setModel(camadas[5].model_camada);

                camadas[5].model_camada = camadas[5].model_center;
                camadas[5].model_camada = glm::translate(camadas[5].model_camada, camadas[5].cubePos[25]);
                camadas[5].cubos[6].setModel(camadas[5].model_camada);

                cubos[10].model = camadas[idx].cubos[2].model;
                cubos[13].model = camadas[idx].cubos[5].model;
                cubos[16].model = camadas[idx].cubos[8].model;

                cubos[2].model = camadas[idx].cubos[1].model;
                cubos[4].model = camadas[idx].cubos[4].model;
                cubos[7].model = camadas[idx].cubos[7].model;

                cubos[19].model = camadas[idx].cubos[0].model;
                cubos[22].model = camadas[idx].cubos[3].model;
                cubos[25].model = camadas[idx].cubos[6].model;
            }

            else if (idx == 6) {

                camadas[6].model_camada = camadas[6].model_center;
                camadas[6].model_camada = glm::translate(camadas[6].model_camada, camadas[6].cubePos[9]);
                camadas[6].cubos[1].setModel(camadas[6].model_camada);

                camadas[6].model_camada = camadas[6].model_center;
                camadas[6].model_camada = glm::translate(camadas[6].model_camada, camadas[6].cubePos[15]);
                camadas[6].cubos[7].setModel(camadas[6].model_camada);

                camadas[6].model_camada = camadas[6].model_center;
                camadas[6].model_camada = glm::translate(camadas[6].model_camada, camadas[6].cubePos[10]);
                camadas[6].cubos[2].setModel(camadas[6].model_camada);

                camadas[6].model_camada = camadas[6].model_center;
                camadas[6].model_camada = glm::translate(camadas[6].model_camada, camadas[6].cubePos[13]);
                camadas[6].cubos[5].setModel(camadas[6].model_camada);

                camadas[6].model_camada = camadas[6].model_center;
                camadas[6].model_camada = glm::translate(camadas[6].model_camada, camadas[6].cubePos[16]);
                camadas[6].cubos[8].setModel(camadas[6].model_camada);

                camadas[6].model_camada = camadas[6].model_center;
                camadas[6].model_camada = glm::translate(camadas[6].model_camada, camadas[6].cubePos[8]);
                camadas[6].cubos[0].setModel(camadas[6].model_camada);

                camadas[6].model_camada = camadas[6].model_center;
                camadas[6].model_camada = glm::translate(camadas[6].model_camada, camadas[6].cubePos[11]);
                camadas[6].cubos[3].setModel(camadas[6].model_camada);

                camadas[6].model_camada = camadas[6].model_center;
                camadas[6].model_camada = glm::translate(camadas[6].model_camada, camadas[6].cubePos[14]);
                camadas[6].cubos[6].setModel(camadas[6].model_camada);

                cubos[10].model = camadas[idx].cubos[2].model;
                cubos[13].model = camadas[idx].cubos[5].model;
                cubos[16].model = camadas[idx].cubos[8].model;

                cubos[9].model = camadas[idx].cubos[1].model;
                cubos[12].model = camadas[idx].cubos[4].model;
                cubos[15].model = camadas[idx].cubos[7].model;

                cubos[8].model = camadas[idx].cubos[0].model;
                cubos[11].model = camadas[idx].cubos[3].model;
                cubos[14].model = camadas[idx].cubos[6].model;

            }

            else if (idx == 7) {

                camadas[7].model_camada = camadas[7].model_center;
                camadas[7].model_camada = glm::translate(camadas[7].model_camada, camadas[7].cubePos[1]);
                camadas[7].cubos[1].setModel(camadas[7].model_camada);

                camadas[7].model_camada = camadas[7].model_center;
                camadas[7].model_camada = glm::translate(camadas[7].model_camada, camadas[7].cubePos[6]);
                camadas[7].cubos[7].setModel(camadas[7].model_camada);

                camadas[7].model_camada = camadas[7].model_center;
                camadas[7].model_camada = glm::translate(camadas[7].model_camada, camadas[7].cubePos[2]);
                camadas[7].cubos[2].setModel(camadas[7].model_camada);

                camadas[7].model_camada = camadas[7].model_center;
                camadas[7].model_camada = glm::translate(camadas[7].model_camada, camadas[7].cubePos[4]);
                camadas[7].cubos[5].setModel(camadas[7].model_camada);

                camadas[7].model_camada = camadas[7].model_center;
                camadas[7].model_camada = glm::translate(camadas[7].model_camada, camadas[7].cubePos[7]);
                camadas[7].cubos[8].setModel(camadas[7].model_camada);

                camadas[7].model_camada = camadas[7].model_center;
                camadas[7].model_camada = glm::translate(camadas[7].model_camada, camadas[7].cubePos[0]);
                camadas[7].cubos[0].setModel(camadas[7].model_camada);

                camadas[7].model_camada = camadas[7].model_center;
                camadas[7].model_camada = glm::translate(camadas[7].model_camada, camadas[7].cubePos[3]);
                camadas[7].cubos[3].setModel(camadas[7].model_camada);

                camadas[7].model_camada = camadas[7].model_center;
                camadas[7].model_camada = glm::translate(camadas[7].model_camada, camadas[7].cubePos[5]);
                camadas[7].cubos[6].setModel(camadas[7].model_camada);

                cubos[2].model = camadas[idx].cubos[2].model;
                cubos[4].model = camadas[idx].cubos[5].model;
                cubos[7].model = camadas[idx].cubos[8].model;

                cubos[1].model = camadas[idx].cubos[1].model;
                cubos[26].model = camadas[idx].cubos[4].model;
                cubos[6].model = camadas[idx].cubos[7].model;

                cubos[0].model = camadas[idx].cubos[0].model;
                cubos[3].model = camadas[idx].cubos[3].model;
                cubos[5].model = camadas[idx].cubos[6].model;

            }

            else if (idx == 8) {

                camadas[8].model_camada = camadas[8].model_center;
                camadas[8].model_camada = glm::translate(camadas[8].model_camada, camadas[8].cubePos[18]);
                camadas[8].cubos[1].setModel(camadas[8].model_camada);

                camadas[8].model_camada = camadas[8].model_center;
                camadas[8].model_camada = glm::translate(camadas[8].model_camada, camadas[8].cubePos[24]);
                camadas[8].cubos[7].setModel(camadas[8].model_camada);

                camadas[8].model_camada = camadas[8].model_center;
                camadas[8].model_camada = glm::translate(camadas[8].model_camada, camadas[8].cubePos[19]);
                camadas[8].cubos[2].setModel(camadas[8].model_camada);

                camadas[8].model_camada = camadas[8].model_center;
                camadas[8].model_camada = glm::translate(camadas[8].model_camada, camadas[8].cubePos[22]);
                camadas[8].cubos[5].setModel(camadas[8].model_camada);

                camadas[8].model_camada = camadas[8].model_center;
                camadas[8].model_camada = glm::translate(camadas[8].model_camada, camadas[8].cubePos[25]);
                camadas[8].cubos[8].setModel(camadas[8].model_camada);

                camadas[8].model_camada = camadas[8].model_center;
                camadas[8].model_camada = glm::translate(camadas[8].model_camada, camadas[8].cubePos[17]);
                camadas[8].cubos[0].setModel(camadas[8].model_camada);

                camadas[8].model_camada = camadas[8].model_center;
                camadas[8].model_camada = glm::translate(camadas[8].model_camada, camadas[8].cubePos[20]);
                camadas[8].cubos[3].setModel(camadas[8].model_camada);

                camadas[8].model_camada = camadas[8].model_center;
                camadas[8].model_camada = glm::translate(camadas[8].model_camada, camadas[8].cubePos[23]);
                camadas[8].cubos[6].setModel(camadas[8].model_camada);

                cubos[19].model = camadas[idx].cubos[2].model;
                cubos[22].model = camadas[idx].cubos[5].model;
                cubos[25].model = camadas[idx].cubos[8].model;

                cubos[18].model = camadas[idx].cubos[1].model;
                cubos[21].model = camadas[idx].cubos[4].model;
                cubos[24].model = camadas[idx].cubos[7].model;

                cubos[17].model = camadas[idx].cubos[0].model;
                cubos[20].model = camadas[idx].cubos[3].model;
                cubos[23].model = camadas[idx].cubos[6].model;
            }

            int cur_ang = (int)camadas[idx].ang_;
            if (cur_ang && cur_ang % 90 == 0) {
                if (cur_ang == 90) camadas[idx].ang_ = 0;
                camadas[idx].girar = 0;
            }

        }

    }

    void rotCamada(int& idx, bool rotation) {
        int n_idx = idx - 1;
        int mov = 0;
        if (n_idx > -1) {
            if (camadas[n_idx].animation && camadas[n_idx].girar == 0) {
                camadas[n_idx].animation = 0;
                camadas[n_idx].girar = 0;
                idx = 0;
                updatefinalCamadas(n_idx, camadas[n_idx].orientation, rotation,mov);
            }
            else {
                camadas[n_idx].animation = 1;
                camadas[n_idx].girar = 1;
                camadas[n_idx].set_cubes_rot(rotation);
                updateCamadas(n_idx);
            }
        }

    }

    int rotCamada02(int& idx, bool rotation,int& mov_cam) {
        int n_idx = idx - 1;
        if (n_idx > -1) {
            if (camadas[n_idx].animation && camadas[n_idx].girar == 0) {
                camadas[n_idx].animation = 0;
                camadas[n_idx].girar = 0;
                idx = 0;
                updatefinalCamadas(n_idx, camadas[n_idx].orientation, rotation, mov_cam);
                return 1;
            }
            else {
                camadas[n_idx].animation = 1;
                camadas[n_idx].girar = 1;
                camadas[n_idx].set_cubes_rot(rotation);
                updateCamadas(n_idx);
                return 2;
            }
        }
        return 3;

    }




    int parser_mov(int& camada_giro, bool& rotation, string& moves_cp,int& mov_cam) {
        
        if (!flag_sol) {
            borr = 1;

            if ('\n' == moves_cp[0] || ' ' == moves_cp[0]) {
                moves_cp.erase(0, 1);
                cout << "Solucionado?\n";
                return 0;
            }

            m = moves_cp[0];
            if (moves_cp.size() > 1) {
                if (moves_cp[1] == '2') {
                    m += moves_cp[1];
                    borr = 0;
                }
            }

            if (m == "R") {
                camada_giro = 6;
                rotation = 0;
            }
            else if (m == "L") {
                camada_giro = 4;
                rotation = 1;
            }
            else if (m == "U") {
                camada_giro = 1;
                rotation = 0;
            }
            else if (m == "D") {
                camada_giro = 3;
                rotation = 1;
            }
            else if (m == "F") {
                camada_giro = 7;
                rotation = 1;
            }
            else if (m == "W") {
                camada_giro = 9;
                rotation = 0;
            }
            //////

            else if (m == "r") {
                camada_giro = 6;
                rotation = 1;
            }
            else if (m == "l") {
                camada_giro = 4;
                rotation = 0;
            }
            else if (m == "u") {
                camada_giro = 1;
                rotation = 1;
            }
            else if (m == "d") {
                camada_giro = 3;
                rotation = 0;
            }
            else if (m == "f") {
                camada_giro = 7;
                rotation = 0;
            }
            else if (m == "w") {
                camada_giro = 9;
                rotation = 1;
            }


            flag_sol = 1;
        }


        int ind = rotCamada02(camada_giro, rotation,mov_cam);
        if (ind == 1) {
            if (borr) moves_cp.erase(0, 1);
            else {
                moves_cp.erase(0, 2);
                borr = 1;
            }
            flag_sol = 0;
        }
    }


    int parser_mov02(int& camada_giro, bool& rotation, string& moves_cp) {

        if (!flag_sol) {
            borr = 1;

            if ('\n' == moves_cp[0] || ' ' == moves_cp[0]) {
                moves_cp.erase(0, 1);
                return 0;
            }

            m = moves_cp[0];
            if (moves_cp.size() > 1) {
                if (moves_cp[1] == '2') {
                    m += moves_cp[1];
                    borr = 0;
                }
            }

            if (m == "Z") {
                camada_giro = 1;
                rotation = 1;
            }
            else if (m == "V") {
                camada_giro = 4;
                rotation = 1;
            }
            else if (m == "J") {
                camada_giro = 7;
                rotation = 1;
            }

            flag_sol = 1;
        }

        int mov = 0;
        int ind = rotCamada02(camada_giro, rotation,mov);
        if (ind == 1) {
            if (borr) moves_cp.erase(0, 1);
            else {
                moves_cp.erase(0, 2);
                borr = 1;
            }
            flag_sol = 0;
        }
    }


    void readSolution() {
        ifstream file("sol.dat");
        stringstream buffer;
        buffer << file.rdbuf();
        sol_movs = buffer.str();
        cout << "Solucion: " << sol_movs <<"\n";
    }

    void solutionCube(bool &acc,string& word) {
        if (acc) {
            system("Rubik-solver\\bin\\Rubik.exe stateCub.dat sol.dat");
            readSolution();
            word = sol_movs;
            acc = 0;
        }

    }

    void drawCubeRubik(Shader shaderc,bool op=0) {
        for (int i = 0; i < 26; i++) {
            glm::mat4 model;
            glm::mat4 model_text;
            model = cubos[i].getModelMatrix(1);
            //model = glm::translate(model, glm::vec3(0.0,-5.0,0.0));
            model_text = cubos[i].getModelText();
            shaderc.setMat4("model", model);
            if(op) cubos[i].drawCubeText();
            else cubos[i].drawCubeColors(shaderc);
        }
    }

    void drawCubeRubik_(Shader shaderc, bool op, glm::vec3 pos) {
        for (int i = 0; i < 26; i++) {
            glm::mat4 model;
            model = cubos[i].getModelMatrix(1);
            model = glm::translate(model, pos);
            shaderc.setMat4("model", model);
            if (op) cubos[i].drawCubeText();
            else cubos[i].drawCubeColors(shaderc);
        }
    }


};


#endif