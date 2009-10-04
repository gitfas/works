#include <stdio.h>

int main()
{
	int i;
	char ch[20];
	char *p;
	p = ch;

	gets(ch);

	while(*(p + i) != '/0') {
		printf("%c" , *(p + i));
		i++;
	}

	return 1;
}
