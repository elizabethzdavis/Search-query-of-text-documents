#ifndef TRAINING_H_
#define TRAINING_H_



//Fineds the file by the name filenam
FILE* openFile(char* filename) ;

//Takes the file and then goes through line by line to break each line into words 
//Then each word is then inserted into the hash table 
void readFile(char* filename, int docID) ;


//Takes in number of documents and their names and then adds each to the hashtable
void training(int numDoc, char* filenames[]) ;

#endif
