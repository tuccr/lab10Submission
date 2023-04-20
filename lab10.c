#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    int count;
    struct Trie * next[26]; // 26 letters in alphabet
};


void insert(struct Trie *pTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
struct Trie * init(void);
void deallocateNode(struct Trie * pTrie);

void printWord(struct Trie * pTrie, char * word) {
    if(word == NULL || pTrie == NULL) {return;}
    printf("printing %s\n", word);
    struct Trie * temp = pTrie;
    int k;
    for(int i = 0; i < strlen(word); i++) {
        k = word[i] - 'a';
        printf("%d ", k);
        temp = temp->next[k];
    }
    printf("\n");
}

void insert(struct Trie *pTrie, char *word) {
    if(word == NULL || pTrie == NULL) {return;}
    struct Trie * temp = pTrie;
    int k;
    for(int i = 0; i < strlen(word); i++) {
        k = word[i] - 'a';
        if(temp->next[k] == NULL) { 
            temp->next[k] = init();
        }
        temp = temp->next[k];
    }
    temp->count = temp->count + 1;
    printWord(pTrie, word);
}

int numberOfOccurances(struct Trie *pTrie, char *word) {
    if(word == NULL) {return 0;}
    //printf("begin count for %s\n", word);
    struct Trie * temp = pTrie;
    int l = strlen(word);
    int k;
    for(int i = 0; i < l; i++) {
        k = word[i] - 'a';
        //printf("k = %d\n", k);
        if(temp->next[k] == NULL) { 
            return 0;
        }
        temp = temp->next[k];
    }
    //printf("count is %d\n", temp->count);
    return temp->count;
}

void deallocateNode(struct Trie * pTrie) {
    struct Trie * temp = pTrie;
    for(int i = 0; i < 26; i++) {
        if(temp->next[i] != NULL) {
            deallocateNode(temp->next[i]);
        }
    }
    free(temp);
}

struct Trie * deallocateTrie(struct Trie *pTrie) {
    for(int i = 0; i < 26; i++) {
        if(pTrie->next[i] != NULL) {
            deallocateNode(pTrie->next[i]);
        }
    }
    free(pTrie);
    pTrie = NULL;
    return pTrie;
}

struct Trie * init(void) {

    struct Trie * pTrie = NULL;

    pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    for(int i = 0; i < 26; i++) {
        pTrie->next[i] = NULL;
    }
    pTrie->count = 0;
   // if(pTrie) {
   //     printf("init(%d)\n", pTrie);
   //     printf("%d->count = %d\n", pTrie, pTrie->count);
   //     printf("%d->next[0] = %d\n", pTrie, pTrie->next[0]);
   // }
    return pTrie;
}


int main(void)
{
    // read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    struct Trie * trie = init();
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for(int j = 0; j < 5; j++) {
        insert(trie, pWords[j]);
    }
    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0;
}