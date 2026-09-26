
void FUN_0010fe5a(long param_1)

{
  long lVar1;
  
  while( true ) {
    lVar1 = FUN_0010f9b6(param_1,1);
    if (lVar1 == 0) break;
    osl_pktfree(*(undefined8 *)(param_1 + 0x30),lVar1,0);
  }
  return;
}

