/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <queue>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t;
    t = t->right;
    temp->right = t->left;
    t->left = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t;
    t = t->left;
    temp->left = t->right;
    t->right = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
int AVLTree<K, V>::getHeight(Node* subtree) {
    if(subtree == NULL) {
        return -1;
    } else {
        return 1 + std::max(getHeight(subtree->left), getHeight(subtree->right));
    }
} 

template <class K, class V>
void AVLTree<K, V>::updateHeight(Node* subtree) {
    if(subtree == NULL) {
        return;
    }
    std::queue<Node*> q;
    q.push(subtree);
    while(!q.empty()) {
        Node* cur = q.front();
        q.pop();
        int curHeight = getHeight(cur);
        if(cur->height != curHeight) {
            cur->height = curHeight;
        }
        
        if (cur->left) {
            q.push(cur->left);
        }
        if (cur->right) {
            q.push(cur->right);
        }
    }
} 



template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree == NULL) {
        return;
    }

    int balance = 0;

    if (subtree->right && subtree->left) {
        balance = subtree->right->height - subtree->left->height;
    } else if (subtree->right) {
        balance = subtree->right->height + 1;
    } else if (subtree->left) {
        balance = -subtree->left->height - 1;
    }

    if(balance == -2) {
        int l_balance = 0;
        if(subtree->left->right && subtree->left->left) {
            l_balance = subtree->left->right->height - subtree->left->left->height;
        } else if(subtree->left->right) {
            l_balance = subtree->left->right->height + 1;
        } else if(subtree->left->left){
            l_balance = -subtree->left->left->height - 1;
        }
        if(l_balance == -1) {
            rotateRight(subtree);
        } else {
            rotateLeftRight(subtree);
        }
    } else if (balance == 2) {

        int r_balance = 0;
        if(subtree->right->right && subtree->right->left) {
            r_balance = subtree->right->right->height - subtree->right->left->height;
        } else if(subtree->right->right) {
            r_balance = subtree->right->right->height + 1;
        } else if(subtree->right->left){
            r_balance = -subtree->right->left->height - 1;
        }
        if(r_balance == 1) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
    }

    // update height
    updateHeight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL) {
        subtree = new Node(key, value);
    } else if (key < subtree->key) {
        insert(subtree->left, key, value);
    } else if (key > subtree->key) {
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        Node* temp = subtree;
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete(temp);
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* IOP = subtree->left; // Find IOP
            while(IOP->right) {
                IOP = IOP->right;
            }
            swap(subtree, IOP);
            remove(subtree->left, IOP->key);
        } else {
            /* one-child remove */
            // your code here
            if(subtree->left == NULL) {
                subtree = subtree->right;
            } else {
                subtree = subtree->left;
            }
            delete(temp);
        }
        // your code here
    }
    updateHeight(subtree);
    rebalance(subtree);
}
