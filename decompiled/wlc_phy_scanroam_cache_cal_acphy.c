
void wlc_phy_scanroam_cache_cal_acphy(long param_1,char param_2)

{
  long lVar1;
  undefined1 uVar2;
  ushort uVar3;
  undefined2 uVar4;
  long lVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined1 local_48 [2];
  undefined2 uStack_46;
  
  wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  wlc_phyreg_enter(param_1);
  uVar3 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  if (param_2 == '\0') {
    if (*(short *)(*(long *)(param_1 + 0x138) + 0x44a) == -0x5324) {
      FUN_0019cea1(param_1,*(long *)(param_1 + 0x138) + 0x412);
    }
  }
  else {
    for (uVar6 = 0; (byte)uVar6 < *(byte *)(param_1 + 0x168); uVar6 = uVar6 + 1) {
      uVar7 = uVar6 & 0xff;
      lVar5 = (long)(int)uVar7 * 0xe;
      FUN_0019ccd9(param_1,0,local_48,8,uVar7);
      uVar8 = uVar7 << 9;
      *(short *)(*(long *)(param_1 + 0x138) + lVar5 + 0x412) = (short)_local_48;
      *(undefined2 *)(*(long *)(param_1 + 0x138) + lVar5 + 0x414) = uStack_46;
      FUN_0019ccd9(param_1,0,*(long *)(param_1 + 0x138) + lVar5 + 0x416,9,uVar7);
      lVar1 = *(long *)(param_1 + 0x138);
      uVar2 = read_radio_reg(param_1,uVar8 & 0xffff | 2);
      *(undefined1 *)(lVar1 + 0x418 + lVar5) = uVar2;
      lVar1 = *(long *)(param_1 + 0x138);
      uVar2 = read_radio_reg(param_1,uVar8 & 0xffff | 3);
      *(undefined1 *)(lVar1 + 0x419 + lVar5) = uVar2;
      lVar1 = *(long *)(param_1 + 0x138);
      uVar2 = read_radio_reg(param_1,uVar8 & 0xffff | 4);
      *(undefined1 *)(lVar1 + 0x41a + lVar5) = uVar2;
      lVar1 = *(long *)(param_1 + 0x138);
      uVar2 = read_radio_reg(param_1,uVar8 & 0xffff | 5);
      *(undefined1 *)(lVar1 + 0x41b + lVar5) = uVar2;
      lVar1 = *(long *)(param_1 + 0x138);
      uVar4 = phy_reg_read(param_1,(short)uVar6 * 0x200 + 0x6a0);
      *(undefined2 *)(lVar1 + 0x41c + lVar5) = uVar4;
      lVar1 = *(long *)(param_1 + 0x138);
      uVar4 = phy_reg_read(param_1);
      *(undefined2 *)(lVar1 + 0x41e + lVar5) = uVar4;
    }
    *(undefined2 *)(*(long *)(param_1 + 0x138) + 0x44a) = 0xacdc;
  }
  phy_reg_mod(param_1,0x19e,2,uVar3 & 2);
  wlc_phyreg_exit(param_1);
  wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  return;
}

