
void wlc_bmac_write_hw_bcntemplates(long param_1,undefined8 param_2,undefined4 param_3,char param_4)

{
  byte bVar1;
  long lVar2;
  
  if (param_4 == '\0') {
    lVar2 = *(long *)(param_1 + 0xd0) + 0x124;
    bVar1 = osl_readl(lVar2);
    if ((bVar1 & 1) == 0) {
      FUN_00163582(param_1,param_2,param_3);
      return;
    }
    bVar1 = osl_readl(lVar2);
    if ((bVar1 & 2) != 0) {
      return;
    }
  }
  else {
    FUN_00163582();
  }
  FUN_001635f7(param_1,param_2,param_3);
  return;
}

