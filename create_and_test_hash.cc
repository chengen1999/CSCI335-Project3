// Alfredo Morales

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_probing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;

  //Since NumOfCollisions is  mutatable  
  //And "static std::hash<HashedObj> hf;" retains the value no matter the amount of calls,
  //We must make the hash_table empty and reset the amount of collisions
  hash_table.MakeEmpty();  
  hash_table.resetNumOfCollisions();
  

  /*------------------------------------READ WORD FILE PROCEDURE--------------------------------------------------------*/
  ifstream words_file;			 
  

  words_file.open(words_filename);

  if (words_file.fail()) {
	  cout << "ERROR WHILE OPENING WORDS FILE" << endl;
  }
  /*--------------------------------------------------------------------------------------------------------------------*/
  string new_line;

  while (getline(words_file, new_line)) {	//Read all words from a given text file words.txt and insert them into a hash table.
	  hash_table.Insert(new_line);
  }

  cout << endl;
  cout << "Inserting words into the Hash table... \n" << endl;
  
  cout << "Statistics for this Hash Table:" << endl;
  
  cout << "Elements in Table: " << hash_table.NumOfElements() << endl;	// Total number of elements in the table(N)
  
  cout << "Size of the table: " <<	hash_table.getSize() << endl;	 // The size of table (T)
 
  cout << "Load factor: " << hash_table.LoadFactor() << endl;	 // The load factor (N/T)
 
  cout << "Number of Collisions: " << hash_table.NumOfCollisions() << endl;	 // Number of Collisions (C)
  
  cout << "Avgerage number of collisions: " << hash_table.AvgNumOfCollisions() << endl;		// The average number of collisions(C / N).

  cout << endl;
  cout << "Beginning seaching for query words: " << endl;

  /*------------------------------------READ WORD FILE PROCEDURE--------------------------------------------------------*/
  ifstream query_file;
  query_file.open(query_filename);

  if (query_file.fail()) {
	  cout << "ERROR WHILE OPENING QUERY FILE" << endl;
  }
  /*--------------------------------------------------------------------------------------------------------------------*/

  hash_table.resetNumOfCollisions();

  while (getline(query_file, new_line)) {

	  // We want to find the number of probes only, therefore we reset collisions
	  hash_table.resetNumOfCollisions();

	  if (hash_table.Contains(new_line)) {
		  // If it contains the word, then that means we encountered an instnace.
		  // We must find a new position in the hashtable, so you collide until you find a position
		  cout << new_line << ": Found in " << hash_table.NumOfCollisions() + 1 << " probes" << endl;
	  }
	  else {
		  cout << new_line << ": Not found in " << hash_table.NumOfCollisions() + 1 << " probes" << endl; 
	  }

 }
 
  words_file.clear();
  words_file.close();
  query_file.clear();
  query_file.close();
}


// Sample main for program create_and_test_hash
int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  cout << endl;
  cout << "Input words file is " << words_filename << ", and query file is " << query_filename << endl;

  if (param_flag == "linear") {
	cout << "I will run the linear Hash code" << endl;
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);  

  } else if (param_flag == "quadratic") {
	cout << "I will run the quadratic Hashing code" << endl;
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);    

  } else if (param_flag == "double") {
	cout << "I will run the double Hashing code" << endl;
	HashTableDouble<string> double_probing_table;
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename);  

  } else {
    cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
