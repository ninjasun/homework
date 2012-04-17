#ifndef WORDSTAT_H
#define WORDSTAT_H

typedef struct node
{
	char *word;
	int occurences;
	int inDict;
	struct node *next;
} palindrome;

typedef struct dictWord
{
	char *word;
	struct dictWord *next;
} entry;

char* getDelims();
/*
	 Checks palindrome linked list to see if the word exists in the list and returns it.
	 If word is unique, returns null
	 */
palindrome* isUnique(char *currPal, palindrome *head);

	
	/*
	 Updates count of occurrences of a given palindrome
	 */

palindrome sortList (palindrome head);

	/*
	 Sorts linked list of palindromes into lexographical order
	 */

int isPalindrome(char *currWord);

	/*
	 Checks if given word is a palindrome
	 Returns 1 if true, 0 if false
	 */

void dictionaryCheck (palindrome *pList, entry *dList);

	/*
	 Goes through both linked lists in order. 
	 Updates boolean values in each palindrome node that exists in dictionary to true
	 */

void stringToUpper (char *string);

void gundamFREEDOM(palindrome *pClean, entry *eClean); 

int nodecmp(palindrome *target, palindrome *head);

#endif
