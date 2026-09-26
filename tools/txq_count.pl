#!/usr/bin/env perl
# Count unique injected test frames (B43Q marker) per tag/rate/len in `tcpdump -r X -xx` output.
use strict; use warnings;
my (%seen, $hex);
sub flush { return unless $hex; while ($hex =~ /42343351(..)(..)(....)(....)/g) {
	my ($tag, $rate, $len, $seq) = (hex $1, hex $2, hex(substr($3,2,2).substr($3,0,2)), hex(substr($4,2,2).substr($4,0,2)));
	$seen{"$tag $rate $len"}{$seq} = 1; } $hex = ""; }
while (<>) {
	if (/^\S/) { flush(); next; }
	if (/^\s+0x[0-9a-f]+:\s+((?:[0-9a-f]{4}\s?)+)/) { (my $h = $1) =~ s/\s//g; $hex .= $h; }
}
flush();
print "$_ " . scalar(keys %{$seen{$_}}) . "\n" for sort keys %seen;
