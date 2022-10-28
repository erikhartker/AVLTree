#include "AVLTree.h"
#include <iostream>
using namespace std;
#pragma once

AVLTree::TreeNode* AVLTree::insert(int ID, string IDName) {
    if (root == nullptr){
        root = new TreeNode(ID,IDName,0);
        cout << "successful" << endl;
    }
    else {
        root = insertRecursive(root, ID, IDName, root->height);
    }
    return root;
}

AVLTree::TreeNode *AVLTree::insertRecursive(TreeNode *root, int ID, string IDName, int height) {
    if (root == nullptr){
        height = 0;
        cout << "successful" << endl;
        return new TreeNode(ID,IDName, height);
    }
    if (ID < root->value){
        root->left = insertRecursive(root->left, ID, IDName, height-1);
    }
    else if (ID > root->value){
        root->right = insertRecursive(root->right, ID, IDName, height-1);
    }
    else if (ID == root->value){
        cout << "unsuccessful" << endl;
        return root;
    }

    root->height = max(findHeight(root->left), findHeight(root->right)) + 1;
    root->balanceFactor = findHeight(root->left) - findHeight(root->right);

    if (root->balanceFactor > 1 || root->balanceFactor < -1){
        if (root->balanceFactor > 1 && root->left->balanceFactor>0){
            root = rightRotation(root);
        }
        else if (root->balanceFactor < -1 && root->right->balanceFactor < 0){
            root = leftRotation(root);
        }
        else if (root->balanceFactor < -1 && root->right->balanceFactor > 0){
            root = rightLeftRotation(root);
        }
        else if (root->balanceFactor > 1 && root->left->balanceFactor < 0){
            root = leftRightRotation(root);
        }
    }
    return root;
}

AVLTree::TreeNode* AVLTree::leftRotation(TreeNode* root){
    TreeNode* grandchild = root->right->left;
    TreeNode* newParent = root->right;
    newParent->left = root;
    root->right = grandchild;

    root->height = max(findHeight(root->left), findHeight(root->right)) + 1;
    newParent->height = max(findHeight(newParent->left), findHeight(newParent->right)) + 1;

    return newParent;
}

AVLTree::TreeNode* AVLTree::rightRotation(TreeNode* root) {
    TreeNode* grandchild = root->left->right;
    TreeNode* newParent = root->left;
    newParent->right = root;
    root->left = grandchild;

    root->height = max(findHeight(root->left), findHeight(root->right)) + 1;
    newParent->height = max(findHeight(newParent->left), findHeight(newParent->right)) + 1;

    return newParent;
}

AVLTree::TreeNode* AVLTree::leftRightRotation(TreeNode *root) {
    root->left = leftRotation(root->left);
    return rightRotation(root);
}

AVLTree::TreeNode* AVLTree::rightLeftRotation(TreeNode *root) {
    root->right = rightRotation(root->right);
    return leftRotation(root);
}

void AVLTree::remove(int ID) {
    TreeNode* node = searchIDHelper(root, ID);
    if (node == nullptr){
        cout << "unsuccessful" << endl;
    }
    else if (node->right == nullptr && node->left == nullptr){
        TreeNode* parentNode = searchParentIDHelper(root, ID);
        if (parentNode == nullptr){

        }
        else {
            if (parentNode->left != nullptr){
                if (parentNode->left->value == ID) {
                    parentNode->left = nullptr;
                }
            }
            else if (parentNode->right != nullptr){
                if (parentNode->right->value == ID) {
                    parentNode->right = nullptr;
                }
            }
            node->left = node;
            node->right = node;
            delete node;
            cout << "successful" << endl;
        }
    }
    else if (node->left != nullptr && node->right == nullptr){
        node->value = node->left->value;
        node->name = node->left->name;
        TreeNode* tempNode = node->left;
        node->left = node->left->left;
        node->right = node->left->right;
        tempNode->left = tempNode;
        tempNode->right = tempNode;
        delete tempNode;
        cout << "successful" << endl;
    }
    else {
        if (node->right->left == nullptr){
            node->value = node->right->value;
            node->name = node->right->name;
            TreeNode* tempNode = node->right;
            node->right = node->right->right;
            tempNode->right = tempNode;
            tempNode->left = tempNode;
            delete tempNode;
            cout << "successful" << endl;
        }
        else {
            TreeNode* repParent = removeHelper(node->right);
            node->value = repParent->left->value;
            node->name = repParent->left->name;
            TreeNode* tempNode = repParent->left;
            repParent->left = repParent->left->right;
            tempNode->right = tempNode;
            tempNode->left = tempNode;
            delete tempNode;
            cout << "successful" << endl;
        }
    }
}

