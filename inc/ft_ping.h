#ifndef FT_PING_H
# define FT_PING_H

#include <stdio.h>
#include <unistd.h>

#include <stdint.h>
#include <sysexits.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <signal.h>

// for getaddrinfo()
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

// for inet_ntoa()
#include <arpa/inet.h>

// ICMP packet structure
#define DATA_LEN 8
struct icmp_packet {
	uint8_t		type;		// ICMP type (8 for echo request)
	uint8_t		code;		// ICMP code (0 for echo request)  
	uint16_t	checksum;	// Checksum (calculated)
	uint16_t	id;			// Identifier (usually process ID)
	uint16_t	sequence;	// Sequence number
	char		data[DATA_LEN];	// Data payload
} __attribute__((packed));

#define ICMP_ECHO_REQUEST	8
#define ICMP_ECHO_REPLY		0

struct ping_flags {
   uint8_t verbose	: 1;  // -v flag
   uint8_t help		: 1;  // -? flag
   uint8_t flood	: 1;  // -f flag (bonus)
   uint8_t numeric	: 1;  // -n flag (bonus)
   uint8_t quiet	: 1;  // -q flag (bonus)
   uint8_t timestamp	: 1;  // -T flag (bonus)
   uint8_t res1		: 1;
   uint8_t res2		: 1;
} __attribute__((packed));

//90_helpers
void	print_help_exit(char *av0);
void	help_and_exit(); 

//91_print_fts
void	print_packet_details(struct icmp_packet *packet);
void	print_packet_hex(struct icmp_packet *packet);

//00_handle_options
void	handle_options(int ac, char **av, struct ping_flags *flags);

//10_resolve_targets
int	    resolve_target(const char *target, struct in_addr *dest_ip);
#endif
