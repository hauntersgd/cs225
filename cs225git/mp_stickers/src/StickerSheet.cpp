#include "StickerSheet.h"


StickerSheet::StickerSheet(const Image &picture, unsigned max){ // constructor
    base = picture;
    max_ = max;
    stickers.clear();
    x.clear();
    y.clear();
    stickers.resize(max, nullptr);
    x.resize(max, 0);
    y.resize(max, 0);
}

StickerSheet::StickerSheet(const StickerSheet &other){ // copy constructor
    base = other.base;
    max_ = other.max_;
    x.clear();
    y.clear();
    stickers.clear();
    stickers.resize(other.max_, nullptr);
    x.resize(other.max_, 0);
    y.resize(other.max_, 0);
    for(unsigned i = 0; i < other.max_; i++) {
        if(other.stickers[i] != nullptr) {
            stickers[i] = other.stickers[i];
            x[i] = other.x[i];
            y[i] = other.y[i];
        } 
    }
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other){ // assignment operator
    if(this != &other) {
        base = other.base;
        max_ = other.max_;
        x.clear();
        y.clear();
        stickers.clear();
        stickers.resize(other.max_, nullptr);
        x.resize(other.max_, 0);
        y.resize(other.max_, 0);
        for(unsigned i = 0; i < other.max_; i++) {
            if(other.stickers[i] != nullptr) {
                stickers[i] = other.stickers[i];
                x[i] = other.x[i];
                y[i] = other.y[i];
            } 
        }
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){

    if(max_ == max) {
        return;
    } else if(max < max_) {
        stickers.resize(max);
        x.resize(max);
        y.resize(max);
    } else {
        stickers.resize(max, nullptr);
        x.resize(max, 0);
        y.resize(max, 0);
    }
    max_ = max;
}

int StickerSheet::addSticker(Image &sticker, int x_, int y_){
    for(unsigned i = 0; i < max_; i++) {
        if(stickers[i] == nullptr) {
            stickers[i] = &sticker;
            x[i] = x_;
            y[i] = y_;
            return i;
        }
    }
    stickers.push_back(&sticker);
    x.push_back(x_);
    y.push_back(y_);
    max_++;
    return max_ - 1;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x_, int y_){ // Continue here
    if(layer < 0 || layer >= max_) {
        return -1;
    } else {
        stickers[layer] = &sticker;
        x[layer] = x_;
        y[layer] = y_;
    }
    return layer;
}

bool StickerSheet::translate(unsigned index, int x_, int y_){
    if(index < 0 || index >= max_ || stickers[index] == nullptr) {
        return false;
    }
    x[index] = x_;
    y[index] = y_;
    return true;
}

void StickerSheet::removeSticker(unsigned index){
    if(index >= 0 && index < max_) {
        if(stickers[index] != nullptr) {
            stickers[index] = nullptr; // just remove sticker, not layer
        }
    }
}

Image* StickerSheet::getSticker(unsigned index){
    if(index >= 0 && index < max_) {
        if(stickers[index] != nullptr) { // maybe want to return nullptr?
            return stickers[index];
        }
    }
    return NULL;
}

int StickerSheet::layers() const{
    return max_;
}

Image StickerSheet::render() const{

    Image canvas = Image();

    int minx = 0;
    int miny = 0;
    int maxx = int(base.width());
    int maxy = int(base.height()); 

    // find dimensions of canvas to fit all stickers and base image

    // iterate through x and y pixel vectors

    for(unsigned i = 0; i < max_; i++) {
        if(x[i] < minx) {
            minx = x[i];
        } 
        if(stickers[i] != nullptr) {
            if(x[i] + int(stickers[i]->width()) > maxx) { //
                maxx = x[i] + int(stickers[i]->width());
            }
        }

        if(y[i] < miny) {
            miny = y[i];
        }

        if(stickers[i] != nullptr) {
            if(y[i] + int(stickers[i]->height()) > maxy) { //
                maxy = y[i] + int(stickers[i]->height());
            }
        }
    }

    canvas.resize(int(maxx-minx), int(maxy-miny)); //

    //draw the base image


    for(unsigned int x1 = 0; x1 < base.width(); x1++) {
        for(unsigned int y1 = 0; y1 < base.height(); y1++) {
            cs225::HSLAPixel& canvaspixel = canvas.getPixel(x1 - minx, y1 - miny);
            canvaspixel = base.getPixel(x1,y1);
        }
    }

    //draw the stickers


    for(unsigned int currStick = 0; currStick < stickers.size(); currStick++) {
        if(stickers[currStick] == nullptr) {
                    continue;
        }
        for(unsigned int y1 = 0; y1 < stickers[currStick]->height(); y1++) {
            for(unsigned int x1 = 0; x1 < stickers[currStick]->width(); x1++) {
                 // check sticker is not null and that it is not transparent
                 if(stickers[currStick]->getPixel(x1, y1).a > 0) {
                    cs225::HSLAPixel& canvaspixel = canvas.getPixel(x[currStick] - minx + x1, y[currStick] - miny + y1); // out of bounds
                    canvaspixel = stickers[currStick]->getPixel(x1, y1);
                 }
                
            }
        }
    }

    //return the image

    return canvas;
}