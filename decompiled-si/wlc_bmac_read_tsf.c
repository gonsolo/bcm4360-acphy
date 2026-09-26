
void wlc_bmac_read_tsf(long param_1,undefined4 *param_2,undefined4 *param_3)

{
  long lVar1;
  undefined4 uVar2;
  
  lVar1 = *(long *)(param_1 + 0xd0);
  uVar2 = osl_readl(lVar1 + 0x180);
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = uVar2;
  }
  if (param_3 != (undefined4 *)0x0) {
    uVar2 = osl_readl(lVar1 + 0x184);
    *param_3 = uVar2;
  }
  return;
}

