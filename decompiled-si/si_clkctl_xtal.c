
undefined8 si_clkctl_xtal(long param_1,uint param_2,char param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if (*(int *)(param_1 + 4) == 1) {
    if (*(int *)(param_1 + 8) == 0x83c) {
      return 0xffffffff;
    }
    if (*(int *)(param_1 + 8) == 0x820) {
      return 0xffffffff;
    }
    uVar1 = osl_pci_read_config(*(undefined8 *)(param_1 + 0x58),0xb0,4);
    uVar2 = osl_pci_read_config(*(undefined8 *)(param_1 + 0x58),0xb4,4);
    uVar3 = osl_pci_read_config(*(undefined8 *)(param_1 + 0x58),0xb8,4);
    if ((param_3 == '\0') || ((uVar1 & 0x40) == 0)) {
      uVar1 = param_2 & 1;
      if (uVar1 != 0) {
        uVar3 = uVar3 | 0x40;
      }
      param_2 = param_2 & 2;
      if (param_2 != 0) {
        uVar3 = uVar3 | 0x80;
      }
      if (param_3 == '\0') {
        if (uVar1 != 0) {
          uVar2 = uVar2 & 0xffffffbf;
        }
        if (param_2 != 0) {
          uVar2 = uVar2 | 0x80;
        }
        osl_pci_write_config(*(undefined8 *)(param_1 + 0x58),0xb4,4,uVar2);
        osl_pci_write_config(*(undefined8 *)(param_1 + 0x58),0xb8,4,uVar3);
      }
      else {
        if (uVar1 != 0) {
          uVar4 = uVar2 | 0x40;
          uVar1 = uVar2 >> 8;
          uVar2 = uVar4;
          if (param_2 != 0) {
            uVar2 = CONCAT31((int3)uVar1,(char)uVar4) | 0x80;
          }
          osl_pci_write_config(*(undefined8 *)(param_1 + 0x58),0xb4,4,uVar2);
          osl_pci_write_config(*(undefined8 *)(param_1 + 0x58),0xb8,4,uVar3);
          osl_delay(1000);
        }
        if (param_2 != 0) {
          osl_pci_write_config(*(undefined8 *)(param_1 + 0x58),0xb4,4,uVar2 & 0xffffff7f);
          osl_delay(2000);
        }
      }
    }
  }
  else if (*(int *)(param_1 + 4) != 2) {
    return 0xffffffff;
  }
  return 0;
}

