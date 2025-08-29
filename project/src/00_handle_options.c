#include "ft_ping.h"

void	handle_options(int ac, char **av, struct ping_flags *flags) {
	if (!av || !flags) { return; }

	char *last_slash = strrchr(av[0], '/');
	if (last_slash)
		av[0] = last_slash + 1;

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
				flags->verbose = 1;
				continue;
			case '?':
				// edge case when -? is first option
				if(i == 1) {
					help_and_exit();
				}
				flags->help = 1;
				continue;	
			default:
				continue;				
		}
	}
	if(flags->help) {
		help_and_exit();
	}
}
