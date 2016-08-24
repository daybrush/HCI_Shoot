#include "ofMain.h"
class Enemy {
public:
    void setup(float max_enemy_amplitude, float max_enemy_shoot_interval, ofImage *
               enemy_image, float speed);
    void update();
    void draw();
    bool time_to_shoot();
public:
    ofPoint pos;
    float speed;
    float bullet_speed;
    float amplitude;
    float width;
    float start_shoot;
    float shoot_interval;
    ofImage * img;
};