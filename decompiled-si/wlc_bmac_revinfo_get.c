
undefined8 wlc_bmac_revinfo_get(long param_1,uint *param_2)

{
  long lVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  ulong uVar5;
  
  lVar1 = *(long *)(param_1 + 0xb8);
  *param_2 = (uint)*(ushort *)(param_1 + 0x80);
  param_2[1] = (uint)*(ushort *)(param_1 + 0x82);
  param_2[2] = (uint)*(ushort *)(param_1 + 0x8a);
  param_2[3] = *(uint *)(param_1 + 0x84);
  param_2[4] = (uint)*(byte *)(param_1 + 0x88);
  param_2[5] = *(uint *)(lVar1 + 0x40);
  param_2[6] = *(uint *)(lVar1 + 0x3c);
  param_2[7] = *(uint *)(lVar1 + 0x44);
  param_2[8] = *(uint *)(lVar1 + 0x28);
  param_2[9] = *(uint *)(lVar1 + 0x30);
  param_2[10] = *(uint *)(lVar1 + 4);
  param_2[0xb] = *(uint *)(lVar1 + 8);
  param_2[0xc] = *(uint *)(lVar1 + 0xc);
  param_2[0xd] = (uint)*(byte *)(lVar1 + 0x4c);
  param_2[0xf] = *(uint *)(param_1 + 0x8c);
  param_2[0x10] = *(uint *)(param_1 + 0x90);
  param_2[0xe] = *(uint *)(param_1 + 0x118);
  for (uVar5 = 0; (uint)uVar5 < *(uint *)(param_1 + 0x118); uVar5 = (ulong)((int)uVar5 + 1)) {
    iVar4 = wlc_is_singleband_5g(*(undefined2 *)(param_1 + 0x82));
    if (iVar4 != 0) {
      uVar5 = 1;
    }
    puVar2 = *(uint **)(param_1 + 0xf0 + uVar5 * 8);
    param_2[uVar5 * 8 + 0x11] = puVar2[1];
    param_2[uVar5 * 8 + 0x12] = *puVar2;
    param_2[uVar5 * 8 + 0x14] = (uint)(ushort)puVar2[7];
    param_2[uVar5 * 8 + 0x15] = (uint)*(ushort *)((long)puVar2 + 0x1e);
    param_2[uVar5 * 8 + 0x17] = (uint)(ushort)puVar2[8];
    param_2[uVar5 * 8 + 0x13] = (uint)*(ushort *)((long)puVar2 + 0x22);
    uVar3 = puVar2[0xc];
    param_2[uVar5 * 8 + 0x16] = 0;
    *(char *)(param_2 + uVar5 * 8 + 0x18) = (char)uVar3;
  }
  return 0;
}

