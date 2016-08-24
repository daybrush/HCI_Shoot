#include "Player.hpp"
Player::Player() {
}
void Player::setup(ofImage * _img)
{
    img = _img;
    pos.x = 100;
    pos.y = ofGetHeight() - 100;
    width = 80;
    height= 80;
    speed = 5;
    lives = 5;
}
void Player::reset() {
    speed = 5;
    lives = 5;
    level = 0;
}
void Player::update(int level)
{
    if((int)(this->level / 2 ) != (int)(level / 2)) {
        if(lives < 5)
            lives++;
    }
    this->level = level;
    if (is_left_pressed) {
        pos.x -= speed;
    }
    if (is_right_pressed) {
        pos.x += speed;
    }
    if (is_up_pressed) {
        pos.y -= speed;
    }
    if (is_down_pressed) {
        pos.y += speed;
    }
}


void Player::draw()
{
    img->draw(pos.x - width/2, pos.y - height/2 , width, height);
}

void Player::shoot()
{
}
void Player::calculate_movement()
{
}
bool Player::check_can_shoot()
{
}