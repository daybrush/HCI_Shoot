//
//  Item.hpp
//  myGame
//
//  Created by younkue's air on 2016. 8. 1..
//
//
#include "ofMain.h"

class Item {
public:
    void setup(ofPoint p, ofImage * img);
    void update();
    void draw();
    
    ofPoint pos;
    float num_bullet;
    float width;
    int speed;
    bool from_player;
    ofImage * img;
};