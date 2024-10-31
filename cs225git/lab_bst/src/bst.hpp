/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <algorithm>

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    Node* & answer = find(root, key);
    return answer->value;
    
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here

    if(subtree == NULL) {
        return subtree;
    }

    if(key < subtree->key) {
        return find(subtree->left, key);
    } else if(key > subtree->key) {
        return find(subtree->right, key);
    } else {
        return subtree;
    }
    
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    insert(root, key, value);
    return;
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    Node*& answer = find(subtree, key);

    if(answer == NULL) {
        answer = new Node(key, value);
    }

    return;
    
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    if(first != NULL && second != NULL) {
        K fkey = first->key;
        V fvalue = first->value;
        first->key = second->key;
        first->value = second->value;
        second->key = fkey;
        second->value = fvalue;
    }
    return;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    remove(root, key);
    return;
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    //your code here
    Node*& node = find(subtree, key);

    if(node) {
        if(node->left == NULL && node->right == NULL) {
            delete(node);
            node = NULL;
        } else if (node->left == NULL && node->right != NULL) {
            Node* temp = node;
            node = node->right;
            delete(temp);
        } else if (node->left != NULL && node->right == NULL) {
            Node* temp = node;
            node = node->left;
            delete(temp);
        } else{
            Node* IOP = node->right; // Find IOP
            while(IOP->left) {
                IOP = IOP->left;
            }
            swap(node, IOP);
            remove(node->right, IOP->key);
        }
    }

    return;

}


template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V> bst;
    for(auto it = inList.begin(); it != inList.end(); it++) {
        bst.insert((*it).first, (*it).second);
    }
    return bst;
}

template <class K, class V>
int BST<K, V>::getHeight(Node* root) {
    if(root == NULL) {
        return -1;
    } else {
        return 1 + std::max(getHeight(root->left), getHeight(root->right));
    }
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::vector<int> ans;
    int maxHeight = 0;
    std::sort(inList.begin(), inList.end());

    do {
        BST<K, V> bst = listBuild(inList);
        int height = bst.getHeight(bst.getRoot());
        if(height > maxHeight) {
            maxHeight = height;
        }
        ans.resize(maxHeight + 1, 0);
        ans[height] = ans[height] + 1;
    }
    while(next_permutation(inList.begin(), inList.end()));

    return ans;


};