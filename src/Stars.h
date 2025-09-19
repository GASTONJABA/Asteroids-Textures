#pragma once
#include "raylib.h"



    enum StarsSize { Large, Medium, Small };

    class Stars
    {
    public:
        Vector2 position;
        Vector2 velocity;
       float radius;
        bool active;
        StarsSize size;
       
      Stars();
        void Spawn(Vector2 pos, StarsSize s,Texture2D tex, Vector2 parentDir = { 0,0 });
        void Update(float deltaTime);
        void Draw();
        //int Break(Stars* pool, int poolSize);
    };




