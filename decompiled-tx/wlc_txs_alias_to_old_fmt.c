
ulong wlc_txs_alias_to_old_fmt(long *param_1,long param_2)

{
  uint uVar1;
  ulong uVar2;
  
  if (*(uint *)(*param_1 + 0x14) < 0x28) {
    uVar2 = CONCAT62((int6)((ulong)*param_1 >> 0x10),*(undefined2 *)(param_2 + 0xc));
  }
  else {
    uVar1 = ~-(uint)(*(char *)(param_2 + 1) == '\0') & 0x40;
    if (*(char *)(param_2 + 2) != '\0') {
      uVar1 = uVar1 | 0x80;
    }
    if (*(byte *)(param_2 + 4) != 0) {
      uVar1 = uVar1 | (uint)*(byte *)(param_2 + 4) << 2;
    }
    if (*(char *)(param_2 + 5) != '\0') {
      uVar1 = uVar1 | 2;
    }
    uVar2 = (ulong)(uVar1 | (uint)*(ushort *)(param_2 + 8) << 0xc);
  }
  return uVar2;
}

