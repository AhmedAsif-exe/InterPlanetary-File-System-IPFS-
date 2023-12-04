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

		//0 1 2 3 4
	//   0 1 2 	
		fullChildSize = fullChild->children.size;
		if (!fullChild->leaf) {
			for (int idx = order; idx < fullChildSize; ++idx)
				newChild->children.push_back(fullChild->children[idx]);


			fullChild->key.pop(fullChildSize - order + 1);
		}

	}

	void insertNonFull(BNode* node, int value) {
		int insertionIdx = node->key.size - 1;

		if (node->leaf) {
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

	void merge(BNode*& node, int idx, int nextIdx) {
		BNode* childNode = node->children[idx];

		BNode* newNode = nullptr;
		if (nextIdx > idx) {
			BNode* rightNode = node->children[nextIdx];
			childNode->key.push_back(node->key[idx]);

			for (int i = 0; i < rightNode->key.size; ++i) {
				childNode->key.push_back(node->key[i]);
				if (rightNode->children.size > 0)
					childNode->children.push_back(rightNode->children[i]);
			}

			if (rightNode->children.size > 0) {
				childNode->children.push_back(rightNode->children.peek());
				rightNode->children.pop();
			}
			newNode = childNode;
			node->key.remove(idx);
			node->children.remove(nextIdx);
		}
		else {
			BNode* leftNode = node->children[nextIdx];
			leftNode->key.push_back(node->key[nextIdx]);
			for (int i = 0; i < childNode->key.size; ++i) {
				leftNode->key.push_back(node->key[idx]);
				if (leftNode->children.size > 0)
					leftNode->children.push_back(childNode->children[idx]);
			}
			if (leftNode->children.size > 0) {
				leftNode->children.push_back(childNode->children.peek());
				childNode->children.pop();
			}
			newNode = leftNode;
			node->key.remove(nextIdx);
			node->children.remove(idx);
		}

		if (node == root && node->key.size == 0)
			root = newNode;
		

	}
	void removeSibling(BNode* node, int idx, int nextIdx) {

		BNode* childNode = node->children[idx];
		if (idx < nextIdx) {
			BNode* rightNode = node->children[nextIdx];
			childNode->key.push_back(node->key[idx]);
			node->key[idx] = rightNode->key[0];
			if (rightNode->children.size > 0) {
				childNode->children.push_back(rightNode->children[0]);
				rightNode->children.remove(0);
			}
			rightNode->key.remove(0);
		}
		else {
			BNode* leftNode = node->children[nextIdx];
			childNode->key.insert(node->key[idx - 1], 0);
			node->key[idx - 1] = leftNode->key.peek();
			leftNode->key.pop();
			if (leftNode->children.size > 0)
				childNode->children.insert(leftNode->children.peek(), 0);
		}
	}
	int removePredecessor(BNode* node) {
		if (node->leaf) {
			int key = node->key.peek();
			node->key.pop();
			return key;
		}
		int keySize = node->key.size - 1;
		if (node->children[keySize]->key.size >= order)
			removeSibling(node, keySize + 1, keySize);
		else
			merge(node, keySize, keySize + 1);

		removePredecessor(node->children[keySize]);

	}
	int removeSuccessor(BNode* node) {
		if (node->leaf) {
			int key = node->key.peek();
			node->key.pop();
			return key;
		}
		if (node->children[1]->key.size >= order)
			removeSibling(node, 0, 1);
		else
			merge(node, 0, 1);

		removeSuccessor(node->children[0]);
	}
	void removeInternalNode(BNode* node, int value, int idx) {

		if (node->leaf) {
			if (node->key[idx] == value)
				node->key.remove(idx);
			return;
		}

		if (node->children[idx]->key.size >= order) {
			node->key[idx] = removePredecessor(node->children[idx]);
			return;
		}
		else if (node->children[idx + 1]->key.size >= order) {
			node->key[idx] = removeSuccessor(node->children[idx + 1]);
			return;

		}
		else {
			merge(node, idx, idx + 1);
			removeInternalNode(node->children[idx], value, order - 1);
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

	BNode* remove(int value, BNode* node) {
		int idx = 0;
		while (idx < node->key.size && value > node->key[idx]) ++idx;

		if (node->leaf) {
			if (idx < node->key.size && value == node->key[idx])
				node->key.remove(idx);
			return nullptr;
		}

		if (idx < node->key.size && node->key[idx] == value)
		{
			removeInternalNode(node, value, idx);
			return nullptr;
		}
		else if (node->children[idx]->key.size >= order)
			remove(value, node->children[idx]);
		else {

			if (idx != 0 && idx + 2 < node->children.size) {
				if (node->children[idx - 1]->key.size >= order)
					removeSibling(node, idx, idx - 1);
				else if (node->children[idx + 1]->key.size >= order)
					removeSibling(node, idx, idx + 1);
				else
					merge(node, idx, idx + 1);
			}
			else if (idx == 0) {
				if (node->children[idx + 1]->key.size >= order)
					removeSibling(node, idx, idx + 1);
				else
					merge(node, idx, idx + 1);
			}
			else if (idx + 1 == node->children.size) {
				if (node->children[idx - 1]->key.size >= order)
					removeSibling(node, idx, idx - 1);
				else
					merge(node, idx, idx - 1);
			}

			
		}

	}
	void display() {
		displayTree(root);
	}
};
