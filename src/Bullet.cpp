//
//  Bullet.cpp
//  myGame
//
//  Created by younkue's air on 2016. 8. 1..
//
//

#include "Bullet.hpp"


void Bullet::setup(bool f_p, ofPoint p, float s, ofImage * bullet_image) {
    from_player = f_p;
    pos = p;
    speed = s + 3;
    speed_x = 0;
    img = bullet_image;
    width = 20;
}

void Bullet::update() {
    if (from_player) {
        pos.y -= speed;
        pos.x -= speed_x;
    } else {
        pos.y += speed;
        pos.y += speed_x;
    }
}
void Bullet::draw() {
    img->draw(pos.x - width/2, pos.y - width/2, width, width);
}