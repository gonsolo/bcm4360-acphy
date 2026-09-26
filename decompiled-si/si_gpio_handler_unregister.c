
void si_gpio_handler_unregister(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  
  if (10 < *(int *)(param_1 + 0x14)) {
    lVar2 = *(long *)(param_1 + 0x98);
    lVar1 = *(long *)(lVar2 + 0x20);
    if (lVar2 == param_2) {
      *(long *)(param_1 + 0x98) = *(long *)(lVar2 + 0x20);
      uVar4 = *(undefined8 *)(param_1 + 0x58);
    }
    else {
      do {
        lVar3 = lVar2;
        lVar2 = lVar1;
        if (lVar2 == 0) {
          return;
        }
        lVar1 = *(long *)(lVar2 + 0x20);
      } while (lVar2 != param_2);
      *(long *)(lVar3 + 0x20) = *(long *)(lVar2 + 0x20);
      uVar4 = *(undefined8 *)(param_1 + 0x58);
    }
    osl_mfree(uVar4,lVar2,0x28);
  }
  return;
}

