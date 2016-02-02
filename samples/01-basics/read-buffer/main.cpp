#include <stdio.h>

int main(int argc, char * argv[])
{
	int ch;
	char buffer[10];
	const int MAX_SIZE = sizeof(buffer) - 1;
	int len = 0;

	while ((len < MAX_SIZE) &&
		((ch = getchar()) != EOF))
	{
		buffer[len++] = ch;
	}
	buffer[len] = '\0';
	puts(buffer);

	return 0;
}
