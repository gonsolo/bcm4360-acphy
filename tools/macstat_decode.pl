#!/usr/bin/env perl
# Decode d11 ucode MAC statistics (SHM 0xe0, 64 u16) from either a
# macstat_wl.bt trace or b43 "macstat:" dmesg lines; print first/last and delta.
use strict;
my @n = qw(txallfrm txrtsfrm txctsfrm txackfrm txdnlfrm txbcnfrm txfunfl0 txfunfl1 txfunfl2
  txfunfl3 txfunfl4 txfunfl5 txfunfl6 txfunfl7 txtplunfl txphyerr pktengrxducast pktengrxdmcast
  rxfrmtoolong rxfrmtooshrt rxinvmachdr rxbadfcs rxbadplcp rxcrsglitch rxstrt rxdfrmucastmbss
  rxmfrmucastmbss rxcfrmucast rxrtsucast rxctsucast rxackucast rxdfrmocast rxmfrmocast rxcfrmocast
  rxrtsocast rxctsocast rxdfrmmcast rxmfrmmcast rxcfrmmcast rxbeaconmbss rxdfrmucastobss
  rxbeaconobss rxrsptmout bcntxcancl pad rxf0ovfl rxf1ovfl rxf2ovfl txsfovfl pmqovfl);
my (@snaps, @cur, $w);
while (<>) {
  if (/^C 000100([0-9a-f]{2})/) { $w = hex($1) - 0x38; next; }
  if (/^W16([46]) ([0-9a-f]{4})/ && defined $w && $w >= 0 && $w < 32) {
    $cur[$w * 2 + ($1 eq '6')] = hex($2);
    if ($w == 31 && $1 eq '6') { push @snaps, [@cur]; @cur = (); }
    next;
  }
  if (/\[\s*([\d.]+)\].*macstat:((?: [0-9a-f]{4}){64})/) { push @snaps, [map { hex } split ' ', $2]; }
}
die "need 2 snapshots, got " . scalar(@snaps) . "\n" if @snaps < 2;
my ($a, $b) = ($snaps[0], $snaps[-1]);
printf "%d snapshots\n%-18s %6s %6s %6s\n", scalar(@snaps), "counter", "first", "last", "delta";
for my $i (0 .. $#n) {
  next if $n[$i] eq 'pad';
  printf "%-18s %6d %6d %6d\n", $n[$i], $a->[$i], $b->[$i], ($b->[$i] - $a->[$i]) & 0xffff;
}
