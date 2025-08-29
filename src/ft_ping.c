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

void	create_icmp_packet(struct icmp_packet *packet, uint16_t seq) {
	if (!packet) {return;}

	packet->type = ICMP_ECHO_REQUEST;
	packet->code = 0;
	packet->checksum = 0;
	packet->id = getpid();
	packet->sequence = seq;

	for (int i = 0; i < DATA_LEN ; i++) {
		packet->data[i] = 0;
	}
}



uint8_t	calc_checksum(struct icmp_packet *packet, uint16_t *res) {
	if (!packet || !res) {
		return 1;
	}
	uint32_t sum = 0;
	uint8_t *data = (uint8_t*)packet;
	uint32_t len = sizeof(struct icmp_packet) >> 1;
	uint32_t i = 0;

	printf("len = %d\n", len);
	uint16_t two_byte_word = 0;
	for(i = 0; i < len; i += 2) {
		two_byte_word = 0;
		two_byte_word = (data[i] << 8) | data[i + 1];
		sum += two_byte_word;
		printf("i: %d\n", i);
	}

	if (i < len) {
		two_byte_word = 0;
		two_byte_word = data[i] << 8;
		sum += two_byte_word;
	}

	while (sum > 0xFFFF) {
		sum = (sum & 0xFFFF) + (sum >> 16);
	}
	printf("sum: %x02\n", sum);
	*res = (uint16_t)~sum;
	return 0;
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
		//printf("socket: %d\n", sockfd);
	
		struct icmp_packet packet;
		
		//////////////
		printf("\n=== Before creating packet ===\n");
		printf("Process ID: %d\n", getpid());
		printf("Expected packet size: %zu bytes\n", sizeof(struct icmp_packet));
		//////////////
		
		create_icmp_packet(&packet, 1);
		
		uint16_t checksum;
		if (calc_checksum(&packet, &checksum) != 0) {
			printf("Error on calc_checksum");
			exit(1);
		}
		packet.checksum = htons(checksum);
		print_packet_details(&packet);
		print_packet_hex(&packet);

		signal(SIGINT, handle_sigint);
		while(keep_running) {
			printf("here will be info on result\n");
			exit(0);
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
