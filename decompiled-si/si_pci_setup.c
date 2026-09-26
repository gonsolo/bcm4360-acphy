
void si_pci_setup(long param_1,int param_2)

{
  long lVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  long lVar5;
  undefined4 uVar6;
  
  if (*(int *)(param_1 + 4) == 1) {
    if (*(int *)(param_1 + 8) == 0x804) {
      uVar6 = *(undefined4 *)(param_1 + 0x1c0);
      uVar3 = si_flag();
      lVar5 = si_setcoreidx(param_1,*(undefined4 *)(param_1 + 0x10));
    }
    else {
      uVar6 = 0;
      uVar3 = 0;
      lVar5 = 0;
    }
    if ((*(int *)(param_1 + 4) == 1) &&
       (((iVar2 = *(int *)(param_1 + 8), iVar2 == 0x83c || (iVar2 == 0x820)) ||
        ((iVar2 == 0x804 && (5 < *(uint *)(param_1 + 0xc))))))) {
      uVar4 = osl_pci_read_config(*(undefined8 *)(param_1 + 0x58),0x94,4);
      osl_pci_write_config(*(undefined8 *)(param_1 + 0x58),0x94,4,uVar4 | param_2 << 8);
    }
    else {
      si_setint(param_1,uVar3);
    }
    if ((*(int *)(param_1 + 4) == 1) && (*(int *)(param_1 + 8) == 0x804)) {
      lVar1 = lVar5 + 0x108;
      uVar4 = osl_readl(lVar1);
      osl_writel(uVar4 | 0xc,lVar1);
      if (10 < *(uint *)(param_1 + 0xc)) {
        lVar5 = lVar5 + 0x14;
        uVar4 = osl_readl(lVar1);
        osl_writel(uVar4 | 0x20,lVar1);
        uVar4 = osl_readl(lVar5);
        osl_writel(uVar4 | 0x8000,lVar5);
        osl_readl(lVar5);
      }
      si_setcoreidx(param_1,uVar6);
    }
  }
  return;
}

