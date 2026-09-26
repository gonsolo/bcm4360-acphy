
void si_pmu_gband_spurwar(long param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  long lVar8;
  ulong uVar9;
  undefined8 uVar10;
  int iVar11;
  undefined4 local_40;
  undefined4 local_3c [3];
  
  if ((*(int *)(param_1 + 0x3c) == 0xa99c) || (*(int *)(param_1 + 0x3c) == 0xa8d6)) {
    lVar8 = si_switch_core(param_1,0x800,local_3c,&local_40);
    lVar1 = lVar8 + 0x1e0;
    lVar2 = lVar8 + 0x618;
    lVar3 = lVar8 + 0x61c;
    uVar4 = osl_readl(lVar1);
    uVar5 = osl_readl(lVar1);
    osl_writel(uVar5 & 0xffffffed,lVar1);
    uVar6 = osl_readl(lVar2);
    uVar7 = osl_readl(lVar3);
    uVar5 = osl_readl(lVar2);
    osl_writel(uVar5 & 0xffffffdf,lVar2);
    uVar5 = osl_readl(lVar3);
    iVar11 = 0x4e29;
    osl_writel(uVar5 & 0xffffffdf,lVar3);
    while( true ) {
      uVar9 = osl_readl(lVar1);
      if (((uVar9 & 0x20000) == 0) || (iVar11 == 9)) break;
      iVar11 = iVar11 + -10;
      osl_delay(10);
    }
    lVar1 = lVar8 + 0x618;
    lVar2 = lVar8 + 0x61c;
    lVar3 = lVar8 + 0x664;
    uVar5 = osl_readl(lVar1);
    osl_writel(uVar5 & 0xffffffef,lVar1);
    uVar5 = osl_readl(lVar2);
    osl_writel(uVar5 & 0xffffffef,lVar2);
    osl_delay(0x96);
    osl_writel(2,lVar8 + 0x660);
    uVar10 = osl_readl(lVar3);
    osl_writel((uint)CONCAT62((int6)((ulong)uVar10 >> 0x10),(ushort)(byte)uVar10) | 0xc00,lVar3);
    osl_writel(5,lVar8 + 0x660);
    uVar5 = osl_readl(lVar3);
    osl_writel(uVar5 & 0xff0000ff | 0x111100,lVar3);
    uVar5 = osl_readl(lVar8 + 0x600);
    iVar11 = 0x4e29;
    osl_writel(uVar5 | 0x400,lVar8 + 0x600);
    osl_delay(100);
    osl_writel(uVar7,lVar2);
    osl_delay(100);
    osl_writel(uVar6,lVar1);
    osl_delay(100);
    while( true ) {
      uVar9 = osl_readl(lVar8 + 0x1e0);
      if (((uVar9 & 0x20000) != 0) || (iVar11 == 9)) break;
      iVar11 = iVar11 + -10;
      osl_delay(10);
    }
    osl_writel(uVar4,lVar8 + 0x1e0);
    si_restore_core(param_1,local_3c[0],local_40);
  }
  return;
}

