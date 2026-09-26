
void wlc_bmac_blink_sync(long param_1,uint param_2)

{
  long lVar1;
  int iVar2;
  
  lVar1 = *(long *)(param_1 + 0x198);
  iVar2 = 0;
  do {
    if ((1 << ((byte)iVar2 & 0x1f) & param_2) != 0) {
      *(undefined1 *)(lVar1 + 0x1d) = 1;
    }
    iVar2 = iVar2 + 1;
    lVar1 = lVar1 + 0x18;
  } while (iVar2 != 0x20);
  return;
}

