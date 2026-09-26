
uint si_findcoreidx(long param_1,int param_2,int param_3)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  
  puVar1 = (uint *)(param_1 + 0x1c4);
  uVar2 = 0;
  iVar3 = 0;
  do {
    if (*puVar1 <= uVar2) {
      return 0x21;
    }
    if (*(int *)(param_1 + 0x1c8) == param_2) {
      if (iVar3 == param_3) {
        return uVar2;
      }
      iVar3 = iVar3 + 1;
    }
    uVar2 = uVar2 + 1;
    param_1 = param_1 + 4;
  } while( true );
}

