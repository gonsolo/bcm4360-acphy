
undefined8 si_devpath(long param_1,undefined1 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (param_3 < 1) {
    return 0xffffffff;
  }
  if (param_2 == (undefined1 *)0x0) {
    return 0xffffffff;
  }
  iVar1 = *(int *)(param_1 + 4);
  if (iVar1 == 1) {
    uVar3 = osl_pci_slot(*(undefined8 *)(param_1 + 0x58));
    uVar4 = osl_pci_bus(*(undefined8 *)(param_1 + 0x58));
    iVar2 = osl_snprintf(param_2,(long)param_3,"pci/%u/%u/",uVar4,uVar3);
    goto LAB_0011fdc9;
  }
  if (iVar1 != 0) {
    if (iVar1 == 2) {
      iVar2 = osl_snprintf(param_2,(long)param_3,"pc/1/1/");
      goto LAB_0011fdc9;
    }
    iVar2 = -1;
    if (iVar1 != 4) goto LAB_0011fdc9;
  }
  iVar2 = osl_snprintf(param_2,(long)param_3,"sb/%u/",*(undefined4 *)(param_1 + 0x1c0));
LAB_0011fdc9:
  if ((iVar2 < param_3) && (-1 < iVar2)) {
    return 0;
  }
  *param_2 = 0;
  return 0xffffffff;
}

