
int wlc_bmac_wowlucode_start(long param_1)

{
  long lVar1;
  long lVar2;
  uint uVar3;
  ulong uVar4;
  int iVar5;
  
  lVar2 = *(long *)(param_1 + 0xd0);
  lVar1 = lVar2 + 0x128;
  osl_writel(0xffffffff,lVar1);
  wlc_bmac_mctrl(param_1,0xffffffff,0x4020402);
  iVar5 = 0xf4249;
  while( true ) {
    uVar4 = osl_readl(lVar1);
    if (((uVar4 & 1) != 0) || (iVar5 == 9)) break;
    iVar5 = iVar5 + -10;
    osl_delay(10);
  }
  uVar3 = osl_readl(lVar2 + 0x128);
  return -(uint)((uVar3 & 1) == 0);
}

