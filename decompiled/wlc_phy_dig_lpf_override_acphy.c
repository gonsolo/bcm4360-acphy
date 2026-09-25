
void wlc_phy_dig_lpf_override_acphy(long param_1,char param_2)

{
  undefined2 uVar1;
  
  if (param_2 == '\0') {
LAB_00191a6f:
    if (*(char *)(param_1 + 0xf82) != '\0') {
      phy_reg_write(param_1,0x18b,*(undefined2 *)(param_1 + 0xf6e));
      phy_reg_write(param_1,0x18c,*(undefined2 *)(param_1 + 0xf70));
      phy_reg_write(param_1,0x18d,*(undefined2 *)(param_1 + 0xf72));
      phy_reg_write(param_1,0x18e,*(undefined2 *)(param_1 + 0xf74));
      phy_reg_write(param_1,399,*(undefined2 *)(param_1 + 0xf76));
      phy_reg_write(param_1,400,*(undefined2 *)(param_1 + 0xf78));
      phy_reg_write(param_1,0x191,*(undefined2 *)(param_1 + 0xf7a));
      phy_reg_write(param_1,0x192,*(undefined2 *)(param_1 + 0xf7c));
      phy_reg_write(param_1,0x193,*(undefined2 *)(param_1 + 0xf7e));
      phy_reg_write(param_1,0x194,*(undefined2 *)(param_1 + 0xf80));
      *(undefined1 *)(param_1 + 0xf82) = 0;
    }
  }
  else {
    if (*(char *)(param_1 + 0xf82) == '\0') {
      uVar1 = phy_reg_read(param_1,0x18b);
      *(undefined2 *)(param_1 + 0xf6e) = uVar1;
      uVar1 = phy_reg_read(param_1,0x18c);
      *(undefined2 *)(param_1 + 0xf70) = uVar1;
      uVar1 = phy_reg_read(param_1,0x18d);
      *(undefined2 *)(param_1 + 0xf72) = uVar1;
      uVar1 = phy_reg_read(param_1,0x18e);
      *(undefined2 *)(param_1 + 0xf74) = uVar1;
      uVar1 = phy_reg_read(param_1,399);
      *(undefined2 *)(param_1 + 0xf76) = uVar1;
      uVar1 = phy_reg_read(param_1,400);
      *(undefined2 *)(param_1 + 0xf78) = uVar1;
      uVar1 = phy_reg_read(param_1,0x191);
      *(undefined2 *)(param_1 + 0xf7a) = uVar1;
      uVar1 = phy_reg_read(param_1,0x192);
      *(undefined2 *)(param_1 + 0xf7c) = uVar1;
      uVar1 = phy_reg_read(param_1,0x193);
      *(undefined2 *)(param_1 + 0xf7e) = uVar1;
      uVar1 = phy_reg_read(param_1,0x194);
      *(undefined1 *)(param_1 + 0xf82) = 1;
      *(undefined2 *)(param_1 + 0xf80) = uVar1;
    }
    if (param_2 == '\x01') {
      uVar1 = phy_reg_read(param_1,0x181);
      phy_reg_write(param_1,0x18b,uVar1);
      uVar1 = phy_reg_read(param_1,0x182);
      phy_reg_write(param_1,0x18c,uVar1);
      uVar1 = phy_reg_read(param_1,0x183);
      phy_reg_write(param_1,0x18d,uVar1);
      uVar1 = phy_reg_read(param_1,0x186);
      phy_reg_write(param_1,400,uVar1);
      uVar1 = phy_reg_read(param_1,0x187);
      phy_reg_write(param_1,0x191,uVar1);
      uVar1 = phy_reg_read(param_1,0x188);
      phy_reg_write(param_1,0x192,uVar1);
      uVar1 = phy_reg_read(param_1,0x184);
      phy_reg_write(param_1,0x18e,uVar1);
      uVar1 = phy_reg_read(param_1,0x185);
      phy_reg_write(param_1,399,uVar1);
      uVar1 = phy_reg_read(param_1,0x189);
      phy_reg_write(param_1,0x193,uVar1);
      uVar1 = phy_reg_read(param_1,0x18a);
    }
    else {
      if (param_2 == '\0') goto LAB_00191a6f;
      if (param_2 != '\x02') {
        return;
      }
      phy_reg_write(param_1,0x18b,0x2d4);
      phy_reg_write(param_1,0x18c,0);
      phy_reg_write(param_1,0x18d,0);
      phy_reg_write(param_1,0x18e,0);
      phy_reg_write(param_1,399,0);
      phy_reg_write(param_1,400,0x2d4);
      phy_reg_write(param_1,0x191,0);
      phy_reg_write(param_1,0x192,0);
      phy_reg_write(param_1,0x193,0);
      uVar1 = 0;
    }
    phy_reg_write(param_1,0x194,uVar1);
  }
  return;
}

