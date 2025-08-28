#include <ft_ping.h>

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
