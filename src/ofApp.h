#pragma once

#include "ofMain.h"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Item.hpp"
#include "LevelController.hpp"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void draw_scores();
        void draw_lives();
        void update_bullets();
    void update_items();
        void check_bullet_collision(void);
    void check_items_collision(void);
    
    string game_state;
    int score;
    ofImage start_screen;
    ofImage end_screen;
    ofTrueTypeFont score_font;
    
    Player player_1;
    ofImage player_image;
    
    vector<Bullet> bullets;
    ofImage player_bullet_image;
    
    
    vector<Enemy> enemies;
    ofImage enemy_image;
    ofImage enemy_bullet_image;
    
    vector<Item> items;
    ofImage item_image;
    
    
    float max_enemy_amplitude;
    float max_enemy_shoot_interval;
    
    LevelController level_controller;
};
