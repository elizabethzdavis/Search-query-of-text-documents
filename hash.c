#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

int numBuckets = 0; 					//Needs to be initialized to some input 
struct htEntry** buckets; 				//An array of pointers to the entries that represents buckets 				

void create_entry(char* word, int docID, int bucketNum){
	struct htEntry *entry;
	entry = malloc(sizeof(struct htEntry));
	strcpy(entry -> word, word);
	entry -> docID = docID;
	entry -> occurrences = 1;
	entry -> next = buckets[bucketNum];		//Set to the next in the list
	buckets[bucketNum] = entry; 			//Puts it at the head of the list
}

void incrementCount(struct htEntry* e) {
	e -> occurrences ++;
}

void createHashtable(int size) {
	buckets = malloc(sizeof(struct htEntry*) * size); 		//Allocate space for size spots * the htEntries pointers 
	numBuckets = size;
	//set array to null 
	for(int i = 0; i < numBuckets; i++) {
		buckets[i] = NULL; 							//Each bucket has an empty htEntry list 
	}
}

//Returns the bucket we need given a string 
int hash_code(char* w) {
	int sum = 0; 						//going to  hold the sum of the characters
	int bucket = 0;						//Individual bucket  
	//printf("numBuckets = %d \n", numBuckets);

	//printf("hashing word: %s\n", w);
	while(*w)	{					//While there is a character there 
		//printf("got character %c %d\n", *w, (int) *w);
		sum = sum + *w++;					//Adds the ASCII values to sum 
		//printf("Sum for %c is = %d \n", *w, sum);
	} 
	//printf("It left this loop");
	bucket = sum % numBuckets;
	//printf("bucket = %d", bucket);
	//printf("it found the bucket\n");
	return bucket;
}


//Inserts an occurrence of w in document i into the hashtable 
void hash_table_insert(char* w, int docID) {
	//printf("It called hastable insert method with word = %s\n", w);
	int b = hash_code(w); 							//Find the bucket 
	//printf("Got a hash code! \n");
	struct htEntry* found = findEntry(b, w, docID);
	if(found != NULL) {
		incrementCount(found);
	}

	else { 
		//printf("it created an entry");
		create_entry(w, docID, b);
	}
}

//Finds the entry 
struct htEntry* findEntry(int bucketNum, char* w, int docID) {
	struct htEntry* e = buckets[bucketNum];				//Get head of list
	int i;
	while(e != NULL) {
		if(strcmp(e -> word, w) == 0 ) {
			if(e -> docID == docID) {
				return e;
			}
		}
		e = e -> next;
	}
	return NULL;
}

void printHashtable() {
	//For each bucket, print out bucket number and then every entry in that bucket
	struct htEntry* E;
	for(int i = 0; i < numBuckets; i++) {
		printf("Bucket number = %d \n", i);
		E = buckets[i];
		while(E) {
			printf("The word is: %s  The docID is: %d  The num occurences is: %d \n", 
				E-> word, E-> docID, E-> occurrences);
				E = E-> next;
		}
	}
}





