#include "ft_ping.h"

void	print_help_exit(char *av0) {
	printf("Try '%s -?' for more information.\n", av0);
	exit(EX_USAGE);
}

int main(int ac, char **av)
{
	char *last_slash = strrchr(av[0], '/');
	if (last_slash)
		av[0] = last_slash + 1;

	struct ping_flags flags = {0};
	int opt;

	int i = 0;
	while ((opt = getopt(ac, av, "v?")) != -1) {
		i++;
		//printf ("opt is: %d\n", opt);
		//printf("optopt %d\n", optopt);
		if (optopt != 0) {
			print_help_exit(av[0]);
		}
		switch (opt) {
			case 'v':
				flags.verbose = 1;
				continue;
			case '?':
				if(i == 1) {
					printf("%s", help_text);
					return 0;
				}
				flags.help = 1;
				continue;	
			default:
				continue;				
		}
	}
	if(flags.help) {
		printf("%s", help_text);
		return 0;
	}

	(void)flags;
	if (optind < ac) {
		printf("target hostname/IP: %s\n", av[optind]);
	} else {
		printf("%s: missing host operand\n", av[0]);
		print_help_exit(av[0]);
	}
	return 0;
}
