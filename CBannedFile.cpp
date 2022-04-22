// Name			    - Dilsane Singh
// Student Number   - G20961395
// Email			- DSingh6@uclan.ac.uk

// Headers and namespaces
#include "CBannedFile.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constant to set intitial frequency of banned word as 0 before starting the comparison.
const int INITIAL_FREQUENCY = 0;

// To set banned filename - By default the filename is set to "banned.txt".
void CBannedFile::setFilename(string fname)
{
	mFilename = fname;
}

// To set Vector that contains, structures of all the banned words detail.
void CBannedFile::setWords()
{
	ifstream infile;
	infile.open(mFilename);		// Open banned file.

	if (!infile) {				// If the file couldn't be open, print the following text
		cout << "Error! Unable to open the file " << mFilename << endl << endl;
	}

	else {							// Else if the file is open

		while (!infile.eof()) {		// While end of the file is not reached
			string iword;
			infile >> iword;		// Read banned word one by one and store it in iword (i stands for input)

			// Setting replacement word.
			string replacement = iword;							// Initialise replacement word to input word.
			for (int i = 0; i < replacement.size(); i++) {		// Go through each character in it.
				if (i == 0 || i == (replacement.size()-1)) {	// Do nothing to first and last character
					// Do Nothing
				}
				else {
					replacement[i] = '*';						// Change rest of the middle characters to *
				}
			}
			mWords.push_back({ iword,replacement,INITIAL_FREQUENCY });	// Push bannedword, replacement word and 0 as initial frequency to the vector mWords.
		}
	}
	infile.close();		// Close the file after the desired task is done.
}

// To print the banned word and it's frequency.
void CBannedFile::printBannedFrequency()
{
	for (int i = 0; i < mWords.size(); i++) {
		cout << "'" << mWords[i].word << "' found " << mWords[i].frequency << " times." << endl;
	}
}

// Method made for text1.txt only as per the assignment brief.
void CBannedFile::CompareWithText1(string fname)
{
	ifstream infile;
	infile.open(fname);		// Open file.

	if (!infile) {			// If file couldn't be open, print the following message.
		cout << "Error! Unable to open file " << fname << endl << endl;
	}
	else {							// Else if the file is open
		string iword;
		while (!infile.eof()) {		// While the end of file is not reached
			infile >> iword;		// Read words one by one and store it in iword (input word)

			
			for (int i = 0; i < mWords.size(); i++) {	// Loop through the banned word vector mWords
				if (iword==mWords[i].word) {			// If the banned word matches the input word.
					mWords[i].frequency += 1;			// Increase the frequency of banned word by 1
				}
			}
		}
	}

	infile.close();		// Close the file after the desired task is done.
}

// To get Vector that contains, structures of all the banned words detail.
vector<SWordInfo> CBannedFile::getWords()
{
	return (mWords);
}
