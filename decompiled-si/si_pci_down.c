
void si_pci_down(long param_1)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 4) == 1) {
    iVar1 = *(int *)(param_1 + 8);
    if ((((iVar1 == 0x820) && (*(int *)(param_1 + 0x3c) == 0x4311)) &&
        (*(uint *)(param_1 + 0x40) < 2)) ||
       (((iVar1 == 0x820 || (iVar1 == 0x804)) &&
        ((iVar2 = *(int *)(param_1 + 0x3c), iVar2 == 0x4321 ||
         ((iVar1 == 0x820 && ((iVar2 == 0x4716 || (iVar2 == 0x4748)))))))))) {
      FUN_00121d9c(param_1,2);
    }
    pcicore_down(*(undefined8 *)(param_1 + 0x90),2);
  }
  return;
}

