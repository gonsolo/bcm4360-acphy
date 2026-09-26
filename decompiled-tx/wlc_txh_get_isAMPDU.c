
ushort wlc_txh_get_isAMPDU(long *param_1,long param_2)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)(param_2 + 6);
  if (*(uint *)(*param_1 + 0x14) < 0x28) {
    uVar1 = CONCAT11((char)(uVar1 >> 8),(uVar1 & 0x600) != 0);
  }
  else {
    uVar1 = uVar1 >> 6 & 1;
  }
  return uVar1;
}

