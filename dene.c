#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>

int main()
{
	int num = LONG_MIN % 256;
	long lnum = LONG_MAX / 10;
	printf("%d\n%ld\n", num, lnum);
/* 	long long domat;
	char str[100];
	scanf("%s", str);
	domat = atoll(str);
	if (domat > LONG_MAX)
		printf("buyuk\n");
	else if (domat == LONG_MAX)
		printf("esit\n");
	else
		printf("kucuk\n");
	printf("%lld\n", domat); */
}
// 9223372036854775807
// 18446744073709551616