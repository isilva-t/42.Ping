#include "ft_ping.h"

void	print_help_exit(char *av0) {
	printf("Try '%s -?' for more information.\n", av0);
	exit(EX_USAGE);
}

void	help_and_exit() {
	printf("%s", help_text);
	exit(0);
}

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

int	resolve_target(const char *target, struct in_addr *dest_ip) {
	if (!target || !dest_ip) { return 1; }

	struct addrinfo *result = NULL; 
	struct addrinfo hints = {0};
	hints.ai_family = AF_INET;
	
	int s;
	s = getaddrinfo(target, NULL, &hints, &result);

	if (s == 0) {
		//typecast addrinfo to sockaddr_in to extract IPV4 address
		struct sockaddr_in *addr = (struct sockaddr_in*)result->ai_addr;
		*dest_ip = addr->sin_addr;
		freeaddrinfo(result);
		return 0;
	}
	return -1;
}

int main(int ac, char **av)
{
	struct ping_flags flags = {0};
	handle_options(ac, av, &flags);
	if (optind < ac) {
		struct in_addr dest_ip = {0};
		if(resolve_target(av[optind], &dest_ip) != 0) {
			printf("%s: unknown host\n", av[0]);
			exit(1);
		}
		printf("PING %s (%s) x(y) bytes of data.\n", av[optind], inet_ntoa(dest_ip));
	} else {
		printf("%s: missing host operand\n", av[0]);
		print_help_exit(av[0]);
	}
	return 0;
}
