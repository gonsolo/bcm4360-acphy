
void FUN_001982a2(long param_1)

{
  int iVar1;
  long lVar2;
  short sVar3;
  ulong uVar4;
  ulong uVar5;
  
  lVar2 = *(long *)(param_1 + 0x138);
  for (uVar5 = 0; (byte)uVar5 < *(byte *)(param_1 + 0x168); uVar5 = (ulong)((int)uVar5 + 1)) {
    uVar4 = uVar5 & 0xff;
    sVar3 = (short)uVar5 * 0x200;
    phy_reg_write(param_1,sVar3 + 0x73e,*(undefined2 *)(lVar2 + 8 + (uVar4 + 0x50) * 2));
    phy_reg_write(param_1,sVar3 + 0x721,*(undefined2 *)(lVar2 + 0x10 + (uVar4 + 0x50) * 2));
    phy_reg_write(param_1,sVar3 + 0x729,*(undefined2 *)(lVar2 + 8 + (uVar4 + 0x58) * 2));
    phy_reg_write(param_1,sVar3 + 0x720,*(undefined2 *)(lVar2 + 0x10 + (uVar4 + 0x58) * 2));
    phy_reg_write(param_1,sVar3 + 0x728,*(undefined2 *)(lVar2 + 8 + (uVar4 + 0x60) * 2));
    phy_reg_write(param_1,sVar3 + 0x724,*(undefined2 *)(lVar2 + 0x10 + (uVar4 + 0x60) * 2));
    phy_reg_write(param_1,sVar3 + 0x736,*(undefined2 *)(lVar2 + 8 + (uVar4 + 0x68) * 2));
    phy_reg_write(param_1,sVar3 + 0x723,*(undefined2 *)(lVar2 + 0x10 + (uVar4 + 0x68) * 2));
    phy_reg_write(param_1,sVar3 + 0x735,*(undefined2 *)(lVar2 + 8 + (uVar4 + 0x70) * 2));
    phy_reg_write(param_1,sVar3 + 0x737,*(undefined2 *)(lVar2 + 0x10 + (uVar4 + 0x70) * 2));
    phy_reg_write(param_1,sVar3 + 0x738,*(undefined2 *)(lVar2 + 8 + (uVar4 + 0x78) * 2));
    phy_reg_write(param_1,sVar3 + 0x727,*(undefined2 *)(lVar2 + 0x10 + (uVar4 + 0x78) * 2));
    phy_reg_write(param_1,sVar3 + 0x73c,*(undefined2 *)(lVar2 + 0x108 + uVar4 * 2));
    phy_reg_write(param_1,sVar3 + 0x725,*(undefined2 *)(lVar2 + 0x90 + uVar4 * 2));
    phy_reg_write(param_1,sVar3 + 0x739,*(undefined2 *)(lVar2 + 8 + (uVar4 + 0x48) * 2));
    phy_reg_write(param_1,sVar3 + 0x73a,*(undefined2 *)(lVar2 + 0x10 + (uVar4 + 0x48) * 2));
  }
  phy_reg_write(param_1,0x19e,*(undefined2 *)(lVar2 + 0x8c));
  phy_reg_write(param_1,0x40f,*(undefined2 *)(lVar2 + 0x8e));
  iVar1 = *(int *)(param_1 + 0x164);
  if (((iVar1 == 5) || (iVar1 == 2)) || (iVar1 == 6)) {
    phy_reg_mod(param_1,0x19e,0x3c,0);
    phy_reg_mod(param_1,0x19e,1,1);
    phy_reg_mod(param_1,0x19e,1,0);
  }
  wlc_phy_resetcca_acphy(param_1);
  return;
}

