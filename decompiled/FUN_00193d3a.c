
void FUN_00193d3a(long param_1)

{
  ushort uVar1;
  byte bVar2;
  ushort *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int local_6c;
  ushort local_68 [28];
  
  iVar6 = 0x73a;
  iVar5 = 0x739;
  uVar4 = 0;
  puVar3 = local_68;
  local_6c = 0x725;
  for (bVar2 = 0; bVar2 < *(byte *)(param_1 + 0x168); bVar2 = bVar2 + 1) {
    uVar1 = phy_reg_read(param_1,iVar5);
    *puVar3 = uVar1;
    puVar3[1] = (ushort)iVar5;
    phy_reg_write(param_1,iVar5,uVar1 | 0x80);
    uVar4 = uVar4 + 3;
    uVar1 = phy_reg_read(param_1,iVar6);
    puVar3[2] = uVar1;
    puVar3[3] = (ushort)iVar6;
    phy_reg_write(param_1,iVar6,uVar1 | 0x80);
    iVar5 = iVar5 + 0x200;
    iVar6 = iVar6 + 0x200;
    uVar1 = phy_reg_read(param_1,local_6c);
    puVar3[4] = uVar1;
    puVar3[5] = (ushort)local_6c;
    puVar3 = puVar3 + 6;
    phy_reg_write(param_1,local_6c,uVar1 | 0x204);
    local_6c = local_6c + 0x200;
  }
  osl_delay(1);
  while (uVar4 != 0) {
    uVar4 = uVar4 - 1;
    phy_reg_write(param_1,local_68[(ulong)uVar4 * 2 + 1],local_68[(ulong)uVar4 * 2]);
  }
  osl_delay(1);
  return;
}

