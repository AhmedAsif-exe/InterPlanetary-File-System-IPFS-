
#ifndef MACHINE_H
#define MACHINE_H
#include<iostream>
#include"BigInt.h"
#include<cmath>
using  std::string;
using  std::cout;
using  std::endl;
class Machine_Node;

class Files {
public:
	int id;
	string name;
	string content;
	Files()
	{
		id = 0;
		name = "NotAssigned.txt";
		content = "";
	}
};

class RoutingTable_Node {
public:

	int index;
	BigInt nextMachineID;
	Machine_Node* nextMachineAddress;
	RoutingTable_Node* next;
	RoutingTable_Node* previous;

	RoutingTable_Node()
	{
		index = 0;
		nextMachineAddress = nullptr;
		next = nullptr;
		previous = nullptr;
	}

	RoutingTable_Node(int i)
	{
		index = i;
		next = nullptr;
		nextMachineAddress = nullptr;
		previous = nullptr;
	}
};

class RoutingTable {
public:
	RoutingTable_Node* Head;
	RoutingTable_Node* tail;
	int count;

	RoutingTable()
	{
		Head = nullptr;
		tail = nullptr;
		count = 1;
	}

	void AddNode()
	{
		RoutingTable_Node* newNode = new RoutingTable_Node(count);
		newNode->index = count;
		//newNode->nextMachineID = ptr->ID;
	//	newNode->nextMachineAddress = ptr;

		if (Head == nullptr) {
			Head = newNode;
			tail = newNode;
		}
		else
		{
			RoutingTable_Node* temp = Head;
			while (temp->next) {
				temp = temp->next;
			}
			newNode->next = temp->next;
			temp->next = newNode;
			newNode->previous = temp;
			tail = newNode;
		}
		count++;
	}

	void Diaplay()
	{
		RoutingTable_Node* temp = Head;
		while (temp != nullptr)
		{
			cout << "index " << temp->index << "\t";
			cout << "nextmachineid\t" << temp->nextMachineID << "\n";
			temp = temp->next;
		}
		cout << endl;
	}
};

class Machine_Node {
public:
	BigInt ID;
	Machine_Node* next;
	RoutingTable FT;
	Files* root;

	Machine_Node() {
		next = nullptr;
		root = nullptr;
	}

	Machine_Node(BigInt id, int sizeofTables) {
		ID = id;
		next = nullptr;
		root = nullptr;
		for (int i = 0; i < sizeofTables; i++) {
			FT.AddNode();
		}
	}
};

class Machine_list {
	Machine_Node* Head;
	BigInt count;
	BigInt maxid;
	int no_of_bits_used;
	int sizeofTables;

	void manageSuccessorsHelper(Machine_Node* temp) {
		int i = 1;
		RoutingTable_Node* tableTemp = temp->FT.Head;
		Machine_Node* last = Head;
		while (last->next != Head)
		{
			last = last->next;
		}
		while (tableTemp != nullptr) {

			BigInt p = temp->ID;
			BigInt calculatedId("1");
			Machine_Node* temp2 = temp->next;

			calculatedId = p + calculatedId.pow(i - 1);

			while (calculatedId > last->ID) {
				calculatedId = calculatedId - maxid;
				temp2 = Head;
			}

			while ((temp2->ID < calculatedId) && (temp2->next != temp)) {

				temp2 = temp2->next;
			}

			tableTemp->nextMachineAddress = temp2;
			tableTemp->nextMachineID = temp2->ID;
			tableTemp = tableTemp->next;
			i++;

		}
		temp = temp->next;
	}
	void mangesuccessors() {
		Machine_Node* temp = Head;

		while (temp->next != Head) {
			manageSuccessorsHelper(temp);
			temp = temp->next;
		}
		if (temp->next == Head) {
			manageSuccessorsHelper(temp);
		}
	}
public:

	Machine_list() {
		Head = nullptr;
		sizeofTables = 0;
		no_of_bits_used = 0;
	}

	void SetMaxId(BigInt max) {
		maxid = max;
	}

	Machine_list(int total, int used)
	{
		Head = nullptr;
		no_of_bits_used = used;
	}

	bool AddMachine(BigInt ID) {
		Machine_Node* newNode = new Machine_Node(ID, sizeofTables);

		if (!Head) {
			Head = newNode;
			Head->next = Head;
		}
		else {
			if (newNode->ID < Head->ID) {
				Machine_Node* last = Head;
				while (last->next != Head) {
					last = last->next;
				}
				if (last->ID == newNode->ID)
					return false;
				last->next = newNode;
				newNode->next = Head;
				Head = newNode;
			}
			else if (newNode->ID > Head->ID) {
				Machine_Node* current = Head;
				while (current->next != Head && current->next->ID < newNode->ID)
				{
					current = current->next;
				}
				if (current->next->ID == newNode->ID)
					return false;
				newNode->next = current->next;
				current->next = newNode;
			}
			else {
				return false;
			}
		}
		++count;
		mangesuccessors();
		return true;
	}

	bool deleteMachine(BigInt ID) {

		if (Head == nullptr) {
			return false;
		}

		Machine_Node* temp = Head;
		Machine_Node* prev = nullptr;
		bool status = false;
		if (Head->ID == ID) {
			// if head to be deleted and only one node
			if (Head->next == Head) {
				delete Head;
				Head = nullptr;
				status = true;
			}
			else {
				prev = Head;
				while (prev->next != Head) {
					prev = prev->next;
				}
				prev->next = Head->next;
				Head = Head->next;
				delete temp;
				status = true;
			}
		}
		else {
			while (temp->next != Head && temp->ID != ID) {
				prev = temp;
				temp = temp->next;
			}
			if (temp->ID == ID) {
				prev->next = temp->next;
				delete temp;
				status = true;
			}
		}
		if (status) {
			mangesuccessors();
		}
		return status;
	}

	void setSizeofTables(int n) {
		sizeofTables = n;
	}

	void PrintAllRoutingTables()
	{
		Machine_Node* temp = Head;
		cout << temp->ID << "\n";
		temp->FT.Diaplay();
		temp = temp->next;
		while (temp != Head)
		{
			cout << temp->ID << "\n";
			temp->FT.Diaplay();
			temp = temp->next;
		}
	}

	void printMachineList() {
		if (Head == nullptr) {
			cout << "sorry but there is no machine in system\n";
		}
		else {
			Machine_Node* temp = Head;
			while (temp->next != Head) {
				cout << temp->ID << " ";
				temp = temp->next;
			}
			cout << temp->ID << "\n";
		}
	}

	void PrintRoutingTable(BigInt Id) {
		if (Head->ID == Id) {
			cout << "Machin Id: " << Head->ID << endl;
			cout << "Routing Table\n";
			Head->FT.Diaplay();
		}
		else {
			Machine_Node* temp = Head->next;
			while (temp->next != Head)
			{
				if (temp->ID == Id) {
					cout << "Machin Id: " << Head->ID << endl;
					cout << "Routing Table\n";
					Head->FT.Diaplay();
					return;
				}
				temp = temp->next;
			}
			cout << "We are Relly sorry but no such machine with this Id exist\n";
		}
	}
};

#endif 