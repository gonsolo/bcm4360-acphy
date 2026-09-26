
void wlc_bmac_phy_iovar_dispatch(long param_1,undefined8 param_2,undefined2 param_3)

{
  wlc_phy_iovar_dispatch(*(undefined8 *)(*(long *)(param_1 + 0xe8) + 0x28),param_2,param_3);
  return;
}

