/*
 * This program generates a text file that contains a stasitical summary of inputed file
 * Author: Kartik Aggarwal
 * Date: 5/20/2018
 */

#include "stdafx.h"
#include <fstream>
#include "BSTForWords.h"

int main()
{
	ifstream file;
	ofstream out;
	string name;
	string str;

	cout << "Enter file name: ";
	cin >> name;
	file.open(name);
	out.open("stats.txt");

	BSTForWords report;
	
	while (file >> str) {
		report.insert(str);
	}
	file.close();

	report.analyze();

	out << "File Name: " << name << endl;
	
	out << " \t \t STATISTICAL SUMMARY" << endl;

	out << "Total Words: " << report.getTotalWords() << endl;
	out << "Total Unique: " << report.getTotalUniqueWords() << endl;
	out << "Total Unique over three: " << report.getTotalUniqueWordsThree() << endl;
	out << "Average Sentence Length: " << report.getAvgSentenceLength() << endl;
	out << "Average Word Length: " << report.getAvgWordLength() << endl;
	
	out << " \t \t STYLE WARNINGS" << endl;

	out << "Words used too often" << endl;
	vector<string> often = report.getUsedOften();
	int i = 1;
	for (vector<string>::iterator it = often.begin(); it != often.end(); ++it) {
		out << i << ") " << *it;
	}
	out << endl;
	int avg = report.getAvgSentenceLength();
	
	if (avg > 10)
		out << "Average Sentence Length Too Long: " << avg << endl;

	avg = report.getAvgWordLength();
	if (avg > 5)
		out << "Average Word Length Too Long: " << avg << endl;

	report.printIndexes(out);

	out.close();

	return 0;
}

