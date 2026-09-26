
undefined8 wlc_bmac_set_ctrl_ePA(long param_1)

{
  long lVar1;
  undefined8 uVar2;
  
  uVar2 = 0xffffffff;
  if (*(char *)(param_1 + 0x186) != '\0') {
    lVar1 = *(long *)(param_1 + 0xb8);
    if ((*(int *)(lVar1 + 4) == 1) &&
       ((*(int *)(lVar1 + 0x3c) == 0xa9a7 || (*(int *)(lVar1 + 0x3c) == 0x4331)))) {
      si_chipcontrl_epa4331(lVar1,1);
    }
    uVar2 = 0;
  }
  return uVar2;
}

