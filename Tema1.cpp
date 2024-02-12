#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;
#include <cstdlib> 
#include <ctime>   




/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;
    for (int i = 0; i < 1000; i++) {
        enemy_start[i] = window->GetResolution().x;
        enemy_color[i] = 0;
        enemy_row[i] = 0;
        garantat[i] = 0;
    }
    

    start_eq = 0;
    no_hearts = 3;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?
    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    for (int i = 0; i < 9; i++) {
        scale_diamond[i].x = 1;
        scale_diamond[i].y = 1;
        new_projectile_timer[i] = 1.5f;
        need_new_projectile[i] = 1;
    }

    // Initialize angularStep
    angularStep = 0;
    translateStepX = 1;
    translateStepY = 1;
    scaleStepX = 1;
    scaleStepY = 1;
    scaleStepY = 1;
    rotationStep = 4;
    start_pos = window->GetResolution().x;
    start_enemy = window->GetResolution().x;
    speed = 0.5;
    // Initialize stars currency relates variables
    star_counter = 4;
    no_stars = 0;
    corner = glm::vec3(0, 0, 0);
    glm::vec3 center = glm::vec3(0, 0, 0);

    // Florile (gloantele) - proiectilele pe culori diferite 
    {
        center = glm::vec3(0, 0, 0.11f);
        Mesh* flowerOrange = object2D::CreateFlower(("flowerOrange"), center, 25, 50, glm::vec3(0.87f, 0.54f, 0.15f));
        AddMeshToList(flowerOrange);
        center = glm::vec3(0, 0, 0.11f);
        Mesh* flowerBlue = object2D::CreateFlower(("flowerBlue"), center, 25, 50, glm::vec3(0.27f, 0.40f, 0.74f));
        AddMeshToList(flowerBlue);
        center = glm::vec3(0, 0, 0.11f);
        Mesh* flowerYellow = object2D::CreateFlower(("flowerYellow"), center, 25, 50, glm::vec3(0.94f, 0.93f, 0.27f));
        AddMeshToList(flowerYellow);
        center = glm::vec3(0, 0, 0.11f);
        Mesh* flowerPurple = object2D::CreateFlower(("flowerPurple"), center, 25, 50, glm::vec3(0.58f, 0.27f, 0.94f));
        AddMeshToList(flowerPurple);
    }

    // Patrate si danger zone
    {
        corner = glm::vec3(100, 20, 0);
        Mesh* sq1 = object2D::CreateSquare(("square1"), corner, 100, glm::vec3(0, 1, 0));
        AddMeshToList(sq1);

        corner = glm::vec3(220, 20, 0);
        Mesh* sq2 = object2D::CreateSquare(("square2"), corner, 100, glm::vec3(0, 1, 0));
        AddMeshToList(sq2);

        corner = glm::vec3(340, 20, 0);
        Mesh* sq3 = object2D::CreateSquare(("square3"), corner, 100, glm::vec3(0, 1, 0));
        AddMeshToList(sq3);

        corner = glm::vec3(100, 140, 0);
        Mesh* sq4 = object2D::CreateSquare(("square4"), corner, 100, glm::vec3(0, 1, 0));
        AddMeshToList(sq4);

        corner = glm::vec3(220, 140, 0);
        Mesh* sq5 = object2D::CreateSquare(("square5"), corner, 100, glm::vec3(0, 1, 0));
        AddMeshToList(sq5);

        corner = glm::vec3(340, 140, 0);
        Mesh* sq6 = object2D::CreateSquare(("square6"), corner, 100, glm::vec3(0, 1, 0));
        AddMeshToList(sq6);

        corner = glm::vec3(100, 260, 0);
        Mesh* sq7 = object2D::CreateSquare(("square7"), corner, 100, glm::vec3(0, 1, 0));
        AddMeshToList(sq7);

        corner = glm::vec3(220, 260, 0);
        Mesh* sq8 = object2D::CreateSquare(("square8"), corner, 100, glm::vec3(0, 1, 0));
        AddMeshToList(sq8);

        corner = glm::vec3(340, 260, 0);
        Mesh* sq9 = object2D::CreateSquare(("square9"), corner, 100, glm::vec3(0, 1, 0));
        AddMeshToList(sq9);

        // Danger zone
        corner = glm::vec3(10, 2.77, 0);
        Mesh* rectangle = object2D::CreateSquare("rectangle", corner, 100, glm::vec3(1, 0, 0));
        AddMeshToList(rectangle);


    }

    // Contur in forma de patrat si romburi + dreptungiuri pentru chenarele romburilor
    {
        corner = glm::vec3(10, 600, 0);
        Mesh* sq10 = object2D::CreateSquare(("square10"), corner, 100, glm::vec3(0.94f, 0.89f, 0.11f), false);
        AddMeshToList(sq10);

        corner = glm::vec3(160, 600, 0);
        Mesh* sq11 = object2D::CreateSquare(("square11"), corner, 100, glm::vec3(0.94f, 0.89f, 0.11f), false);
        AddMeshToList(sq11);

        corner = glm::vec3(310, 600, 0);
        Mesh* sq12 = object2D::CreateSquare(("square12"), corner, 100, glm::vec3(0.94f, 0.89f, 0.11f), false);
        AddMeshToList(sq12);

        corner = glm::vec3(460, 600, 0);
        Mesh* sq13 = object2D::CreateSquare(("square13"), corner, 100, glm::vec3(0.94f, 0.89f, 0.11f), false);
        AddMeshToList(sq13);

        center = glm::vec3(60, 650, 0);
        Mesh* diamond1 = object2D::CreateDiamond(("diamond1"), center, 40, glm::vec3(0.87f, 0.54f, 0.15f));
        AddMeshToList(diamond1);

        center = glm::vec3(210, 650, 0);
        Mesh* diamond2 = object2D::CreateDiamond(("diamond2"), center, 40, glm::vec3(0.27f, 0.40f, 0.74f));
        AddMeshToList(diamond2);

        center = glm::vec3(360, 650, 0);
        Mesh* diamond3 = object2D::CreateDiamond(("diamond3"), center, 40, glm::vec3(0.94f, 0.93f, 0.27f));
        AddMeshToList(diamond3);

        center = glm::vec3(510, 650, 0);
        Mesh* diamond4 = object2D::CreateDiamond(("diamond4"), center, 40, glm::vec3(0.58f, 0.27f, 0.94f));
        AddMeshToList(diamond4);

        corner = glm::vec3(60, 640, 0.1f);
        Mesh* rectangle1 = object2D::CreateRectangle(("rectangle1"), corner,  45, 20, glm::vec3(0.87f, 0.54f, 0.15f));
        AddMeshToList(rectangle1);

        corner = glm::vec3(210, 640, 0.1f);
        Mesh* rectangle2 = object2D::CreateRectangle(("rectangle2"), corner, 45, 20, glm::vec3(0.27f, 0.40f, 0.74f));
        AddMeshToList(rectangle2);

        corner = glm::vec3(360, 640, 0.1f);
        Mesh* rectangle3 = object2D::CreateRectangle(("rectangle3"), corner, 45, 20,glm::vec3(0.94f, 0.93f, 0.27f));
        AddMeshToList(rectangle3);

        corner = glm::vec3(510, 640, 0.1f);
        Mesh* rectangle4 = object2D::CreateRectangle(("rectangle4"), corner, 45, 20, glm::vec3(0.58f, 0.27f, 0.94f));
        AddMeshToList(rectangle4);
    }

    
    // Diamantele(romburile) pentru campul de joc - ce vor fi plasate acolo - pe care le vom translata
    {
        center = glm::vec3(0, 0, 0);
        Mesh* diamond1_1 = object2D::CreateDiamond(("diamond1_1"), center, 40, glm::vec3(0.87f, 0.54f, 0.15f));
        AddMeshToList(diamond1_1);
        corner = glm::vec3(0, 0, 0);
        Mesh* rectangle1_1 = object2D::CreateRectangle(("rectangle1_1"), corner, 45, 20, glm::vec3(0.87f, 0.54f, 0.15f));
        AddMeshToList(rectangle1_1);

        center = glm::vec3(0, 0, 0);
        Mesh* diamond2_1 = object2D::CreateDiamond(("diamond2_1"), center, 40, glm::vec3(0.27f, 0.40f, 0.74f));
        AddMeshToList(diamond2_1);
        corner = glm::vec3(0, 0, 0);
        Mesh* rectangle2_1 = object2D::CreateRectangle(("rectangle2_1"), corner, 45, 20, glm::vec3(0.27f, 0.40f, 0.74f));
        AddMeshToList(rectangle2_1);

        center = glm::vec3(0, 0, 0);
        Mesh* diamond3_1 = object2D::CreateDiamond(("diamond3_1"), center, 40, glm::vec3(0.94f, 0.93f, 0.27f));
        AddMeshToList(diamond3_1);
        corner = glm::vec3(0, 0, 0);
        Mesh* rectangle3_1 = object2D::CreateRectangle(("rectangle3_1"), corner, 45, 20, glm::vec3(0.94f, 0.93f, 0.27f));
        AddMeshToList(rectangle3_1);

        center = glm::vec3(0, 0, 0);
        Mesh* diamond4_1 = object2D::CreateDiamond(("diamond4_1"), center, 40, glm::vec3(0.58f, 0.27f, 0.94f));
        AddMeshToList(diamond4_1);
        corner = glm::vec3(0, 0, 0);
        Mesh* rectangle4_1 = object2D::CreateRectangle(("rectangle4_1"), corner, 45, 20, glm::vec3(0.58f, 0.27f, 0.94f));
        AddMeshToList(rectangle4_1);



    }

    // Inimi - vietile
    {
        corner = glm::vec3(0, 0, 0);
        Mesh* heart = object2D::CreateHeart(("heart"), corner, 70, glm::vec3(1, 0, 0));
        AddMeshToList(heart);

    }
    
    // Stelele care se misca
    {
        corner = glm::vec3(0, 0, 0.1f);
        Mesh* star1 = object2D::CreateStar1(("star1"), corner, 100, glm::vec3(1, 0, 1), true);
        AddMeshToList(star1);
    }
     
    // Stelele - resursa pentru fiecare romb
    {
        center = glm::vec3(10, 560, 0);
        Mesh* star11 = object2D::CreateStar(("star11"), center, 15, glm::vec3(0.58f, 0.62f, 0.65f));
        AddMeshToList(star11);

        center = glm::vec3(160, 560, 0);
        Mesh* star12 = object2D::CreateStar(("star12"), center, 15, glm::vec3(0.58f, 0.62f, 0.65f));
        AddMeshToList(star12);

        center = glm::vec3(190, 560, 0);
        Mesh* star13 = object2D::CreateStar(("star13"), center, 15, glm::vec3(0.58f, 0.62f, 0.65f));
        AddMeshToList(star13);

        center = glm::vec3(310, 560, 0);
        Mesh* star14 = object2D::CreateStar(("star14"), center, 15, glm::vec3(0.58f, 0.62f, 0.65f));
        AddMeshToList(star14);

        center = glm::vec3(340, 560, 0);
        Mesh* star15 = object2D::CreateStar(("star15"), center, 15, glm::vec3(0.58f, 0.62f, 0.65f));
        AddMeshToList(star15);

        center = glm::vec3(460, 560, 0);
        Mesh* star16 = object2D::CreateStar(("star16"), center, 15, glm::vec3(0.58f, 0.62f, 0.65f));
        AddMeshToList(star16);

        center = glm::vec3(490, 560, 0);
        Mesh* star17 = object2D::CreateStar(("star17"), center, 15, glm::vec3(0.58f, 0.62f, 0.65f));
        AddMeshToList(star17);

        center = glm::vec3(520, 560, 0);
        Mesh* star18 = object2D::CreateStar(("star18"), center, 15, glm::vec3(0.58f, 0.62f, 0.65f));
        AddMeshToList(star18);

        center = glm::vec3(800, 560, 0);
        Mesh* star19 = object2D::CreateStar(("star19"), center, 15, glm::vec3(0.58f, 0.62f, 0.65f));
        AddMeshToList(star19);
    }

    // Hexagoanele - inamicii 
    {
        center = glm::vec3(0, 0, 0.2f);
        Mesh* pOrange = object2D::CreateHexagon(("pOrange"), center, 40, glm::vec3(0.87f, 0.54f, 0.15f));
        AddMeshToList(pOrange);
        center = glm::vec3(0, 0, 0.2f);
        Mesh* pBlue = object2D::CreateHexagon(("pBlue"), center, 40, glm::vec3(0.27f, 0.40f, 0.74f));
        AddMeshToList(pBlue);
        center = glm::vec3(0, 0, 0.2f);
        Mesh* pYellow = object2D::CreateHexagon(("pYellow"), center, 40, glm::vec3(0.94f, 0.93f, 0.27f));
        AddMeshToList(pYellow);
        center = glm::vec3(0, 0, 0.2f);
        Mesh* pPurple = object2D::CreateHexagon(("pPurple"), center, 40, glm::vec3(0.58f, 0.27f, 0.94f));
        AddMeshToList(pPurple);
        center = glm::vec3(0, 0, 0.1f);
        Mesh* f = object2D::CreateHexagon(("f"), center, 20, glm::vec3(0, 0, 1));
        AddMeshToList(f);

    }
}

 // Functie pentru miscarea proiectilului
