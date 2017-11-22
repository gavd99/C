#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define NUM_OF_ACCEPT_SYM 256
#define IS_SYM_ACCEPT(x) ((x) < NUM_OF_ACCEPT_SYM)

int compare(const void *x1, const void *x2) {
	return (*(char *)x1 - *(char *)x2);
}

unsigned int isPermutation(char *string) {
	char *symbols = (char *) calloc(NUM_OF_ACCEPT_SYM, sizeof(char));

	for (int i = 0; string[i]; i++) {
		if (IS_SYM_ACCEPT(string[i]))
			symbols[string[i]]++;
		else {
			free(symbols);
			return 0;
		}
	}

	for (int i = 0; i < NUM_OF_ACCEPT_SYM; i++) {
		if (symbols[i] > 1) {
			free(symbols);
			return 0;
		}
	}

	free(symbols);
	return 1;
}

unsigned int isLastPermutation(char *string) {
	if (!string[0])
		return 1;

	for (int i = 1; string[i]; i++)
		if (string[i - 1] < string[i])
			return 0;

	return 1;
}

void reverseString(char *left, char *right) {
	char tmp;
	while (left < right) {
		tmp = *left;
		*left++ = *right;
		*right-- = tmp;
	}
}

char *findNextPermutation(char *string) {
	if (isLastPermutation(string)) {
		string[0] = 0;
		return string;
	}

	int iWrong = strlen(string) - 2;
	while (string[iWrong] > string[iWrong + 1])
		iWrong--;

	int jMin = iWrong + 1, k = iWrong + 2;
	while (string[k]) {
		if (string[k] > string[iWrong] && string[k] < string[jMin])
			jMin = k;
		k++;
	}

	char tmp = string[iWrong];
	string[iWrong] = string[jMin];
	string[jMin] = tmp;

	reverseString(&string[iWrong + 1], &string[k - 1]);
	return string;
}

void printAllNextPermatations(char *string) {
	while (string[0] != 0)
		printf("%s\n", string = findNextPermutation(string));
}

void printAllPermutationsForSet(char *set) {
	qsort(set, strlen(set), sizeof(char), compare);
	printf("%s\n", set);
	printAllNextPermatations(set);
}

char *fillString(char *string) {
	int size = 8;
	string = (char *) malloc((size + 1) * sizeof(char));

	for (int i = 0; (i < 1) ? 1 : string[i - 1]; i++) {
		string[i] = _getche();

		switch (string[i]) {
		case '\r': // enter
			string[i] = 0;
			string = (char *) realloc(string, i + 1);
			break;
		case '\b': // backspase
			i = (i > 1) ? (i - 2) : -1;
		}

		if (i == size - 1) {
			size <<= 1; // *2
			string = (char *) realloc(string, size + 1);
		}
	}
	puts(string);

	return string;
}

int main(void) {
	char *string = NULL;
	string = fillString(string);

	if (!isPermutation(string))
		printf("%s is not a permutation!", string);
	else
		printAllNextPermatations(string);

	free(string);
	return 0;
}