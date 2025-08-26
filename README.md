# ft_ping - TODO Checklist

## ✅ COMPLETED
- [x] Basic project structure (Makefile, headers, main)
- [x] Command line argument parsing (-v, -?)
- [x] Help text generation and display
- [x] Basic error handling for invalid options

## 🔄 MANDATORY PART - TODO

### Core ICMP Implementation
- [ ] Create raw socket (requires root privileges)
- [ ] Build ICMP Echo Request packet structure
- [ ] Send ICMP packets to target
- [ ] Receive and parse ICMP Echo Reply packets
- [ ] Calculate RTT (Round Trip Time)

### Network Resolution
- [ ] Handle IPv4 addresses as input
- [ ] Handle hostnames as input (DNS resolution)
- [ ] Validate input format (IP vs hostname)

### Output Format (match inetutils-2.0 ping)
- [ ] Display initial "PING hostname (IP) X(Y) bytes of data"
- [ ] Display per-packet results: "64 bytes from IP: icmp_seq=X ttl=Y time=Z ms"
- [ ] Handle timeout cases (no reply received)
- [ ] Display final statistics on exit (packets sent/received, packet loss %, RTT min/avg/max/mdev)
- [ ] Handle Ctrl+C gracefully with statistics

### Verbose Mode (-v)
- [ ] Show additional packet information
- [ ] Display error packets (TTL expired, destination unreachable, etc.)
- [ ] Show raw packet data when requested

## 🎯 BONUS PART - TODO
- [ ] Additional flags: -f -l -n -w -W -p -r -s -T --ttl --ip-timestamp
- [ ] Each flag implementation as separate feature

## 🧪 TESTING TODO
- [ ] Test with valid IPv4 addresses
- [ ] Test with valid hostnames
- [ ] Test with unreachable hosts
- [ ] Test verbose mode with TTL modification
- [ ] Test error handling (invalid hosts, network errors)
- [ ] Compare output format with reference ping (inetutils-2.0)

## 📝 TECHNICAL NOTES
- Must use raw sockets (SOCK_RAW, IPPROTO_ICMP)
- Requires root privileges for raw sockets
- No use of system ping or standard ping sources allowed
- All libc functions are authorized




## Parsing tests already made on GNU ping

$ ping -?-a
Usage: ping [OPTION...] HOST ...
Send ICMP ECHO_REQUEST packets to network hosts.

$ ping -a?
ping: invalid option -- 'a'
Try 'ping --help' or 'ping --usage' for more information.

$ ping -a-?
ping: invalid option -- 'a'
Try 'ping --help' or 'ping --usage' for more information.

$ ping -?a
Usage: ping [OPTION...] HOST ...
Send ICMP ECHO_REQUEST packets to network hosts.


