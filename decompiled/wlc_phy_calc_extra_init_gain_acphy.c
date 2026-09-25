
void wlc_phy_calc_extra_init_gain_acphy(long param_1,uint param_2,long param_3)

{
  ushort *puVar1;
  ushort uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  int iVar7;
  byte *pbVar8;
  byte bVar9;
  byte bVar10;
  uint uVar11;
  uint uVar12;
  ushort *puVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  ushort local_48 [12];
  
  puVar13 = local_48;
  phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  wlc_phy_table_read_acphy(param_1,7,3,0xf9,0x10,puVar13);
  phy_reg_mod(param_1,0x19e,2);
  puVar1 = puVar13 + *(byte *)(param_1 + 0x168);
  param_2 = param_2 & 0xff;
  for (; bVar4 = (byte)param_2, puVar13 != puVar1; puVar13 = puVar13 + 1) {
    uVar2 = *puVar13;
    iVar15 = 4 - (uVar2 >> 6 & 0xf);
    if (iVar15 < 0) {
      iVar15 = 0;
    }
    iVar7 = (10 - (uVar2 >> 10 & 7)) - (uint)(byte)(uVar2 >> 0xd);
    if (iVar7 < 0) {
      iVar7 = 0;
    }
    uVar12 = iVar15 + 4 + iVar7;
    if ((byte)uVar12 < bVar4) {
      param_2 = uVar12;
    }
  }
  if (bVar4 != 0) {
    for (bVar5 = 0; bVar5 < *(byte *)(param_1 + 0x168); bVar5 = bVar5 + 1) {
      uVar2 = local_48[bVar5];
      uVar16 = uVar2 >> 6 & 0xf;
      uVar12 = uVar2 >> 10 & 7;
      bVar10 = 4;
      if (bVar4 < 5) {
        bVar10 = bVar4;
      }
      bVar6 = bVar4 - bVar10;
      uVar14 = (10 - (uint)(byte)(uVar2 >> 0xd)) - uVar12;
      if ((int)uVar14 < 0) {
        uVar14 = 0;
      }
      if (bVar6 <= (byte)uVar14) {
        uVar14 = (uint)bVar6;
      }
      uVar11 = uVar14 + (uVar2 >> 0xd);
      bVar6 = bVar6 - (char)uVar14;
      iVar15 = (10 - (uVar11 & 0xff)) - uVar12;
      if (iVar15 < 0) {
        iVar15 = 0;
      }
      bVar3 = (byte)iVar15;
      if (bVar6 <= (byte)iVar15) {
        bVar3 = bVar6;
      }
      iVar15 = 4 - uVar16;
      if (iVar15 < 0) {
        iVar15 = 0;
      }
      bVar9 = bVar6 - bVar3;
      if ((byte)iVar15 < (byte)(bVar6 - bVar3)) {
        bVar9 = (byte)iVar15;
      }
      pbVar8 = (byte *)((ulong)bVar5 * 6 + param_3);
      *pbVar8 = (byte)uVar2 & 7;
      pbVar8[1] = (byte)(uVar2 >> 3) & 7;
      pbVar8[2] = bVar9 + (char)uVar16;
      pbVar8[3] = bVar3 + (char)uVar12;
      pbVar8[4] = (byte)uVar11;
      pbVar8[5] = bVar10;
    }
  }
  return;
}

