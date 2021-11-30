#include <stdio.h>


int main(int ac, char **av, char **envp)
{

	(void) ac;
	(void) av;
	printf("%s\n", envp[8]);
}
