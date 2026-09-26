
undefined8 wlc_bmac_radio_hw(long param_1,char param_2,char param_3)

{
  char cVar1;
  uint uVar2;
  undefined8 uVar3;
  long lVar4;
  
  cVar1 = si_iscoreup(*(undefined8 *)(param_1 + 0xb8));
  uVar3 = 0;
  if (cVar1 != '\0') {
    if (param_2 == '\0') {
      wlc_bmac_suspend_mac_and_wait(param_1);
      wlc_phy_switch_radio(*(undefined8 *)(*(long *)(param_1 + 0xe8) + 0x28),0);
      if (param_3 == '\0') {
        wlc_phy_anacore(*(undefined8 *)(*(long *)(param_1 + 0xe8) + 0x28),0);
      }
      if ((*(byte *)(*(long *)(param_1 + 0xb8) + 0x1b) & 0x10) == 0) {
        return 1;
      }
      si_pmu_radio_enable(*(long *)(param_1 + 0xb8),0);
      lVar4 = *(long *)(param_1 + 0xd0) + 0x1e0;
      uVar2 = osl_readl(lVar4);
      osl_writel(uVar2 | 0x20,lVar4);
    }
    else {
      if ((*(byte *)(*(long *)(param_1 + 0xb8) + 0x1b) & 0x10) != 0) {
        lVar4 = *(long *)(param_1 + 0xd0) + 0x1e0;
        uVar2 = osl_readl(lVar4);
        osl_writel(uVar2 & 0xffffffdf,lVar4);
        si_pmu_radio_enable(*(undefined8 *)(param_1 + 0xb8),1);
      }
      if (param_3 == '\0') {
        wlc_phy_anacore(*(undefined8 *)(*(long *)(param_1 + 0xe8) + 0x28),1);
      }
      wlc_phy_switch_radio(*(undefined8 *)(*(long *)(param_1 + 0xe8) + 0x28),1);
      wlc_bmac_enable_mac(param_1);
    }
    uVar3 = 1;
  }
  return uVar3;
}

