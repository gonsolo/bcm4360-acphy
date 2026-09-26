
void wlc_bmac_fifoerrors(undefined8 *param_1)

{
  int *piVar1;
  long lVar2;
  ushort uVar3;
  ushort uVar4;
  uint uVar5;
  ulong uVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  
  uVar6 = 0;
  lVar2 = param_1[0x1a];
  do {
    uVar3 = osl_readl(lVar2 + 0x20 + uVar6 * 8);
    uVar4 = uVar3 & 0xdc00;
    if (uVar4 != 0) {
      bVar7 = (uVar3 & 0x4000) != 0;
      if (bVar7) {
        piVar1 = (int *)(*(long *)(*(long *)*param_1 + 0xa0) + 0x80);
        *piVar1 = *piVar1 + 1;
      }
      bVar8 = (uVar3 & 0x400) != 0;
      if (bVar8) {
        piVar1 = (int *)(*(long *)(*(long *)*param_1 + 0xa0) + 0xa8);
        *piVar1 = *piVar1 + 1;
      }
      bVar9 = (uVar3 & 0x800) != 0;
      if (bVar9) {
        piVar1 = (int *)(*(long *)(*(long *)*param_1 + 0xa0) + 0xac);
        *piVar1 = *piVar1 + 1;
      }
      bVar10 = (uVar3 & 0x1000) != 0;
      if (bVar10) {
        piVar1 = (int *)(*(long *)(*(long *)*param_1 + 0xa0) + 0xb0);
        *piVar1 = *piVar1 + 1;
      }
      if ((short)uVar4 < 0) {
        piVar1 = (int *)(*(long *)(*(long *)*param_1 + 0xa0) + 0x34);
        *piVar1 = *piVar1 + 1;
LAB_0016548c:
        wlc_fatal_error(*param_1);
        return;
      }
      if (bVar10 || (bVar9 || (bVar8 || bVar7))) goto LAB_0016548c;
      osl_writel(uVar4,lVar2 + 0x20 + uVar6 * 8);
    }
    uVar5 = (int)uVar6 + 1;
    uVar6 = (ulong)uVar5;
    if (uVar5 == 6) {
      return;
    }
  } while( true );
}

