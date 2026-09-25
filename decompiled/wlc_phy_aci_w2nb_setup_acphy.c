
void wlc_phy_aci_w2nb_setup_acphy(long param_1,char param_2)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  undefined8 uVar4;
  
  for (uVar3 = 0; bVar2 = (byte)uVar3, bVar2 < *(byte *)(param_1 + 0x168); uVar3 = uVar3 + 1) {
    uVar4 = 0x729;
    if ((bVar2 != 0) && (uVar4 = 0xb29, bVar2 == 1)) {
      uVar4 = 0x929;
    }
    phy_reg_mod(param_1,uVar4,0x1000,(uint)(param_2 != '\0') << 0xc);
    uVar4 = 0x721;
    if ((bVar2 != 0) && (uVar4 = 0xb21, bVar2 == 1)) {
      uVar4 = 0x921;
    }
    phy_reg_mod(param_1,uVar4,0x1000,0x1000);
    if (param_2 != '\0') {
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar1 = 0x3a, acphychipid == 0xaa06)) {
        uVar1 = 0x33;
      }
      mod_radio_reg(param_1,(uVar3 & 0x7f) << 9 | uVar1,0xf000,
                    (*(byte *)(*(long *)(param_1 + 0x138) + 0x680) & 0xf) << 0xc);
    }
  }
  return;
}

