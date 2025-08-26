#include "ft_ping.h"

int main(int ac, char **av)
{
	int opt;
	int verbose = 0;

	while ((opt = getopt(ac, av, "v?")) != -1) {
		switch (opt) {
			case 'v':
				verbose = 1;
				printf("verbose on \n");
				continue;
			case '?':
				printf("help\n");
				return 0;
			default:
				printf("default\n");
				return 1;
		}
	}

	if (optind < ac) {
		printf("target hostname/IP: %s\n", av[optind]);
	} else {
		printf("No hostname provided\n");
	}
	(void)verbose;
	return 0;
}
