
void wlc_bmac_hw_up(long *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  long lVar4;
  undefined4 *puVar5;
  uint uVar6;
  
  if (*(char *)(*(long *)*param_1 + 0x40) == '\0') {
    if (((long *)*param_1)[0xea] != 0) {
      si_survive_perst_war(param_1[0x17],1,0,0);
    }
    lVar4 = param_1[0x17];
    if (*(int *)(lVar4 + 4) == 1) {
      si_ldo_war(lVar4,*(undefined4 *)(lVar4 + 0x3c));
    }
    if (*(int *)(param_1[0x17] + 0x3c) == 0xa886) {
      si_pmu_res_init(param_1[0x17],param_1[2]);
    }
    if ((*(int *)(param_1[0x17] + 4) == 1) && (0x27 < *(uint *)((long)param_1 + 0x84))) {
      si_pmu_res_init(param_1[0x17],param_1[2]);
    }
    lVar4 = param_1[0x17];
    if ((*(int *)(lVar4 + 4) == 1) && (*(int *)(lVar4 + 0x3c) == 0x4350)) {
      si_pmu_chip_init(lVar4,param_1[2]);
    }
    wlc_bmac_xtal(param_1,1);
    si_clkctl_init(param_1[0x17]);
    FUN_001655c7(param_1,0);
    si_pcie_ltr_war(param_1[0x17]);
    FUN_0016407d(param_1);
    if (*(int *)(param_1[0x17] + 4) == 1) {
      iVar1 = *(int *)(param_1[0x17] + 0x3c);
      if (((iVar1 == 0xa9c4) || (iVar1 == 0x4360)) || (iVar1 == 0x4352)) {
        wlc_bmac_4360_pcie2_war(param_1,(int)param_1[0x38]);
      }
      si_pci_fixcfg(param_1[0x17]);
      iVar1 = *(int *)(param_1[0x17] + 0x3c);
      if ((iVar1 - 0xa8d8U < 2) || (iVar1 == 0xa99d)) {
        lVar4 = si_setcore(param_1[0x17],0x812,0);
        param_1[0x1a] = lVar4;
      }
      if (*(int *)(param_1[0x17] + 0x3c) == 0x4313) {
        si_clk_pmu_htavail_set(param_1[0x17],0);
        si_pmu_synth_pwrsw_4313_war(param_1[0x17]);
      }
    }
    uVar2 = *(uint *)(param_1 + 0x30);
    lVar4 = param_1[0x33];
    if (*(char *)((long)param_1 + 0x187) != '\0') {
      si_gpiocontrol(param_1[0x17],uVar2,0,0);
      si_gpioled(param_1[0x17],uVar2,uVar2);
      uVar6 = 0;
      for (puVar5 = (undefined4 *)(lVar4 + 8); puVar5 != (undefined4 *)(lVar4 + 0x308);
          puVar5 = puVar5 + 6) {
        if (*(char *)(puVar5 + 1) == '\0') {
          uVar6 = uVar6 | 1 << ((byte)*puVar5 & 0x1f);
        }
      }
      if ((*(byte *)((long)param_1 + 0x91) & 8) == 0) {
        uVar3 = si_gpioout(param_1[0x17],uVar2,uVar6 & uVar2,0);
        *(undefined4 *)(lVar4 + 0x308) = uVar3;
        si_gpioouten(param_1[0x17],uVar2,uVar2,0);
      }
      else {
        si_gpioout(param_1[0x17],uVar2,~(uVar6 & uVar2) & uVar2,0);
        uVar3 = si_gpioouten(param_1[0x17],uVar2,0,0);
        *(undefined4 *)(lVar4 + 0x308) = uVar3;
        if (0x13 < *(int *)(param_1[0x17] + 0x14)) {
          si_gpiopull(param_1[0x17],1,uVar2,0);
          si_gpiopull(param_1[0x17],0,uVar2,0);
        }
      }
      *(uint *)(lVar4 + 0x30c) = uVar2;
    }
    wlc_phy_por_inform(*(undefined8 *)(param_1[0x1d] + 0x28));
    *(undefined1 *)((long)param_1 + 0xae) = 0;
    *(undefined1 *)(*(long *)*param_1 + 0x40) = 1;
    if (((*(uint *)((long)param_1 + 0x8c) & 0x800) != 0) &&
       (*(int *)(param_1[0x17] + 0x3c) == 0x4313)) {
      if ((*(ushort *)((long)param_1 + 0x8a) < 0x1250) ||
         ((*(uint *)((long)param_1 + 0x8c) & 0x400000) == 0)) {
        si_epa_4313war();
      }
      else {
        si_btcombo_p250_4313_war();
      }
    }
    if ((*(int *)(param_1[0x17] + 0x3c) == 0xa8dc) &&
       ((*(byte *)((long)param_1 + 0x8e) & 0x40) != 0)) {
      si_btcombo_43228_war();
      si_pmu_chipcontrol(param_1[0x17],1,0x20,0x20);
    }
  }
  return;
}

