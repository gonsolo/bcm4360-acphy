
void wlc_bmac_xtal(long param_1,char param_2)

{
  long lVar1;
  
  if ((param_2 != '\0') || (*(int *)(param_1 + 0x160) == 0)) {
    if (*(long *)(param_1 + 0xb8) != 0) {
      si_clkctl_xtal(*(long *)(param_1 + 0xb8),3,param_2);
    }
    *(char *)(param_1 + 0x187) = param_2;
    if (param_2 == '\0') {
      *(undefined1 *)(param_1 + 0x186) = 0;
      if ((*(long *)(param_1 + 0xe8) != 0) &&
         (lVar1 = *(long *)(*(long *)(param_1 + 0xe8) + 0x28), lVar1 != 0)) {
        wlc_phy_hw_clk_state_upd(lVar1,0);
      }
    }
  }
  return;
}

