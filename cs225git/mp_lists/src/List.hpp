/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

#include <cmath>

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  ListNode* pos = nullptr;
  if(head_ != NULL) {
    pos = head_;
  }
  return List<T>::ListIterator(pos, tail_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  ListNode* pos = nullptr;
  if(tail_ != NULL) {
    pos = tail_->next;
  }
  return List<T>::ListIterator(pos, tail_);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
     ListNode *current = head_;
     while(current != NULL) {
       ListNode *temp = current;
       current = current->next;
       delete(temp);
     }

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  } else {
    tail_ = newNode;
  }
  head_ = newNode;
  
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode->prev = tail_;
  newNode->next = NULL;

  if(tail_ != NULL) {
    tail_->next = newNode;
  } else {
    head_ = newNode;
  }
  tail_ = newNode;

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1

  if (start == NULL || splitPoint <= 0) {
    return start;
  }

  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if(curr == NULL) {
    return NULL;
  }

  if (curr->prev != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  ListNode * curr = head_;
  int counter = 1;
  while(curr != NULL && curr != tail_) {
    if(counter % 2 == 0) {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        tail_->next = curr;
        curr->prev = tail_;
        tail_ = curr;
        ListNode* temp = curr;
        curr = curr->next;
        temp->next = NULL;
    } else {
       curr = curr->next;
    }
    counter++;
  }

}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in mp_lists part 2
  ListNode * nodestart = startPoint;

  if(startPoint == endPoint) {
    return;
  }

  while(startPoint != NULL && startPoint != endPoint) {
    ListNode * temp = startPoint->next;
    startPoint->next = startPoint->prev;
    startPoint->prev = temp;
    startPoint = temp;
  }

  ListNode * nodeend = endPoint->next;

  if(nodestart != NULL && nodestart->next != NULL) {
     nodestart->next->next = endPoint;
   }

  if(nodeend != NULL) {
   nodeend->prev = nodestart;
  }
  endPoint->next = endPoint->prev;
  if(nodestart != NULL) {
    endPoint->prev = nodestart->next;
    nodestart->next = nodeend;
  }

  endPoint = nodestart;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in mp_lists part 2
  ListNode * nodestart = head_;
  ListNode * nodeend = head_;

  // int groups = int(std::ceil(double(length_/n)));
  int groups;
  if(length_ % n == 0) {
    groups = length_/n;
  } else {
    groups = length_/n + 1;
  }

  for(int i = 0; i < groups; i++) {
    for(int j = 0; j < n - 1; j++) {
      if(nodeend->next != NULL) {
        nodeend = nodeend->next;
      } 
    }
    reverse(nodestart, nodeend);
    if(i == 0) {
      head_ = nodestart;
    }
    // nodestart = nodestart->next;
    // nodeend = nodestart;
    nodeend = nodeend->next;
    nodestart = nodeend;
  }

  tail_ = nodeend;

  

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in mp_lists part 2
  ListNode * endpoint;
  ListNode * startpoint;
  if(second->data < first->data) {
    startpoint = second;
  } else {
    startpoint = first;
  }
  while(first != NULL && second != NULL) {
    if(second->data < first->data) {
      ListNode* temp = second->next;
      second->next = first;
      if(first->prev != NULL) {
        first->prev->next = second;
        second->prev = first->prev;
      }
      first->prev = second;
      second = temp;
    }

    if(first->next == NULL) {
      endpoint = first;
    }

    if(second != NULL && !(second->data < first->data)) {
      first = first->next;
    }
  }

  if(first == NULL && second != NULL) {
    second->prev = endpoint;
    endpoint->next = second;
  }

  return startpoint;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in mp_lists part 2
  if(chainLength == 1) {
    return start;
  }
  ListNode * second = split(start, chainLength/2);
  ListNode * A = mergesort(start, chainLength/2);
  ListNode * B =  mergesort(second, chainLength - chainLength/2);
  return merge(A, B);
}
