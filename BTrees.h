#pragma once
#include "Vector.h"
struct BNode {
	bool leaf;
	const int order;
	Vector<int> key;
	Vector<BNode*> children;
	BNode(int order, bool l = false) : key(order + 1), children(order + 1), order(order) {
		leaf = l;
	}
	void displayNode() const {
		for (int i = 0; i < key.size; ++i) {
			std::cout << key[i] << " ";
		}
		std::cout << "| ";
	}
};


class BTree {
	BNode* root;
	const int order;

	void splitChild(BNode* node, int idx) {

		BNode* fullChild = node->children[idx];

		BNode* newChild = new BNode(2 * order - 1, fullChild->leaf);

		node->children.insert(newChild, idx + 1);

		node->key.insert(fullChild->key[order - 1], idx);

		int fullChildSize = fullChild->key.size;

		for (int idx = order; idx < fullChildSize; ++idx)
			newChild->key.push_back(fullChild->key[idx]);



		fullChild->key.pop(fullChildSize - order + 1);


		if (!fullChild->leaf) {
			for (int idx = 2 * order - 1; idx >= order; --idx) {
				newChild->children.push_back(fullChild->children[order - 1]);
				fullChild->children.remove(order - 1);
			}

		}

	}

	void insertNonFull(BNode* node, int value) {
		int insertionIdx = node->key.size - 1;

		if (node->leaf) {
			//			node->key.push_back(-1); // adding null val. This will likely cause error when templatizing for pointer vals
			while (insertionIdx >= 0 && value < node->key[insertionIdx])  // type that will be templatized will need to have operator overloading
				--insertionIdx;

			node->key.insert(value, insertionIdx + 1);
			return;
		}

		while (insertionIdx >= 0 && value < node->key[insertionIdx])
			--insertionIdx;

		++insertionIdx;


		if (node->children[insertionIdx]->key.size == 2 * order - 1) {
			splitChild(node, insertionIdx);
			if (value > node->key[insertionIdx]) ++insertionIdx;
		}
		insertNonFull(node->children[insertionIdx], value);

	}
	void printKey(int key, int level) {
		std::cout << "Level " << level << ": " << key << std::endl;
	}
	void displayTree(BNode* node) {
		if (root != nullptr) {
			// Display keys in the current node
			node->displayNode();

			// Recursively display children
			if (!node->leaf) {
				for (int i = 0; i < node->children.size; ++i) {
					displayTree(node->children[i]);
				}
			}
		}

	}
public:
	BTree(int order) : order(order) {
		root = new BNode(2 * order - 1, true);
	}

	void insert(int value) {
		if (root->key.size != 2 * order - 1) {
			insertNonFull(root, value);
			return;
		}

		BNode* newRoot = new BNode(2 * order - 1);
		newRoot->children.insert(root, 0);
		root = newRoot;
		splitChild(root, 0);
		insertNonFull(root, value);


	}

	void search(int key, BNode* node = nullptr) {
		node = node == nullptr ? root : node;
		if (!node) return;
		int idx = 0;
		while (idx < node->key.size && key > node->key[idx])
			++idx;

		if (idx < node->key.size && key == node->key[idx]) {
			std::cout << "found " << node->key[idx];
			return;
		}
		else if (node->leaf) return;
		else
			search(key, node->children[idx]);
	}
	void display() {
		displayTree(root);
	}
};
