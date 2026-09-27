
void FUN_0019dc93(long param_1)

{
  long lVar1;
  int iVar2;
  short sVar3;
  ushort uVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  
  lVar1 = *(long *)(param_1 + 0x138);
  uVar4 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  *(undefined1 *)(lVar1 + 0x14c) = 0;
  phy_reg_write(param_1,0x401,*(undefined2 *)(lVar1 + 0x23a));
  for (uVar7 = 0; (byte)uVar7 < *(byte *)(param_1 + 0x168); uVar7 = (ulong)((int)uVar7 + 1)) {
    uVar6 = uVar7 & 0xff;
    iVar2 = (int)(uVar7 & 0xff);
    wlc_phy_table_write_acphy(param_1,7,1,iVar2 + 0x100,0x10,lVar1 + 0x222 + uVar6 * 2);
    wlc_phy_table_write_acphy(param_1,7,1,iVar2 + 0x103,0x10,lVar1 + 0x228 + uVar6 * 2);
    wlc_phy_table_write_acphy(param_1,7,1,iVar2 + 0x106,0x10,lVar1 + 0x22e + uVar6 * 2);
    lVar5 = (long)iVar2;
    wlc_phy_txpwr_by_index_acphy
              (param_1,1 << ((byte)uVar7 & 0x1f) & 0xff,(int)*(char *)(lVar1 + 0x24e + lVar5));
    FUN_0019d224(param_1,lVar1 + 0x21a + uVar6 * 2,uVar7 & 0xff);
    sVar3 = (short)uVar7 * 0x200;
    phy_reg_write(param_1,sVar3 + 0x73e,*(undefined2 *)(lVar1 + 0xc + (lVar5 + 0x118) * 2));
    phy_reg_write(param_1,sVar3 + 0x678,*(undefined2 *)(lVar1 + 0x14 + (lVar5 + 0x118) * 2));
    phy_reg_write(param_1,sVar3 + 0x720,*(undefined2 *)(lVar1 + 0xe + (lVar5 + 0xa0) * 2));
    phy_reg_write(param_1,sVar3 + 0x721,*(undefined2 *)(lVar1 + 0xe + (lVar5 + 0xa8) * 2));
    phy_reg_write(param_1,sVar3 + 0x722,*(undefined2 *)(lVar1 + 0xe + (lVar5 + 0xb0) * 2));
    phy_reg_write(param_1,sVar3 + 0x723,*(undefined2 *)(lVar1 + 0x16 + (lVar5 + 200) * 2));
    phy_reg_write(param_1,sVar3 + 0x724,*(undefined2 *)(lVar1 + 0x16 + (lVar5 + 0xd8) * 2));
    phy_reg_write(param_1,sVar3 + 0x725,*(undefined2 *)(lVar1 + 0x16 + (lVar5 + 0xe0) * 2));
    phy_reg_write(param_1,sVar3 + 0x727,*(undefined2 *)(lVar1 + 0xe + (lVar5 + 0xf8) * 2));
    phy_reg_write(param_1,sVar3 + 0x726,*(undefined2 *)(lVar1 + 0xe + (lVar5 + 0xf0) * 2));
    phy_reg_write(param_1,sVar3 + 0x728,*(undefined2 *)(lVar1 + 0x16 + (lVar5 + 0xa0) * 2));
    phy_reg_write(param_1,sVar3 + 0x729,*(undefined2 *)(lVar1 + 0x16 + (lVar5 + 0xa8) * 2));
    phy_reg_write(param_1,sVar3 + 0x732,*(undefined2 *)(lVar1 + 0xe + (lVar5 + 0xb8) * 2));
    phy_reg_write(param_1,sVar3 + 0x733,*(undefined2 *)(lVar1 + 0x16 + (lVar5 + 0xb8) * 2));
    phy_reg_write(param_1,sVar3 + 0x730,*(undefined2 *)(lVar1 + 0xe + (lVar5 + 0xc0) * 2));
    phy_reg_write(param_1,sVar3 + 0x731,*(undefined2 *)(lVar1 + 0x16 + (lVar5 + 0xc0) * 2));
    phy_reg_write(param_1,sVar3 + 0x734,*(undefined2 *)(lVar1 + 0xe + (lVar5 + 200) * 2));
    phy_reg_write(param_1,sVar3 + 0x735,*(undefined2 *)(lVar1 + 0xe + (lVar5 + 0xd0) * 2));
    phy_reg_write(param_1,sVar3 + 0x737,*(undefined2 *)(lVar1 + 0x16 + (lVar5 + 0xd0) * 2));
    phy_reg_write(param_1,sVar3 + 0x738,*(undefined2 *)(lVar1 + 0xe + (lVar5 + 0xd8) * 2));
    phy_reg_write(param_1,sVar3 + 0x736,*(undefined2 *)(lVar1 + 0xe + (lVar5 + 0xe0) * 2));
    phy_reg_write(param_1,sVar3 + 0x739,*(undefined2 *)(lVar1 + 0xe + (lVar5 + 0xe8) * 2));
    phy_reg_write(param_1,sVar3 + 0x73a,*(undefined2 *)(lVar1 + 0x16 + (lVar5 + 0xe8) * 2));
    phy_reg_write(param_1,sVar3 + 0x73b,*(undefined2 *)(lVar1 + 0x16 + (lVar5 + 0xf0) * 2));
    phy_reg_write(param_1,sVar3 + 0x73c,*(undefined2 *)(lVar1 + 0x16 + (lVar5 + 0xf8) * 2));
    phy_reg_write(param_1,sVar3 + 0x73d,*(undefined2 *)(lVar1 + 0x20e + lVar5 * 2));
    phy_reg_write(param_1,sVar3 + 0x747,*(undefined2 *)(lVar1 + 0x16 + (lVar5 + 0xb0) * 2));
  }
  phy_reg_write(param_1,0x40f,*(undefined2 *)(lVar1 + 0x24c));
  wlc_phy_force_rfseq_acphy(param_1,2);
  phy_reg_mod(param_1,0x19e,2,uVar4 & 2);
  return;
}

