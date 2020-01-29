// Alfredo Morales

#include "linear_probing.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


template <typename HashTableType>
void MisspelledWords(HashTableType& hash_table, const string& document_filename, const string& dictionary_filename) {

	//Since NumOfCollisions is a mutatable variable 
	//And "static std::hash<HashedObj> hf;" retains the value no matter the amount of calls,
	//We must make the hash_table empty and reset the amount of collisions
	hash_table.MakeEmpty();
	hash_table.resetNumOfCollisions();

	/*------------------------------------READ DOCUMENT FILE PROCEDURE--------------------------------------------------------*/
	ifstream document_file;
	document_file.open(document_filename);

	if (document_file.fail()){
		cout << "ERROR WHILE OPENING DOCUMENT FILE" << endl;
	}

	/*---------------------------------- READ DICTIONARY FILE PROCEDURE -------------------------------------------------------*/
	ifstream dictionary_file;
	dictionary_file.open(dictionary_filename);

	if (dictionary_file.fail()){
		cout << "ERROR WHILE OPENING DICTIONARY FILE" << endl;
	}

	string new_line;
	//Store each line/"word" from the dictionary into new_line
	while (getline(dictionary_file, new_line)){	
		hash_table.Insert(new_line);	//Store that into the hash_table
	}

	bool skipWord = false; // will use to skip words that have non-alphabetical characters
	bool correctionAvl = false;	//will use to check if at the end, if false, we can't use any of the cases to fix the mispelled word
								//OR the dictionary does not contain the word.

	
	while (document_file >> new_line) {		//This while loop will check every word in the document
		string letter = "";
		string word = "";
		
		for (unsigned int i = 0; i < new_line.length(); i++) {	// We will start to get each word
						
			letter = tolower(new_line[i]);	//turn char to letter and upload to letter

			if (letter == "\'") {
				skipWord = true; // skip apostrophised words. Might add to check for hypen if later
			}
			if ((letter >= "a" && letter <= "z")) {
				word += letter;
			}
			else {
				skipWord = true;
			}
		}	// Stop getting each word
		
		/*This part of the project will check the obtained word for the following:

		For each misspelled word we will provide a list of candidate corrections from the dictionary
		that can be formed by applying one of the following rules to the misspelled word:
			a) Adding one character in each possible position
			b) Removing one character from the word
			c) Swapping adjacent characters in the word
		*/		
		string newWord = word;
		
		if (!skipWord && !hash_table.Contains(newWord)) {

			//a) Adding one character in each possible position
			cout << "-------------------------------------------------------------" << endl;
			cout << "MISPELLED WORD: " << newWord << endl;
			
			for (unsigned int i = 0; i < word.length() + 1; i++) {
				// insert a - z
				for (char ch = 'a'; ch <= 'z'; ch++) {
					newWord.insert(i, 1, ch);
					if (hash_table.Contains(newWord)) {
						cout << word << " -> " << newWord << " (case a) " << endl;
						correctionAvl = true;
					}
					newWord = word; // reset
				}
			}
			//newWord = word;

			//b) Removing one character from the word

			for (unsigned int j = 0; j < word.length(); j++) {
				newWord.erase(j,1);
				if (hash_table.Contains(newWord)) {
					cout << word << " -> " << newWord << " (case b) " << endl;
					correctionAvl = true;
				}
				newWord = word; // reset
			}

			//newWord = word;
			//c) Swapping adjacent characters in the word

			for (unsigned int k = 0; k < word.length()-1; k++) {
				swap(newWord[k], newWord[k + 1]);
				if (hash_table.Contains(newWord)) {
					cout << word << " -> " << newWord << " (case c) " << endl;
					correctionAvl = true;
				}
				newWord = word; //reset
			}
			if (correctionAvl != true) {
				cout << "NO CORRECTION AVAILABLE or WORD POSSIBLY NOT IN DICTIONARY " << endl;;
			}
			cout << "-------------------------------------------------------------\n" << endl;
		}
		correctionAvl = false;	//Have to reset to false in order to check if the word can be fixed.
		skipWord = false;		//Have to reset to false in order to get back to the if statemnt
	}//END WHILE LOOP

	document_file.close();
	dictionary_file.close();
}

//Main for program spell_check
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file> " << endl;
    return 0;
  }
  
  const string document_filename(argv[1]);
  const string dictionary_filename(argv[2]);

  cout << "TestFunctionForHashTables..." << endl;
  cout << "Input document filename is " << document_filename << endl;
  cout << "Input dictionary filename is " << dictionary_filename << endl;

  cout << "Implemented this with linear Hashing: " << endl;
  HashTableLinear<string> linear_probing_table;

  // Call functions implementing the assignment requirements.
  MisspelledWords(linear_probing_table, document_filename, dictionary_filename);  

  return 0;
}
