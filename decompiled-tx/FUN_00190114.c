
void FUN_00190114(undefined8 param_1,undefined1 param_2,char param_3)

{
  undefined8 uVar1;
  
  if (param_3 == '\x01') {
    uVar1 = 0x844;
  }
  else if (param_3 == '\0') {
    uVar1 = 0x644;
  }
  else {
    if (param_3 != '\x02') {
      return;
    }
    uVar1 = 0xa44;
  }
  phy_reg_mod(param_1,uVar1,0x7f,param_2);
  return;
}

