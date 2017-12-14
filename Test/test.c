#include "malloc.h"
#include <stdio.h>
int main(void)
{
	int i;
	char *addr;

	i = 0;
	while (i < 10)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		show_alloc_mem();
	//	printf("OK\n");
		i++;
	}
	return (0);
}
/*
int main(void)
{
	char	*ptr;

	ptr = mmap(0, 40960, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0);
	munmap(ptr, 40960);
	
	return 0;
}*/