void Tema1::Flower_move(Projectile *sts, float deltaTimeSeconds) {
    if (sts->color == 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(sts->x, sts->y)
            * transform2D::Rotate(sts->angularStep);
        RenderMesh2D(meshes["flowerOrange"], shaders["VertexColor"], modelMatrix);
    }
    else if (sts->color == 1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(sts->x, sts->y)
            * transform2D::Rotate(sts->angularStep);
        RenderMesh2D(meshes["flowerBlue"], shaders["VertexColor"], modelMatrix);
    }
    else if (sts->color == 2) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(sts->x, sts->y)
            * transform2D::Rotate(sts->angularStep);
        RenderMesh2D(meshes["flowerYellow"], shaders["VertexColor"], modelMatrix);
    }
    else if (sts->color == 3) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(sts->x, sts->y)
            * transform2D::Rotate(sts->angularStep);
        RenderMesh2D(meshes["flowerPurple"], shaders["VertexColor"], modelMatrix);
    }

    sts->x += sts->speed * deltaTimeSeconds;
    sts->angularStep -= (3 * 3.1415 / 5) * deltaTimeSeconds;
}

// Spamarea cu inamici la un interval prestabilit de secunde
// Culoare si rand random alese
void Tema1::Enemy_spawn(Hexagon* sts, float deltaTimeSeconds) {

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate((*sts).x, (*sts).y)
        * transform2D::Scale(sts->scaleX, sts->scaleY);
    RenderMesh2D(meshes["f"], shaders["VertexColor"], modelMatrix);

    if ((*sts).color == 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate((*sts).x, (*sts).y)
            * transform2D::Scale(sts->scaleX, sts->scaleY);
        RenderMesh2D(meshes["pOrange"], shaders["VertexColor"], modelMatrix);
    }
    else if ((*sts).color == 1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate((*sts).x, (*sts).y)
            * transform2D::Scale(sts->scaleX, sts->scaleY);
        RenderMesh2D(meshes["pBlue"], shaders["VertexColor"], modelMatrix);
    }
    else if ((*sts).color == 2) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate((*sts).x, (*sts).y)
            * transform2D::Scale(sts->scaleX, sts->scaleY);
        RenderMesh2D(meshes["pYellow"], shaders["VertexColor"], modelMatrix);
    }
    else if ((*sts).color == 3) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate((*sts).x, (*sts).y)
            * transform2D::Scale(sts->scaleX, sts->scaleY);
        RenderMesh2D(meshes["pPurple"], shaders["VertexColor"], modelMatrix);
    }

    if (!(*sts).deleted) {
        (*sts).x -= (*sts).speed * deltaTimeSeconds;
    }
    else if (sts->deleted && sts->scaleX > 0) {
        sts->scaleX -= 0.02f;
        sts->scaleY -= 0.02f;
    }
}

