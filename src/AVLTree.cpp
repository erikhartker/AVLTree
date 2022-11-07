#include "AVLTree.h"
#include <iostream>
using namespace std;


//main insert function which calls a recursive helper to iterate through the tree
AVLTree::TreeNode* AVLTree::insert(int ID, string IDName) {
    //if else accounting for the edge case where the root is null
    if (root == nullptr){
        root = new TreeNode(ID,IDName,0);
        cout << "successful" << endl;
    }
    else {
        root = insertRecursive(root, ID, IDName, root->height);
    }
    return root;
}

//recursive helper method for insertion
AVLTree::TreeNode *AVLTree::insertRecursive(TreeNode *root, int ID, string IDName, int height) {

    //base condition, creates a new node and sets its height to zero
    if (root == nullptr){
        height = 0;
        cout << "successful" << endl;
        return new TreeNode(ID,IDName, height);
    }

    //if statements navigate through the tree by ID
    if (ID < root->value){
        root->left = insertRecursive(root->left, ID, IDName, height-1);
    }
    else if (ID > root->value){
        root->right = insertRecursive(root->right, ID, IDName, height-1);
    }

    //if ID is already in tree, operation ceases
    else if (ID == root->value){
        cout << "unsuccessful" << endl;
        return root;
    }

    //after insertion, the height of the node is calculated by adding one to the max of the subtree height
    root->height = max(findHeight(root->left), findHeight(root->right)) + 1;

    //balance factor is found by subtracting subtrees
    root->balanceFactor = findHeight(root->left) - findHeight(root->right);

    //rotations are called according to balance factor via helper functions
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

//rotation is performed in right-right case by reassigning nodes
AVLTree::TreeNode* AVLTree::leftRotation(TreeNode* root){
    TreeNode* grandchild = root->right->left;
    TreeNode* newParent = root->right;
    newParent->left = root;
    root->right = grandchild;

    //height of the original parent found by taking max of its new left and right subtrees
    root->height = max(findHeight(root->left), findHeight(root->right)) + 1;

    //height of the new parent found the same way
    //able to do this because subtree heights themselves don't change, although they may be reassigned.
    newParent->height = max(findHeight(newParent->left), findHeight(newParent->right)) + 1;

    return newParent;
}

//rotation is performed in left-left case by reassigning nodes
AVLTree::TreeNode* AVLTree::rightRotation(TreeNode* root) {
    TreeNode* grandchild = root->left->right;
    TreeNode* newParent = root->left;
    newParent->right = root;
    root->left = grandchild;

    root->height = max(findHeight(root->left), findHeight(root->right)) + 1;
    newParent->height = max(findHeight(newParent->left), findHeight(newParent->right)) + 1;

    return newParent;
}

//rotation is performed in left-right case by making use of previously defined left and right rotation functions
AVLTree::TreeNode* AVLTree::leftRightRotation(TreeNode *root) {
    root->left = leftRotation(root->left);
    return rightRotation(root);
}

//rotation is performed in right-left case by making use of previously defined left and right rotation functions
AVLTree::TreeNode* AVLTree::rightLeftRotation(TreeNode *root) {
    root->right = rightRotation(root->right);
    return leftRotation(root);
}

//function removes a node from the tree
void AVLTree::remove(int ID) {
    //finds the node in tree and returns reference
    TreeNode* node = searchIDHelper(root, ID);
    //accounts for node not in tree
    if (node == nullptr){
        cout << "unsuccessful" << endl;
    }
    //accounts for no children
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
            if (parentNode->right != nullptr){
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
    //accounts for left child only
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
    //in order successor
    else {
        //accounts for no left child from the right child of the node to be removed
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

//finds in order successor
AVLTree::TreeNode* AVLTree::removeHelper(TreeNode *node) {
    if (node->left->left != nullptr){
        removeHelper(node->left);
    }
    return node;
}

//prints in order by storing names in a vector and calling a recursive helper function
void AVLTree::printInorder() {
    vector<string> names;
    printInorderHelper(root, names);
    if (names.empty()){
    }
    else {
        for (int i = 0; i < names.size()-1; i++){
            cout << names[i] << ", ";
        }
        cout << names[names.size()-1] << endl;
    }
}

void AVLTree::printInorderHelper(TreeNode* node, vector<string>& names) {
    if (node->left != nullptr){
        printInorderHelper(node->left, names);
    }
    names.push_back(node->name);;
    if (node->right != nullptr){
        printInorderHelper(node->right, names);
    }
}

//prints pre order by storing names in a vector and calling a recursive helper function
void AVLTree::printPreorder() {
    vector<string> names;
    printPreorderHelper(root, names);
    if (names.empty()){
    }
    else {
        for (int i = 0; i < names.size()-1; i++){
            cout << names[i] << ", ";
        }
        cout << names[names.size()-1] << endl;
    }
}

void AVLTree::printPreorderHelper(TreeNode *node, vector<string>& names) {
    names.push_back(node->name);
    if (node->left != nullptr){
        printPreorderHelper(node->left, names);
    }
    if (node->right != nullptr){
        printPreorderHelper(node->right, names);
    }
}

//prints post order by storing names in a vector and calling a recursive helper function
void AVLTree::printPostorder() {
    vector<string> names;
    printPostorderHelper(root, names);
    if (names.empty()){
    }
    else {
        for (int i = 0; i < names.size()-1; i++){
            cout << names[i] << ", ";
        }
        cout << names[names.size()-1] << endl;
    }
}

void AVLTree::printPostorderHelper(TreeNode *node, vector<string>& names) {
    if (node->left != nullptr){
        printPostorderHelper(node->left, names);
    }
    if (node->right != nullptr){
        printPostorderHelper(node->right, names);
    }
    names.push_back(node->name);
}

//prints the level count by using the root's height
void AVLTree::printLevelCount() {
    if (root == nullptr){
        cout << 0 << endl;
    }
    else {
        cout << root->height+1 << endl;
    }
}

//searches for name using an ID by calling a recursive helper function
AVLTree::TreeNode* AVLTree::searchID(int ID) {
    TreeNode* node = searchIDHelper(root, ID);
    if (node == nullptr){
        cout << "unsuccessful" << endl;
    }
    else {
        cout << node->name << endl;
    }
}

//uses a form of preorder to find the desired node
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

//helper function for height which accounts for a nullptr root
int AVLTree::findHeight(TreeNode* root){
    if (root == nullptr){
        return -1;
    }
    else {
        return root->height;
    }
}

//removes the nth node from the inorder traversal by calling a helper function
void AVLTree::removeInorder(int num) {
    int count = removeInorderHelper(root, num, 0);
    if (num >= count){
        cout << "unsuccessful" << endl;
    }
    else {
    }
}

//makes use of recursion as well as the previously defined remove function to find and remove a node from the traversal
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

//similar to searchIDHelper except returns the parent node so deletion can be mae easier in remove()
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

//given a name, finds all corresponding IDs and prints them through use of a recursive helper function
void AVLTree::searchName(string name) {
    if (root == nullptr){
        cout << "unsuccessful" << endl;
        return;
    }
    vector<int> idList;
    searchNameHelper(root, name, idList);
    if (idList.empty()){
        cout << "unsuccessful" << endl;
    }
    else {
        for (int i = 0; i < idList.size()-1; i++){
            cout << idList[i] << endl;
        }
        cout << idList[idList.size()-1] << endl;
    }
}

//uses a form of pre order traversal to push IDs onto a vector for printing
void AVLTree::searchNameHelper(TreeNode *node, string name, vector<int>& idList) {
    if (node->name.compare(name) == 0){
        idList.push_back(node->value);
    }
    if (node->left != nullptr){
        searchNameHelper(node->left, name, idList);
    }
    if (node->right != nullptr){
        searchNameHelper(node->right, name, idList);
    }
}

//recursively deletes all nodes using postorder traversal
void AVLTree::destructorHelper(TreeNode *node) {
    if (root == nullptr){
        return;
    }
    if (node->left != nullptr){
        if (node->left->left != nullptr || node->left->right != nullptr){
            destructorHelper(node->left);
        }
    }
    if (node->right != nullptr){
        if (node->right->right != nullptr || node->right->left != nullptr){
            destructorHelper(node->right);
        }
    }
    if (node->left != nullptr){
        TreeNode* tempNode = node->left;
        node->left = nullptr;
        tempNode->left = tempNode;
        tempNode->right = tempNode;
        delete tempNode;
    }
    if (node->right != nullptr){
        TreeNode* tempNode = node->right;
        node->right = nullptr;
        tempNode->right = tempNode;
        tempNode->left = tempNode;
        delete tempNode;
    }
}

//calls destructor helper function and deletes the root to prevent memory leaks
AVLTree::~AVLTree(){
    destructorHelper(root);
    delete root;
}