// InterPlanetary File System (IPFS).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include "Menu.h"
#include "BTrees.h"
using std::cout;
using std::cin;
int main() {
	Menu menu;
	menu.mainController();
	//BTree tree(5);
	//std::string arr[] = { "1", "2", "3" , "12", "10", "11", "14", "13", "13" };
	//std::string path = "ahmed";
	//for (int i = 0; i < 9; i++)
	//{
	//	std::cout << "Inserting " << arr[i] << "....\n";
	//	BigInt a(arr[i]);
	//	tree.insert(path + arr[i] + arr[i > 0 ? i - 1 : i + 1],a);
	//	tree.display();
	//	std::cout << std::endl;
	//}
	//BigInt t("11");
	//tree.search(t, path);
	//
	//std::cout << (tree.remove(t)) ? "TRUE" : "FALSE";
	//std::cout << path;
	//tree.display();

	//return 0 ;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
