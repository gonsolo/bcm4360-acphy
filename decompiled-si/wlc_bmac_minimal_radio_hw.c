
void wlc_bmac_minimal_radio_hw(long *param_1,char param_2)

{
  uint uVar1;
  long lVar2;
  
  lVar2 = *param_1;
  if ((0xc < *(uint *)((long)param_1 + 0x84)) && ((*(byte *)(param_1[0x17] + 0x1b) & 0x10) != 0)) {
    if (param_2 == '\x01') {
      lVar2 = *(long *)(lVar2 + 0x18) + 0x1e0;
      uVar1 = osl_readl(lVar2);
      osl_writel(uVar1 & 0xffffffdf,lVar2);
      si_pmu_radio_enable(param_1[0x17],1);
    }
    else {
      si_pmu_radio_enable(param_1[0x17],0);
      lVar2 = *(long *)(lVar2 + 0x18) + 0x1e0;
      uVar1 = osl_readl(lVar2);
      osl_writel(uVar1 | 0x20,lVar2);
    }
  }
  return;
}

