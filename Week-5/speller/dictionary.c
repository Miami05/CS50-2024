// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

//  Choose number of buckets in hash table
const unsigned int N = 193000;
unsigned int hash_word = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // 
    int index = hash(word);
    node *temp = table[index];
    while (temp != NULL)
    {
        if (strcasecmp(temp->word, word) == 0)
            return (true);
        temp = temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int count = 0;
    for (unsigned int i = 0; word[i] != '\0'; i++)
    {
        int char_value = toupper(word[i]) - 'A';
        count = (count *31 + toupper(word[i])) % N;
    }
    return (count);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // 
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Error reading the file\n");
        return (1);
    }
    char words[LENGTH + 1];
    while (fscanf(file, "%s", words) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return (NULL);
        }
        strcpy(n->word, words);
        unsigned int bucket = hash(words);
        n->next = table[bucket];
        table[bucket] = n;
        hash_word++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // 
    return (hash_word);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // 
    for (int i = 0; i < N; i++)
    {
        node *current = table[i];
        while (current != NULL)
        {
            node *temp = current->next;
            free(current->word);
            current = temp;
        }
        table[i] = NULL;
    }
    return true;
}
