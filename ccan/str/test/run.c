#include "str/str.h"
#include <stdlib.h>
#include <stdio.h>
#include "tap/tap.h"

/* FIXME: ccanize */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

static char *substrings[] = { "far", "bar", "baz", "b", "ba", "z", "ar", NULL };

#define NUM_SUBSTRINGS (ARRAY_SIZE(substrings) - 1)

static char *strdup_rev(const char *s)
{
	char *ret = strdup(s);
	unsigned int i;

	for (i = 0; i < strlen(s); i++)
		ret[i] = s[strlen(s) - i - 1];
	return ret;
}

int main(int argc, char *argv[])
{
	unsigned int i, j, n;
	char *strings[NUM_SUBSTRINGS * NUM_SUBSTRINGS];
	
	n = 0;
	for (i = 0; i < NUM_SUBSTRINGS; i++) {
		for (j = 0; j < NUM_SUBSTRINGS; j++) {
			strings[n] = malloc(strlen(substrings[i])
					    + strlen(substrings[j]) + 1);
			sprintf(strings[n++], "%s%s",
				substrings[i], substrings[j]);
		}
	}

	plan_tests(n * n * 5);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			unsigned int k, identical = 0;
			char *reva, *revb;

			/* Find first difference. */
			for (k = 0; strings[i][k]==strings[j][k]; k++) {
				if (k == strlen(strings[i])) {
					identical = 1;
					break;
				}
			}

			if (identical) 
				ok1(streq(strings[i], strings[j]));
			else
				ok1(!streq(strings[i], strings[j]));

			/* Postfix test should be equivalent to prefix
			 * test on reversed string. */
			reva = strdup_rev(strings[i]);
			revb = strdup_rev(strings[j]);

			if (!strings[i][k]) {
				ok1(strstarts(strings[j], strings[i]));
				ok1(strends(revb, reva));
			} else {
				ok1(!strstarts(strings[j], strings[i]));
				ok1(!strends(revb, reva));
			}
			if (!strings[j][k]) {
				ok1(strstarts(strings[i], strings[j]));
				ok1(strends(reva, revb));
			} else {
				ok1(!strstarts(strings[i], strings[j]));
				ok1(!strends(reva, revb));
			}
		}
	}

	return exit_status();
}				
