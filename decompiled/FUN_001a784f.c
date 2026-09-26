
void FUN_001a784f(long param_1)

{
  int iVar1;
  long lVar2;
  uint uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined1 uVar7;
  undefined2 *puVar8;
  undefined1 uVar9;
  uint uVar10;
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  undefined2 local_3c;
  undefined2 local_3a [5];
  
  local_3a[0] = 0x20;
  local_3c = 0x78;
  uVar10 = *(uint *)(*(long *)(param_1 + 0x20) + 0x68);
  uVar3 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  lVar2 = *(long *)(param_1 + 0x138);
  FUN_001a6d6f(param_1);
  wlc_phy_set_analog_tx_lpf
            (param_1,0x1ff,0xffffffff,0xffffffff,0xffffffff,*(undefined1 *)(lVar2 + 0x339),
             *(undefined1 *)(lVar2 + 0x33a),0xffffffff);
  wlc_phy_set_tx_afe_dacbuf_cap(param_1,0x1ff,*(undefined1 *)(lVar2 + 0x33b),0xffffffff);
  if (*(uint *)(param_1 + 0x164) < 2) {
    uVar7 = (undefined1)((uint)*(byte *)(lVar2 + 0x339) * 0xdd >> 8);
    uVar9 = (char)((uint)*(byte *)(lVar2 + 0x339) * 0xd7 >> 8);
  }
  else {
    uVar7 = *(undefined1 *)(lVar2 + 0x339);
    uVar9 = uVar7;
  }
  wlc_phy_set_analog_rx_lpf
            (param_1,1,0xffffffff,0xffffffff,0xffffffff,uVar7,*(undefined1 *)(lVar2 + 0x33a),
             0xffffffff);
  wlc_phy_set_analog_rx_lpf
            (param_1,2,0xffffffff,0xffffffff,0xffffffff,uVar9,*(undefined1 *)(lVar2 + 0x33a),
             0xffffffff);
  wlc_phy_set_analog_rx_lpf
            (param_1,4,0xffffffff,0xffffffff,0xffffffff,uVar9,*(undefined1 *)(lVar2 + 0x33a),
             0xffffffff);
  wlc_phy_table_write_acphy(param_1,7,0x10,0x20,0x10,&DAT_006765d0);
  wlc_phy_table_write_acphy(param_1,7,0x10,0x90,0x10,&DAT_006765f0);
  wlc_phy_table_write_acphy(param_1,7,2,0x121,0x10,&DAT_00676610);
  wlc_phy_table_write_acphy(param_1,7,2,0x131,0x10,&DAT_00676610);
  wlc_phy_table_write_acphy(param_1,7,2,0x124,0x10,&DAT_00676614);
  wlc_phy_table_write_acphy(param_1,7,2,0x137,0x10,&DAT_00676614);
  iVar1 = *(int *)(param_1 + 0x164);
  if (((iVar1 == 5) || (iVar1 == 2)) || (iVar1 == 6)) {
    wlc_phy_table_write_acphy(param_1,7,0x10,0,0x10,&DAT_00676620);
    wlc_phy_table_write_acphy(param_1,7,0x10,0x70,0x10,&DAT_00676640);
    phy_reg_mod(param_1,0x413,0x8000,0x8000);
    phy_reg_mod(param_1,0x40f,0x200,0x200);
    local_48 = 0;
    local_46 = 0x20;
    puVar8 = &local_48;
    local_44 = 0;
    uVar6 = 0x30;
    uVar4 = 1;
    uVar5 = 0x14;
  }
  else {
    puVar8 = (undefined2 *)&DAT_00676660;
    uVar6 = 0x10;
    uVar4 = 0x10;
    uVar5 = 7;
  }
  wlc_phy_table_write_acphy(param_1,uVar5,uVar4,0,uVar6,puVar8);
  wlc_phy_table_write_acphy(param_1,7,1,0x3c6,0x10,local_3a);
  wlc_phy_table_write_acphy(param_1,7,1,0x3c7,0x10,local_3a);
  wlc_phy_table_write_acphy(param_1,7,1,0x3d6,0x10,local_3a);
  wlc_phy_table_write_acphy(param_1,7,1,0x3d7,0x10,local_3a);
  wlc_phy_table_write_acphy(param_1,7,1,0x3e6,0x10,local_3a);
  wlc_phy_table_write_acphy(param_1,7,1,999,0x10,local_3a);
  if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
    uVar10 = uVar10 & 0x100000;
  }
  else {
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) != 0xc000) goto LAB_001a7c7a;
    uVar10 = uVar10 & 0x200000;
  }
  if (uVar10 != 0) {
    wlc_phy_table_write_acphy(param_1,7,1,0x80,0x10,&local_3c);
  }
LAB_001a7c7a:
  if (*(uint *)(param_1 + 0x164) < 2) {
    wlc_phy_table_write_acphy(param_1,0x10,0xf3,0x4c4,0x20,acphy_txv_for_spexp);
  }
  if (*(char *)(param_1 + 0x16e) != '\0') {
    wlc_phy_set_analog_tx_lpf(param_1,2,0xffffffff,5,5,0xffffffff,0xffffffff,0xffffffff);
    wlc_phy_set_analog_tx_lpf(param_1,4,0xffffffff,5,5,0xffffffff,0xffffffff,0xffffffff);
    wlc_phy_set_analog_tx_lpf(param_1,0x10,0xffffffff,5,5,0xffffffff,0xffffffff,0xffffffff);
    wlc_phy_set_analog_tx_lpf(param_1,0x20,0xffffffff,5,5,0xffffffff,0xffffffff,0xffffffff);
    wlc_phy_set_analog_tx_lpf(param_1,0x80,0xffffffff,6,6,0xffffffff,0xffffffff,0xffffffff);
  }
  phy_reg_mod(param_1,0x19e,2,(uVar3 >> 1 & 1) * 2);
  return;
}

