

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/
#include <iostream>
#include <sstream>
#include "AVLTree.h"
#include <regex>


int main(){

    string number;
    cin >> number;
    int numLoop = stoi(number);
    AVLTree poop;
    regex name_expr ("\"[a-zA-Z]+\"");
    regex num_expr ("[0-9]+");
    for (int i = 0; i < numLoop; i++){
        string line;
        getline(cin, line);
        istringstream read(line);
        string word;
        while(read >> line){
            read >> word;
            if (regex_match(word, regex("insert"))){
                read >> word;
                if (regex_match(word, name_expr)){
                    string inputName = word.substr(1,word.size()-2);
                    read >> word;
                    if (regex_match(word, num_expr) && word.size() == 8){
                        int insertNum = stoi(word);
                        poop.insert(insertNum, inputName);
                    }
                }
            }
        }
    }
    poop.printInorder(poop.root);
	return 0;
}


