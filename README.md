# CSCI335-Project3
Hashing Implementations
The goal of this assignment is to test three hashing implementations. 
Will also use best hashing implementation (in my case linear) for a simple spell-checker. 


You can compile everything by typing 

make clean
make all

------------------------------------------------------------------------------------------------------------------------------
To compile on terminal type
  make all

To delete executables and object file type
  make clean

Execute part 1: For quadratic and linear as follows:
./create_and_test_hash  words.txt query_words.txt quadratic
./create_and_test_hash  words.txt query_words.txt linear
		

Execute part 2: For double as follows:
./create_and_test_hash  words.txt query_words.txt double


Execute part 3: Program should run as follows: 
spell_check <document file> <dictionary file> 
Example:
./spell_check document1.txt wordsEn.txt 	

------------------------------------------------------------------------------------------------------------------------------
(i). All parts of the assignment were executed
	-Modify the code for quadratic and linear probing and test them with create_and_test_hash. 

	-Write code to implement double hashing and test it using create_and_test_hash.  
		-For the hash implementation of R – (x mod R) where R is a prime smaller than table size I used R = 101

	-Implement a spell checker by using your favorite hash table (linear). Given a document 
	 your program should output all of the misspelled words or words that cannot be found in dictionary.
	 For each misspelled word also provide a list of candidate corrections from the dictionary that can be formed
	 by applying one of the following rules to the misspelled word: 
		-Adding one character in each possible position 
		-Removing one character from the word 
		-Swapping adjacent characters in the word 
 	

(ii). There are no known bugs in the program. However, due to a computer architecture issue, the collisions and probes differ
      from expected output, but nothing grave.
      As well as for spell checker, works as intended, but ran into some trouble, when it came to words that were not in the dictionary.
      Printed those as well for efficiency as well as words that weren't able to be fixed by the few rules that we were made to implement.
 

(iv).  The input files for parts 1 and 2 are words.txt and query_words.txt
       The input files for part 3 are the following:
         -document1.txt and document1_short.txt as the files you will check misspelled words from
	 -wordsEn.txt as the dictionary which we will use to check for these mispelled word.
