
ulong wlc_rate_legacy_phyctl(int param_1)

{
  uint uVar1;
  ulong uVar2;
  int *piVar3;
  
  piVar3 = &DAT_00593990;
  uVar2 = 0;
  do {
    if (param_1 == *piVar3) {
      return (ulong)(byte)(&DAT_00593994)[uVar2 * 8];
    }
    uVar1 = (int)uVar2 + 1;
    uVar2 = (ulong)uVar1;
    piVar3 = piVar3 + 2;
  } while (uVar1 != 0xc);
  return 0xffffffff;
}

