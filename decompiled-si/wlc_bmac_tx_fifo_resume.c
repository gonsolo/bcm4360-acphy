
void wlc_bmac_tx_fifo_resume(long param_1,ulong param_2)

{
  long *plVar1;
  byte bVar2;
  
  plVar1 = *(long **)(param_1 + 0x20 + (param_2 & 0xffffffff) * 8);
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x28))();
  }
  if (*(byte *)(param_1 + 0x164) != 0) {
    bVar2 = (byte)param_2 & 0x1f;
    bVar2 = *(byte *)(param_1 + 0x164) & ((byte)(-2 << bVar2) | (byte)(0xfffffffe >> 0x20 - bVar2));
    *(byte *)(param_1 + 0x164) = bVar2;
    if (bVar2 == 0) {
      wlc_ucode_wake_override_clear(param_1,8);
    }
  }
  return;
}

