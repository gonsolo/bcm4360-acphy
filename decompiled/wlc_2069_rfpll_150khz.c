
void wlc_2069_rfpll_150khz(undefined8 param_1)

{
  undefined8 uVar1;
  
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     (uVar1 = 0x8d1, acphychipid == 0xaa06)) {
    uVar1 = 0x8c9;
  }
  mod_radio_reg(param_1,uVar1,0xff00,0);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || (uVar1 = 0x8d1, acphychipid == 0xaa06)))) {
    uVar1 = 0x8c9;
  }
  mod_radio_reg(param_1,uVar1,0xff,2);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || (uVar1 = 0x8d2, acphychipid == 0xaa06)))) {
    uVar1 = 0x8ca;
  }
  write_radio_reg(param_1,uVar1,2);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     (uVar1 = 0x8d4, acphychipid == 0xaa06)) {
    uVar1 = 0x8cc;
  }
  mod_radio_reg(param_1,uVar1,0xff,2);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || (uVar1 = 0x8d4, acphychipid == 0xaa06)))) {
    uVar1 = 0x8cc;
  }
  mod_radio_reg(param_1,uVar1,0xff00,0xff00);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || (uVar1 = 0x8cf, acphychipid == 0xaa06)))) {
    uVar1 = 0x8c7;
  }
  write_radio_reg(param_1,uVar1,0xffff);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     (uVar1 = 0x8d0, acphychipid == 0xaa06)) {
    uVar1 = 0x8c8;
  }
  write_radio_reg(param_1,uVar1,0xffff);
  return;
}

