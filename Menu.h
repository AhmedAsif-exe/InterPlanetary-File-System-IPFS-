#pragma once
#include<iostream>
#include"DHT.h"
using std::cout;
using std::cin;
using std::string;
class Menu {
private:
	DHT dh;
	void AddMachine() {
		dh.addMachine();
	}

	void DeleteMachine() {
		string id;
		cout << "Enter machine Id: ";
		cin >> id;
		dh.deleteMachine(id);
	}

	void printmachineWithTable() {
		dh.PrintAllMachinesWithRoutingTalbes();
	}

	void SpecificTable() {
		string id;
		cout << "Enter machine Id: ";
		cin >> id;
		dh.printRoutingTable(id);
	}

	void PrintBTree() {

	}

	void AddFile() {

	}

	void deleteFile() {

	}

	void openAFile() {

	}
public:
	void mainController() {
		int choice = 1;
		while (choice != 0)
		{
			cout << "\n\n\n\t\t\t\t\"Menu\"\n";
			cout << "\t1.Add new machine\n";
			cout << "\t2.Add delete machine\n";
			cout << "\t3.Print All machines with routing Tables\n";
			cout << "\t4.Print routing Tables of a specific machine\n";
			cout << "\t5.Print B Tree of a specific machine\n";
			cout << "\t6.Add file to the system\n";
			cout << "\t7.Delete a file from system\n";
			cout << "\t8.Open a specific file\n";
			cout << "\t0.Exit the system\n";
			cin >> choice;
			while (choice < 0 || choice > 8)
			{
				cout << "Enter a valid Choice\n";
			}
			if (choice == 1) {
				this->AddMachine();
			}
			else if (choice == 2) {
				this->DeleteMachine();
			}
			else if (choice == 3) {
				this->printmachineWithTable();
			}
			else if (choice == 4) {
				this->SpecificTable();
			}
			else if (choice == 5) {
				this->PrintBTree();
			}
			else if (choice == 6) {
				this->AddFile();
			}
			else if (choice == 7) {
				this->deleteFile();
			}
			else if (choice == 8) {
				this->openAFile();
			}
			char ch;
			cout << "\n\t\tEnter any key to continue\n";
			cin >> ch;
		}

	}

};