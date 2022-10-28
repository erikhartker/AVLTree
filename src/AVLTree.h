//
// Created by Erik Hartker on 9/28/22.
//
#include <string>
#include <iostream>
using namespace std;

#pragma once
class AVLTree{
public:
    struct TreeNode{
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
        int value = 0;
        string name = "";
        int height = 0;
        int balanceFactor = 0;
        TreeNode(int val, string IDName, int nodeHeight) : value(val), name(IDName), height(nodeHeight), left(nullptr), right(nullptr), balanceFactor(0){}
    };
    TreeNode* root = nullptr;
    TreeNode* insert(int ID, string IDName);
    void remove(int ID);
    void printInorder(TreeNode* node);
    void printPreorder(TreeNode* node);
    void printPostorder(TreeNode* node);
    void printLevelCount();
    void removeInorder(int num);
    TreeNode* searchID(int ID);

private:
    TreeNode* searchIDHelper(TreeNode* node, int ID);
    TreeNode* insertRecursive(TreeNode* root, int ID, string IDName, int height);
    TreeNode* leftRotation(TreeNode* root);
    TreeNode* rightRotation (TreeNode* root);
    TreeNode* leftRightRotation (TreeNode* root);
    TreeNode* rightLeftRotation (TreeNode* root);
    TreeNode* removeHelper(TreeNode* node);
    int findHeight(TreeNode* root);
    int removeInorderHelper(TreeNode* root, int num, int count);
    TreeNode* searchParentIDHelper(TreeNode* node, int ID);
};

