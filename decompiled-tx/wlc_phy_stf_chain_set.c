
void wlc_phy_stf_chain_set(long param_1,undefined1 param_2,undefined1 param_3)

{
  int iVar1;
  
  *(undefined1 *)(*(long *)(param_1 + 0x20) + 0xa6) = param_2;
  iVar1 = *(int *)(param_1 + 0x160);
  if (iVar1 == 4) {
    wlc_phy_rxcore_setstate_nphy(param_1,param_3,0xf < *(uint *)(param_1 + 0x164));
  }
  else if (iVar1 == 7) {
    wlc_phy_rxcore_setstate_htphy(param_1,param_3);
  }
  else if (iVar1 == 0xb) {
    wlc_phy_rxcore_setstate_acphy(param_1,param_3);
  }
  return;
}

