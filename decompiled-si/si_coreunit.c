
int si_coreunit(long param_1)

{
  uint *puVar1;
  int *piVar2;
  long lVar3;
  int iVar4;
  uint uVar5;
  
  puVar1 = (uint *)(param_1 + 0x1c0);
  lVar3 = param_1 + 0x1c8;
  iVar4 = 0;
  for (uVar5 = 0; uVar5 != *puVar1; uVar5 = uVar5 + 1) {
    piVar2 = (int *)(param_1 + 0x1c8);
    param_1 = param_1 + 4;
    iVar4 = iVar4 + (uint)(*piVar2 == *(int *)(lVar3 + (ulong)*puVar1 * 4));
  }
  return iVar4;
}