AVLTree::TreeNode* AVLTree::removeHelper(TreeNode *node) {
    if (node->left->left != nullptr){
        removeHelper(node->left);
    }
    return node;
}

void AVLTree::printInorder(TreeNode* node) {
    if (node->left != nullptr){
        printInorder(node->left);
    }
    cout << node->name << ", ";
    if (node->right != nullptr){
        printInorder(node->right);
    }
}

void AVLTree::printPreorder(TreeNode *node) {
    cout << node->name << ", ";
    if (node->left != nullptr){
        printPreorder(node->left);
    }
    if (node->right != nullptr){
        printPreorder(node->right);
    }
}

void AVLTree::printPostorder(TreeNode *node) {
    if (node->left != nullptr){
        printPostorder(node->left);
    }
    if (node->right != nullptr){
        printPostorder(node->right);
    }
    cout << node->name << ", ";
}

void AVLTree::printLevelCount() {
    if (root == nullptr){
        cout << 0;
    }
    else {
        cout << root->height+1 << endl;
    }
}

AVLTree::TreeNode* AVLTree::searchID(int ID) {
    TreeNode* node = searchIDHelper(root, ID);
    if (node == nullptr){
        cout << "unsuccessful" << endl;
    }
    else {
        cout << node->name << endl;
    }
}

AVLTree::TreeNode* AVLTree::searchIDHelper(TreeNode *node, int ID) {
    if (node == nullptr){
        return nullptr;
    }
    if (ID == node->value){
        return node;
    }
    else if (ID < node->value){
        return searchIDHelper(node->left, ID);
    }
    else if (ID > node->value){
        return searchIDHelper(node->right, ID);
    }
}

int AVLTree::findHeight(TreeNode* root){
    if (root == nullptr){
        return -1;
    }
    else {
        return root->height;
    }
}

void AVLTree::removeInorder(int num) {
    removeInorderHelper(root, num, 0);
}

int AVLTree::removeInorderHelper(TreeNode *root, int num, int count) {
    if (root->left != nullptr){
        count = removeInorderHelper(root->left, num, count);
    }
    count += 1;
    if (count-1 == num){
        remove(root->value);
        return count;
    }
    if (root->right != nullptr && count < num + 1){
        count = removeInorderHelper(root->right, num, count);
    }
    return count;
}

AVLTree::TreeNode* AVLTree::searchParentIDHelper(TreeNode *node, int ID) {
    if (node == nullptr){
        return nullptr;
    }
    if (ID == node->value){
        return node;
    }
    if (node->left == nullptr && node->right == nullptr){
        return nullptr;
    }
    if (node->right != nullptr){
        if (ID == node->right->value){
            return node;
        }
        else if (ID > node->right->value){
            return searchParentIDHelper(node->right, ID);
        }
        else if (ID < node->right->value && ID > node->value){
            return searchParentIDHelper(node->right, ID);
        }
    }
    if (node->left != nullptr){
        if (ID == node->left->value){
            return node;
        }
        else if (ID < node->left->value){
            return searchParentIDHelper(node->left, ID);
        }
        else if (ID > node->left->value && ID < node->value){
            return searchParentIDHelper(node->left, ID);
        }
    }
    return nullptr;
}