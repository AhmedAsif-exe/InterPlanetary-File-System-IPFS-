
#ifndef MACHINE_H
#define MACHINE_H
#include<iostream>
#include"BigInt.h"
#include"FileHandling.h"
#include"BTrees.h"
#include<cmath>
using  std::string;
using  std::cout;
using  std::endl;
class Machine_Node;

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
	~RoutingTable() {
		RoutingTable_Node* temp = Head;
		while (temp != nullptr) {
			Head = Head->next;
			delete temp;
			temp = Head;
		}
	}
};

struct Machine_Node {
	BigInt ID;
	Machine_Node* next;
	RoutingTable FT;
	BTree* btree;
	BigInt fileCount;
	Machine_Node(BigInt id, int sizeofTables, int sizeofBtree) {
		ID = id;
		next = nullptr;
		for (int i = 0; i < sizeofTables; i++) {
			FT.AddNode();
		}
		createDirectory(id.getData());
		btree = new BTree(sizeofBtree);
	}
	~Machine_Node() {

	}
};

class Machine_list {
	Machine_Node* Head;
	Machine_Node* last;
	BigInt count;
	BigInt maxid;
	int no_of_bits_used;
	int sizeofTables;
	int sizeofBtree;

	void manageSuccessorsHelper(Machine_Node* temp) {
		int i = 1;
		RoutingTable_Node* tableTemp = temp->FT.Head;
		last = Head;
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

			if (temp2 != temp) {

				tableTemp->nextMachineAddress = temp2;
				tableTemp->nextMachineID = temp2->ID;
			}
			else {
				tableTemp->nextMachineAddress = temp2->next;
				tableTemp->nextMachineID = temp2->next->ID;
			}
			tableTemp = tableTemp->next;
			i++;

		}
		temp = temp->next;
	}
	void mangesuccessors() {
		if (!Head)
			return;
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

	void SetsizeofBtree(int size) {
		sizeofBtree = size;
	}

	bool AddMachine(BigInt ID) {
		Machine_Node* newNode = new Machine_Node(ID, sizeofTables, sizeofBtree);

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

		//Here The folder related to the machine is deleted
		deleteDirectory(ID.getData());

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

	Machine_Node* mappingIdToMachine(BigInt fileHash, string& pathTaken) {
		Machine_Node* temp = Head;
		pathTaken += "machine" + temp->ID.getData() + " ";
		while (temp->ID < fileHash && temp->next != Head) {
			RoutingTable_Node* Table_Temp = temp->FT.Head;
			for (int i = 0; i < sizeofTables - 1; i++) {
				if (Table_Temp->next->nextMachineID <= fileHash && Table_Temp->next->nextMachineID >= Table_Temp->nextMachineID)
					Table_Temp = Table_Temp->next;
				else
					break;
			}
			temp = Table_Temp->nextMachineAddress;
			pathTaken += "machine" + temp->ID.getData() + " ";
		}
		return temp;
	}

	void StoringFile(string fileContent, BigInt fileHash, string extension) {
		string pathTaken = "";
		Machine_Node* temp = nullptr;
		if (fileHash > last->ID) {
			temp = Head;
			pathTaken = pathTaken += "machine" + temp->ID.getData() + " ";
		}
		else {
			temp = mappingIdToMachine(fileHash, pathTaken);
		}
		cout << "File storing Path : " << pathTaken << "\n";
		++(temp->fileCount);
		std::string newPath = temp->ID.getData() + "\\" + (temp->fileCount.getData()) + extension; // Replace this with your desired file path
		temp->btree->insert(newPath, fileHash);
		writeFile(newPath, fileContent);
	}

	void deletingAFile(BigInt id) {
		std::string pathTaken = "";
		Machine_Node* temp = nullptr;
		if (id > last->ID) {
			temp = Head;
			pathTaken = pathTaken += "machine" + temp->ID.getData() + " ";
		}
		else {
			temp = mappingIdToMachine(id, pathTaken);
		}
		std::cout << "File storing Path : " << pathTaken << "\n";
		if (temp->btree->remove(id))
			--(temp->fileCount);
		

	}
	void searchFile(BigInt id) {
		std::string path = "";
		std::string pathTaken = "";
		Machine_Node* temp = nullptr;
		if (id > last->ID) {
			temp = Head;
			pathTaken = pathTaken += "machine" + temp->ID.getData() + " ";
		}
		else {
			temp = mappingIdToMachine(id, pathTaken);
		}
		std::cout << "File storing Path : " << pathTaken << " \n";
		temp->btree->search(id, path);
		std::cout << path << "\n";
	}

	void PrintBtree(BigInt id) {
		
		if (Head == nullptr)
			return;
		if (Head->ID == id) {
			Head->btree->display();
		}
		else {
			Machine_Node* temp = Head->next;
			while (temp->ID != id && temp->next != Head)			{
				temp = temp->next;
			}
			if (temp->ID == id) {
				temp->btree->display();
			}esle{
					cout << "NO machine with this id\n";
			}
		}

	}

	~Machine_list() {
		Machine_Node* temp = Head;
		while (Head->next != Head) {
			last->next = Head->next;
			Head = Head->next;
			deleteDirectory(temp->ID.getData());
			delete temp;
			temp = Head;
		}
		deleteDirectory(Head->ID.getData());
		Head = nullptr;
		last = nullptr;
	}
};

#endif 