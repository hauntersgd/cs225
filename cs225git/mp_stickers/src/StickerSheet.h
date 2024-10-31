/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "../src/Image.h"
#include <vector>

class StickerSheet {
    public:

        StickerSheet(const Image &picture, unsigned max);
        
        StickerSheet(const StickerSheet &other);

        //~StickerSheet();
        
        const StickerSheet & operator=(const StickerSheet &other);
        
        void changeMaxStickers(unsigned max);
        
        int addSticker(Image &sticker, int x_, int y_);
        
        int setStickerAtLayer(Image &sticker, unsigned layer, int x_, int y_);
        
        bool translate(unsigned index, int x_, int y_);
        
        void removeSticker(unsigned index);
        
        Image* getSticker(unsigned index);
        
        int layers() const;
        
        Image render() const;

    private:
        Image base;
        std::vector<Image*> stickers;
        std::vector<int> x;
        std::vector<int> y;
        unsigned max_;
};