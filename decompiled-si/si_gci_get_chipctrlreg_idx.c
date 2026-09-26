
undefined8 si_gci_get_chipctrlreg_idx(uint param_1,uint *param_2,int *param_3)

{
  *param_2 = param_1 >> 3;
  *param_3 = (param_1 & 7) << 2;
  return 0;
}

