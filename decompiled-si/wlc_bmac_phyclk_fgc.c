
void wlc_bmac_phyclk_fgc(long param_1,char param_2)

{
  short sVar1;
  undefined8 uVar2;
  
  sVar1 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
  if (((sVar1 == 7) || (sVar1 == 4)) || (sVar1 == 0xb)) {
    if (param_2 == '\x01') {
      uVar2 = 2;
    }
    else {
      uVar2 = 0;
    }
    si_core_cflags(*(undefined8 *)(param_1 + 0xb8),2,uVar2);
  }
  return;
}

