#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **tokenize(void)
{
	char *line = NULL; // buffer for getline() to put all chars read, set to NULL bc getline is smart enough to set it's own buffer and update size_t bytes
	char *temp_line; // copy line after getline() and replace '\r' with '\0', to keep reference of string before it will be tokenized
	size_t buf_bytes = 0; // size of buffer in bytes
	ssize_t num_read; // stores number of chars read from getline(), for the return (long int)
	char *word; //stores token(s) from strtok()
	char *temp_word;  //stores count of token(s) from strtok()
	char **av; // set pointer to an array of char *, each element in the array is another pointer (thus making it a double pointer)
	int ac = 0; // while tokenizing, count amount of tokens/words (starting from 0)
	unsigned int av_count = 0; // need counter to keep track of where we are in malloc'd array
	// unsigned int i; // for loop counter during iteration through av indexes (deleted after move from main to new **tokenize function)

	printf("\nRats! ");
												// stdin - standard input file stream
	num_read = getline(&line, &buf_bytes, stdin); // ssize_t getline(char **lineptr, size_t *n, FILE *stream);
	line[num_read - 1] = '\0'; // must replace new line last char (from user return input) with null byte at end of line read to remove extra space 
	temp_line = strdup(line); // to change instances of line in tokenization with temp_line, use temp_line to count the words (then get rid of it) and line to tokenize words - break into 2 loops

	if (temp_line == NULL)
	{
		free(line); // if malloc fails, free line since we don't have valid pointer to reference string
		return (NULL); // in new function we're returning a char ptr to a ptr, update from -1 to NULL to handle any errors in this function in main
	}

	temp_word = strtok(temp_line, " "); // char *strtok(char *str, const char *delim);
	while (temp_word != NULL) // when strtok() runs out of tokens or fails it will return NULL
	{
		ac++; // if we passed a char pointer instead of NULL, it would start all over with the new place
		temp_word = strtok(NULL, " "); // give NULL to strtok() bc it stores it's string pointing to the beginning of the next token in a static variable (which can hold data between calls)
	}
	free(temp_line);

	av = malloc(sizeof(char * ) * (ac + 1)); // av is the name of our 1st pointer, allocate size of char ptr multiply by number of args (ac) plus 1
									// (ac + 1) need space for last pointer of argv which is NULL;
									// now we the array that we can store pointers to each word
									// if we keep a reference to eack of the words, we can use the same memory filled by line (allocated from getline) 26:20
	if (av == NULL)
	{
		free(line); // if malloc fails, free line since we don't have valid pointer to reference string
		return (NULL); // in new function we're returning a char ptr to a ptr, update from -1 to NULL to handle any errors in this function in main
	}

	word = strtok(line, " "); // char *strtok(char *str, const char *delim);

	// take advantage of while loop to save char pointers to words (from strtok) in malloc'd array av 
	while (word != NULL) // when strtok() runs out of tokens or fails it will return NULL
	{
		av[av_count] = word; // modify av, position to set will be our counter (av_count) set at zero, set it to whatever strtok() returns which is word
		av_count++; // increment which count we're on
		word = strtok(NULL, " "); // give NULL to strtok() bc it stores it's string pointing to the beginning of the next token in a static variable (which can hold data between calls)
		 						// if we passed a char pointer instead of NULL, it would start all over with the new place
	}
	av[av_count] = NULL; // need to make last element in our array of pointers NULL when we're done

	return(av); // return double pointer to our calling function (main)
}

int main (void) // gets pointer to our array of pointers, able to use the array to print all words out
{
	unsigned int i; // for loop counter during iteration through av indexes
	char **tokens; 

	tokens = tokenize();
	if (tokens == NULL) // in new function we're returning a char ptr to a ptr, update from -1 to NULL to handle any errors in this function in main
	{
		printf("OH NO SEND HELP!\n");
		return (0); // do all error checks in tokenize(), error is simplied down to one NULL return statment no matter what happens 
	}

	// condition: updated from av[i] to tokens[i]
	for (i = 0; tokens[i] != NULL; i++) // demonstrate args/reference to all words in line via av, condition options: loop while less than the amount of args that we have (i < ac) or
		printf("Stored word: %s\n", tokens[i]);	// loop without the count of args with av[i] != NULL bc we we have NULL at the end of av array, we can check if the pointer we're looking at is equal to NULL
								// bc if it is (NULL) then we're done/at end of av array
	free(tokens[0]); // free at zero index frees all tokens bc we used the same set of memory for all of our words
	free(tokens);								
	printf("\n");


	return (0);
}
