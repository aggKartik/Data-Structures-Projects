/*
* This is a specilized Binary Search Tree for words
* It provides useful information such as sentence length, number of words
* number of unique words etc
* 
* It inherits a generic Binary Search Tree.
* 
* Author: Kartik Aggarwal
* Version: 3.0
*
*/
#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <fstream>
#include "BST.cpp"

using namespace std;

#ifndef BSTFORWORDS_H
#define BSTFORWORDS_H
class BSTForWords : public BST<string>
{
public:
	BSTForWords();
	void displayTree();
	int getTotalWords();
	int getTotalUniqueWords();
	int getTotalUniqueWordsThree();
	int getTotalSentences();
	int getAvgSentenceLength();
	int getAvgWordLength();
	vector<string> getUsedOften();
	void insert(string);
	void inOrder() { inOrder(root); }
	void analyze() { analyze(root); }
	void printIndexes() { cout << "Index of Unique Words" << endl; printIndexes(root); }
	void printIndexes(ofstream& out) { out << "Index of Unique Words" << endl; printIndexesFile(root, out); }
	

private:
	//BST<string> tree;
	int numWords;
	int totalUnique;
	int totalUniqueThree;
	int sentences;
	int avgSentenceLength;
	int avgWordLength;
	vector<string> usedOften;
	void inOrder(Node<string>*);
	bool equals(string, string);
	string toLowerString(string);
	void analyze(Node<string>*);
	void printIndexes(Node<string>*);
	void printIndexesFile(Node<string>*, ofstream& out);
	char change; //helps with printing indexes

};

#endif 
