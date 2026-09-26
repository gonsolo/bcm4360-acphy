
void si_pmu_pllupd(undefined8 param_1)

{
  si_corereg(param_1,0,0x600,0x400,0x400);
  return;
}

