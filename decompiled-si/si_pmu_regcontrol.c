
void si_pmu_regcontrol(undefined8 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  si_corereg(param_1,0,0x658,0xffffffff,param_2);
  si_corereg(param_1,0,0x65c,param_3,param_4);
  return;
}

