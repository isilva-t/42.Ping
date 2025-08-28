#include "ft_ping.h"

static volatile int keep_running = 1;

void	handle_sigint(int sig) {
	keep_running = 0;
	(void)sig;
}	

int	create_icmp_socket() {
	int sockfd;

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) {
		perror("socket");
		return -1;
	}
	return sockfd;
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
		int sockfd = create_icmp_socket();
		if (sockfd < 0) {
			printf("failed to create socket. Are you root?\n");
			exit(1);
		}
		printf("socket: %d\n", sockfd);
		
		signal(SIGINT, handle_sigint);
		while(keep_running) {
			printf("here will be info on result\n");
			sleep(1);
		}
		close(sockfd);
		printf("--- %s statistics ---\n", av[0]);
	} else {
		printf("%s: missing host operand\n", av[0]);
		print_help_exit(av[0]);
	}
	return 0;
}
