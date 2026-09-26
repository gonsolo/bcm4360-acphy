
bool si_pci_war16165(long param_1)

{
  bool bVar1;
  
  if ((*(int *)(param_1 + 4) == 1) && (*(int *)(param_1 + 8) == 0x804)) {
    bVar1 = *(uint *)(param_1 + 0xc) < 0xb;
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

