#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt((h*h) + (s*s) + (l*l));
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_back(point);
    return;
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_back(point);
    return;
  }

  /**
  * Removes the current Point in the bfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    if(!work_list.empty()) {
      work_list.pop_front();
    }
    return;
  }

  /**
  * Removes the current Point in the dfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    if(!work_list.empty()) {
      work_list.pop_back();
    }
    return;
  }

  /**
   * Returns the current Point in the bfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point bfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    if(!work_list.empty()) {
      return work_list.front();
    }
    return Point(-1, -1);
  }

  /**
   * Returns the current Point in the dfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point dfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    if(!work_list.empty()) {
      return work_list.back();
    }
    return Point(-1, -1);
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param fns the set of functions describing a traversal's operation
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns) {  
    /** @todo [Part 1] */
    png_ = png;
    start_ = start;
    tolerance_ = tolerance;
    fns_ = fns;
  }

  // x + 1 - right
  // y + 1 - down
  // x - 1 - left
  // y - 1 - up

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    ImageTraversal::Iterator b(png_, start_, tolerance_, fns_, start_);
    b.getDQ().push_back(start_);
    //b.getVisited()[]
    return b;
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    ImageTraversal::Iterator e(PNG(), start_, tolerance_, fns_, Point(-1, -1));
    return e;
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() {
    /** @todo [Part 1] */
  }

  ImageTraversal::Iterator::Iterator(PNG png, Point start, double tolerance, TraversalFunctions fns, Point current) {
    png__ = png;
    start__ = start;
    tolerance__ = tolerance;
    fns__ = fns;
    current_ = current;
    // std::vector<std::vector<bool>> visitedTemp(png.width(), std::vector<bool>(png.height()));
    
    int width = png.width();
    int height = png.height();
    visited.resize(width);
    for (int i = 0; i < width; i++) {
      visited[i].resize(height);
    }
  }


  /**
  * Iterator increment operator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */

    Point right = Point(current_.x + 1, current_.y);
    Point down = Point(current_.x, current_.y + 1);
    Point left = Point(current_.x - 1, current_.y);
    Point up = Point(current_.x, current_.y - 1);

    std::vector<Point> dirs = {right, down, left, up};
    Point curDir;

    //current_ = fns__.peek(work_list_);
    fns__.pop(work_list_);
    visited[current_.x][current_.y] = true;

    for(int i = 0; i < 4; i++) {
      curDir = dirs[i];
      if(curDir.x < 0 || curDir.y < 0 || curDir.x >= png__.width() || curDir.y >= png__.height()) {
        continue;
      }

      if(visited[curDir.x][curDir.y] == false && calculateDelta(png__.getPixel(curDir.x, curDir.y), 
      png__.getPixel(start__.x, start__.y)) < tolerance__) {
        fns__.add(work_list_, curDir);
      }
    }

    // std::cout << "Tolerance: " << tolerance__;

    // //debug
    // while(!work_list_.empty()) {
    //   std::cout << work_list_.front();
    //   work_list_.pop_front();
    // }

    current_ = fns__.peek(work_list_);

    // if(!work_list_.empty() && visited[current_.x][current_.y] == true) {
    //   fns__.pop(work_list_);
    //   current_ = fns__.peek(work_list_);
    // }
    while(!work_list_.empty() && visited[current_.x][current_.y] == true) {
      fns__.pop(work_list_);
      current_ = fns__.peek(work_list_);
    }

    return *this;
  }

  /**
  * Iterator accessor operator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return current_;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    if(current_ == other.current_) {
      return false;
    }
    return true;
  }

  /**
   * Iterator size function.
   *
   * @return size_t the size of the iterator work queue.
   */
  size_t ImageTraversal::Iterator::size() const {
    return work_list_.size();
  }

  /**
   * Iterator empty function.
   *
   * @return bool whether the iterator work queue is empty.
   */
  bool ImageTraversal::Iterator::empty() const {
    return work_list_.empty();
  }

}