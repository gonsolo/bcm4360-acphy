
void gen_radio_reg(undefined8 param_1,undefined2 param_2,ushort param_3,ushort param_4,
                  undefined2 *param_5,ushort *param_6,undefined2 *param_7,ushort *param_8)

{
  ushort uVar1;
  
  *param_5 = param_2;
  uVar1 = read_radio_reg(param_1,param_2);
  *param_6 = uVar1;
  *param_7 = param_2;
  *param_8 = ~param_3 & *param_6 | param_3 & param_4;
  return;
}

