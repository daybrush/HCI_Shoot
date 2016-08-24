//
//  Item.cpp
//  myGame
//
//  Created by younkue's air on 2016. 8. 1..
//
//

#include "Item.hpp"

void Item::setup(ofPoint p, ofImage * img) {
    pos = p;
    speed = 4;
    this->img = img;
    width = 50;
}

void Item::update() {
        pos.y += speed;
}
void Item::draw() {
    img->draw(pos.x - width/2, pos.y - width/2, width, width);
}