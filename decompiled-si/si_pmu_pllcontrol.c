
void si_pmu_pllcontrol(undefined8 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  si_corereg(param_1,0,0x660,0xffffffff,param_2);
  si_corereg(param_1,0,0x664,param_3,param_4);
  return;
}

