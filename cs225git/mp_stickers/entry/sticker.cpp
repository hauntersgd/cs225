#include "Image.h"
#include "StickerSheet.h"

int main() {
  
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 50, 150);
  sheet.render().writeToFile("myImage.png");


  return 0;
}
