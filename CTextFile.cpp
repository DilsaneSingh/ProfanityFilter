// Name			    - Dilsane Singh
// Student Number   - G20961395
// Email			- DSingh6@uclan.ac.uk

// Headers and namespaces
#include "CTextFile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Constants
const int COLUMN_SIZE = 20;

// To set input and output text filenames.
// Takes two mandatory parameters
// First parameter is the name of input text filename	- string data type
// Second parameter is the name of output text filename	- string data type
void CTextFile::setFilenames(string fname, string ofname)
{
	mFilename = fname;		
	mOutFilename = ofname;	
}

// To get input filename.
string CTextFile::getFilename()
{
	return mFilename;
}

// To get output filename.
string CTextFile::getOutFilename()
{
	return mOutFilename;
}

// To set the vectors mwords, mTop10Frequency, mTop10Alphabetically.
void CTextFile::setFrequencyData(vector <SWordInfoTF>& VAllWords)
{
	ifstream infile;
	infile.open(mFilename);		// Open inputfile.
	if (!infile) {				// If file could not be opened, print the following message
		cout << "Error! Unable to open the file " << mFilename << endl << endl;
	}
	else {						// Else if the file is open
		while (!infile.eof()) {	// While the end of the file is not reached
			string iword;
			infile >> iword;	// Read one word at a time and store it in iword (input word)
								// Convert the iword to lowercase
			transform(iword.begin(), iword.end(), iword.begin(), ::tolower);
			int pos = 0;
			string word;

			// Find position of any character that is not an alphabet
			while ((pos = iword.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz")) != string::npos)
			{
				if (pos != 0)	// If non-alphabetic character is not found at first position
				{	
					word = iword.substr(0, pos);	// Extract the substring from first position to the position where the non-alphabetic character is found
													// So we have the substring of input word without any non-alphabetic character
					Push(word, VAllWords);			// Push word
				}
				else
				{
					// Found non-alphabetic character
					// Do Nothing
				}

				iword.erase(0, pos + 1);  // remove pos+1 to get rid of non-alphabetic character
			}
			// Cover the word with no non-alphabetic character
			if (iword.length() > 0)
			{
				word = iword;
				Push(word, VAllWords);
			}
		}
	}
	infile.close();		// Close file.

	// Sort the words in descending order of their frequency
	sort(mwords.begin(), mwords.end(), [](SWordInfoTF a, SWordInfoTF b) {
		return a.frequency > b.frequency;
	});

	// Push Top 10 most frequent words to the vector mTop10Frequency
	for (int i = 0; i < 10; i++) {
		mTop10Frequency.push_back(mwords[i]);
	}
	
	// Vector with Top 10 most frequent words sorted in dictionary order
	mTop10Alphabetically = mTop10Frequency;
	sort(mTop10Alphabetically.begin(), mTop10Alphabetically.end(), [](SWordInfoTF a, SWordInfoTF b) {
		return a.word < b.word;
	});
}

/* To Push the first parameter(word) in the
	vector 2nd parameter (vector that contains all the word from each text file and their frequency.)
	and the vector mwords if the word does not exist already or increase the frequency by 1 if it does. */
void CTextFile::Push(string word, vector <SWordInfoTF>& VALL)
{
	bool found = false;
	for (int i = 0; i < mwords.size(); i++) {
		if (mwords[i].word == word) {
			mwords[i].frequency += 1;
			found = true;
		}
	}
	if (found == false) {
		mwords.push_back({ word, 1 });
	}

	for (int i = 0; i < VALL.size(); i++) {
		if (VALL[i].word == word) {
			VALL[i].frequency += 1;
			found = true;
		}
	}
	if (found == false) {
		VALL.push_back({ word, 1 });
	}
}

// To print the top 10 most frequent words from the input file in descending order of frequency.
void CTextFile::PrintTop10Freq()
{
	cout << "Top 10 most frequent words from the file " << mFilename << " in descending order of frequency :-" << endl << endl;
	cout << setw(COLUMN_SIZE) << left << setfill(' ') << "Word" << "Frequency" << right << setfill(' ') << endl << endl;
	for (int i = 0; i < mTop10Frequency.size(); i++) {
		cout << setw(COLUMN_SIZE) << left << setfill(' ') << mTop10Frequency[i].word <<  mTop10Frequency[i].frequency << right << setfill(' ') << endl;
	}
	cout << endl;
}

// To print the top 10 most frequent words from the input file in dictionary order.
void CTextFile::PrintTop10Alpha()
{
	cout << "Top 10 most frequent words from the file " << mFilename << " in dictionary order :-" << endl << endl;
	cout << setw(COLUMN_SIZE) << left << setfill(' ') << "Word" << "Frequency" << right << setfill(' ') << endl << endl;
	for (int i = 0; i < mTop10Alphabetically.size(); i++) {
		cout << setw(COLUMN_SIZE) << left << setfill(' ') << mTop10Alphabetically[i].word << mTop10Alphabetically[i].frequency << right << setfill(' ') << endl;
	}
	cout << endl;
}

// To get the vector mWords.
vector<SWordInfoTF> CTextFile::getWordsTF()
{
	return mwords;
}