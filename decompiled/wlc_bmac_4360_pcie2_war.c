
void wlc_bmac_4360_pcie2_war(long *param_1,uint param_2)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  
  lVar1 = param_1[0x17];
  iVar2 = *(int *)(lVar1 + 0x3c);
  if ((((iVar2 == 0xa9c4) || (iVar2 == 0x4360)) || (iVar2 == 0x4352)) &&
     ((*(uint *)(lVar1 + 0x40) < 3 && (*(int *)(lVar1 + 4) == 1)))) {
    iVar2 = wl_osl_pcie_rc(*(undefined8 *)(*param_1 + 0x10),0,0);
    if ((iVar2 != 1) && (do_4360_pcie2_war == 0)) {
      do_4360_pcie2_war = 1;
      si_corereg(param_1[0x17],3,0x120,0xffffffff,0xbc);
      uVar3 = si_corereg(param_1[0x17],3,0x124,0,0);
      if ((uVar3 >> 0x10 & 0xf) != 2) {
        si_pcie_configspace_cache(param_1[0x17]);
        uVar3 = (uint)(param_2 % 0x14 != 0);
        si_pmu_pllcontrol(param_1[0x17],10,0xffffffff,param_2 / 0x14 << 7 | 2 | (-uVar3 & 3) << 4);
        if (uVar3 != 0) {
          si_pmu_pllcontrol(param_1[0x17],0xb,0xffffffff,(ulong)(param_2 % 0x14 << 0x18) / 0x14);
        }
        si_pmu_pllupd(param_1[0x17]);
        si_watchdog(param_1[0x17],2);
        osl_delay(2000);
        wl_osl_pcie_rc(*(undefined8 *)(*param_1 + 0x10),1,0);
        osl_delay(50000);
        si_pcie_configspace_restore(param_1[0x17]);
        si_corereg(param_1[0x17],3,0x120,0xffffffff,0x4dc);
        uVar3 = si_corereg(param_1[0x17],3,0x124,0,0);
        si_corereg(param_1[0x17],3,0x120,0xffffffff,0x4dc);
        si_corereg(param_1[0x17],3,0x124,0xffffffff,uVar3 & 0xfffffff0 | 2);
        si_corereg(param_1[0x17],3,0x120,0xffffffff,0x1800);
        uVar3 = si_corereg(param_1[0x17],3,0x124,0,0);
        si_corereg(param_1[0x17],3,0x120,0xffffffff,0x1800);
        si_corereg(param_1[0x17],3,0x124,0xffffffff,uVar3 & 0xfffffff0 | 2);
        si_corereg(param_1[0x17],3,0x120,0xffffffff,0x1800);
        si_corereg(param_1[0x17],3,0x124,0xffffffff,uVar3 & 0xfffffff0);
        osl_delay(1000);
        si_corereg(param_1[0x17],3,0x120,0xffffffff,0xbc);
        si_corereg(param_1[0x17],3,0x124,0,0);
      }
    }
  }
  return;
}

