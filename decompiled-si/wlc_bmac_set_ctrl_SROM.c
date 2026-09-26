
undefined8 wlc_bmac_set_ctrl_SROM(long param_1)

{
  int iVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0xb8);
  if (*(int *)(lVar2 + 4) == 1) {
    iVar1 = *(int *)(lVar2 + 0x3c);
    if ((iVar1 == 0xa9a7) || (iVar1 == 0x4331)) {
      si_chipcontrl_epa4331(lVar2,0);
    }
    else if (((iVar1 == 0xa9c4) || ((iVar1 == 0x4360 || (iVar1 == 0x4352)))) &&
            (*(uint *)(lVar2 + 0x40) < 3)) {
      si_chipcontrl_srom4360(lVar2,1);
    }
  }
  return 0;
}

