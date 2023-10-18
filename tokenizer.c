#include "shell.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * split_string - Splits a string into words based on delimiters.
 * @str: The input string.
 * @delimiters: A string containing the delimiters.
 *
 * Return: An array of strings (words) or NULL on failure.
 */
char **split_string(char *str, const char *delimiters)
{
if (str == NULL || delimiters == NULL || str[0] == '\0')
return (NULL);

size_t num_words = countWords(str, delimiters);
if (num_words == 0)
return (NULL);

char **words = (char **)malloc((num_words + 1) * sizeof(char *));
if (words == NULL)
{
return (NULL);
}
extractWords(str, delimiters, words, num_words);
if (words[num_words] == NULL)
{
freeWords(words, num_words);
return (NULL);
}

words[num_words] = NULL;
return (words);
}

void freeWords(char **words, size_t num_words)
{
if (words == NULL)
return ();

for (size_t i = 0; i < num_words; i++)
{
free(words[i]);
}
free(words);
}


/**
* countWords - Counts the number of words in a string based on delimiters.
* @str: The input string.
* @delimiters: A string containing the delimiters.
*
* Return: The number of words.
*/
size_t countWords(char *str, const char *delimiters)
{
size_t num_words = 0;
bool in_word = false;

for (size_t i = 0; str[i] != '\0'; i++)
{
if (strchr(delimiters, str[i]) != NULL)
{
if (in_word)
{
in_word = false;
num_words++;
}
}
else
{
if (!in_word)
in_word = true;
}
}

if (in_word)
num_words++;

return (num_words);
}

/**
 * extractWords - Extracts words from the input string and populates the array.
 * @str: The input string.
 * @delimiters: A string containing the delimiters.
 * @words: An array to store the words.
 * @num_words: The number of words to extract.
 */
void extractWords(char *str, const char *delimiters, char **words, size_t num_words)
{
size_t word_length = 0;
size_t word_count = 0;
bool in_word = false;

for (size_t i = 0; str[i] != '\0'; i++)
{
if (strchr(delimiters, str[i]) != NULL)
{
if (in_word)
{
in_word = false;
words[word_count] = extractWord(str, i - word_length, word_length);
if (words[word_count] == NULL)
{
freeWords(words, word_count);
return;
}
word_count++;
word_length = 0;
}
}
else
{
if (!in_word)
in_word = true;
word_length++;
}
}
if (in_word)
{
words[word_count] = extractWord(str, strlen(str) - word_length, word_length);
if (words[word_count] == NULL)
{
freeWords(words, word_count);
}
}
}

/**
* extractWord - Extracts a word from the input string.
* @str: The input string.
* @start: The starting index of the word.
* @length: The length of the word.
*
* Return: The extracted word or NULL on failure.
*/
char *extractWord(char *str, size_t start, size_t length)
{
char *word = (char *)malloc((length + 1) * sizeof(char));
if (word == NULL)
return (NULL);

strncpy(word, str + start, length);
word[length] = '\0';
return (word);
}
