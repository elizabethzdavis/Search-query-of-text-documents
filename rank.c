#include <stdio.h>
#include <math.h>
#include <string.h>
#include "hash.h"
#include "training.h"


struct htEntry* getEntry(char* word, int docId) {
 		struct htEntry* correct;
 		int b= hash_code(word);
 		correct = findEntry(b, word, docId);
 		if(correct == NULL) {
 			return NULL;
 		}

 		return correct;
}

//returns a 1 if contains, 0 if not
int contains(char* word, int docID) {
	struct htEntry* recieved;
	recieved = getEntry(word, docID);
	if(recieved != NULL) {
		return 1;
	}

	return 0;
}

//Find the number of times that word occurs in a document
int termFrequency(char* word, int docID) {
	//Search through all htEntries- then search occurrences 
	if(contains(word, docID) == 0){
		return 0;
	}

	int num = 0;
	struct htEntry* e;
	e = getEntry(word, docID);
	num = e -> occurrences;
	//printf("the term frequencey of %s in doc %d is: %d \n", word, docID, num);
	return num;
}


//How many documents out of three it comes up with 
int documentFrequency(char* word) {
	int docFreq = 0;

	for(int i = 0; i < 3; i++) {
		docFreq = docFreq + contains(word, i);
	}

	//printf("The document frequence is: %d\n", docFreq);

	return docFreq;
}

//Document frequence but the log(recipricol)
double inverseDF(int docFreq) {
	double inverseDF = 0;
	double docF = (double) docFreq;
	if(docFreq != 0) {
		inverseDF = log(3 / docF);
	}
	
	//printf("The inverse is: %f\n", inverseDF);

	return inverseDF;
}

//Ranking of the individual word in a document 
//tf-IDF
double wordRank(char* word, int docID) {
	int tf = termFrequency(word, docID);
	double inversedf = inverseDF(documentFrequency(word));

	return tf * inversedf;
}

//Phrase rank for a single document 
double rank(char* keywords, int docID) {
	//Break up words
	//Rank each word
	//Rank phrase
	double totalRank = 0;
	//Break up the words, rank each word, then phrase 
	//printf("keywords: %s|\n", keywords);
	char* word;
	word = strtok(keywords, " ");
	//Runs the ranking function for each word in the query
	//printf("Time for ranking: \n");
	while(word != NULL) {
		//printf("I got : %s\n", word);
		//int contain = containsAtAll(word, docID); 
		/*if(contain != 0) {
			totalRank = totalRank + wordRank(word, docID);					//Calculates the tdidf 
			//printf("Total rank is calculated to be: %f\n", totalRank);
		}*/
		totalRank = totalRank + wordRank(word, docID);					//Calculates the tdidf 
		//printf("Total rank is calculated to be: %f\n", totalRank);
		word = strtok(NULL, " ");
	}

	return totalRank;	
}


//Read into an input and return the string 
void read_query(char* phrase1, char* phrase2, char* phrase3) {
	//gets(phrase);
	//double rankings[3]
		double d1 = rank(phrase1, 0);
		//printf("%f\n", d1); 
		double d2 = rank(phrase2, 1);
		//printf("%f\n", d2); 
		double d3 = rank(phrase3, 2);
		//printf("%f\n", d3); 


		char* doc1 = "D1.txt";
		char* doc2 = "D2.txt";
		char* doc3 = "D3.txt";

		//Time to order them: 
		//Check for zeros: 
		if(d1 == 0 && d2 == 0 && d3 == 0) {
			printf("There are no matches to your query\n");
		}

		//d1 = 0
		else if(d1 == 0) {
			if(d2 == 0) {
				printf("(%s)\n", doc3);
			}

			else if(d3 == 0) {
				printf("(%s)\n", doc2);
			}

			else if(d2 >= d3) {
				printf("(%s, %s)\n", doc2, doc3);
			}

			else if(d3 > d2) {
				printf("(%s, %s)\n", doc3, doc2);
			}
		}

		else if(d2 == 0) {
			if(d1 == 0) {
				printf("(%s)\n", doc3);
			}

			else if(d3 == 0) {
				printf("(%s)\n", doc1);
			}

			else if(d1 >= d3) {
				printf("(%s, %s)\n", doc1, doc3);
			}

			else if(d3 > d1) {
				printf("(%s, %s)\n", doc3, doc1);
			}
		}

		else if(d3 == 0) {
			if(d1 == 0) {
				printf("(%s)\n", doc2);
			}

			else if(d2 == 0) {
				printf("(%s)\n", doc1);
			}

			else if(d1 >= d2) {
				printf("(%s, %s)\n", doc1, doc2);
			}

			else if(d2 > d1) {
				printf("(%s, %s)\n", doc2, doc1);
			}
		}

		//d1 is most relevant
		else if(d1 >= d2 && d1 >= d3) {
			if(d2 >= d3) {
				printf("(%s, %s, %s)\n", doc1, doc2, doc3);
			}
			else if(d3 > d2) {
				printf("(%s, %s, %s)\n", doc1, doc3, doc2);
			}
		}

		//d2 is most relevant
		else if(d2 >= d1 && d2 >= d3) {
			if(d1 >= d3) {
				printf("(%s, %s, %s)\n", doc2, doc1, doc3);
			}
			else if(d3 > d1) {
				printf("(%s, %s, %s)\n", doc2, doc3, doc1);
			}
		}

		//d3 most relevant
		else if(d3 >= d1 && d3 >= d2) {
			if(d2 >= d1) {
				printf("(%s, %s, %s)\n", doc3, doc2, doc1);
			}
			else if(d1 > d2) {
				printf("(%s, %s, %s)\n", doc3, doc1, doc2);
			}
		}
}









