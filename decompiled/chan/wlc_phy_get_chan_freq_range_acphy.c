
ulong wlc_phy_get_chan_freq_range_acphy(long param_1,uint param_2)

{
  int iVar1;
  uint3 uVar2;
  uint uVar3;
  ulong uVar4;
  ushort *puVar5;
  bool bVar6;
  bool bVar7;
  undefined1 local_40 [8];
  undefined1 local_38 [8];
  undefined1 local_30 [8];
  undefined1 local_28 [12];
  uint local_1c;
  
  if (param_2 == 0) {
    param_2 = (uint)*(byte *)(param_1 + 0x17e);
  }
  if (*(short *)(param_1 + 0x16a) == 0x2069) {
    FUN_0018f6f1(param_1,param_2,&local_1c,local_28,local_30,local_38,local_40);
  }
  else {
    uVar4 = 0;
    puVar5 = &chan_tuning_20691rev_1;
    if (*(char *)(param_1 + 0x16c) == '\x01') {
      do {
        if (*puVar5 == param_2) {
          local_1c = (uint)(ushort)(&DAT_006ec8b2)[uVar4 * 2];
          goto LAB_0018fb6d;
        }
        uVar3 = (int)uVar4 + 1;
        uVar4 = (ulong)uVar3;
        puVar5 = puVar5 + 2;
      } while (uVar3 != 0x4d);
    }
    local_1c = 0;
  }
LAB_0018fb6d:
  if (param_2 < 0xf) {
    return 0;
  }
  iVar1 = *(int *)(*(long *)(param_1 + 0x20) + 0x4c);
  uVar2 = (uint3)(local_1c >> 8);
  if (iVar1 == 4) {
    uVar4 = (ulong)local_1c;
    if (local_1c - 0x1432 < 0x50) goto LAB_0018fc0e;
    if (local_1c - 0x1482 < 0xfa) goto LAB_0018fc12;
    uVar4 = CONCAT71((uint7)uVar2,4);
    if (0xf4 < local_1c - 0x157c) {
      return uVar4;
    }
  }
  else {
    if (iVar1 == 0) {
      if (local_1c - 0x1432 < 0x14a) goto LAB_0018fc0e;
      local_1c = local_1c - 0x157c;
      uVar4 = (ulong)local_1c;
      bVar6 = local_1c < 0xf4;
      bVar7 = local_1c == 0xf4;
    }
    else if (iVar1 == 1) {
      if (local_1c - 0x1432 < 0x50) {
LAB_0018fc0e:
        return CONCAT71((uint7)uVar2,1);
      }
      local_1c = local_1c - 0x1482;
      uVar4 = (ulong)local_1c;
      bVar6 = local_1c < 0x1ee;
      bVar7 = local_1c == 0x1ee;
    }
    else {
      if (local_1c - 0x1324 < 200) goto LAB_0018fc0e;
      local_1c = local_1c - 0x13ec;
      uVar4 = (ulong)local_1c;
      bVar6 = local_1c < 399;
      bVar7 = local_1c == 399;
    }
    if (bVar6 || bVar7) {
LAB_0018fc12:
      return CONCAT71((int7)(uVar4 >> 8),2);
    }
  }
  return CONCAT71((int7)(uVar4 >> 8),3);
}

