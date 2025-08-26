#include "ft_ping.h"
int main(int ac, char **av)
{
	struct ping_flags flags = {0};
	int opt;

	while ((opt = getopt(ac, av, "v?")) != -1) {
		switch (opt) {
			case 'v':
				flags.verbose = 1;
				continue;
			case '?':
				flags.help = 1;
				continue;	
			default:
				continue;				
		}
	}
	if(optopt == '-') {
		printf("Try './ft_ping -?' for more information.\n");
		return 0;
	}


	(void)flags;
	if (optind < ac) {
		printf("target hostname/IP: %s\n", av[optind]);
	} else {
		printf("No hostname provided\n");
	}
	return 0;
}
