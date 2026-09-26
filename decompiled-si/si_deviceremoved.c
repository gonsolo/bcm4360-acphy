
bool si_deviceremoved(long param_1)

{
  short sVar1;
  bool bVar2;
  
  bVar2 = false;
  if (*(int *)(param_1 + 4) == 1) {
    sVar1 = osl_pci_read_config(*(undefined8 *)(param_1 + 0x58),0,4);
    bVar2 = sVar1 != 0x14e4;
  }
  return bVar2;
}

