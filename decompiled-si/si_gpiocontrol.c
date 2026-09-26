
void si_gpiocontrol(long param_1,uint param_2,uint param_3,char param_4)

{
  if ((param_4 != '\x02') && (*(int *)(param_1 + 4) == 0)) {
    if ((param_3 == 0) && (param_2 == 0)) {
      param_3 = 0;
    }
    else {
      if (param_4 == '\0') {
        param_2 = (param_2 | DAT_006f07b4) & ~DAT_006f07b4;
      }
      else {
        param_2 = param_2 & DAT_006f07b4;
      }
      param_3 = param_3 & param_2;
    }
  }
  FUN_00122a5d(param_1,0x6c,param_2,param_3);
  return;
}

