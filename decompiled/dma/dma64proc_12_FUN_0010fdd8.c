
void FUN_0010fdd8(long param_1,undefined4 param_2)

{
  long lVar1;
  
  if ((short)*(undefined4 *)(param_1 + 0x6c) != *(short *)(param_1 + 0x6e)) {
    while (lVar1 = FUN_0010fb4d(param_1,param_2), lVar1 != 0) {
      if ((*(byte *)(param_1 + 0xc) & 8) == 0) {
        osl_pktfree(*(undefined8 *)(param_1 + 0x30),lVar1,1);
      }
    }
  }
  return;
}