void Tema1::Erase_diamond(int i, int j)
{
    if (scale_diamond[j].x > 0) {
        if (i == 0) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 70 + (j / 3) * 120)
                * transform2D::Scale(scale_diamond[j].x, scale_diamond[j].y);
            RenderMesh2D(meshes["diamond1_1"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 60 + (j / 3) * 120)
                * transform2D::Scale(scale_diamond[j].x, 1);
            RenderMesh2D(meshes["rectangle1_1"], shaders["VertexColor"], modelMatrix);
        }
        else if (i == 1) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 70 + (j / 3) * 120)
                * transform2D::Scale(scale_diamond[j].x, scale_diamond[j].y);
            RenderMesh2D(meshes["diamond2_1"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 60 + (j / 3) * 120)
                * transform2D::Scale(scale_diamond[j].x, 1);
            RenderMesh2D(meshes["rectangle2_1"], shaders["VertexColor"], modelMatrix);
        }
        else if (i == 2) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 70 + (j / 3) * 120)
                * transform2D::Scale(scale_diamond[j].x, scale_diamond[j].y);
            RenderMesh2D(meshes["diamond3_1"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 60 + (j / 3) * 120)
                * transform2D::Scale(scale_diamond[j].x, 1);
            RenderMesh2D(meshes["rectangle3_1"], shaders["VertexColor"], modelMatrix);
        }
        else if (i == 3) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 70 + (j / 3) * 120)
                * transform2D::Scale(scale_diamond[j].x, scale_diamond[j].y);
            RenderMesh2D(meshes["diamond4_1"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 60 + (j / 3) * 120)
                * transform2D::Scale(scale_diamond[j].x, 1);
            RenderMesh2D(meshes["rectangle4_1"], shaders["VertexColor"], modelMatrix);
        }

        scale_diamond[j].x -= 0.01;
        scale_diamond[j].y -= 0.01;
    }
    else {
        scale_diamond[j].x = 1;
        scale_diamond[j].y = 1;
        deleted_diamond[i][j] = 0;
        matrix[i][j] = 0;
    }
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}



