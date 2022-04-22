// Name			    - Dilsane Singh
// Student Number   - G20961395
// Email			- DSingh6@uclan.ac.uk

// Headers and namespaces
#pragma once
#include <string>
#include <vector>

using namespace std;

// Structure to contain the details of input text file word.
struct SWordInfoTF {
	string word;
	int frequency;
};

class CTextFile
{
private:
	string mFilename;							// Unfiltered Input Filename.
	string mOutFilename;						// Filtered Output Filename.
	vector <SWordInfoTF> mwords;				// Vector to contain details of all the words in the input text file.
	vector <SWordInfoTF> mTop10Frequency;		// Vector to contain details of top 10 most frequent words in text file in descending order of frequency.
	vector <SWordInfoTF> mTop10Alphabetically;	// Vector to contain details of top 10 most frequent words in text file in dictionary order.

public:
	// Setters
	void setFilenames(string fname, string ofname);				// To set input and output filenames.
	void setFrequencyData(vector <SWordInfoTF>& VAllWords);		// To set the vectors mwords, mTop10Frequency, mTop10Alphabetically.

	// Getters
	string getFilename();						// To get input filename.
	string getOutFilename();					// To get output Filename.
	vector <SWordInfoTF> getWordsTF();			// To get the vector mWords.
	
	// Other Methods

	/* To Push the first parameter(word) in the 
	vector 2nd parameter (vector that contains all the word from each text file and their frequency.)
	and the vector mwords if the word does not exist already or increase the frequency by 1 if it does. */
	void Push(string word, vector <SWordInfoTF>& VAllWords);

	void PrintTop10Freq();		// To print the top 10 most frequent words from the input file in descending order of frequency.
	void PrintTop10Alpha();		// To print the top 10 most frequent words from the input file in dictionary order.
};

