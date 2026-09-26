
void wlc_bmac_set_shortslot(long param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x102) = param_2;
  if ((**(int **)(param_1 + 0xe8) == 2) && (*(char *)(param_1 + 0x10c) != '\0')) {
    wlc_bmac_suspend_mac_and_wait();
    FUN_00163456(param_1,param_2);
    wlc_bmac_enable_mac(param_1);
  }
  return;
}

