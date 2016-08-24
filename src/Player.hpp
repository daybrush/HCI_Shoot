#pragma once

#include "ofMain.h"

class Player {
public:
    Player();
    void setup(ofImage * _img);
    void update(int level);
    void draw();
    void reset();
    void shoot();
    void calculate_movement();
    bool check_can_shoot();
    
public:

    ofPoint pos;
    ofImage *img;
    float width, height, speed;
    int lives;
    int level;
    bool is_left_pressed, is_right_pressed, is_down_pressed, is_up_pressed;
};