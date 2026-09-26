
undefined8 dma_addrwidth(long param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 uVar2;
  ulong uVar3;
  
  uVar2 = si_osh();
  uVar3 = si_core_sflags(param_1,0,0);
  if ((uVar3 & 0x1000) == 0) {
    if ((*(int *)(param_1 + 4) != 0) &&
       (((*(int *)(param_1 + 4) != 1 ||
         ((*(int *)(param_1 + 8) != 0x83c && (*(int *)(param_1 + 8) != 0x820)))) &&
        (cVar1 = FUN_0010f6ff(uVar2,param_2), cVar1 == '\0')))) {
      return 0x1e;
    }
  }
  else {
    cVar1 = si_backplane64(param_1);
    if ((cVar1 != '\0') &&
       ((*(int *)(param_1 + 4) == 0 ||
        ((*(int *)(param_1 + 4) == 1 &&
         ((*(int *)(param_1 + 8) == 0x83c || (*(int *)(param_1 + 8) == 0x820)))))))) {
      return 0x40;
    }
  }
  return 0x20;
}

