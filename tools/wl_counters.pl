#!/usr/bin/env perl
# Minimal "wl counters": WLC_GET_VAR "counters" via SIOCDEVPRIVATE; dumps u32 words at wl_cnt_t offsets.
use strict; use Socket;
my $ifname = shift // 'wlp3s0';
socket(my $s, AF_INET, SOCK_DGRAM, 0) or die "socket: $!";
my $len = 2048;
my $buf = "counters\0" . ("\0" x ($len - 9));
my $bufaddr = unpack("Q", pack("p", $buf));
my $ioc = pack("L x4 Q L C x3 L L", 262, $bufaddr, $len, 0, 0, 0);
my $iocaddr = unpack("Q", pack("p", $ioc));
my $ifr = pack("a16 Q x16", $ifname, $iocaddr);
ioctl($s, 0x89F0, $ifr) or die "ioctl: $!";
my ($ver, $l) = unpack("S S", $buf);
printf "version %d length %d\n", $ver, $l;
for (my $o = 4; $o + 4 <= $l && $o < $len; $o += 4) { printf "%03x %u\n", $o, unpack("L", substr($buf, $o, 4)); }
