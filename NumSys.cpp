#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define	MAX_NUM_OF_SYM_OUTPUT 32
#define HIGHEST_DEGREE_OF_ACCURACY 13

struct Number {
	long long intP;
	double fractP;
};

void reverseString(char *left, char *right) {
	char tmp;
	while (left < right) {
		tmp = *left;
		*left++ = *right;
		*right-- = tmp;
	}
}

int charToInt(char symbol, unsigned int base) {
	unsigned int result;
	if (symbol >= '0' && symbol <= '9')
		result = symbol - '0';
	else
		result = toupper(symbol) - 'A' + 10;

	return (result >= base || result < 0) ? -1 : result;
}

char intToChar(int number) {
	if (number >= 0 && number <= 9) return number + '0';
	return number + 'A' - 10;
}

Number findIntermediateValue(char *s, unsigned int base) {
	int digit = 0, i = 0;
	Number number = {0, 0};

	while (s[i] && s[i] != '.' && s[i] != ',') {
		digit = charToInt(s[i], base);
		if (digit == -1) {
			number.intP = -1;
			return number;
		}

		number.intP = number.intP * base + digit;
		i++;
	}

	if (!s[i]) 
		return number;

	i = strlen(s) - 1;
	while (i && s[i] != '.' && s[i] != ',') {
		digit = charToInt(s[i], base);
		if (digit == -1) {
			number.intP = -1;
			return number;
		}

		number.fractP = (number.fractP + digit) / base;
		i--;
	}

	return number;
}

char *findBaseValue(Number num, unsigned int base) {
	char *res = (char *) malloc((MAX_NUM_OF_SYM_OUTPUT + 1) * sizeof(char));
	if (!num.intP && !num.fractP) {
		res[0] = '0';
		res[1] = 0;
		return res;
	}

	res[MAX_NUM_OF_SYM_OUTPUT] = 0;
	int i = 0;

	while (num.intP) {
		res[i] = intToChar(num.intP % base);
		num.intP /= base;
		i++;
	}
	reverseString(res, &res[i - 1]);

	if (!num.fractP) {
		res[i] = 0;
		return res;
	}

	res[i] = '.';
	i++;
	int j = 0, digit;
	while (num.fractP && j < HIGHEST_DEGREE_OF_ACCURACY && (i + j) < MAX_NUM_OF_SYM_OUTPUT) {
		digit = (int) (num.fractP * base);
		res[i+j] = intToChar(digit);
		num.fractP = num.fractP * base - digit;
		j++;
	}
	res[i+j] = 0;

	return res;
}

char *valueFromBase1ToBase2(char *string, unsigned int base1, unsigned int base2) {
	if (base1 < 2 || base2 < 2)
		return NULL;

	Number intermedResult = findIntermediateValue(string, base1);
	if (intermedResult.intP == -1) 
		return NULL;

	return findBaseValue(intermedResult, base2);
}

int main(void) {
	char *string = (char *) malloc((MAX_NUM_OF_SYM_OUTPUT + 1) * sizeof(char));
	unsigned int base1, base2;

	scanf("%d%d%s", &base1, &base2, string);

	char *result = valueFromBase1ToBase2(string, base1, base2);
	printf("%s", result? result:"Error");

	free(string);
	free(result);
	return 0;
}
