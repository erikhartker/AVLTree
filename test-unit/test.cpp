#include "../src/main.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("BST Insert", "[flag]"){

    AVLTree tree;   // Create a Tree object
    tree.insert(10, "10");
    tree.insert(4, "4");
    tree.insert(12, "12");
    tree.insert(11, "11");
    tree.insert(7, "7");
    tree.insert(3, "3");
    tree.insert(5, "5");
    tree.insert(8, "8");
    tree.insert(1, "1");
    tree.insert(6, "6");
    tree.removeInorder(7);
    tree.printInorder(tree.root);
    tree.printPreorder(tree.root);
    tree.printPostorder(tree.root);
    tree.printLevelCount();



	REQUIRE(1 == 1);
}