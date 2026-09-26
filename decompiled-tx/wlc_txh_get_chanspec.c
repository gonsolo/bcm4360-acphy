
ulong wlc_txh_get_chanspec(long *param_1,long param_2)

{
  long lVar1;
  ulong uVar2;
  
  lVar1 = *(long *)(param_2 + 0x18);
  if (*(uint *)(*param_1 + 0x14) < 0x28) {
    uVar2 = (ulong)*(byte *)(lVar1 + 0x15);
  }
  else {
    uVar2 = CONCAT62((int6)((ulong)lVar1 >> 0x10),*(undefined2 *)(lVar1 + 6));
  }
  return uVar2;
}

