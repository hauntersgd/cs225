#include "Image.h"
#include "../lib/cs225/HSLAPixel.h"
#include <cmath>

Image::Image(){
}  

Image::Image(unsigned int width, unsigned int height){
    this->resize(width, height);
}

void Image::darken(){
    unsigned width_ = width();
    unsigned height_ = height();
    for(unsigned y = 0; y < height_; y++) {
        for(unsigned x = 0; x < width_; x++) {
            cs225::HSLAPixel& curr = this->getPixel(x, y);
            if(curr.l - 0.1 <= 0) {
                curr.l = 0;
            } else {
                curr.l = curr.l - 0.1;
            }
        }
    }
}

void Image::darken(double amount){
    unsigned width_ = this->width();
    unsigned height_ = this->height();
    for(unsigned y = 0; y < height_; y++) {
        for(unsigned x = 0; x < width_; x++) {
            cs225::HSLAPixel& curr = this->getPixel(x, y);
            if(curr.l - amount <= 0) {
                curr.l = 0;
            } else {
                curr.l = curr.l - amount;
            }
        }
    }
}


void Image::desaturate(){
    unsigned width_ = this->width();
    unsigned height_ = this->height();
    for(unsigned y = 0; y < height_; y++) {
        for(unsigned x = 0; x < width_; x++) {
            cs225::HSLAPixel& curr = this->getPixel(x, y);
            if(curr.s - 0.1 <= 0) {
                curr.s = 0;
            } else {
                curr.s = curr.s - 0.1;
            }
        }
    }
}

void Image::desaturate(double amount){
    unsigned width_ = this->width();
    unsigned height_ = this->height();
    for(unsigned y = 0; y < height_; y++) {
        for(unsigned x = 0; x < width_; x++) {
            cs225::HSLAPixel& curr = this->getPixel(x, y);
            if(curr.s - amount <= 0) {
                curr.s = 0;
            } else {
                curr.s = curr.s - amount;
            }
        }
    }
}

void Image::grayscale(){
    unsigned width_ = this->width();
    unsigned height_ = this->height();
    for(unsigned y = 0; y < height_; y++) {
        for(unsigned x = 0; x < width_; x++) {
            cs225::HSLAPixel& curr = this->getPixel(x, y);
            curr.s = 0;
        }
    }
}

void Image::illinify(){
    /*
        “Illini Orange” has a hue of 11
        “Illini Blue” has a hue of 216
    */
    unsigned width_ = this->width();
    unsigned height_ = this->height();
    for(unsigned y = 0; y < height_; y++) {
        for(unsigned x = 0; x < width_; x++) {
            cs225::HSLAPixel& curr = this->getPixel(x, y);
            unsigned distOrange = std::min(std::fabs((360 - curr.h) + 11), std::fabs(curr.h - 11));
            unsigned distBlue = std::min(std::fabs((360 - curr.h) + 216), std::fabs(curr.h - 216));
            if(distOrange <= distBlue) {
                curr.h = 11;
            } else {
                curr.h = 216;
            }
        }
    }
}


void Image::lighten(){
    unsigned width_ = this->width();
    unsigned height_ = this->height();
    for(unsigned y = 0; y < height_; y++) {
        for(unsigned x = 0; x < width_; x++) {
            cs225::HSLAPixel& curr = this->getPixel(x, y);
            if(curr.l + 0.1 >= 1.0) {
                curr.l = 1.0;
            } else {
                curr.l = curr.l + 0.1;
            }
        }
    }
}

void Image::lighten(double amount){
    unsigned width_ = this->width();
    unsigned height_ = this->height();
    for(unsigned int y = 0; y < height_; y++) {
        for(unsigned int x = 0; x < width_; x++) {
            cs225::HSLAPixel& curr = this->getPixel(x, y);
            if(curr.l + amount >= 1) {
                curr.l = 1.0;
            } else {
                curr.l = curr.l + amount;
            }
        }
    }
}

void Image::rotateColor(double degrees){
    unsigned width_ = this->width();
    unsigned height_ = this->height();
    for(unsigned y = 0; y < height_; y++) {
        for(unsigned x = 0; x < width_; x++) {
            cs225::HSLAPixel& curr = this->getPixel(x, y);
            double degchange = fmod(degrees, 360);
            if(degchange > 0) {
                curr.h = fmod(curr.h + degchange, 360);
            } else {
                curr.h = fmod(360 + curr.h + degchange, 360);
            }
        }
    }
}

void Image::saturate(){
    unsigned width_ = this->width();
    unsigned height_ = this->height();
    for(unsigned y = 0; y < height_; y++) {
        for(unsigned x = 0; x < width_; x++) {
            cs225::HSLAPixel& curr = this->getPixel(x, y);
            if(curr.s + 0.1 >= 1) {
                curr.s = 1;
            } else {
                curr.s = curr.s + 0.1;
            }
        }
    }
}

void Image::saturate(double amount){
    unsigned width_ = this->width();
    unsigned height_ = this->height();
    for(unsigned y = 0; y < height_; y++) {
        for(unsigned x = 0; x < width_; x++) {
            cs225::HSLAPixel& curr = this->getPixel(x, y);
            if(curr.s + amount >= 1) {
                curr.s = 1;
            } else {
                curr.s = curr.s + amount;
            }
        }
    }
}

void Image::scale(double factor){
    unsigned width_ = this->width();
    unsigned height_ = this->height();
    unsigned newwidth_ = width_ * factor;
    unsigned newheight_ = height_ * factor;
    Image changed;
    changed.resize(newwidth_, newheight_);
    for(unsigned y = 0; y < newheight_; y++) {
        for(unsigned x = 0; x < newwidth_; x++) {
            cs225::HSLAPixel& cpixel = changed.getPixel(x, y);
            unsigned nx = x / factor;
            unsigned ny = y / factor;
            cpixel = this->getPixel(nx, ny);
        }
    }
    (*this) = changed;
}

void Image::scale(unsigned w, unsigned h){
    unsigned width_ = this->width();
    unsigned height_ = this->height();
    double wsf = static_cast<double>(w)/width_;
    double hsf = static_cast<double>(h)/height_;
    this->scale(std::min(wsf, hsf));
}
