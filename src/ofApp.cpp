#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    game_state = "start";
    score = 0;
    
    start_screen.load("start_screen.png");
    end_screen.load("end_screen.png");
    score_font.load("Gota_Light.otf", 48);
    
    player_image.load("player.png");
    player_1.setup(&player_image);
    
    bullets.clear();
    player_bullet_image.load("player_bullet.png");
    
    
    max_enemy_amplitude = 3.0;
    max_enemy_shoot_interval = 1.5;
    enemies.clear();
    enemy_image.load("enemy.png");
    enemy_bullet_image.load("enemy_bullet.png");
    
    items.clear();
    item_image.load("item.png");
}

//--------------------------------------------------------------
void ofApp::update(){
    if (game_state == "start") {
    } else if (game_state == "game") {
        player_1.update(level_controller.level);
        update_bullets();
        update_items();
        
        level_controller.update(score);
        
        for(int i=0;i<enemies.size();i++) {
            enemies[i].update();
            if (enemies[i].time_to_shoot()) {
                Bullet b;
                b.setup(false, enemies[i].pos, enemies[i].bullet_speed, &enemy_bullet_image);
                bullets.push_back(b);
            }
        }
        if(level_controller.should_spawn()) {
            int max = MIN(level_controller.mul_number, 6);
            int s_max = MIN(level_controller.mul_speed, 10);
            for(int i=0;i< 3 * max;i++) {
                Enemy e;
                e.setup(max_enemy_amplitude, max_enemy_shoot_interval , &enemy_image, s_max);
                enemies.push_back(e);
            }
        }
        
    } else if (game_state == "end") {
    }
}
void ofApp::update_bullets() {
    for(int i=0;i<bullets.size();i++) {
        bullets[i].update();
        if (bullets[i].pos.x - bullets[i].width/2 < 0 || bullets[i].pos.y + bullets[i].width/2 >
            ofGetHeight()) {
            bullets.erase(bullets.begin()+i);
        }
    }
    check_bullet_collision();
}
void ofApp::update_items() {
    for(int i=0;i<items.size();i++) {
        items[i].update();
        if (items[i].pos.x - items[i].width/2 < 0 || items[i].pos.y + items[i].width/2 >
            ofGetHeight()) {
            items.erase(items.begin()+i);
        }
    }
    check_items_collision();
}
//--------------------------------------------------------------
void ofApp::draw(){
    if (game_state == "start") {
        start_screen.draw(0, 0, ofGetWidth(), ofGetHeight());
    } else if (game_state == "game") {
        ofBackground(0, 0, 0);
        player_1.draw();
        draw_scores();
        for (int i=0;i<bullets.size();i++) {
            bullets[i].draw();
        }
        for(int i=0;i<enemies.size();i++) {
            enemies[i].draw();
        }
        for(int i=0;i<items.size();i++) {
            items[i].draw();
        }
        draw_lives();
        draw_scores();
    } else if (game_state == "end") {
        end_screen.draw(0, 0, ofGetWidth(), ofGetHeight());
        draw_scores();
    }
}
void ofApp::draw_lives() {
    for(int i=0;i<player_1.lives;i++) {
        player_image.draw(ofGetWidth()-(i * 50)-100,30,48,48);
    }
}
void ofApp::draw_scores() {
    if (game_state == "game") {
        score_font.drawString(ofToString(score), 30, 72);
    } else if (game_state == "end") {
        float w = score_font.stringWidth(ofToString(score));
        score_font.drawString(ofToString(score), ofGetWidth()/2 - w/2, 200);
    }
}

void ofApp::check_bullet_collision(void) {
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i].from_player) {
            for (int e = enemies.size()-1; e >= 0; e--) {
                if (ofDist(bullets[i].pos.x, bullets[i].pos.y, enemies[e].pos.x, enemies[e].pos.y) < (enemies[e].width +
                                                                                                      bullets[i].width)/2) {
                    if(ofRandom(0, 50+ player_1.level) > 45+ player_1.level) {
                        Item b;
                        b.setup(enemies[e].pos, &item_image);
                        items.push_back(b);
                    }
                    
                    enemies.erase(enemies.begin()+e);
                    bullets.erase(bullets.begin()+i);
                    --i;
                    score+=10;
                    
                    
                }
            }
        } else {
            if (ofDist(bullets[i].pos.x, bullets[i].pos.y, player_1.pos.x , player_1.pos.y ) <
                (bullets[i].width+player_1.width)/4) {
                bullets.erase(bullets.begin()+i);
                player_1.lives--;
                if (player_1.lives <= 0) {
                    game_state = "end";
                }
            }
        }
    }
}


void ofApp::check_items_collision(void) {
    int max = 10;
    for (int i = 0; i < items.size(); i++) {
        if (ofDist(items[i].pos.x, items[i].pos.y, player_1.pos.x , player_1.pos.y ) <
            (items[i].width+player_1.width)/2) {
            items.erase(items.begin()+i);
        
            for(int j = 0; j < max;j++) {
                Bullet b;
                ofPoint pos;
                pos.x = player_1.pos.x + (j - max/2) * 15;
                pos.y = player_1.pos.y;
                b.setup(true, pos , player_1.speed * 2, &player_bullet_image);
                b.speed_x = - (j-max/2) /2;
                bullets.push_back(b);
            }
        
        }
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (game_state == "game") {
        if (key == OF_KEY_LEFT) {
            player_1.is_left_pressed = true;
        }
        if (key == OF_KEY_RIGHT) {
            player_1.is_right_pressed = true;
        }
        if (key == OF_KEY_UP) {
            player_1.is_up_pressed = true;
        }
        if (key == OF_KEY_DOWN) {
            player_1.is_down_pressed = true;
        }
        if (key == ' ') {
            int max = MIN(player_1.level / 3 + 1, 5);
            for(int i = 0; i < max; ++i) {
                Bullet b;
                ofPoint pos;
                pos.x = player_1.pos.x + (i - max/2) * 10;
                pos.y = player_1.pos.y;
                
                b.setup(true, pos, player_1.speed, &player_bullet_image);
                b.speed_x = (i-max/2) / 2;
                bullets.push_back(b);
            }
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (game_state == "start") {
        game_state = "game";
        score = 0;
        bullets.clear();
        enemies.clear();
        player_1.reset();
        items.clear();
        level_controller.setup(ofGetElapsedTimeMillis());
    } else if (game_state == "game") {
        if (key == OF_KEY_LEFT) {
            player_1.is_left_pressed = false;
        }
        if (key == OF_KEY_RIGHT) {
            player_1.is_right_pressed = false;
        }
        if (key == OF_KEY_UP) {
            player_1.is_up_pressed = false;
        }
        if (key == OF_KEY_DOWN) {
            player_1.is_down_pressed = false;
        }
        
    } else if(game_state == "end") {
        if(key =='r' || key == 'R') {
            game_state = "start";
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
