#include <stdio.h>
#include <conio.h>
#include <string.h>
#define N 256

int getFirstEntry(char *string, char *pattern) {
	int lenStr = strlen(string), lenPat = strlen(pattern);
	if (lenPat > lenStr)
		return -1;

	int shift[256];
	for (int i = 0; i < 256; i++) 
		shift[i] = lenPat;

	lenPat--;
	for (int i = 0; i < lenPat; i++) 
		shift[(unsigned char) pattern[i]] = lenPat - i;

	int iStr = lenPat, jPat;
	do {
		jPat = lenPat;
		while ((jPat >= 0) && (string[iStr + jPat - lenPat] == pattern[jPat]))
			jPat--;

		if (jPat < 0)
			return iStr - lenPat;

		iStr += shift[(unsigned char) string[iStr]];
	} while (iStr < lenStr);

	return -1;
}

int main(void) {
	char string[N], pattern[N];
	gets_s(string, N);
	gets_s(pattern, N);

	printf("%d", getFirstEntry(string, pattern));

	return 0;
}