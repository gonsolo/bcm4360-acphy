
uint si_corebist(undefined8 param_1)

{
  short sVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = 0x186a9;
  uVar2 = si_core_cflags(param_1,0,0);
  si_core_cflags(param_1,0xffffffff,0x8002);
  while( true ) {
    sVar1 = si_core_sflags(param_1,0,0);
    if ((sVar1 < 0) || (iVar4 == 9)) break;
    iVar4 = iVar4 + -10;
    osl_delay(10);
  }
  uVar3 = si_core_sflags(param_1,0,0);
  si_core_cflags(param_1,0xffff,uVar2);
  return ~-(uint)((uVar3 & 0x4000) == 0);
}

