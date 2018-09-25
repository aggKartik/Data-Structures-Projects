#include "stdafx.h"
#include "BSTForWords.h"

BSTForWords::BSTForWords(){
	totalUnique = 0;
	numWords = 0;
	sentences = 0;
	avgSentenceLength = 0;
	avgWordLength = 0;
	change = '1';
	usedOften;
}

/*
* This function analyzes information of a node
* @param Node<string>* p pointer to a node
*/
void BSTForWords::analyze(Node<string>* p) {
	if (p != nullptr) {
		if (p->left != nullptr) analyze(p->left);
			totalUnique++;
			avgWordLength += p->info.length() + (p->info.length() * p->counter);
			if (p->info.length() > 3) {
				totalUniqueThree++;
				if (p->counter > (.05 * numWords))
					usedOften.push_back(p->info);
			}
		if (p->right != nullptr) analyze(p->right);
	}
}


vector<string> BSTForWords::getUsedOften() {
	return usedOften;
}

//in case client needs to see content of tree
void BSTForWords::displayTree() {
	inOrder();
}


void BSTForWords::inOrder(Node<string>* p) {
	if (p != nullptr) {
		if(p->left!=nullptr) inOrder(p->left);
		cout << p->info << endl;
		if (p->right != nullptr) inOrder(p->right);
	}
}

/*
* Insertion into a BST For Words is a speicalized process
* No punctuation is allowed.
* To preserve analysis integrity, words are inserted as lowercase equivalents
* @param string item - item to be inserted
*/

void BSTForWords::insert(string item) {
	numWords++;
	Node<string>* temp = new Node<string>;
	item = toLowerString(item);
	char c = item[item.length() - 1];

	bool punc = c == '.' || c == ',' || c == ':' || c == ';' || c == '/';

	if (punc) {
		temp->info = item.substr(0, item.length() - 1);
		if (c == '.') {
			sentences++;
			avgSentenceLength = numWords/sentences;
		}
	}
	else
		temp->info = item;
	temp->left = temp->right = nullptr;


	if (root == nullptr)
		root = temp;
	else {
		Node<string>* p = root;
		Node<string>* r = nullptr;

		while (p != nullptr) {
			r = p;
			if (equals(p->info, item)) {
				p->counter += 1;
				return;
			}
			else if (p->info > item)
				p = p->left;
			else
				p = p->right;
		}

		if (r->info < item)
			r->right = temp;
		else
			r->left = temp;
	}

}

/*
* Helper function to check if two strings are equivalent
*/
bool BSTForWords::equals(string treeNode, string item) {
	
	char c = item[item.length() - 1];
	bool punc = c == '.' ||  c == ',' || c == ':' || c == ';' || c == '/';

	if (treeNode == item)
		return true;
	else if (treeNode == item.substr(0, item.length() - 1) && punc)
		return true;
	else
		return false;

}

int BSTForWords::getTotalUniqueWords() {
	return totalUnique;
}

int BSTForWords::getTotalUniqueWordsThree() {
	return totalUniqueThree;
}

int BSTForWords::getTotalWords() {
	return numWords;
}
int BSTForWords::getTotalSentences() {
	return sentences;
}
int BSTForWords::getAvgSentenceLength() {
	return avgSentenceLength;
}
int BSTForWords::getAvgWordLength() {
	return avgWordLength/numWords;
}

string BSTForWords::toLowerString(string str) {

	int i = 0;
	while (str[i]) {
		str[i] = tolower(str[i]);
		i++;
	}
	return str;

}

/*
  This function allows all unique words of a tree to be printed prefaced by first letter of character
  @param Node<string>* p - pointer to node
*/
void BSTForWords::printIndexes(Node<string>* p) {
	
	if (p != nullptr) {
		if (p->left != nullptr) printIndexes(p->left);
		if (change != p->info[0]) {
			char x = toupper(p->info[0]);
			cout << x << endl;
			change = p->info[0];
		}
		cout << p->info << endl;
		if (p->right != nullptr) printIndexes(p->right);
	}

}
/*
* Specialized version of printIndexes() function that prints to a file provided by the user.
*/
void BSTForWords::printIndexesFile(Node<string>* p, ofstream& outi) {
	if (p != nullptr) {
		if (p->left != nullptr) printIndexesFile(p->left, outi);
		if (change != p->info[0]) {
			char x = toupper(p->info[0]);
			outi << x << endl;
			change = p->info[0];
		}
		outi << p->info << endl;
		if (p->right != nullptr) printIndexesFile(p->right, outi);
	}

}