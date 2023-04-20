#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    int count;
    struct Trie * next[26]; // 26 letters in alphabet
};


void insert(struct Trie **ppTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
void init(struct Trie * pTrie, char * pWords[]);
void deallocateNode(struct Trie * pTrie);

void insert(struct Trie **ppTrie, char *word) {
    if(word == NULL) {return;}
    printf("for %s ", word);
    struct Trie * temp = *ppTrie;
    int l = strlen(word);
    int k;
    for(int i = 0; i < l; i++) {
        k = word[i] - 'a';
        if(temp->next[k] == NULL) {
            temp->next[k] = (struct Trie *)malloc(sizeof(struct Trie));
            for(int j = 0; j < 26; j++) {
                temp->next[k]->next[j] = NULL;
            }
            temp->next[k]->count = 0;
        }
        temp->next[k];
    }
    temp->count += 1;
    printf("successful, %s count is %d\n", word, temp->count);
}

int numberOfOccurances(struct Trie *pTrie, char *word) {
    if(word == NULL) {return 0;}
    printf("begin count for %s\n", word);
    struct Trie * temp = pTrie;
    int l = strlen(word);
    int k;
    for(int i = 0; i < l; i++) {
        k = word[i] - 'a';
        printf("k = %d\n", k);
        if(temp->next[k] == NULL) {
            return 0;
        }
        temp = temp->next[k];
    }
    printf("count is %d\n", temp->count);
    return temp->count++;
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

void init(struct Trie * pTrie, char * pWords[]) {
    pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    int length = 5;
    for(int i = 0; i < 26; i++) {
        pTrie->next[i] = NULL;
    }
    pTrie->count = 0;
    printf("init()\n");
    for(int i = 0; i < length; i++) {
        printf("insert start...");
        insert(&pTrie, pWords[i]);
        printf("\n");
    }
}

int main(void)
{
    // read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    struct Trie * trie;
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    init(trie, pWords); // this is going to initialize and fill
    
    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0;
}