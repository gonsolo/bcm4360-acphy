
uint FUN_001913ee(undefined8 param_1,char param_2)

{
  uint uVar1;
  undefined8 uVar2;
  
  if (param_2 == '\x01') {
    uVar2 = 0x840;
  }
  else if (param_2 == '\0') {
    uVar2 = 0x640;
  }
  else {
    if (param_2 != '\x02') {
      return 0;
    }
    uVar2 = 0xa40;
  }
  uVar1 = phy_reg_read(param_1,uVar2);
  return (uVar1 & 0x7f00) >> 8;
}

