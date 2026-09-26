
void wlc_bmac_core_phypll_reset(long param_1)

{
  short sVar1;
  
  sVar1 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
  if ((sVar1 == 7) || (sVar1 == 4)) {
    si_corereg(*(undefined8 *)(param_1 + 0xb8),0,0x650,0xffffffff,0);
    osl_delay(1);
    si_corereg(*(undefined8 *)(param_1 + 0xb8),0,0x654,4,0);
    osl_delay(1);
    si_corereg(*(undefined8 *)(param_1 + 0xb8),0,0x654,4,4);
    osl_delay(1);
    si_corereg(*(undefined8 *)(param_1 + 0xb8),0,0x654,4,0);
    osl_delay(1);
  }
  return;
}

