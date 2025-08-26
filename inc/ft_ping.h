#ifndef FT_PING_H
# define FT_PING_H

#include <stdio.h>
#include <unistd.h>
#include "../help.h"
#include <stdint.h>

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


#endif
