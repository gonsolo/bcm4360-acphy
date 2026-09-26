
void FUN_00161ca7(long param_1,long param_2)

{
  uint *puVar1;
  long lVar2;
  int iVar3;
  ushort uVar4;
  
  iVar3 = 0;
  lVar2 = *(long *)(param_1 + 0xd0);
  while( true ) {
    puVar1 = (uint *)(param_2 + (long)iVar3 * 8);
    uVar4 = (ushort)*puVar1;
    if (uVar4 == 0xffff) break;
    if (*(short *)((long)puVar1 + 2) == 2) {
      osl_writew((short)puVar1[1],lVar2 + (ulong)uVar4);
    }
    else if (*(short *)((long)puVar1 + 2) == 4) {
      osl_writel(puVar1[1],lVar2 + ((ulong)*puVar1 & 0xffff));
    }
    iVar3 = iVar3 + 1;
  }
  return;
}

