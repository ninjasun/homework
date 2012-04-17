#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "wordstat.h"

int main(int argc, char** argv)
{
	palindrome *palHead;/*head of Palindrome linked list*/
	palHead = malloc(sizeof(palindrome));
	palHead=NULL;

	palindrome *palPTR;/*pointer for Palindrome linked list*/
	palPTR = malloc(sizeof(palindrome));
	palPTR = NULL; 

	entry *dictHead;
	dictHead = malloc(sizeof(entry)); /*head of Dictionary linked list*/
	dictHead = NULL;

	entry *dictPTR;/*pointer for Dictionary linked list*/
	dictPTR = malloc(sizeof(entry)); 
	dictPTR = NULL;

	/*Checking amount of arguments*/
	if (argc <=1 || argc >3)
	{
		printf("Invalid input. Please run again\n");
		return 1;
	}

	if ( strcmp( "-h", argv[1] ) == 0 )
	{
		printf("Usage: ./wordstat <option> <filename> \n"
		"Options: -l : number of lines\n"
		"-w: number of words\n"
		"-p: palindrome's statistics.\n");
		return 0;
	}

	if (argc == 3)
	{
		/*Reading from user text file*/
		FILE *fp = fopen (argv[2], "r");	
		if (fp == NULL)
		{
			printf("File not found. Please run again.");
			return 1;
		}
		char *delims = getDelims();
		char *buffer = malloc(sizeof(char)*1024);
		int numLines = 0;
		int numWords = 0;
		while ( fgets(buffer, 1024, fp) )
		{
		//	printf("%s", delims);
			numLines++;
			//char *tokBuffer = malloc(sizeof( char)*1024);
			//char * token = malloc(sizeof(char) * 1024);
			char * token;
			//while( strtok(tokBuffer, delims) )
			for (token = strtok(buffer, delims); token != NULL; token = strtok(NULL, delims))
			{
				palPTR = palHead;
				numWords++;
				if ( isPalindrome(token) == 1 )
				{
					palindrome *unique;
					unique = isUnique(token,palHead);
					if ( unique  == NULL )
					{
						char *copy = malloc(sizeof(char) * (1+strlen(token)) );
						strcpy(copy, token);
						palindrome *newNode= malloc(sizeof(palindrome));/*needs malloc*/

						//printf("%s\n", copy);
						newNode->word = copy;
						newNode->occurences = 1;
						newNode->inDict=0;
						newNode->next = NULL;

				//		printf("%s\n", newNode->word);

						if (palHead == NULL) /*create head if it does not exist*/
						{
							palHead = newNode;
							palPTR = newNode;
						}
						else
						{						
							while (palPTR->next != NULL && ( nodecmp(palPTR, palHead) < 0) )
							{
								palPTR = palPTR->next;
							}

							if (palPTR->next == NULL)
							{
								palPTR->next = newNode;
							}
							else
							{
								newNode->next = palPTR->next;
								palPTR->next = newNode;
							}			
						}
					}
					else
					{
						unique->occurences++;
					}

				}
			}
		}
		/*
		palindrome *cp = palHead;
		while (cp != NULL)
		{
			printf("%s\n", cp->word);
			cp = cp->next;
		}
		*/


		/*Reading in from dictionary*/
		FILE *dictfp;
		dictfp = fopen ("dict.txt", "r");
		if (dictfp == NULL)
		{
			printf("Dictionary file not found.\n");
			return 1;
		}

		fgets(buffer, 1024, dictfp);
		char *dWordCopy = malloc(sizeof(char) * (1+strlen(buffer)) );
		strcpy(dWordCopy, buffer);
		entry *dictNode = malloc(sizeof(entry));
		dWordCopy[strlen(dWordCopy) -1] = '\0';
		dictNode->word = malloc(sizeof(char) *( strlen(dWordCopy) +1 )) ;
		dictNode->next = NULL;
		dictHead = dictNode;
		dictHead->word = dWordCopy;
		dictPTR = dictHead;		

		while( fgets(buffer, 1024, dictfp))
		{
			char *targetEntry = malloc( strlen(buffer) + 1);
			strcpy(targetEntry, buffer);
			entry *currentEntry = malloc(sizeof (entry));

			targetEntry[strlen(targetEntry) - 1] = '\0';
			
			currentEntry->word = targetEntry;
			currentEntry->next = NULL;

			dictPTR->next = currentEntry;
			dictPTR = currentEntry;
		//	printf("%s\n", dictPTR->word);

		}

		//-l,-w,-p
		if ( strcmp( "-l", argv[1] ) == 0 )
		{
			printf("%d", numLines);
			return 0;
		}	

		if ( strcmp( "-w", argv[1] ) == 0 )
		{
			printf("%d", numWords);
			return 0;
		}	

		if ( strcmp( "-p", argv[1] ) == 0 )
		{
			dictionaryCheck(palHead, dictHead);
			printf("Palindromes\tFrequencies\tIn Dictionary?\n");
			
			palindrome *p_output = palHead;

			while (p_output != NULL)
			{
				int freq = p_output->occurences;
				char isInDict = 'N';
				if (p_output->inDict == 1)
				{
					isInDict = 'Y';
				}
				

				printf("%s\t\t%d\t\t%c\n", p_output->word, freq, isInDict); 

				p_output = p_output->next;
			}
			return 0;
		}	

	}


//	printf("This works");
	return 0;
}

char* getDelims()
{ 
	char *delimList = malloc(sizeof ( char)*257 );
	char *ptr = delimList;
	int i;
	for (i =1; i < 256; i++)
	{
		if (! isalpha(i) )
		{
			*ptr = i;
			ptr++;
		}
	}
	*ptr = '\0';

	return delimList;
}

palindrome* isUnique(char *currPal, palindrome *head)
{
	stringToUpper(currPal);
	palindrome *ptr = head;
	while (ptr != NULL)
	{
		char *current = ptr->word;
		if ( strcmp(current, currPal) == 0) /*if word is not unique, return pointer to respective node*/
		{
			return ptr;
		}
		ptr = ptr->next;
	}
	return NULL;
}

int isPalindrome(char *currWord)
{
	stringToUpper(currWord);
	int length = strlen(currWord);
	int l = 0;
	int r = length - 1;

	while ( ( l < length ) && (r>=0) && (l < r) )
	{
		if ( currWord[l] != currWord[r] ) 
		{
			return 0;
		}
		l++;
		r--;
	}
	return 1;
}
		
int nodecmp (palindrome *target, palindrome *head)
{
	char *targetWord = target->word;
	char *compareWith = head->word;

	int answer = (strcmp(targetWord, compareWith) );
	return answer;
}

void stringToUpper (char *str)
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
	{
		str[i] = (char)toupper(str[i]);
	}
}

void dictionaryCheck (palindrome *pList, entry *dList)
{
	palindrome *p_ptr = pList;
	entry *d_ptr = dList;

	for (p_ptr = pList; p_ptr != NULL; p_ptr = p_ptr->next)
	{
		while ( d_ptr != NULL && (strcmp(p_ptr->word, d_ptr->word) <= 0) )
		{
			//d_ptr->word[strlen(d_ptr - 1)] = NULL;
			if (strcmp(p_ptr->word, d_ptr->word) == 0)
			{
				p_ptr->inDict = 1;
		//		printf("%s", d_ptr->word);
				printf("getting here");
			}
			d_ptr = d_ptr->next;
		//	printf("even here");
		}
	}
}
/*
void gundamFREEDOM(palindrome *pClean, entry *eClean)
{
}
*/
