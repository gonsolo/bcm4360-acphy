
void si_pmu_pll_off_PARR(long param_1,undefined8 param_2,undefined4 *param_3,undefined4 *param_4,
                        undefined4 *param_5)

{
  long lVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  ulong uVar6;
  int iVar7;
  undefined4 local_40;
  undefined4 local_3c [3];
  
  lVar5 = si_switch_core(param_1,0x800,local_3c,&local_40);
  uVar2 = osl_readl(lVar5 + 0x618);
  lVar1 = lVar5 + 0x61c;
  *param_3 = uVar2;
  uVar2 = osl_readl(lVar1);
  *param_4 = uVar2;
  uVar2 = osl_readl(lVar5 + 0x1e0);
  *param_5 = uVar2;
  uVar3 = FUN_0011192d(param_1);
  if (uVar3 != 0) {
    if ((*(int *)(param_1 + 0x3c) == 0x4350) || (*(int *)(param_1 + 0x3c) == 0x4335)) {
      uVar6 = osl_readl(lVar5 + 0x1e0);
      if ((uVar6 & 0x20000) == 0) {
        si_pmu_wait_for_steady_state(param_2,lVar5);
      }
    }
    else {
      iVar7 = 0x4e29;
      uVar4 = osl_readl(lVar1);
      osl_writel(uVar4 | uVar3,lVar1);
      while( true ) {
        uVar6 = osl_readl(lVar5 + 0x1e0);
        if (((uVar6 & 0x20000) != 0) || (iVar7 == 9)) break;
        iVar7 = iVar7 + -10;
        osl_delay(10);
      }
    }
    uVar4 = osl_readl(lVar5 + 0x618);
    osl_writel(uVar4 & ~uVar3,lVar5 + 0x618);
    uVar4 = osl_readl(lVar5 + 0x61c);
    osl_writel(uVar4 & ~uVar3,lVar5 + 0x61c);
    si_restore_core(param_1,local_3c[0],local_40);
  }
  return;
}

