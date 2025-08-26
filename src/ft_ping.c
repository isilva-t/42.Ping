#include "ft_ping.h"
int main(int ac, char **av)
{
	struct ping_flags flags = {0};
	int opt;

	int i = 0;
	while ((opt = getopt(ac, av, "v?")) != -1) {
		i++;
		//printf ("opt is: %d\n", opt);
		//printf("optopt %d\n", optopt);
		if (optopt != 0) {
			printf("Try './ft_ping -?' for more information.\n");
			return EX_USAGE;
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
		printf("No hostname provided\n");
	}
	return 0;
}
