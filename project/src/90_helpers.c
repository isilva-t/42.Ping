#include "ft_ping.h"
#include "../help.h"

void	print_help_exit(char *av0) {
	printf("Try '%s -?' for more information.\n", av0);
	exit(EX_USAGE);
}

void	help_and_exit() {
	printf("%s", help_text);
	exit(0);
}
