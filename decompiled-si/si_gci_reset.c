
void si_gci_reset(undefined8 param_1)

{
  int iVar1;
  int iVar2;
  
  si_gci_direct(param_1,0xc0c,0xffffffff,1);
  si_gci_direct(param_1,0xc0c,0xffffffff,0);
  iVar1 = 0xce0;
  do {
    iVar2 = iVar1 + 4;
    si_gci_direct(param_1,iVar1,0xffffffff,0);
    iVar1 = iVar2;
  } while (iVar2 != 0xd60);
  return;
}

