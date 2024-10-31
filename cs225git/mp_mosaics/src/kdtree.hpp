/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>
#include <cmath>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    /**
     * @todo Implement this function!
     */

    if(double(first[curDim]) == double(second[curDim])) {
      return first < second;
    }
    return double(first[curDim]) < double(second[curDim]);

}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    /**
     * @todo Implement this function!
     */
    double potentialtarget = 0.00;
    double currentBesttarget = 0.00;
    for(int i = 0; i < Dim; i++) {
      potentialtarget += (potential[i] - target[i]) * (potential[i] - target[i]);
    }

    for(int i = 0; i < Dim; i++) {
      currentBesttarget += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
    }

    if(potentialtarget == currentBesttarget) {
      return potential < currentBest;
    }

    return potentialtarget < currentBesttarget;
}

template <int Dim>
void KDTree<Dim>::insert(const vector<Point<Dim>>& newPoints, int splitDim, KDTreeNode*& cur) 
{

    std::vector<Point<Dim>> a = newPoints;

    if(a.empty()) {
      return;
    }


    auto medianIndex = std::floor((a.size() - 1)/2) + a.begin();

    auto cmp = [splitDim](const Point<Dim>& a, const Point<Dim>& b) {
      return smallerDimVal(a, b, splitDim);
    }; 

    select(a.begin(), a.end(), medianIndex, cmp);
    cur = new KDTreeNode(*medianIndex);

    std::vector<Point<Dim>> leftPoints(a.begin(), medianIndex);
    std::vector<Point<Dim>> rightPoints(medianIndex + 1, a.end());

    insert(leftPoints, (splitDim + 1) % Dim, cur->left);
    insert(rightPoints, (splitDim + 1) % Dim, cur->right);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

    insert(newPoints, 0, root);

}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

 
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */

  if(!root) {
    return;
  }
  std::deque<KDTreeNode*> kd;
  kd.push_back(root);
  while (!kd.empty()) {
      KDTreeNode* current = kd.front();
      kd.pop_front();

      if (current->left) {
          kd.push_back(current->left);
      }
      if (current->right) {
          kd.push_back(current->right);
      }

      delete(current);
  }

}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::neighborHelper(const Point<Dim>& query, int dim, KDTreeNode* node) const
{
    bool recursedLeft;
    KDTreeNode* nearest = new KDTreeNode();

    if(node == NULL) {
      return root;
    }

    if(node->left == NULL && node->right == NULL) {
      return node;
    }

    if(smallerDimVal(query, node->point, dim)) {
      nearest = neighborHelper(query, (dim + 1) % Dim, node->left);
      recursedLeft = true;
    } else {
      nearest = neighborHelper(query, (dim + 1) % Dim, node->right);
      recursedLeft = false;
    }

    if(shouldReplace(query, nearest->point, node->point)) {
      nearest = node;
    }

    double radius = squaredDistance(query, nearest->point);
    double splitDist = (node->point[dim] - query[dim]) * (node->point[dim] - query[dim]);

    KDTreeNode* possibleNearest;
    if(radius >= splitDist) {
      if(recursedLeft) {
        possibleNearest = neighborHelper(query, (dim + 1) % Dim, node->right);
      } else {
        possibleNearest = neighborHelper(query, (dim + 1) % Dim, node->left);
      }
      if(shouldReplace(query, nearest->point, possibleNearest->point)) {
        nearest = possibleNearest;
      }
    }
    return nearest;

}

template <int Dim>
double KDTree<Dim>::squaredDistance(const Point<Dim>& point1, const Point<Dim>& point2) const{

    double ans = 0.00;
    for(int i = 0; i < Dim; i++) {
      ans += (double(point1[i] - point2[i])) * (double(point1[i] - point2[i]));
    }
    return ans;
}



template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return neighborHelper(query, 0, root)->point;

}

template <typename RandIter, typename Comparator>
RandIter partitionHelp(RandIter left, RandIter right, RandIter pivotIndex, Comparator cmp)
{
    auto pivotValue = *pivotIndex;
    std::iter_swap(pivotIndex, right); 
    RandIter storeIndex = left;
    for(auto it = left; it <= right - 1; it++) {
      if(cmp(*it, pivotValue)) {
        std::iter_swap(storeIndex, it);
        storeIndex = storeIndex + 1;
      }
    }
    std::iter_swap(right, storeIndex);
    return storeIndex;
}

template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp)
{
    /**
     * @todo Implement this function!
     */    
    RandIter right = end - 1; // end is 1 past last element, so right is end - 1
    
    while(start < right) {
      RandIter pivotIndex = start + std::floor(rand() % (right - start + 1));
      pivotIndex = partitionHelp(start, right, pivotIndex, cmp);
      if(k == pivotIndex) {
        return;
      } else if(cmp(*k, *pivotIndex)) {
        right = pivotIndex - 1;
      } else {
        start = pivotIndex + 1;
      }
    }

    
}

