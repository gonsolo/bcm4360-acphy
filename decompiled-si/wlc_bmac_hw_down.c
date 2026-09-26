
void wlc_bmac_hw_down(long *param_1)

{
  int iVar1;
  long lVar2;
  
  if (*(int *)(param_1[0x17] + 4) == 1) {
    wlc_bmac_set_ctrl_SROM();
    if (((((*(byte *)((long)param_1 + 0x8c) & 1) != 0) && (-1 < (char)param_1[0x12])) &&
        ((*(byte *)(param_1[0x17] + 0x1c) & 1) != 0)) &&
       ((*(byte *)((long)param_1 + 0xa7) & 0x20) != 0)) {
      si_seci_down();
    }
    wlc_bmac_set_ctrl_bt_shd0(param_1,0);
    if (*(long *)(*param_1 + 0x750) != 0) {
      si_survive_perst_war(param_1[0x17],0,0x204,0);
      si_pmu_res_req_timer_clr(param_1[0x17]);
    }
    si_pci_down(param_1[0x17]);
  }
  iVar1 = *(int *)(param_1[0x17] + 0x3c);
  if (((iVar1 == 0x4352) || (iVar1 == 0x4360)) || (iVar1 == 0xaa06)) {
    si_pmu_rfldo(param_1[0x17],0);
  }
  wlc_bmac_xtal(param_1,0);
  lVar2 = param_1[0x17];
  if (((*(int *)(lVar2 + 0x3c) == 0x4350) && (*(int *)(lVar2 + 0x40) == 0)) &&
     ((*(uint *)(lVar2 + 0x48) & 0x700000) == 0x300000)) {
    si_pmu_chipcontrol(lVar2,2,0x80000,0);
  }
  return;
}

