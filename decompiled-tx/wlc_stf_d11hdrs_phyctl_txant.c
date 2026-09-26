
undefined8 wlc_stf_d11hdrs_phyctl_txant(long param_1)

{
  undefined8 uVar1;
  short sVar2;
  
  uVar1 = CONCAT62((int6)((ulong)*(long *)(param_1 + 0x550) >> 0x10),
                   *(undefined2 *)(*(long *)(param_1 + 0x550) + 10));
  sVar2 = (short)*(undefined4 *)(*(long *)(param_1 + 0x40) + 8);
  if (((sVar2 == 7) || (sVar2 == 4)) || (sVar2 == 0xb)) {
    uVar1 = FUN_0027415a();
  }
  return uVar1;
}

