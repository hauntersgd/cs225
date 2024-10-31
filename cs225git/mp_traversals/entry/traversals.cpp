
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "ImageTraversal.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  RainbowColorPicker rainbow(0.05);
  PNG png;
  png.readFromFile("../data/insane.png");
  FloodFilledImage f(png);
  Traversals::ImageTraversal t(png, Point(445, 100), 0.5, {Traversals::dfs_add, Traversals::dfs_pop, Traversals::dfs_peek});
  f.addFloodFill(t, rainbow);
  Animation animation = f.animate(8000);


  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  
  return 0;
}
