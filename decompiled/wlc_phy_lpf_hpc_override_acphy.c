
void wlc_phy_lpf_hpc_override_acphy(long param_1,char param_2)

{
  long lVar1;
  uint uVar2;
  uint uVar3;
  undefined2 uVar4;
  uint uVar5;
  short sVar6;
  int iVar7;
  long lVar8;
  undefined8 uVar9;
  byte bVar10;
  ulong uVar11;
  byte local_4c;
  undefined4 local_3c;
  
  lVar1 = *(long *)(param_1 + 0x138);
  if (param_2 == '\0') {
    *(undefined1 *)(lVar1 + 0x308) = 0;
    for (uVar11 = 0; (byte)uVar11 < *(byte *)(param_1 + 0x168); uVar11 = (ulong)((int)uVar11 + 1)) {
      lVar8 = (uVar11 & 0xff) + 0x180;
      sVar6 = (short)uVar11 * 0x200;
      phy_reg_write(param_1,sVar6 + 0x723,*(undefined2 *)(lVar1 + 10 + lVar8 * 2));
      phy_reg_write(param_1,sVar6 + 0x735,*(undefined2 *)(lVar1 + 0x12 + lVar8 * 2));
    }
  }
  else {
    *(undefined1 *)(lVar1 + 0x308) = 1;
    uVar5 = phy_reg_read(param_1,0x19e);
    phy_reg_mod(param_1,0x19e,2,2);
    wlc_phy_table_read_acphy(param_1,7,1,0x122,0x10,(long)&local_3c + 2);
    wlc_phy_table_read_acphy(param_1,7,1,0x125,0x10,&local_3c);
    phy_reg_mod(param_1,0x19e,2,(uVar5 >> 1 & 1) * 2);
    for (uVar5 = 0; bVar10 = (byte)uVar5, bVar10 < *(byte *)(param_1 + 0x168); uVar5 = uVar5 + 1) {
      iVar7 = uVar5 * 0x200;
      uVar4 = phy_reg_read(param_1,iVar7 + 0x723U & 0xffff);
      lVar8 = (long)(int)(uVar5 & 0xff) + 0x180;
      *(undefined2 *)(lVar1 + 10 + lVar8 * 2) = uVar4;
      sVar6 = (short)iVar7 + 0x735;
      uVar4 = phy_reg_read(param_1,sVar6,lVar8,CONCAT22((short)((uint)iVar7 >> 0x10),sVar6));
      uVar3 = local_3c;
      uVar9 = 0x723;
      *(undefined2 *)(lVar1 + 0x12 + lVar8 * 2) = uVar4;
      uVar2 = local_3c >> 0x10;
      if ((bVar10 != 0) && (uVar9 = 0xb23, bVar10 == 1)) {
        uVar9 = 0x923;
      }
      phy_reg_mod(param_1,uVar9,4,4);
      uVar9 = 0x735;
      if ((bVar10 != 0) && (uVar9 = 0xb35, bVar10 == 1)) {
        uVar9 = 0x935;
      }
      local_4c = (byte)((uVar5 & 0xff) << 2);
      phy_reg_mod(param_1,uVar9,0xe0,((int)uVar2 >> (local_4c & 0x1f) & 0xfU) << 5);
      uVar9 = 0x723;
      if ((bVar10 != 0) && (uVar9 = 0xb23, bVar10 == 1)) {
        uVar9 = 0x923;
      }
      phy_reg_mod(param_1,uVar9,2,2);
      uVar9 = 0x735;
      if ((bVar10 != 0) && (uVar9 = 0xb35, bVar10 == 1)) {
        uVar9 = 0x935;
      }
      phy_reg_mod(param_1,uVar9,0x1e,((int)(uVar3 & 0xffff) >> (local_4c & 0x1f)) * 2 & 0x1e);
    }
  }
  return;
}

