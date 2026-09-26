#!/usr/bin/env perl
# Inject unicast data frames to a given MAC (for ACK tests); TA 02:00:00:00:00:09.
# usage: inject_to.pl IFACE DST_MAC RATE_500K COUNT
use strict; use warnings; use Time::HiRes qw(usleep);
my ($if, $dst, $rate, $count) = @ARGV;
open(my $fh, '<', "/sys/class/net/$if/ifindex") or die "no $if"; my $idx = <$fh>; chomp $idx;
socket(my $s, 17, 3, 0) or die "socket: $!";
bind($s, pack("S n i S C C a8", 17, 0x0003, $idx, 0, 0, 0, "")) or die "bind: $!";
my $rt = pack("C C v V C", 0, 0, 9, 1 << 2, $rate);
my $a1 = pack("C6", map { hex } split /:/, $dst);
my $a2 = pack("C6", 0x02, 0, 0, 0, 0, 0x09);
for my $i (0 .. $count - 1) {
	my $f = pack("v v", 0x0008, 0) . $a1 . $a2 . $a2 . pack("v", ($i & 0xfff) << 4) . "ACKTEST" . pack("v", $i);
	send($s, $rt . $f, 0) or warn "send: $!";
	usleep(20000);
}
