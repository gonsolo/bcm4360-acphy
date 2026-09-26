
void wlc_bmac_bw_set(long param_1,undefined2 param_2)

{
  undefined2 uVar1;
  
  wlc_phy_bw_state_set(*(undefined8 *)(*(long *)(param_1 + 0xe8) + 0x28),param_2);
  if (*(uint *)(param_1 + 0x84) < 0x11) {
    osl_readl(*(long *)(param_1 + 0xd0) + 0x120);
  }
  if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) == 0xb) {
    wlc_bmac_bw_reset(param_1);
  }
  else {
    wlc_bmac_phy_reset(param_1);
  }
  if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 0xb) {
    uVar1 = wlc_phy_chanspec_get(*(undefined8 *)(*(long *)(param_1 + 0xe8) + 0x28));
    wlc_phy_init(*(undefined8 *)(*(long *)(param_1 + 0xe8) + 0x28),uVar1);
  }
  return;
}

