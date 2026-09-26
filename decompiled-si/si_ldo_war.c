
undefined1  [16] si_ldo_war(long param_1,int param_2)

{
  long lVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  ulong uVar4;
  int iVar5;
  undefined1 auVar6 [16];
  undefined8 uStack_28;
  
  lVar1 = *(long *)(param_1 + 0xb8);
  uVar3 = osl_pci_read_config(*(undefined8 *)(param_1 + 0x58),8,4);
  if (((((param_2 == 0x10f6) || (param_2 == 0x4322)) || (param_2 == 0x432c)) ||
      ((param_2 == 0x432b || (param_2 == 0x432d)))) && ((char)uVar3 == '\0')) {
    uVar2 = osl_pci_read_config(*(undefined8 *)(param_1 + 0x58),0x80,4);
    osl_pci_write_config(*(undefined8 *)(param_1 + 0x58),0x80,4,0x18000000);
    osl_writel(0,lVar1 + 0x658);
    osl_writel(0x3001,lVar1 + 0x65c);
    osl_delay(5000);
    iVar5 = 0x4e29;
    osl_writel(0xd,lVar1 + 0x618);
    while( true ) {
      uVar4 = osl_pci_read_config(*(undefined8 *)(param_1 + 0x58),0xa8,4);
      if ((uVar4 & 0x10000) != 0) break;
      if (iVar5 == 9) {
        uVar3 = 0;
        goto LAB_0011f520;
      }
      iVar5 = iVar5 + -10;
      osl_delay(10);
    }
    uVar3 = osl_pci_write_config(*(undefined8 *)(param_1 + 0x58),0x80,4,uVar2);
  }
  uVar3 = CONCAT71((int7)((ulong)uVar3 >> 8),1);
LAB_0011f520:
  auVar6._8_8_ = uStack_28;
  auVar6._0_8_ = uVar3;
  return auVar6;
}

