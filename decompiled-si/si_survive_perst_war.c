
void si_survive_perst_war(long param_1,char param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  
  if ((*(int *)(param_1 + 4) == 1) &&
     (((*(int *)(param_1 + 0x3c) == 0x4352 || (*(int *)(param_1 + 0x3c) == 0x4360)) &&
      (*(uint *)(param_1 + 0x40) < 4)))) {
    if (param_2 != '\0') {
      iVar2 = osl_pci_read_config(*(undefined8 *)(param_1 + 0x58),0x80,4);
      uVar1 = *(undefined4 *)(param_1 + 0x1c0);
      lVar4 = si_setcore(param_1,0x800,0);
      osl_writel(2,lVar4 + 0x634);
      iVar3 = 0;
      do {
        osl_delay(10);
        iVar3 = iVar3 + 1;
      } while (iVar3 != 2000);
      si_setcoreidx(param_1,uVar1);
      iVar3 = osl_pci_read_config(*(undefined8 *)(param_1 + 0x58),0x80,4);
      if (iVar3 != iVar2) {
        osl_pci_write_config(*(undefined8 *)(param_1 + 0x58),0x80,4,iVar2);
      }
    }
    if (((param_3 != 0) && (*(int *)(param_1 + 4) == 1)) &&
       ((*(int *)(param_1 + 8) == 0x83c || (*(int *)(param_1 + 8) == 0x820)))) {
      pcie_survive_perst(*(undefined8 *)(param_1 + 0x90),param_3,param_4);
    }
  }
  return;
}

