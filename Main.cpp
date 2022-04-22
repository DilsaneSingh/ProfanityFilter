// Name			    - Dilsane Singh
// Student Number   - G20961395
// Email			- DSingh6@uclan.ac.uk

// Headers and namespaces
#include "CBannedFile.h"
#include "CTextFile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// Constants 
const int MAX_WORD_SIZE = 30;
const int LINE_LENGTH = 120;

// Function to draw a line
void DrawLine() {
	for (int i = 0; i < LINE_LENGTH; i++) {
		cout << "_";
	}
	cout << endl << endl;
}

// Function to Filter Files.
// Takes 3 mandatory parameters.
// First parameter is the name of input file. Data Type - String
// Second parameter is the name of output file. Data Type - String
// Third parameter is the vector of structures which contain information about banned words. Data type - vector <SWordInfo>
void FilterFile(string inputfile, string outputfile, vector <SWordInfo> bannedWords) {
	cout << "Filtering the file " << inputfile << endl << endl;
	ifstream infile;
	ofstream outfile;

	// Open input and output files
	infile.open(inputfile);
	outfile.open(outputfile);

	if (!infile) {
		cout << "Error! Unable to open file " << inputfile << endl << endl;
	}
	else {
		string iword;	// String to store the word read from input file  - iword
		string liword;  // String to store iwordr converted to lowercase  - liword

		while (!infile.eof()) {

			infile >> iword;
			liword = iword;

			// Converting liword to lowercase.
			transform(liword.begin(), liword.end(), liword.begin(), ::tolower);

			// Loop to match all banned words with each input word.
			for (int i = 0; i < bannedWords.size(); i++) {

				size_t found = liword.find(bannedWords[i].word);
				if (found != string::npos) {
					iword.replace(found, bannedWords[i].word.size(), bannedWords[i].replacement);
				}

			}

			// Adding Whitespace between words.
			cout << iword << " ";
			outfile << iword << " ";

		}
		cout << endl << endl;
		cout << "Above filtered text is successfuly stored in the file " << outputfile << endl;
	}
	
	// Closing files.
	infile.close();
	outfile.close();
}

int main() {

	CBannedFile BannedFile;
	BannedFile.setWords();

	CTextFile Text1;
	Text1.setFilenames("text1.txt", "text1Filtered.txt");
	BannedFile.CompareWithText1(Text1.getFilename());
	DrawLine();
	cout << "Frequency of the banned words in the file " << Text1.getFilename() << ":-" << endl;
	BannedFile.printBannedFrequency();

	DrawLine();

	CTextFile Text2;
	Text2.setFilenames("text2.txt", "text2Filtered.txt");

	CTextFile Text3;
	Text3.setFilenames("text3.txt", "text3Filtered.txt");

	CTextFile Text4;
	Text4.setFilenames("text4.txt", "text4Filtered.txt");

	// Filtering input File and storing the filtered data in the output file.
	FilterFile(Text1.getFilename(), Text1.getOutFilename(), BannedFile.getWords());
	DrawLine();
	FilterFile(Text2.getFilename(), Text2.getOutFilename(), BannedFile.getWords());
	DrawLine();
	FilterFile(Text3.getFilename(), Text3.getOutFilename(), BannedFile.getWords());
	DrawLine();
	FilterFile(Text4.getFilename(), Text4.getOutFilename(), BannedFile.getWords());
	DrawLine();

	// Vector to contain word and frequency of each word from all the text File.
	vector <SWordInfoTF> VAllWords;

	Text1.setFrequencyData(VAllWords);
	Text1.PrintTop10Freq();
	Text1.PrintTop10Alpha();
	DrawLine();

	Text2.setFrequencyData(VAllWords);
	Text2.PrintTop10Freq();
	Text2.PrintTop10Alpha();
	DrawLine();

	Text3.setFrequencyData(VAllWords);
	Text3.PrintTop10Freq();
	Text3.PrintTop10Alpha();
	DrawLine();

	Text4.setFrequencyData(VAllWords);
	Text4.PrintTop10Freq();
	Text4.PrintTop10Alpha();
	DrawLine();

	// Tasks which require all the files combined.
	vector <SWordInfoTF> VAllWordsFreq = VAllWords;
	vector <SWordInfoTF> VTopAllWordsAlpha;
	sort(VAllWordsFreq.begin(), VAllWordsFreq.end(), [](SWordInfoTF a, SWordInfoTF b) {
		return a.frequency > b.frequency;
	});
	cout << "Top 10 most frequent words from all the files combined in descending order of frequency :-" << endl << endl;
	cout << setw(MAX_WORD_SIZE) << left << setfill(' ') << "Word" << "Frequency" << right << setfill(' ') << endl << endl;
	for (int i = 0; i < 10; i++) {
		VTopAllWordsAlpha.push_back({ VAllWordsFreq[i] });
		cout << setw(MAX_WORD_SIZE) << left << setfill(' ') << VAllWordsFreq[i].word << VAllWordsFreq[i].frequency << right << setfill(' ') << endl;
	}

	cout << endl;

	sort(VTopAllWordsAlpha.begin(), VTopAllWordsAlpha.end(), [](SWordInfoTF a, SWordInfoTF b) {
		return a.word < b.word;
	});
	cout << "Top 10 most frequent words from all the files combined in dictionary order :-" << endl << endl;
	cout << setw(MAX_WORD_SIZE) << left << setfill(' ') << "Word" << "Frequency" << right << setfill(' ') << endl << endl;
	for (int i = 0; i < 10; i++) {
		cout << setw(MAX_WORD_SIZE) << left << setfill(' ') << VTopAllWordsAlpha[i].word << VTopAllWordsAlpha[i].frequency << right << setfill(' ') << endl;
	}

	DrawLine();

	// Sorting all words from all the text files alphabetically.
	// Following code to sort is taken from "https://slaystudy.com/c-sort-vector-of-structs/"
	// and modified according to the task desired.
	sort(VAllWords.begin(), VAllWords.end(), [](SWordInfoTF a, SWordInfoTF b) {
		return a.word < b.word;
	});


	// Storing Sorted list of all words in the text file "sorted.txt"
	cout << "Storing Sorted list of all words in the text file sorted.txt" << endl << endl;
	ofstream outfile;
	outfile.open("sorted.txt");
	if (!outfile) {
		cout << "Error! Unable to open the file sorted.txt" << endl;
	}
	else {

		for (int i = 0; i < VAllWords.size(); i++) {
			cout << setw(MAX_WORD_SIZE) << left << setfill(' ') << VAllWords[i].word << "   " << VAllWords[i].frequency << right << setfill(' ') << endl;
			outfile << setw(MAX_WORD_SIZE) << left << setfill(' ') << VAllWords[i].word << "   " << VAllWords[i].frequency << right << setfill(' ') << endl;
		}
		
	}

	DrawLine();

}