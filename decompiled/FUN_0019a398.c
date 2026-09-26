
void FUN_0019a398(long param_1,byte param_2)

{
  byte bVar1;
  long lVar2;
  undefined *puVar3;
  undefined1 uVar4;
  undefined4 uVar5;
  byte bVar6;
  ushort uVar7;
  uint uVar8;
  byte *pbVar9;
  undefined1 *puVar10;
  undefined *puVar11;
  byte bVar12;
  undefined4 uVar13;
  byte local_58 [16];
  undefined1 local_48 [24];
  
  lVar2 = *(long *)(param_1 + 0x138);
  if ((byte)(param_2 - 1) < 2) {
    bVar1 = *(byte *)(lVar2 + 0x64a + (ulong)param_2);
    if (param_2 == 1) {
      puVar3 = &DAT_00676420;
      uVar4 = 8;
      if ((*(ushort *)(param_1 + 0x17e) & 0xc000) != 0) {
        uVar7 = *(ushort *)(param_1 + 0x17e) & 0x3800;
        puVar3 = &DAT_00676426;
        if (uVar7 != 0x1000) {
          puVar3 = &DAT_00676432;
          if (uVar7 == 0x1800) {
            puVar3 = &DAT_0067642c;
          }
          uVar4 = 8;
        }
      }
    }
    else {
      puVar3 = &DAT_00676446;
      uVar4 = 0x10;
      if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
        puVar3 = &DAT_0067643f;
        if (*(char *)(lVar2 + 0x66e) != '\0') {
          puVar3 = &DAT_00676438;
        }
        uVar4 = 0x10;
      }
    }
    bVar12 = *(byte *)(lVar2 + 0x66b);
    if (param_2 == 1) {
      uVar8 = 5;
      bVar12 = *(byte *)(lVar2 + 0x66a);
    }
    else {
      if ((((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) && (*(char *)(lVar2 + 0x66e) == '\0')) &&
         (*(char *)(lVar2 + 0x340) != '\0')) {
        bVar6 = ~-(*(byte *)(lVar2 + 0x3e0) < 10) + 5;
      }
      else {
        bVar6 = 6;
      }
      uVar8 = (uint)bVar6;
    }
    uVar8 = uVar8 - bVar12;
    puVar10 = local_48;
    if ((int)uVar8 < 0) {
      uVar8 = 0;
    }
    pbVar9 = local_58;
    puVar11 = puVar3;
    for (bVar12 = 0; bVar12 < bVar1; bVar12 = bVar12 + 1) {
      if (bVar12 == 0) {
        local_48[0] = puVar3[1];
        local_58[0] = 1;
      }
      else if ((byte)uVar8 < bVar12) {
        *puVar10 = puVar3[uVar8 & 0xff];
        *pbVar9 = (byte)uVar8;
      }
      else {
        *puVar10 = *puVar11;
        *pbVar9 = bVar12;
      }
      puVar10 = puVar10 + 1;
      pbVar9 = pbVar9 + 1;
      puVar11 = puVar11 + 1;
    }
    if (param_2 == 1) {
      *(undefined1 *)(lVar2 + 0x658) = *(undefined1 *)(lVar2 + 0x66a);
    }
    else {
      *(undefined1 *)(lVar2 + 0x659) = *(undefined1 *)(lVar2 + 0x66b);
    }
    for (bVar12 = 0; bVar12 < *(byte *)(param_1 + 0x168); bVar12 = bVar12 + 1) {
      if (bVar12 == 0) {
        uVar13 = 0x45;
        uVar5 = 0x44;
      }
      else {
        uVar13 = 0x85;
        if (bVar12 == 1) {
          uVar13 = 0x65;
        }
        uVar5 = 0x84;
        if (bVar12 == 1) {
          uVar5 = 100;
        }
      }
      osl_memcpy(lVar2 + 0x46a + (ulong)bVar12 * 0x78 + (ulong)param_2 * 10,local_48,bVar1);
      wlc_phy_table_write_acphy(param_1,uVar5,bVar1,uVar4,8,local_48);
      osl_memcpy(lVar2 + 0x4a6 + (ulong)bVar12 * 0x78 + (ulong)param_2 * 10,local_58,bVar1);
      wlc_phy_table_write_acphy(param_1,uVar13,bVar1,uVar4,8,local_58);
    }
  }
  return;
}

