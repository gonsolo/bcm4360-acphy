
void si_gci_chipctrl_overrides(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  long lVar3;
  int iVar4;
  undefined1 local_48 [24];
  
  uVar1 = FUN_00122a5d(param_2,0xc04,0,0);
  for (iVar4 = 0; iVar4 < (int)((uVar1 & 0xf00) >> 8); iVar4 = iVar4 + 1) {
    osl_snprintf(local_48,0x10,"gcr%d",iVar4);
    lVar3 = getvar(0,local_48);
    if (lVar3 != 0) {
      uVar2 = getintvar(param_3,local_48);
      si_gci_chipcontrol(param_2,iVar4,0xffffffff,uVar2);
    }
  }
  return;
}

