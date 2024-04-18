#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_WORD_LENGTH 100

// Trie structure
struct Trie
{	
    struct Trie *children[ALPHABET_SIZE];
    int count;
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    
    if (pTrie) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            pTrie->children[i] = NULL;
        }
        pTrie->count = 0;
    }
    
    return pTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
  if (!pTrie || !word) {
    return;
  }

  struct Trie *current = pTrie;
  int len = strlen(word);
  
  for (int i = 0; i < len; i++) {
    int index = word[i] - 'a';
    struct Trie *newNode = createTrie();
    if (!newNode) {
      return;
    }

    current->children[index] = newNode;
    current = current->children[index];
  }
  current->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if (!pTrie || !word)
        return 0;

    struct Trie *current = pTrie;
    int len = strlen(word);
    
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            return 0; 
        }
        current = current->children[index];
    }
    
    return current->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (!pTrie)
        return NULL;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        deallocateTrie(pTrie->children[i]);
    }

    free(pTrie);
    return NULL;
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    int numWords = 0;
    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[numWords] = (char *)malloc(strlen(word) + 1);
        strcpy(pInWords[numWords], word);
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}