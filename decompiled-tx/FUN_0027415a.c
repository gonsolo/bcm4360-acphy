
ulong FUN_0027415a(long param_1,ulong param_2)

{
  long lVar1;
  byte bVar2;
  undefined8 in_RAX;
  ulong uVar3;
  short sVar4;
  
  lVar1 = *(long *)(param_1 + 0x550);
  uVar3 = CONCAT62((int6)((ulong)in_RAX >> 0x10),*(undefined2 *)(lVar1 + 10));
  sVar4 = (short)*(undefined4 *)(*(long *)(param_1 + 0x40) + 8);
  if ((sVar4 == 0xb) || (sVar4 == 7)) {
    bVar2 = wlc_stf_txcore_get();
    uVar3 = (ulong)bVar2 << 6;
  }
  else {
    if (((param_2 & 0x300) != 0) || (*(char *)(lVar1 + 8) == '\x03')) {
      uVar3 = (ulong)*(byte *)(lVar1 + 1) << 6;
    }
    uVar3 = uVar3 & 0xffffffffffff03c0;
  }
  return uVar3;
}

