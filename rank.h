#ifndef RANK_H_
#define RANK_H_

#include "hash.h"
#include "training.h"


struct htEntry* getEntry(char* word, int docId) ;

//returns a 1 if contains, 0 if not
int contains(char* word, int docID) ;

//Find the number of times that word occurs in a document
int termFrequency(char* word, int docID) ;

//How many documents out of three it comes up with 
int documentFrequency(char* word);

//Document frequence but the log(recipricol)
double inverseDF(int docFreq) ;

//Ranking of the individual word in a document 
//tf-IDF
double wordRank(char* word, int docID) ;

//Phrase rank for a single document 
double rank(char* keywords, int docID) ;

//Read into an input and return the string 
void read_query(char* phrase1, char* phrase2, char* phrase3);

#endif













