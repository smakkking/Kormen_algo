#ifndef CH12
#define CH12

#include <iostream>
#include "ch10.h"

// TODO: rewrite, cause not understandable, what operations needed to be in class1 or class2

template <class key_type>
class BinaryNode
{
public:
    BinaryNode *parent, *left, *right;
    key_type key;

    BinaryNode(BinaryNode<key_type> *par, BinaryNode<key_type> *l, BinaryNode *r, key_type _key) {
        parent = par;
        left = l;
        right = r;
        key = key;
        data = _item;
    }
    friend void inorder_tree_walk(BinaryNode<key_type> *x) {
        // здесь представлена сама идея обхода, а так с ключами и объектами можно делать что угодно
        if (x != NULL) {
            inorder_tree_walk(x->left);
            std::cout << x->key;
            inorder_tree_walk(x->right);
        }
    }
    friend void preorder_tree_walk(BinaryNode<key_type> *x) {
        // здесь представлена сама идея обхода, а так с ключами и объектами можно делать что угодно
        if (x != NULL) {
            std::cout << x->key;
            inorder_tree_walk(x->left);
            inorder_tree_walk(x->right);
        }
    }
    friend void postorder_tree_walk(BinaryNode<key_type> *x) {
        // здесь представлена сама идея обхода, а так с ключами и объектами можно делать что угодно
        if (x != NULL) {
            inorder_tree_walk(x->left);
            inorder_tree_walk(x->right);
            std::cout << x->key;
        }
    }    
    friend void subtree_output(BinaryNode<key_type> *root, BinaryNode<key_type> *current) {
        bool forward = true;
        
        while (current != root) {
            if (current->right != NULL && forward) {
                current = current->right;
            } else if (current->left != NULL && forward) {
                current = current->left;
            } else {
                forward = false;
            }

            if (!forward) {
                cout << current->item;
                if (current == current->parent->right && current->parent->left) {
                    current = current->parent->left;
                    forward = true;
                } else {
                    current = current->parent;
                }
            }

        }    
    }
    int h() {
        return std::max(this->left.h(), this->right.h()) + 1;
    }
    friend BinaryNode<key_type>* search(BinaryNode<key_type> *current, key_type key_x) {
        if (current == NULL)
            return current;

        if (current->key == key_x)
            return current;
        else if (key_x > current->key)
            search(current->right, key_x);
        else
            search(current->left, key_x);
    }
    friend BinaryNode<key_type>* minimum(BinaryNode<key_type> *current) { // O(h)
        while (current->left)
            current = current->left;
        return current;
    }
    friend BinaryNode<key_type>* maximum(BinaryNode<key_type> *current) { // O(h)
        while (current->right)
            current = current->right;
        return current;
    }
    friend BinaryNode<key_type>* successor(BinaryNode<key_type> *x) { // O(h)
        // возвращает пред элемент для поданого (если формировать посл-ть узлов по центрированному поиску)
        if (x->right != NULL)
            return minimum(x->right);
        BinaryNode<key_type> *y = x->parent;
        while (y != NULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }
};

template<class key_type>
class BinaryTree
{
    BinaryNode<key_type> *root;
    // n - число листьев
    // h - высота
    //
    //
    //

public:
    BinaryTree(key_type key) {
        root = new BinaryNode<key_type>(NULL, NULL, NULL, key, data);
    }
    void inorder_tree_walk() {
        BinaryNode::inorder_tree_walk(root);
    }
    void preorder_tree_walk() {
        BinaryNode::preorder_tree_walk(root);
    }
    void postorder_tree_walk() {
        BinaryNode::postorder_tree_walk(root);
    }
    void stack_nonrecurve_inorder_tree_walk() { // O(n) 
        StackOnLinkedList<BinaryNode<key_type>*> R;
        R.push(this->root);
        while (!R.empty()) {
            BinaryNode<key_type> *tmp = R.pop();
            cout << tmp->item << " ";
            if (tmp->left)
                R.push(tmp->left);
            if (tmp->right)
                R.push(tmp->right);
        }
    }
    void nonrecurve_inorder_tree_walk() { // O(n)
        // non-recurve output all tree nodes
        cout << root->key;
        if (root->right)
            subtree_output(root, root->right);
        if (root->left)
            subtree_output(root, root->left);
    }
    int get_h() {
        return root->h();
    }
    BinaryNode<key_type>* recurve_search(key_type key_x) { // O(h)
        return BinaryNode::search(root, key_x);
    }
    BinaryNode<key_type>* tree_search(key_type key_x) {
        BinaryNode<key_type>* current = root;
        while (current != NULL && current->key != key_x) {
            if (key_x > current->key)
                current = current->right;
            else
                current = current->left;
        }
        return current;
    }

    BinaryNode<key_type>* tree_min() {
        BinaryNode::minimum(root);
    }
    BinaryNode<key_type>* tree_max() {
        BinaryNode::maximum(root);
    }

};



#endif