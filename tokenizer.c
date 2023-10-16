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

	size_t num_words = 0;
	char **words = NULL;
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
		} else
		{
			if (!in_word)
			{
				in_word = true;
			}
		}
	}

	if (in_word)
	{
		num_words++;
	}

	if (num_words == 0)
		return (NULL);

	words = (char **)malloc((num_words + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);

	size_t word_length = 0;
	size_t word_count = 0;

	for (size_t i = 0; str[i] != '\0'; i++)
	{
		if (strchr(delimiters, str[i]) != NULL)
		{
			if (in_word)
			{
				in_word = false;
				words[word_count] = (char *)malloc((word_length + 1) * sizeof(char));
				if (words[word_count] == NULL)
				{
					for (size_t j = 0; j < word_count; j++)
					{
						free(words[j]);
					}
					free(words);
					return (NULL);
				}
				strncpy(words[word_count], str + i - word_length, word_length);
				words[word_count][word_length] = '\0';
				word_count++;
				word_length = 0;
			}
		} else
		{
			if (!in_word)
			{
				in_word = true;
			}
			word_length++;
		}
	}

	if (in_word)
	{
		words[word_count] = (char *)malloc((word_length + 1) * sizeof(char));
		if (words[word_count] == NULL)
		{
			for (size_t j = 0; j < word_count; j++)
			{
				free(words[j]);
			}
			free(words);
			return (NULL);
		}
		strncpy(words[word_count], str + strlen(str) - word_length, word_length);
		words[word_count][word_length] = '\0';
	}

	words[num_words] = NULL;
	return (words);
}
