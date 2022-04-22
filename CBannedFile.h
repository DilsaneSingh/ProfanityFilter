// Name			    - Dilsane Singh
// Student Number   - G20961395
// Email			- DSingh6@uclan.ac.uk

// Headers and namespaces
#pragma once
#include <string>
#include <vector>

using namespace std;

// Structure to contain the details of banned word.
struct SWordInfo {
	string word;			// Banned Word. eg. cat
	string replacement;		// Replacement. eg. c*t
	int frequency;			// Frequency of the banned word.
};

class CBannedFile
{
private:

	string mFilename = "banned.txt";	// Banned file set to banned.txt by default, could be changed by setter.
	vector <SWordInfo> mWords;			// Vector to contain structures of all the banned words detail .

public:

	// Setters
	void setFilename(string fname);			// To set filename
	void setWords();						// To set Vector that contains, structures of all the banned words detail.

	// Getters
	vector <SWordInfo> getWords();			// To get Vector that contains, structures of all the banned words detail.

	// Other Methods.
	void printBannedFrequency();			// To print the banned word and it's frequency.
	void CompareWithText1(string fname);	// Method made for text1.txt only as per the assignment brief.
	
};

