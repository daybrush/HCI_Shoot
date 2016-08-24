#include "ofMain.h"
class Bullet {
public:
    void setup(bool f_p, ofPoint p, float s, ofImage * bullet_image);
    void update();
    void draw();
    ofPoint pos;
    float speed;
    float width;
    bool from_player;
    ofImage * img;
    float speed_x;
};