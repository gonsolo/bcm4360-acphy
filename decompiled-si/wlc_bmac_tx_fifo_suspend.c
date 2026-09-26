
void wlc_bmac_tx_fifo_suspend(long param_1,uint param_2)

{
  byte bVar1;
  short sVar2;
  
  bVar1 = (byte)(1 << ((byte)param_2 & 0x1f));
  if ((bVar1 & *(byte *)(param_1 + 0x164)) != bVar1) {
    if (*(byte *)(param_1 + 0x164) == 0) {
      wlc_ucode_wake_override_set(param_1,8);
    }
    *(byte *)(param_1 + 0x164) = *(byte *)(param_1 + 0x164) | bVar1;
    if (*(long *)(param_1 + 0x20 + (ulong)param_2 * 8) != 0) {
      bVar1 = osl_readl(*(long *)(param_1 + 0xd0) + 0x120);
      bVar1 = (bVar1 ^ 1) & 1;
      sVar2 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
      if (((((sVar2 == 6) || (sVar2 == 4)) || (sVar2 == 8)) ||
          (((sVar2 == 10 || (sVar2 == 0xb)) || (sVar2 == 7)))) && (bVar1 == 0)) {
        wlc_bmac_suspend_mac_and_wait(param_1);
      }
      (**(code **)(**(long **)(param_1 + 0x20 + (ulong)param_2 * 8) + 0x20))();
      sVar2 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
      if ((((sVar2 == 6) || (sVar2 == 4)) ||
          ((sVar2 == 8 || (((sVar2 == 10 || (sVar2 == 0xb)) || (sVar2 == 7)))))) && (bVar1 == 0)) {
        wlc_bmac_enable_mac(param_1);
      }
    }
  }
  return;
}

