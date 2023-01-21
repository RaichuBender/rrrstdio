#include "rrrstdio.h"


int main(int argc, char *argv[])
{
	printf("Hello\n");

	printf("Number: %d\n", 123);
	printf("Number: %d\n", -123);
	printf("Number: %d\n", 0xdeadbeef);

	printf("Number: %x\n", 123);
	printf("Number: %x\n", -123);
	printf("Number: %x\n", 0xdeadbeef);

	printf("Char: %c\n", 'a');
	printf("Char: %c\n", -1);
	printf("Char: %c%c\n", 0x08, 0x33);

	return 0;
}
