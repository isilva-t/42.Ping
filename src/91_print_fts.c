#include <ft_ping.h>

void	print_packet_details(struct icmp_packet *packet) {
	printf("=== ICMP Packet Analysis ===\n");
	printf("Type: %d (should be 8 for echo request)\n", packet->type);
	printf("Code: %d (should be 0)\n", packet->code);
	printf("Checksum: 0x%04x (currently %d)\n", packet->checksum, packet->checksum);
	printf("ID: %d (our process ID)\n", packet->id);
	printf("Sequence: %d\n", packet->sequence);
	printf("Data first 8 bytes: ");
	for (int i = 0; i < 8; i++) {
		printf("%02d ", (unsigned char)packet->data[i]);
	}
	printf("\n");
	printf("Total packet size: %zu bytes\n", sizeof(struct icmp_packet));
}

void	print_packet_hex(struct icmp_packet *packet) {
	printf("Raw packet bytes:\n");
	unsigned char *bytes = (unsigned char *)packet;
	for (size_t i = 0; i < sizeof(struct icmp_packet); i++) {
		printf("%02x ", bytes[i]);
		if ((i + 1) % 2 == 0) printf("\n");
	}
	printf("\n");
}

