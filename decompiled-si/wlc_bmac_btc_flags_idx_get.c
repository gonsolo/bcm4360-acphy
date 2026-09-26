
ulong wlc_bmac_btc_flags_idx_get(long param_1,byte param_2)

{
  ushort uVar1;
  ulong uVar2;
  
  uVar2 = 0xbad;
  if (param_2 < 9) {
    uVar1 = 0;
    if (*(long *)(param_1 + 0xf0) != 0) {
      uVar1 = *(ushort *)
               (*(long *)(param_1 + 0xf0) + 8 + (ulong)(byte)btc_ucode_flags[(ulong)param_2 * 4] * 2
               );
    }
    uVar2 = (ulong)((uVar1 & *(ushort *)(btc_ucode_flags + (ulong)param_2 * 4 + 2)) != 0);
  }
  return uVar2;
}

