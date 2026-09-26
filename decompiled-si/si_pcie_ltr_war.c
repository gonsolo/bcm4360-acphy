
void si_pcie_ltr_war(long param_1)

{
  undefined4 uVar1;
  char cVar2;
  undefined8 uVar3;
  
  if (((*(int *)(param_1 + 4) == 1) && (*(int *)(param_1 + 8) == 0x83c)) &&
     (*(int *)(param_1 + 0xc) == 1)) {
    cVar2 = si_pcieltrenable(param_1,0,0);
    uVar1 = *(undefined4 *)(param_1 + 0x1c0);
    if (cVar2 == '\0') {
      si_setcore(param_1,0x812,0);
      uVar3 = 0x2848180;
    }
    else {
      si_setcore(param_1,0x812,0);
      uVar3 = 0x2838280;
    }
    si_wrapperreg(param_1,0x160,0xffffffff,uVar3);
    si_wrapperreg(param_1,0x164,0xffffffff,3);
    si_setcoreidx(param_1,uVar1);
  }
  return;
}

