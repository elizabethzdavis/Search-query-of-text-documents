#ifndef HASH_H_
#define HASH_H_

			
struct htEntry {
	char word[21];				//Word can be 20 + a null
	int docID;
	int occurrences;
	struct htEntry* next;
};

void create_entry(char* word, int docID, int bucketNum);

void incrementCount(struct htEntry* e) ;

void createHashtable(int size) ;

//Returns the bucket we need given a string 
int hash_code(char* w) ;

//Inserts an occurrence of w in document i into the hashtable 
void hash_table_insert(char* w, int docID) ;

//Finds the entry 
struct htEntry* findEntry(int bucketNum, char* w, int docID);

void printHashtable();

#endif 
