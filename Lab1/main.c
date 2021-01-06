#include "add.h"
#include <stdio.h>

int main(void)
{
	int a = 10;
	int b = 20;
	
	int result = add(a, b);
	
	printf("10 + 20 = %d", result);
   	
	return 0;
}
