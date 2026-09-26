
void wlc_bmac_bw_reset(long param_1)

{
  undefined4 uVar1;
  
  if ((*(long *)(param_1 + 0xe8) != 0) && (*(long *)(*(long *)(param_1 + 0xe8) + 0x28) != 0)) {
    uVar1 = wlc_phy_clk_bwbits();
    si_core_cflags(*(undefined8 *)(param_1 + 0xb8),0xc0,uVar1);
  }
  return;
}

