
void and_radio_reg(undefined8 param_1,undefined2 param_2,ushort param_3)

{
  ushort uVar1;
  
  uVar1 = read_radio_reg(param_1,param_2);
  write_radio_reg(param_1,param_2,uVar1 & param_3);
  return;
}

