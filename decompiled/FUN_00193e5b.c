
void FUN_00193e5b(undefined8 param_1)

{
  undefined8 uVar1;
  
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     (uVar1 = 0x8ed, acphychipid == 0xaa06)) {
    uVar1 = 0x8e5;
  }
  mod_radio_reg(param_1,uVar1,0x4000,0);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || (uVar1 = 0x8d8, acphychipid == 0xaa06)))) {
    uVar1 = 0x8d0;
  }
  mod_radio_reg(param_1,uVar1,1,0);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || (uVar1 = 0x8f0, acphychipid == 0xaa06)))) {
    uVar1 = 0x8e8;
  }
  mod_radio_reg(param_1,uVar1,0x40,0);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     (uVar1 = 0x8e4, acphychipid == 0xaa06)) {
    uVar1 = 0x8dc;
  }
  mod_radio_reg(param_1,uVar1,0x2000,0);
  osl_delay(0xb);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || (uVar1 = 0x8d8, acphychipid == 0xaa06)))) {
    uVar1 = 0x8d0;
  }
  mod_radio_reg(param_1,uVar1,1,1);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || (uVar1 = 0x8f0, acphychipid == 0xaa06)))) {
    uVar1 = 0x8e8;
  }
  mod_radio_reg(param_1,uVar1,0x40,0x40);
  osl_delay(1);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     (uVar1 = 0x8e4, acphychipid == 0xaa06)) {
    uVar1 = 0x8dc;
  }
  mod_radio_reg(param_1,uVar1,0x2000,0x2000);
  return;
}

