
void wlc_bmac_wait_for_wake(long param_1)

{
  short sVar1;
  undefined8 uVar2;
  uint uVar3;
  
  if (*(int *)(param_1 + 0x84) == 4) {
    osl_delay(5);
  }
  else {
    if ((*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 2) ||
       (uVar2 = 2000, *(int *)(param_1 + 0x84) != 5)) {
      uVar2 = 0x28;
    }
    osl_delay(uVar2);
    uVar3 = *(ushort *)(param_1 + 0x192) + 9;
    while( true ) {
      sVar1 = wlc_bmac_read_shm(param_1,0x40);
      if ((sVar1 != 4) || (uVar3 < 10)) break;
      uVar3 = uVar3 - 10;
      osl_delay(10);
    }
  }
  return;
}

