
uint wlc_phy_txpwr_idx_get_acphy(long param_1)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  long lVar4;
  uint *puVar5;
  byte bVar6;
  uint local_38 [6];
  
  bVar6 = 0;
  puVar5 = local_38;
  for (lVar4 = 4; lVar4 != 0; lVar4 = lVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  uVar2 = phy_reg_read(param_1,0x70);
  if ((uVar2 & 0xe000) == 0xe000) {
    for (; bVar6 < *(byte *)(param_1 + 0x168); bVar6 = bVar6 + 1) {
      bVar1 = FUN_001913ee(param_1,(uint)bVar6);
      local_38[(int)(uint)bVar6] = (uint)bVar1;
    }
  }
  else {
    bVar6 = *(byte *)(param_1 + 0x168);
    puVar5 = local_38;
    for (iVar3 = 0; (byte)iVar3 < bVar6; iVar3 = iVar3 + 1) {
      *puVar5 = (uint)*(byte *)(*(long *)(param_1 + 0x138) + 0x10 + (long)iVar3);
      puVar5 = puVar5 + 1;
    }
  }
  return local_38[3] << 0x18 | local_38[2] << 0x10 | local_38[0] | local_38[1] << 8;
}

