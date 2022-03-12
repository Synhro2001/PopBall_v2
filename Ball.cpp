#include "Ball.h"
#include <iostream>;

Ball* ball;

Ball::Ball(int frameWidth, int frameHeight) {
    frameHeight_ = frameHeight;
    frameWidth_ = frameWidth;
    x_ = frameWidth / 2.0;
    y_ = frameHeight / 2.0;
    size_ = 30;
    color_ = 0x78FF0000; //   Transparent red color.

    dX_ = 1;
    dY_ = 1;

}


void Ball::draw(Graphics^ graphics) {
  
    Pen ballPen(Color::Black, 1);
    SolidBrush brush(Color::FromArgb(color_));
        graphics->FillEllipse(% brush, x_ - size_, y_ - size_, size_ * 2.0, size_ * 2.0);
        graphics->DrawEllipse(% ballPen, x_ - size_, y_ - size_, size_ * 2.0, size_ * 2.0);
   

}


void Ball::setPos(int x, int y) {
   
    if (x <= size_) x = size_ + 1;
    if (x > frameWidth_ - size_) x = frameWidth_ - size_ - 1;
    
    if (y <= size_) y = size_ + 1;
    if (y > frameHeight_ - size_) y = frameHeight_ - size_ - 1;
    
     x_ = x;
     y_ = y;

}

float Ball::getdX() {
    return dX_;
}

float Ball::getdY() {
    return dY_;
}

void Ball::setSpeed(float dX, float dY) {
    if (dX > 10) dX = 10;
    if (dX < -10) dX = -10;
    if (dY > 10) dY = 10;
    if (dY < -10) dY = -10;

    dX_ = dX;


}

void Ball::move() {

    if ((x_ <= size_) || (x_ > frameWidth_ - size_))
    {
        dX_ = -dX_;
    }
    if ((y_ <= size_) || (y_ > frameHeight_ - size_))
    {
        dY_ = -dY_;
    }

    x_ += dX_;
    y_ += dY_;
}

int Ball::getColor() {
    return color_;
}

void Ball::setColor(int color) {
    color_ = color;

}

int Ball::getSize() {
    return size_;
}



void Ball::setSize(int size) {


    
    if (size > 10 && size < 90) {
        size_ = size;
    }
    setPos(x_, y_);


}


