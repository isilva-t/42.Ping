# 42 Ping

Status: 🚧 In Development

Replication of GNU ping in C to learn about ICMP packets

![ping](ping.jpg)

### TODO Checklist

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
- [x] Handle IPv4 addresses as input
- [x] Handle hostnames as input (DNS resolution)
- [x] Validate input format (IP vs hostname)

### Output Format (match inetutils-2.0 ping)
- [-] Display initial "PING hostname (IP) X(Y) bytes of data"
- [ ] Display per-packet results: "64 bytes from IP: icmp_seq=X ttl=Y time=Z ms"
- [ ] Handle timeout cases (no reply received)
- [ ] Display final statistics on exit (packets sent/received, packet loss %, RTT min/avg/max/mdev)
- [x] Handle Ctrl+C gracefully 
- [ ]               with statistics

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

## some documentation
# parsing
- getopt() - man 3 getopt
- getaddrinfo() - man 3 getaddrinfo



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

### test hostname for parsing

$ ping google.com
PING google.com (142.250.184.14): 56 data bytes
64 bytes from 142.250.184.14: icmp_seq=0 ttl=112 time=32.956 ms
64 bytes from 142.250.184.14: icmp_seq=1 ttl=112 time=37.822 ms
64 bytes from 142.250.184.14: icmp_seq=2 ttl=112 time=37.881 ms
64 bytes from 142.250.184.14: icmp_seq=3 ttl=112 time=32.779 ms
64 bytes from 142.250.184.14: icmp_seq=4 ttl=112 time=47.597 ms
64 bytes from 142.250.184.14: icmp_seq=5 ttl=112 time=43.578 ms
64 bytes from 142.250.184.14: icmp_seq=6 ttl=112 time=34.664 ms
^C--- google.com ping statistics ---
7 packets transmitted, 7 packets received, 0% packet loss
round-trip min/avg/max/stddev = 32.779/38.182/47.597/5.167 ms
$ ping 142.250.184.14
PING 142.250.184.14 (142.250.184.14): 56 data bytes
64 bytes from 142.250.184.14: icmp_seq=0 ttl=112 time=173.293 ms
64 bytes from 142.250.184.14: icmp_seq=1 ttl=112 time=34.439 ms
64 bytes from 142.250.184.14: icmp_seq=2 ttl=112 time=40.889 ms
64 bytes from 142.250.184.14: icmp_seq=3 ttl=112 time=32.693 ms
^C--- 142.250.184.14 ping statistics ---
4 packets transmitted, 4 packets received, 0% packet loss
round-trip min/avg/max/stddev = 32.693/70.329/173.293/59.525 ms
$ ping www.google.com
PING www.google.com (142.250.201.68): 56 data bytes
64 bytes from 142.250.201.68: icmp_seq=0 ttl=112 time=38.752 ms
64 bytes from 142.250.201.68: icmp_seq=1 ttl=112 time=32.446 ms
^C--- www.google.com ping statistics ---
2 packets transmitted, 2 packets received, 0% packet loss
round-trip min/avg/max/stddev = 32.446/35.599/38.752/3.153 ms
$ ping https://google.com
ping: unknown host
$ ping https://www.google.com
ping: unknown host
$ ping www.google.com/test
ping: unknown host
$ ping www.google.com/a
ping: unknown host



