
void FUN_0019ccd9(long param_1,char param_2,undefined2 *param_3,byte param_4,byte param_5)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  long lVar4;
  uint uVar5;
  int iVar6;
  long lVar7;
  undefined4 *puVar8;
  byte *pbVar9;
  int iVar10;
  byte local_78 [72];
  
  puVar8 = &DAT_00558d60;
  pbVar9 = local_78;
  for (lVar7 = 0xf; lVar7 != 0; lVar7 = lVar7 + -1) {
    *(undefined4 *)pbVar9 = *puVar8;
    puVar8 = puVar8 + 1;
    pbVar9 = pbVar9 + 4;
  }
  lVar7 = *(long *)(param_1 + 0xf58);
  uVar5 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  lVar4 = (ulong)param_4 * 3;
  bVar1 = local_78[lVar4];
  bVar2 = local_78[lVar4 + 1];
  bVar3 = local_78[lVar4 + 2];
  if (param_4 < 0xc) {
    if (param_2 == '\0') {
      wlc_phy_table_read_acphy(param_1,0xc,bVar1,(uint)param_5 * (uint)bVar3 + (uint)bVar2,0x10);
    }
    else {
      wlc_phy_table_write_acphy(param_1,0xc,bVar1,(uint)param_5 * (uint)bVar3 + (uint)bVar2,0x10);
    }
  }
  else if (param_4 < 0x10) {
    iVar10 = (uint)bVar3 * (uint)param_5 + (uint)bVar2;
    for (iVar6 = 0; (byte)iVar6 < bVar1; iVar6 = iVar6 + 1) {
      if (param_2 == '\0') {
        *param_3 = *(undefined2 *)(lVar7 + 0x2c + (long)(iVar6 + iVar10) * 2);
      }
      else if (param_2 == '\x02') {
        *(undefined2 *)(lVar7 + 0x54 + (long)(int)(iVar6 + (uint)param_5 * (uint)bVar1) * 2) =
             *param_3;
      }
      else {
        *(undefined2 *)(lVar7 + 0x2c + (long)(iVar6 + iVar10) * 2) = *param_3;
      }
      param_3 = param_3 + 1;
    }
  }
  else {
    iVar10 = (uint)param_5 * (uint)bVar3 + (uint)bVar2;
    for (iVar6 = 0; (byte)iVar6 < bVar1; iVar6 = iVar6 + 1) {
      if (param_2 == '\0') {
        *param_3 = *(undefined2 *)(lVar7 + 4 + (long)(iVar6 + iVar10) * 2);
      }
      else {
        *(undefined2 *)(lVar7 + 4 + (long)(iVar6 + iVar10) * 2) = *param_3;
      }
      param_3 = param_3 + 1;
    }
  }
  phy_reg_mod(param_1,0x19e,2,(uVar5 >> 1 & 1) * 2);
  return;
}

