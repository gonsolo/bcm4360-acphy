#!/usr/bin/env perl
# Inject directed probe requests from our own MAC so the AP answers with
# unicast probe responses; the ucode must ACK them, or the AP retries each
# response (retry bit set). Firmware ACK test that needs no association.
# usage: inject_probe.pl IFACE SA BSSID SSID RATE_500K COUNT
use strict; use warnings; use Time::HiRes qw(usleep);
my ($if, $sa, $bssid, $ssid, $rate, $count) = @ARGV;
die "usage: inject_probe.pl IFACE SA BSSID SSID RATE_500K COUNT\n" unless defined $count;
open(my $fh, '<', "/sys/class/net/$if/ifindex") or die "no $if"; my $idx = <$fh>; chomp $idx;
socket(my $s, 17, 3, 0) or die "socket: $!";
bind($s, pack("S n i S C C a8", 17, 0x0003, $idx, 0, 0, 0, "")) or die "bind: $!";
my $rt = pack("C C v V C", 0, 0, 9, 1 << 2, $rate);
my $mac = sub { pack("C6", map { hex } split /:/, shift) };
my $ie = pack("C C", 0, length $ssid) . $ssid;
$ie .= $rate > 22 ? pack("C C C8", 1, 8, 0x8c, 0x12, 0x98, 0x24, 0xb0, 0x48, 0x60, 0x6c)
		  : pack("C C C4", 1, 4, 0x82, 0x84, 0x8b, 0x96);
for my $i (0 .. $count - 1) {
	my $f = pack("v v", 0x0040, 0) . $mac->($bssid) . $mac->($sa) . $mac->($bssid) .
		pack("v", ($i & 0xfff) << 4) . $ie;
	send($s, $rt . $f, 0) or warn "send: $!";
	usleep(100000);
}
