
void si_gci_set_functionsel(undefined8 param_1,uint param_2,uint param_3)

{
  sbyte sVar1;
  uint uVar2;
  
  sVar1 = (sbyte)((param_2 & 7) << 2);
  uVar2 = 0xf << sVar1;
  si_gci_chipcontrol(param_1,param_2 >> 3,uVar2,(param_3 & 0xff) << sVar1 & uVar2);
  return;
}

