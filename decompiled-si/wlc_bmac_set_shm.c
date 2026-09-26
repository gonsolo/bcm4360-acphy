
void wlc_bmac_set_shm(undefined8 param_1,int param_2,undefined2 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  if (0 < param_4) {
    iVar1 = 0;
    do {
      iVar2 = iVar1 + param_2;
      iVar1 = iVar1 + 2;
      FUN_00162c15(param_1,iVar2,param_3,0x10000);
    } while (iVar1 < param_4);
  }
  return;
}

