#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "training.h"


FILE* openFile(char* filename) {
	//printf("It knows to open the file \n");
	FILE *infile;
	infile = fopen(filename, "r"); 				//opening given name for reading so use "r"
	if(infile == NULL) {
		printf("fopen FAILURE!!\n");
	}
	//printf("It opened the file \n");
	return infile;
}

//Takes the file and then goes through line by line to break each line into words 
//Then each word is then inserted into the hash table 
void readFile(char* filename, int docID) {
	FILE* file = openFile(filename);
	//printf("It called openFile and that worked fine \n");
	char word[21];													//Allowed to be 20 characters long- so need a null spot
		while(fscanf(file, "%s", word) != EOF) {	
			//printf("it enters the scanning loop once \n");	
			hash_table_insert(word, docID);
			//printf("It inserted into the hash table \n");
		}			
}


//Takes in number of documents and their names and then adds each to the hashtable
void training(int numDoc, char* filenames[]) {
	//printf("This even opens \n");
	int docID = 0;
	for(docID = 0; docID < numDoc; docID ++) {
		//printf("It enters the trianing loop \n");
		readFile(filenames[docID], docID);
		//printf("It reads the file completely \n");
	} 

	//printf("It leaves the training method \n");
}

