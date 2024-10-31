/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "nim_learner.h"
#include <ctime>
#include <iostream>
#include <string>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */

    // Insert all vertices
    for(size_t i = 0; i <= startingTokens; i++) {
      Vertex p1 = "p1-" + std::to_string(i);
      Vertex p2 = "p2-" + std::to_string(i);
      g_.insertVertex(p1);
      g_.insertVertex(p2);
    }

    // Insert all edges
    for(int i = startingTokens; i >= 0; i--) {
      for(int j = i - 1; j >= i - 2 ; j--) {
        if(j >= 0) {
            g_.insertEdge("p1-" + std::to_string(i), "p2-" + std::to_string(j));
            g_.setEdgeWeight("p1-" + std::to_string(i), "p2-" + std::to_string(j), 0);
            g_.insertEdge("p2-" + std::to_string(i), "p1-" + std::to_string(j));
            g_.setEdgeWeight("p2-" + std::to_string(i), "p1-" + std::to_string(j), 0);
        }
      }
    }

    startingVertex_ = "p1-" + std::to_string(startingTokens);

}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
  /* Your code goes here! */
  int choice = rand() % 2; // Number in range 0-1
  Vertex curVert = startingVertex_;
  vector<Vertex> posNextVert = g_.getAdjacent(curVert);
  Vertex nextVert;
  if(posNextVert.size() > 1) {
  nextVert = posNextVert[choice];
  }


  while(posNextVert.size() > 1) { 
  path.push_back(Edge(curVert, nextVert));
  choice = rand() % 2;
  curVert = nextVert;
  posNextVert = g_.getAdjacent(curVert);
  if(posNextVert.size() > 1) {
    nextVert = posNextVert[choice];
  }
  }

  if(posNextVert.size() == 1) {
  path.push_back(Edge(curVert, posNextVert[0]));
  }

  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 int p1weights = 0;
 int p2weights = 0;
 
 if(path[path.size() - 1].dest.substr(0, 2) == "p2") {
  p1weights = 1;
  p2weights = -1;
 } else{
  p1weights = -1;
  p2weights = 1;
 }

 for(size_t i = 0; i < path.size(); i++) {
  if(path[i].source.substr(0, 2) == "p1") {
    g_.setEdgeWeight(path[i].source, path[i].dest, g_.getEdgeWeight(path[i].source, path[i].dest) + p1weights);
  } else if(path[i].source.substr(0, 2) == "p2") {
    g_.setEdgeWeight(path[i].source, path[i].dest, g_.getEdgeWeight(path[i].source, path[i].dest) + p2weights);
  }
 }

}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
