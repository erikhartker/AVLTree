//
// Created by Erik Hartker on 9/28/22.
//
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#pragma once
class AVLTree{
public:
    //struct of a node class for each individual node in the larger tree
    struct TreeNode{
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
        int value = 0;
        string name = "";
        int height = 0;
        int balanceFactor = 0;
        TreeNode(int val, string IDName, int nodeHeight) : value(val), name(IDName), height(nodeHeight), left(nullptr), right(nullptr), balanceFactor(0){}
    };

    //the 9 public functions as well as the destructor
    TreeNode* insert(int ID, string IDName);
    void searchName(string name);
    void remove(int ID);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void removeInorder(int num);
    TreeNode* searchID(int ID);
    ~AVLTree();

private:
    //all helper functions, as well as the root attribute
    void destructorHelper(TreeNode* node);
    void printPreorderHelper(TreeNode* node, vector<string>& names);
    void printPostorderHelper(TreeNode* node, vector<string>& names);
    void printInorderHelper(TreeNode* node, vector<string>& names);
    TreeNode* root = nullptr;
    TreeNode* searchIDHelper(TreeNode* node, int ID);
    void searchNameHelper(TreeNode* node, string name, vector<int>& idList);
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

