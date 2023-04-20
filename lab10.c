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
void init(struct Trie * pTrie);
void deallocateNode(struct Trie * pTrie);

void insert(struct Trie **ppTrie, char *word) {
    printf("begin insert for %s\n", word);
    if(word == NULL || ppTrie == NULL) {return;}
    struct Trie * temp = *ppTrie;
    int k;
    for(int i = 0; i < strlen(word); i++) {
        printf("i = %d\n", i);
        k = word[i] - 'a';
        printf("k = %d\n", k);
        if(temp == NULL) {
            temp = (struct Trie *)malloc(sizeof(struct Trie));
            temp->count = 0;
            for(int j = 0; j < 26; j++) {
                temp->next[j] = NULL;
            }
        }
        temp = temp->next[k];
    }
    temp->count = temp->count + 1;
    printf("insert complete\n");
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

void init(struct Trie * pTrie) {
    pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    int length = 5;
    for(int i = 0; i < 26; i++) {
        pTrie->next[i] = NULL;
    }
    pTrie->count = 0;
    printf("init()\n");
}


int main(void)
{
    // read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    struct Trie * trie;
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    init(trie); // this is going to initialize and fill
    for(int j = 0; j < 5; j++) {
        insert(&trie, pWords[j]);
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