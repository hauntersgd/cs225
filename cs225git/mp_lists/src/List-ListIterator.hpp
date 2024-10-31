
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in mp_lists part 1
    ListNode* position_;
    ListNode* tail;

  public:
    
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x, ListNode* tail_) : position_(x), tail(tail_) { }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in mp_lists part 1
        if(position_ != NULL) {
            position_ = position_->next;
        }
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in mp_lists part 1
        //ListNode* temp = position_;
        ListIterator old = *this;
        if(position_ != NULL) {
            position_ = position_->next;
        }
        return old;
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in mp_lists part 1
        if(position_ != NULL) {
            position_ = position_->prev;
        } else {
            position_ = tail;
        }
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in mp_lists part 1
        ListIterator old = *this;
        if(position_ != NULL) {
            position_ = position_->prev;
        } else {
            position_ = tail;
        }
        return old;
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in mp_lists part 1
        return position_ != rhs.position_;
    }

    bool operator==(const ListIterator& rhs) {
        return position_ == rhs.position_;
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
