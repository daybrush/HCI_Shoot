//
//  Enemy.cpp
//  myGame
//
//  Created by younkue's air on 2016. 8. 1..
//
//

#include "Enemy.hpp"

void Enemy::setup(float max_enemy_amplitude, float max_enemy_shoot_interval,
                  ofImage * enemy_image, float speed) {
    pos.x = ofRandom(ofGetWidth());
    pos.y = 0;
    img = enemy_image;
    width = 80;
    this->speed = ofRandom(2, 7);
    this->bullet_speed = speed;
    amplitude = ofRandom(max_enemy_amplitude);
    shoot_interval = ofRandom(0.5, max_enemy_shoot_interval);
    start_shoot = ofGetElapsedTimef();
}

void Enemy::update() {
    pos.y += speed;
    pos.x += amplitude * sin(ofGetElapsedTimef());
}
void Enemy::draw() {
    img->draw(pos.x - width/2, pos.y - width/2, width, width);
}

bool Enemy::time_to_shoot() {
    if (ofGetElapsedTimef() - start_shoot > shoot_interval) {
        start_shoot = ofGetElapsedTimef();
        return true;
    }
    return false;
}

