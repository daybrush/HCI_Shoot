#include "ofMain.h"
class LevelController {
public:
    float start_time;
    float interval_time;
    void setup(float e);
    bool should_spawn();
    void update(int score);
    
    int level;
    float mul_speed;
    int mul_number;
};