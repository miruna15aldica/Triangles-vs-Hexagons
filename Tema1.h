#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        //void UpdateHexagons(float deltaTimeSeconds, int color, int row);
        //void Enemy_spawn(int start, float deltaTimeSeconds, int color, int row);
        struct Hexagon {
            int x;
            int y;
            int color;
            int row;
            bool deleted;
            float speed;
            int health;
            float scaleX;
            float scaleY;

        };
        struct Projectile {
            int x;
            int y;
            int color;
            int camp;
            float angularStep;
            float speed;
        };
        void Enemy_spawn(Hexagon *sts, float deltaTimeSeconds);
        void Flower_move(Projectile *sts, float deltaTimeSeconds);
        void Erase_diamond(int i, int j);

    protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        // TODO(student): If you need any other class variables, define them here.
        float translateStepX;
        float translateStepY;
        float scaleStepX;
        float scaleStepY;
        float rotationStep;

        // patrate + linie rosie - nu prea merge
        float cellSize;
        glm::vec3 cellColor;
        // stea
        float starSize;
        glm::vec3 starColor;
        float start_pos, speed, start_eq;
        float star_counter;
        glm::ivec2 star_positions[3];
        glm::ivec1 start_a[3], start_b[3];
        int star_verify = 0;
        int no_stars;
        int show[5];
        int selected_diamonds[4] = { 0 };
        int matrix[4][9] = { 0 };
        int enemy_verify;
        int trans_y =-50, trans_x = -50;
        int color, row;
        float enemy_counter = 10.0f;
        float start_enemy;
        int enemy_index = 0;
        int enemy_start[1000];
        int enemy_row[1000], enemy_color[1000];
        float proiectil_move[1000];
        int no_hearts;
        int garantat[1000];

        glm::vec2 scale_diamond[9];
        int deleted_diamond[4][9] = { 0 };
        int color0 = 0;
        std::vector<Hexagon> Hexagoane;
        std::vector<Projectile> Projectiles;
        int need_new_projectile[9];
        float new_projectile_timer[9];


    };
}   // namespace m1
