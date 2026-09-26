
undefined1  [16] wlc_scb_rssi_chain(long param_1,int param_2)

{
  int iVar1;
  ulong uVar2;
  int *piVar3;
  ulong uVar4;
  char cVar5;
  undefined1 auVar6 [16];
  
  iVar1 = 0;
  uVar4 = 0;
  piVar3 = (int *)(param_1 + 0x16c + (long)param_2 * 0x20);
  cVar5 = '\0';
  do {
    if (*piVar3 != 0) {
      uVar4 = (ulong)(uint)((int)uVar4 + *piVar3);
      cVar5 = cVar5 + '\x01';
    }
    iVar1 = iVar1 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar1 != 8);
  uVar2 = 0;
  if (cVar5 != '\0') {
    uVar2 = (long)(int)uVar4 / (long)(int)cVar5 & 0xffffffff;
    uVar4 = (long)(int)uVar4 % (long)(int)cVar5 & 0xffffffff;
  }
  auVar6._8_8_ = uVar4;
  auVar6._0_8_ = uVar2;
  return auVar6;
}

