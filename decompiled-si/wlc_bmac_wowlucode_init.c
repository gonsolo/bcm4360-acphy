
undefined8 wlc_bmac_wowlucode_init(long param_1)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  
  if ((*(char *)(param_1 + 0x186) != '\0') &&
     (lVar2 = *(long *)(param_1 + 0xb8), *(int *)(lVar2 + 4) == 1)) {
    iVar1 = *(int *)(lVar2 + 0x3c);
    if ((iVar1 == 0xa9a7) || (iVar1 == 0x4331)) {
      si_chipcontrl_epa4331(lVar2,0);
      si_chipcontrl_epa4331_wowl(*(undefined8 *)(param_1 + 0xb8),1);
    }
    else if ((((iVar1 == 0xa9c4) || (iVar1 == 0x4360)) || (iVar1 == 0x4352)) &&
            (*(uint *)(lVar2 + 0x40) < 3)) {
      si_chipcontrl_srom4360(lVar2,1);
    }
  }
  uVar3 = 0xffffffff;
  if (*(char *)(param_1 + 0x186) != '\0') {
    wlc_bmac_mctrl(param_1,0xffffffff,0x406);
    uVar3 = 0;
  }
  return uVar3;
}

