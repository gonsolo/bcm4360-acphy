
void FUN_0019330c(long param_1,undefined2 param_2)

{
  wlapi_bmac_write_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0xb8,param_2);
  wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  wlc_phyreg_enter(param_1);
  wlc_phy_txpwrctrl_enable_acphy(param_1,0);
  return;
}

