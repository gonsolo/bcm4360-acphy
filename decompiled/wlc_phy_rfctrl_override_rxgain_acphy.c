
void wlc_phy_rfctrl_override_rxgain_acphy(long param_1,char param_2,long param_3,long param_4)

{
  undefined2 *puVar1;
  ushort uVar2;
  undefined2 uVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  undefined8 uVar7;
  byte bVar8;
  uint uVar9;
  ulong uVar10;
  byte *pbVar11;
  short sVar12;
  byte local_3a;
  byte local_39 [9];
  
  uVar10 = 0;
  if (param_2 == '\x01') {
    for (; (byte)uVar10 < *(byte *)(param_1 + 0x168); uVar10 = (ulong)((int)uVar10 + 1)) {
      puVar1 = (undefined2 *)(param_4 + (uVar10 & 0xff) * 8);
      sVar4 = (short)uVar10 * 0x200;
      phy_reg_write(param_1,sVar4 + 0x722,*puVar1);
      phy_reg_write(param_1,sVar4 + 0x730,puVar1[1]);
      phy_reg_write(param_1,sVar4 + 0x731,puVar1[2]);
      phy_reg_write(param_1,sVar4 + 0x734,puVar1[3]);
    }
  }
  else {
    uVar2 = phy_reg_read(param_1,0x19e);
    phy_reg_mod(param_1,0x19e,2,2);
    for (uVar9 = 0; bVar8 = (byte)uVar9, bVar8 < *(byte *)(param_1 + 0x168); uVar9 = uVar9 + 1) {
      puVar1 = (undefined2 *)(param_4 + (ulong)(uVar9 & 0xff) * 8);
      sVar5 = (short)(uVar9 << 9);
      uVar3 = phy_reg_read(param_1,sVar5 + 0x722);
      *puVar1 = uVar3;
      sVar12 = sVar5 + 0x730;
      uVar3 = phy_reg_read(param_1,sVar12);
      puVar1[1] = uVar3;
      sVar4 = sVar5 + 0x731;
      uVar3 = phy_reg_read(param_1,sVar4);
      puVar1[2] = uVar3;
      sVar5 = sVar5 + 0x734;
      uVar3 = phy_reg_read(param_1,sVar5);
      puVar1[3] = uVar3;
      if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
        iVar6 = (uVar9 & 0xff) * 0x18 + 5;
      }
      else {
        iVar6 = (uVar9 & 0xff) * 0x18 + 0xd;
      }
      wlc_phy_table_read_acphy(param_1,0x15,1,iVar6,8,local_39);
      wlc_phy_table_read_acphy(param_1,0x15,1,(uVar9 & 0xff) * 0x18 + 0x16,8,&local_3a);
      pbVar11 = (byte *)((ulong)(uVar9 & 0xff) * 6 + param_3);
      phy_reg_write(param_1,sVar12,
                    (pbVar11[5] & 0x3f) << 10 | (uint)pbVar11[2] << 6 | (uint)*pbVar11 |
                    (uint)pbVar11[1] << 3);
      phy_reg_write(param_1,sVar4,(local_3a >> 3) << 4 | local_39[0] >> 3 & 0xf);
      phy_reg_write(param_1,sVar5,(uint)pbVar11[3] | (uint)pbVar11[4] << 3);
      uVar7 = 0x722;
      if ((bVar8 != 0) && (uVar7 = 0xb22, bVar8 == 1)) {
        uVar7 = 0x922;
      }
      phy_reg_mod(param_1,uVar7,2,2);
      uVar7 = 0x722;
      if ((bVar8 != 0) && (uVar7 = 0xb22, bVar8 == 1)) {
        uVar7 = 0x922;
      }
      phy_reg_mod(param_1,uVar7,4,4);
      uVar7 = 0x722;
      if ((bVar8 != 0) && (uVar7 = 0xb22, bVar8 == 1)) {
        uVar7 = 0x922;
      }
      phy_reg_mod(param_1,uVar7,8,8);
      phy_reg_read(param_1,sVar12);
      phy_reg_read(param_1,sVar4);
      phy_reg_read(param_1,sVar5);
    }
    phy_reg_mod(param_1,0x19e,2,uVar2 & 2);
  }
  return;
}