void Tema1::Update(float deltaTimeSeconds)
{
    // Creare de hexagoane si animarea lor
    {
        // Creez hexagon nou o data la cateva secunde
        {
            if (!enemy_verify) {
                enemy_index++;
                enemy_color[enemy_index] = std::rand() % 4; // 4 culori diferite
                enemy_row[enemy_index] = std::rand() % 3; // 3 randuri

                Hexagon new_hexagon;
                new_hexagon.x = window->GetResolution().x;
                new_hexagon.row = std::rand() % 3;
                new_hexagon.y = new_hexagon.row * 120 + 70;
                new_hexagon.deleted = false;
                new_hexagon.color = std::rand() % 4;
                new_hexagon.speed = 40;
                new_hexagon.health = 3;
                new_hexagon.scaleX = 1;
                new_hexagon.scaleY = 1;

                Hexagoane.push_back(new_hexagon);
            }

            for (vector<Hexagon>::iterator i = Hexagoane.begin(); i < Hexagoane.end(); i++) {
                Enemy_spawn(&(*i), deltaTimeSeconds);
                if (i->scaleX <= 0 && i->deleted == true) {
                    if (i + 1 != Hexagoane.end()) {
                        i = Hexagoane.erase(i);
                    }
                    else {
                        continue;
                    }
                }
            }

            enemy_verify = 1;
            if (enemy_verify) {
                enemy_counter -= deltaTimeSeconds;
                if (enemy_counter < 0) {
                    enemy_counter = rand() % 5 + 4; // numar secunde
                    enemy_verify = 0;
                }
            }

        }

        // Verificarea coliziunilor hexagonului
        {
            for (vector<Hexagon>::iterator inamic = Hexagoane.begin(); inamic != Hexagoane.end(); inamic++) {

                // Coliziune cu danger zone
                if ((*inamic).x <= 40) {
                    no_hearts--;
                    if (inamic + 1 != Hexagoane.end()) {
                        inamic = Hexagoane.erase(inamic);
                    }
                    else {
                        continue;
                    }
                }
                // Coliziune cu diamantele de pe campul de joc
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 9; j++) {
                        if (j / 3 == (*inamic).row && matrix[i][j] == 1) {
                            if (sqrt( ((*inamic).x - ((j % 3 + 1) * 120 + 30)) * ((*inamic).x - ((j % 3 + 1) * 120 + 30))) <= 80
                                && deleted_diamond[i][j] == 0) {
                                deleted_diamond[i][j] = 1;
                            }
                        }
                    }
                }
                // Coliziune cu proiectilele
                for (vector<Projectile>::iterator proiectil = Projectiles.begin(); proiectil < Projectiles.end(); proiectil++) {
                    if (proiectil->color == inamic->color && (proiectil->camp / 3) == inamic->row && inamic->deleted == false && inamic->health > 0) {
                        if (sqrt((inamic->x - proiectil->x) * (inamic->x - proiectil->x)) <= 30) {
                            inamic->health--;
                            if (proiectil + 1 != Projectiles.end()) {
                                proiectil = Projectiles.erase(proiectil);
                            }
                            else {
                                continue;
                            }  
                        }
                    }
                    if (proiectil->color == inamic->color && (proiectil->camp / 3) == inamic->row && inamic->deleted == false &&  inamic->health <= 0) {
                        inamic->deleted = true;
                    }
                }
            }
        }
    }

    // Crearea proiectilelor si animarea lor cand apare un inamic
    {
        for (int j = 0; j < 9; j++) {
            for (vector<Hexagon>::iterator inamic = Hexagoane.begin(); inamic < Hexagoane.end(); inamic++) {
                // Daca avem diamant pe acelasi rand cu inamicul de aceeasi culoare, cream proiectil
                if (matrix[inamic->color][j] == 1 && inamic->row == (j / 3) && inamic->deleted == false) {
                    if (need_new_projectile[j] == 1) {

                        Projectile new_projectile;

                        new_projectile.x = 30 + (j % 3 + 1) * 120;
                        new_projectile.y = 70 + (j / 3) * 120;
                        new_projectile.color = inamic->color;
                        new_projectile.camp = j;
                        new_projectile.angularStep = 0;
                        new_projectile.speed = 250;

                        Projectiles.push_back(new_projectile);

                        new_projectile_timer[j] = 1.5;
                        need_new_projectile[j] = 0;

                    }
                }

                for (vector<Projectile>::iterator proiectil = Projectiles.begin(); proiectil < Projectiles.end(); proiectil++) {
                    for (int color = 0; color < 4; color++) {
                        if (color == proiectil->color && proiectil->camp == j) {
                            Flower_move(&(*proiectil), deltaTimeSeconds);
                        }
                        if (proiectil->x >= window->GetResolution().x) {
                            if (proiectil + 1 != Projectiles.end()) {
                                proiectil = Projectiles.erase(proiectil);
                            }
                            else {
                                continue;
                            }
                        }
                    }
                }
            }

            new_projectile_timer[j] -= deltaTimeSeconds;
            if (new_projectile_timer[j] < 0) {
                need_new_projectile[j] = 1;
                new_projectile_timer[j] = 1.5;
            }
        }
    }


    // Afisare diamantelor pe campul de joc
    {
        for (int j = 0; j < 9; j++) {
            if (matrix[0][j] == 1 && deleted_diamond[0][j] == 0) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 70 + (j / 3) * 120);
                RenderMesh2D(meshes["diamond1_1"], shaders["VertexColor"], modelMatrix);
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 60 + (j / 3) * 120);
                RenderMesh2D(meshes["rectangle1_1"], shaders["VertexColor"], modelMatrix);
            }
            if (matrix[1][j] == 1 && deleted_diamond[1][j] == 0) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 70 + (j / 3) * 120);
                RenderMesh2D(meshes["diamond2_1"], shaders["VertexColor"], modelMatrix);
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 60 + (j / 3) * 120);
                RenderMesh2D(meshes["rectangle2_1"], shaders["VertexColor"], modelMatrix);
            }
            if (matrix[2][j] == 1 && deleted_diamond[2][j] == 0) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(30 + (j % 3 +1) * 120, 70 + (j / 3) * 120);
                RenderMesh2D(meshes["diamond3_1"], shaders["VertexColor"], modelMatrix);
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 60 + (j / 3) * 120);
                RenderMesh2D(meshes["rectangle3_1"], shaders["VertexColor"], modelMatrix);
            }
            if (matrix[3][j] == 1 && deleted_diamond[3][j] == 0) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 70 + (j / 3) * 120);
                RenderMesh2D(meshes["diamond4_1"], shaders["VertexColor"], modelMatrix);
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(30 + (j % 3 + 1) * 120, 60 + (j / 3) * 120);
                RenderMesh2D(meshes["rectangle4_1"], shaders["VertexColor"], modelMatrix);
            }

            for (int i = 0; i < 4; i++) {
                if (deleted_diamond[i][j] == 1) {
                    Erase_diamond(i, j);
                }
            }
            
        }
    }


    // Afisare translatie
    {
        if (selected_diamonds[0] == 1) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(trans_x, trans_y);
            RenderMesh2D(meshes["diamond1_1"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(trans_x, trans_y - 10);
            RenderMesh2D(meshes["rectangle1_1"], shaders["VertexColor"], modelMatrix);
        }

        if (selected_diamonds[1] == 1) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(trans_x, trans_y);
            RenderMesh2D(meshes["diamond2_1"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(trans_x, trans_y - 10);
            RenderMesh2D(meshes["rectangle2_1"], shaders["VertexColor"], modelMatrix);
        }

        if (selected_diamonds[2] == 1) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(trans_x, trans_y);
            RenderMesh2D(meshes["diamond3_1"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(trans_x, trans_y - 10);
            RenderMesh2D(meshes["rectangle3_1"], shaders["VertexColor"], modelMatrix);
        }

        if (selected_diamonds[3] == 1) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(trans_x, trans_y);
            RenderMesh2D(meshes["diamond4_1"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(trans_x, trans_y - 10);
            RenderMesh2D(meshes["rectangle4_1"], shaders["VertexColor"], modelMatrix);
        }
    }

    // Patrate si Danger zone
    {
        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["square5"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["square6"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["square7"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["square8"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["square9"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Scale(0.7, 3.6);
        RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
    }

     // Contur si patrate/romburi
    {
        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["square10"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["square11"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["square12"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["square13"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["diamond1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["diamond2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["diamond3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["diamond4"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["rectangle1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["rectangle2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["rectangle3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["rectangle4"], shaders["VertexColor"], modelMatrix);

    }
    

    bool deplasare = true;

    // Stelele - resursa romburi
    {
        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["star11"], shaders["VertexColor"], modelMatrix);
        
        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["star12"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["star13"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["star14"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["star15"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["star16"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["star17"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["star18"], shaders["VertexColor"], modelMatrix);
    }

     // Hexagoane - deplasare aleatoara a inamicilor pe randuri


    // Numarul de inimi disponibile pe durata jocului - se actualizeaza instantaneu
    {
        for (int i = 0; i < no_hearts; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(800 + 100 * i, 630);
            RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);

        }
    }

    // Numarul de stele disponibile pt a fi "cheltuite - se actualizeaza instantaneu
    {
        for (int i = 0; i < no_stars; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(30 * i, 0);
            RenderMesh2D(meshes["star19"], shaders["VertexColor"], modelMatrix);
        }

    }

    // Stele ce apar random pe ecran - 4 la cate 12 secunde
    {   
        int i = 0;
        if (!star_verify) {
            while (i < 4) {
                star_positions[i].x = 350 - std::rand() % 700; // pozitia stelei
                star_positions[i].y = 175 - std::rand() % 350; // cate 3 stele
                show[i] = 1;
                ++i;
            }
        }
        if (show[0] == 1) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(star_positions[0].x, star_positions[0].y);
            RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix); // prima stea
        }

        if (show[1] == 1) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(star_positions[1].x, star_positions[1].y);
            RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix); // a doua stea
        }

        if (show[2] == 1) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(star_positions[2].x, star_positions[2].y);
            RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix); // atreia stea
        }

        if (show[3] == 1) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(star_positions[3].x, star_positions[3].y);
            RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix); // a patra stea
        }

        star_verify = 1;
        if (star_verify) {
            star_counter -= deltaTimeSeconds;
            if (star_counter < 0) {
                star_counter = 4; // numar secunde
                star_verify = 0;

            }
        }
    }

    if (no_hearts == 0) {
        exit(1);
    }
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event

}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Selctarea instantatnee a coordonatelor cursorului pentru a putea translata rombul
    if (selected_diamonds[0] == 1 || selected_diamonds[1] == 1 || selected_diamonds[2] == 1 || selected_diamonds[3] == 1) {
        trans_x = mouseX;
        trans_y = -mouseY + window->GetResolution().y;
    }

}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

    // Add mouse button press event - stanga - drag
    if (button == GLFW_MOUSE_BUTTON_2)
    {
        if (mouseX >= star_positions[0].x && mouseX <= star_positions[0].x + 110 &&
            -mouseY + window->GetResolution().y >= star_positions[0].y  && -mouseY + window->GetResolution().y <= star_positions[0].y + 110 && show[0] == 1) {
            no_stars++;
            show[0] = 0;
        }

        if (mouseX >= star_positions[1].x && mouseX <= star_positions[1].x + 110 &&
            -mouseY + window->GetResolution().y >= star_positions[1].y && -mouseY + window->GetResolution().y <= star_positions[1].y + 110 && show[1] == 1) {
            no_stars++;
            show[1] = 0;
        }

        if (mouseX >= star_positions[2].x && mouseX <= star_positions[2].x + 110 &&
            -mouseY + window->GetResolution().y >= star_positions[2].y && -mouseY + window->GetResolution().y <= star_positions[2].y + 110 && show[2] == 1) {
            no_stars++;
            show[2] = 0;
        }

        if (mouseX >= star_positions[3].x && mouseX <= star_positions[3].x + 110 &&
            -mouseY + window->GetResolution().y >= star_positions[3].y && -mouseY + window->GetResolution().y <= star_positions[3].y + 110 && show[3] == 1) {
            no_stars++;
            show[3] = 0;
        }
        // Logica apasarii mouse ului pentru a detecta stelele
        if (mouseX >= 10 && mouseX <= 110 && -mouseY + window->GetResolution().y >= 600 && -mouseY + window->GetResolution().y <= 700) {
            if (no_stars >= 1) {
                selected_diamonds[0] = 1; // casuta selectata - romb 1
            }  
        }
        if (mouseX >= 160 && mouseX <= 260 && -mouseY + window->GetResolution().y >= 600 && -mouseY + window->GetResolution().y <= 700) {
            if (no_stars >= 2) {
                selected_diamonds[1] = 1; // casuta selectata - romb 2
            }
        }
        if (mouseX >= 310 && mouseX <= 410 && -mouseY + window->GetResolution().y >= 600 && -mouseY + window->GetResolution().y <= 700) {
            if (no_stars >= 2) {
                selected_diamonds[2] = 1; // casuta selectata - romb 2
            }
        }
        if (mouseX >= 460 && mouseX <= 560 && -mouseY + window->GetResolution().y >= 600 && -mouseY + window->GetResolution().y <= 700) {
            if (no_stars >= 3) {
                selected_diamonds[3] = 1; // casuta selectata - romb 2
            }
        }
    }

    // dreapta - eliminare romb din scena - drop
    if (button == GLFW_MOUSE_BUTTON_3) {
        for (int i = 0; i <= 3; i++) {
            for (int j = 0; j <= 8; j++) {
                if (mouseX >= (j % 3) * 120 + 100 && mouseX <= (j % 3) * 120 + 200 && -mouseY + window->GetResolution().y >= (j / 3) * 120 + 20 &&
                    -mouseY + window->GetResolution().y <= (j / 3) * 120 + 120) {
                    if (matrix[i][j] == 1) {
                        deleted_diamond[i][j] = 1;
                    }
                }
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if (button == GLFW_MOUSE_BUTTON_2) {
        if (selected_diamonds[0] == 1) {
            if (mouseX >= 100 && mouseX <= 200 && -mouseY + window->GetResolution().y >= 20 && -mouseY + window->GetResolution().y <= 120) {
                if (matrix[0][0] == 0 && matrix[1][0] == 0 && matrix[2][0] == 0 && matrix[3][0] == 0) {
                    selected_diamonds[0] = 0;
                    no_stars--;
                    matrix[0][0] = 1;

                } 

            } else if (mouseX >= 220 && mouseX <= 320 && -mouseY + window->GetResolution().y >= 20 && -mouseY + window->GetResolution().y <= 120) {
                if (matrix[0][1] == 0 && matrix[1][1] == 0 && matrix[2][0] == 0 && matrix[3][1] == 0) {
                    selected_diamonds[0] = 0;
                    no_stars--;
                    matrix[0][1] = 1;

                }

            }
            else if (mouseX >= 340 && mouseX <= 440 && -mouseY + window->GetResolution().y >= 20 && -mouseY + window->GetResolution().y <= 120) {
                if (matrix[0][2] == 0 && matrix[1][2] == 0 && matrix[2][2] == 0 && matrix[3][2] == 0) {
                    selected_diamonds[0] = 0;
                    no_stars--;
                    matrix[0][2] = 1;

                }

            }
            else if (mouseX >= 100 && mouseX <= 200 && -mouseY + window->GetResolution().y >= 140 && -mouseY + window->GetResolution().y <= 240) {
                if (matrix[0][3] == 0 && matrix[1][3] == 0 && matrix[2][3] == 0 && matrix[3][3] == 0) {
                    selected_diamonds[0] = 0;
                    no_stars--;
                    matrix[0][3] = 1;

                }

            }
            else if (mouseX >= 220 && mouseX <= 320 && -mouseY + window->GetResolution().y >= 140 && -mouseY + window->GetResolution().y <= 240) {
                if (matrix[0][4] == 0 && matrix[1][4] == 0 && matrix[2][4] == 0 && matrix[3][4] == 0) {
                    selected_diamonds[0] = 0;
                    no_stars--;
                    matrix[0][4] = 1;

                }

            }
            else if (mouseX >= 340 && mouseX <= 440 && -mouseY + window->GetResolution().y >= 140 && -mouseY + window->GetResolution().y <= 240) {
                if (matrix[0][5] == 0 && matrix[1][5] == 0 && matrix[2][5] == 0 && matrix[3][5] == 0) {
                    selected_diamonds[0] = 0;
                    no_stars--;
                    matrix[0][5] = 1;

                }

            }
            else if (mouseX >= 100 && mouseX <= 200 && -mouseY + window->GetResolution().y >= 260 && -mouseY + window->GetResolution().y <= 360) {
                if (matrix[0][6] == 0 && matrix[1][6] == 0 && matrix[2][6] == 0 && matrix[3][6] == 0) {
                    selected_diamonds[0] = 0;
                    no_stars--;
                    matrix[0][6] = 1;

                }

            }
            else if (mouseX >= 220 && mouseX <= 320 && -mouseY + window->GetResolution().y >= 260 && -mouseY + window->GetResolution().y <= 360) {
                if (matrix[0][7] == 0 && matrix[1][7] == 0 && matrix[2][7] == 0 && matrix[3][7] == 0) {
                    selected_diamonds[0] = 0;
                    no_stars--;
                    matrix[0][7] = 1;

                }

            }
            else if (mouseX >= 340 && mouseX <= 440 && -mouseY + window->GetResolution().y >= 260 && -mouseY + window->GetResolution().y <= 360) {
                if (matrix[0][8] == 0 && matrix[1][8] == 0 && matrix[2][8] == 0 && matrix[3][8] == 0) {
                    selected_diamonds[0] = 0;
                    no_stars--;
                    matrix[0][8] = 1;

                }

            }
            else {
                selected_diamonds[0] = 0;
                selected_diamonds[1] = 0;
                selected_diamonds[2] = 0;
                selected_diamonds[3] = 0;

            }

        }
        if (selected_diamonds[1] == 1) {
            if (mouseX >= 100 && mouseX <= 200 && -mouseY + window->GetResolution().y >= 20 && -mouseY + window->GetResolution().y <= 120) {
                if (matrix[0][0] == 0 && matrix[1][0] == 0 && matrix[2][0] == 0 && matrix[3][0] == 0) {
                    selected_diamonds[1] = 0;
                    no_stars = no_stars - 2;
                    matrix[1][0] = 1;

                }

            }
            else if (mouseX >= 220 && mouseX <= 320 && -mouseY + window->GetResolution().y >= 20 && -mouseY + window->GetResolution().y <= 120) {
                if (matrix[0][1] == 0 && matrix[1][1] == 0 && matrix[2][1] == 0 && matrix[3][1] == 0) {
                    selected_diamonds[1] = 0;
                    no_stars = no_stars - 2;
                    matrix[1][1] = 1;

                }

            }
            else if (mouseX >= 340 && mouseX <= 440 && -mouseY + window->GetResolution().y >= 20 && -mouseY + window->GetResolution().y <= 120) {
                if (matrix[0][2] == 0 && matrix[1][2] == 0 && matrix[2][2] == 0 && matrix[3][2] == 0) {
                    selected_diamonds[1] = 0;
                    no_stars = no_stars - 2;
                    matrix[1][2] = 1;

                }

            }
            else if (mouseX >= 100 && mouseX <= 200 && -mouseY + window->GetResolution().y >= 140 && -mouseY + window->GetResolution().y <= 240) {
                if (matrix[0][3] == 0 && matrix[1][3] == 0 && matrix[2][3] == 0 && matrix[3][3] == 0) {
                    selected_diamonds[1] = 0;
                    no_stars = no_stars - 2;
                    matrix[1][3] = 1;

                }

            }
            else if (mouseX >= 220 && mouseX <= 320 && -mouseY + window->GetResolution().y >= 140 && -mouseY + window->GetResolution().y <= 240) {
                if (matrix[0][4] == 0 && matrix[1][4] == 0 && matrix[2][4] == 0 && matrix[3][4] == 0) {
                    selected_diamonds[1] = 0;
                    no_stars = no_stars - 2;
                    matrix[1][4] = 1;

                }

            }
            else if (mouseX >= 340 && mouseX <= 440 && -mouseY + window->GetResolution().y >= 140 && -mouseY + window->GetResolution().y <= 240) {
                if (matrix[0][5] == 0 && matrix[1][5] == 0 && matrix[2][5] == 0 && matrix[3][5] == 0) {
                    selected_diamonds[1] = 0;
                    no_stars = no_stars - 2;
                    matrix[1][5] = 1;

                }

            }
            else if (mouseX >= 100 && mouseX <= 200 && -mouseY + window->GetResolution().y >= 260 && -mouseY + window->GetResolution().y <= 360) {
                if (matrix[0][6] == 0 && matrix[1][6] == 0 && matrix[2][6] == 0 && matrix[3][6] == 0) {
                    selected_diamonds[1] = 0;
                    no_stars = no_stars - 2;
                    matrix[1][6] = 1;

                }

            }
            else if (mouseX >= 220 && mouseX <= 320 && -mouseY + window->GetResolution().y >= 260 && -mouseY + window->GetResolution().y <= 360) {
                if (matrix[0][7] == 0 && matrix[1][7] == 0 && matrix[2][7] == 0 && matrix[3][7] == 0) {
                    selected_diamonds[1] = 0;
                    no_stars = no_stars - 2;
                    matrix[1][7] = 1;

                }

            }
            else if (mouseX >= 340 && mouseX <= 440 && -mouseY + window->GetResolution().y >= 260 && -mouseY + window->GetResolution().y <= 360) {
                if (matrix[0][8] == 0 && matrix[1][8] == 0 && matrix[2][8] == 0 && matrix[3][8] == 0) {
                    selected_diamonds[1] = 0;
                    no_stars = no_stars - 2;
                    matrix[1][8] = 1;

                }

            }
            else {
                selected_diamonds[0] = 0;
                selected_diamonds[1] = 0;
                selected_diamonds[2] = 0;
                selected_diamonds[3] = 0;

            }

        }
        if (selected_diamonds[2] == 1) {
            if (mouseX >= 100 && mouseX <= 200 && -mouseY + window->GetResolution().y >= 20 && -mouseY + window->GetResolution().y <= 120) {
                if (matrix[0][0] == 0 && matrix[1][0] == 0 && matrix[2][0] == 0 && matrix[3][0] == 0) {
                    selected_diamonds[2] = 0;
                    no_stars = no_stars - 2;
                    matrix[2][0] = 1;

                }

            }
            else if (mouseX >= 220 && mouseX <= 320 && -mouseY + window->GetResolution().y >= 20 && -mouseY + window->GetResolution().y <= 120) {
                if (matrix[0][1] == 0 && matrix[1][1] == 0 && matrix[2][1] == 0 && matrix[3][1] == 0) {
                    selected_diamonds[2] = 0;
                    no_stars = no_stars - 2;
                    matrix[2][1] = 1;

                }

            }
            else if (mouseX >= 340 && mouseX <= 440 && -mouseY + window->GetResolution().y >= 20 && -mouseY + window->GetResolution().y <= 120) {
                if (matrix[0][2] == 0 && matrix[1][2] == 0 && matrix[2][2] == 0 && matrix[3][2] == 0) {
                    selected_diamonds[2] = 0;
                    no_stars = no_stars - 2;
                    matrix[2][2] = 1;

                }

            }
            else if (mouseX >= 100 && mouseX <= 200 && -mouseY + window->GetResolution().y >= 140 && -mouseY + window->GetResolution().y <= 240) {
                if (matrix[0][3] == 0 && matrix[1][3] == 0 && matrix[2][3] == 0 && matrix[3][3] == 0) {
                    selected_diamonds[2] = 0;
                    no_stars = no_stars - 2;
                    matrix[2][3] = 1;

                }

            }
            else if (mouseX >= 220 && mouseX <= 320 && -mouseY + window->GetResolution().y >= 140 && -mouseY + window->GetResolution().y <= 240) {
                if (matrix[0][4] == 0 && matrix[1][4] == 0 && matrix[2][4] == 0 && matrix[3][4] == 0) {
                    selected_diamonds[2] = 0;
                    no_stars = no_stars - 2;
                    matrix[2][4] = 1;

                }

            }
            else if (mouseX >= 340 && mouseX <= 440 && -mouseY + window->GetResolution().y >= 140 && -mouseY + window->GetResolution().y <= 240) {
                if (matrix[0][5] == 0 && matrix[1][5] == 0 && matrix[2][5] == 0 && matrix[3][5] == 0) {
                    selected_diamonds[2] = 0;
                    no_stars = no_stars - 2;
                    matrix[2][5] = 1;

                }

            }
            else if (mouseX >= 100 && mouseX <= 200 && -mouseY + window->GetResolution().y >= 260 && -mouseY + window->GetResolution().y <= 360) {
                if (matrix[0][6] == 0 && matrix[1][6] == 0 && matrix[2][6] == 0 && matrix[3][6] == 0) {
                    selected_diamonds[2] = 0;
                    no_stars = no_stars - 2;
                    matrix[2][6] = 1;

                }

            }
            else if (mouseX >= 220 && mouseX <= 320 && -mouseY + window->GetResolution().y >= 260 && -mouseY + window->GetResolution().y <= 360) {
                if (matrix[0][7] == 0 && matrix[1][7] == 0 && matrix[2][7] == 0 && matrix[3][7] == 0) {
                    selected_diamonds[2] = 0;
                    no_stars = no_stars - 2;
                    matrix[2][7] = 1;

                }

            }
            else if (mouseX >= 340 && mouseX <= 440 && -mouseY + window->GetResolution().y >= 260 && -mouseY + window->GetResolution().y <= 360) {
                if (matrix[0][8] == 0 && matrix[1][8] == 0 && matrix[2][8] == 0 && matrix[3][8] == 0) {
                    selected_diamonds[2] = 0;
                    no_stars = no_stars - 2;
                    matrix[2][8] = 1;

                }

            }
            else {
                selected_diamonds[0] = 0;
                selected_diamonds[1] = 0;
                selected_diamonds[2] = 0;
                selected_diamonds[3] = 0;

            }

        }
        if (selected_diamonds[3] == 1) {
            if (mouseX >= 100 && mouseX <= 200 && -mouseY + window->GetResolution().y >= 20 && -mouseY + window->GetResolution().y <= 120) {
                if (matrix[0][0] == 0 && matrix[1][0] == 0 && matrix[2][0] == 0 && matrix[3][0] == 0) {
                    selected_diamonds[3] = 0;
                    no_stars = no_stars - 3;
                    matrix[3][0] = 1;

                }

            }
            else if (mouseX >= 220 && mouseX <= 320 && -mouseY + window->GetResolution().y >= 20 && -mouseY + window->GetResolution().y <= 120) {
                if (matrix[0][1] == 0 && matrix[1][1] == 0 && matrix[2][1] == 0 && matrix[3][1] == 0) {
                    selected_diamonds[3] = 0;
                    no_stars = no_stars - 3;
                    matrix[3][1] = 1;

                }

            }
            else if (mouseX >= 340 && mouseX <= 440 && -mouseY + window->GetResolution().y >= 20 && -mouseY + window->GetResolution().y <= 120) {
                if (matrix[0][2] == 0 && matrix[1][2] == 0 && matrix[2][2] == 0 && matrix[3][2] == 0) {
                    selected_diamonds[3] = 0;
                    no_stars = no_stars - 3;
                    matrix[3][2] = 1;

                }

            }
            else if (mouseX >= 100 && mouseX <= 200 && -mouseY + window->GetResolution().y >= 140 && -mouseY + window->GetResolution().y <= 240) {
                if (matrix[0][3] == 0 && matrix[1][3] == 0 && matrix[2][3] == 0 && matrix[3][3] == 0) {
                    selected_diamonds[3] = 0;
                    no_stars = no_stars - 3;
                    matrix[3][3] = 1;

                }

            }
            else if (mouseX >= 220 && mouseX <= 320 && -mouseY + window->GetResolution().y >= 140 && -mouseY + window->GetResolution().y <= 240) {
                if (matrix[0][4] == 0 && matrix[1][4] == 0 && matrix[2][4] == 0 && matrix[3][4] == 0) {
                    selected_diamonds[3] = 0;
                    no_stars = no_stars - 3;
                    matrix[3][4] = 1;

                }

            }
            else if (mouseX >= 340 && mouseX <= 440 && -mouseY + window->GetResolution().y >= 140 && -mouseY + window->GetResolution().y <= 240) {
                if (matrix[0][5] == 0 && matrix[1][5] == 0 && matrix[2][5] == 0 && matrix[3][5] == 0) {
                    selected_diamonds[3] = 0;
                    no_stars = no_stars - 3;
                    matrix[3][5] = 1;

                }

            }
            else if (mouseX >= 100 && mouseX <= 200 && -mouseY + window->GetResolution().y >= 260 && -mouseY + window->GetResolution().y <= 360) {
                if (matrix[0][6] == 0 && matrix[1][6] == 0 && matrix[2][6] == 0 && matrix[3][6] == 0) {
                    selected_diamonds[3] = 0;
                    no_stars = no_stars - 3;
                    matrix[3][6] = 1;

                }

            }
            else if (mouseX >= 220 && mouseX <= 320 && -mouseY + window->GetResolution().y >= 260 && -mouseY + window->GetResolution().y <= 360) {
                if (matrix[0][7] == 0 && matrix[1][7] == 0 && matrix[2][7] == 0 && matrix[3][7] == 0) {
                    selected_diamonds[3] = 0;
                    no_stars = no_stars - 3;
                    matrix[3][7] = 1;

                }

            }
            else if (mouseX >= 340 && mouseX <= 440 && -mouseY + window->GetResolution().y >= 260 && -mouseY + window->GetResolution().y <= 360) {
                if (matrix[0][8] == 0 && matrix[1][8] == 0 && matrix[2][8] == 0 && matrix[3][8] == 0) {
                    selected_diamonds[3] = 0;
                    no_stars = no_stars - 3;
                    matrix[3][8] = 1;

                }

            }
            else {
                selected_diamonds[0] = 0;
                selected_diamonds[1] = 0;
                selected_diamonds[2] = 0;
                selected_diamonds[3] = 0;

            }

        }
    }

}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}