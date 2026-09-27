
void FUN_0019d65d(undefined8 param_1,uint param_2)

{
  ushort uVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  undefined4 *puVar5;
  byte *pbVar6;
  int iVar7;
  byte local_98 [48];
  byte local_68 [46];
  ushort local_3a [5];
  
  iVar7 = 0;
  lVar4 = 0;
  puVar5 = &DAT_00558e30;
  pbVar6 = local_68;
  for (lVar3 = 9; lVar3 != 0; lVar3 = lVar3 + -1) {
    *(undefined4 *)pbVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    pbVar6 = pbVar6 + 4;
  }
  puVar5 = &DAT_00558e00;
  pbVar6 = local_98;
  for (lVar3 = 9; lVar3 != 0; lVar3 = lVar3 + -1) {
    *(undefined4 *)pbVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    pbVar6 = pbVar6 + 4;
  }
  uVar1 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  do {
    local_3a[0] = (ushort)(((uint)local_68[lVar4] * (param_2 & 0xffff)) / 100 << 8) |
                  (ushort)local_68[lVar4 + 1];
    wlc_phy_table_write_acphy(param_1,0xc,1,iVar7,0x10,local_3a);
    pbVar6 = local_98 + lVar4;
    lVar3 = lVar4 + 1;
    iVar2 = iVar7 + 0x20;
    iVar7 = iVar7 + 1;
    lVar4 = lVar4 + 2;
    local_3a[0] = (ushort)(((uint)*pbVar6 * (param_2 & 0xffff)) / 100 << 8) |
                  (ushort)local_98[lVar3];
    wlc_phy_table_write_acphy(param_1,0xc,1,iVar2,0x10,local_3a);
  } while (iVar7 != 0x12);
  phy_reg_mod(param_1,0x19e,2,uVar1 & 2);
  return;
}

