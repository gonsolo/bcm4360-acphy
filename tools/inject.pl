#!/usr/bin/env perl
# Inject test data frames on a monitor interface (radiotap: rate + no-ACK).
# usage: inject.pl IFACE RATE_500K LEN COUNT [TAG]
#   frame: data, addr1 02:00:00:00:00:01, payload "B43Q" TAG rate len seq + pad
use strict;
use warnings;
use Time::HiRes qw(usleep);

my ($if, $rate, $len, $count, $tag) = @ARGV;
die "usage: inject.pl IFACE RATE_500K LEN COUNT [TAG]\n" unless defined $count;
$tag //= 0;

open(my $fh, '<', "/sys/class/net/$if/ifindex") or die "no $if: $!";
my $ifindex = <$fh>;
chomp $ifindex;

socket(my $s, 17, 3, 0) or die "socket: $!";	# PF_PACKET, SOCK_RAW
my $sll = pack("S n i S C C a8", 17, 0x0003, $ifindex, 0, 0, 0, "");
bind($s, $sll) or die "bind: $!";

# radiotap: version 0, len 12, present = RATE (bit 2) | TX_FLAGS (bit 15)
my $rt = pack("C C v V C x v", 0, 0, 12, (1 << 2) | (1 << 15), $rate, 0x0008);
my $a1 = pack("C6", 0x02, 0, 0, 0, 0, 0x01);
my $a2 = pack("C6", 0x02, 0, 0, 0, 0, 0x02);
my $a3 = pack("C6", 0x02, 0, 0, 0, 0, 0x03);

for my $i (0 .. $count - 1) {
	my $hdr = pack("v v", 0x0008, 0) . $a1 . $a2 . $a3 . pack("v", ($i & 0xfff) << 4);
	my $body = "B43Q" . pack("C C v v", $tag, $rate, $len, $i);
	my $need = $len - length($hdr) - 4;	# frame length incl. FCS
	$body .= chr(0x55) x ($need - length($body)) if $need > length($body);
	send($s, $rt . $hdr . $body, 0) or warn "send: $!";
	usleep(5000);
}
