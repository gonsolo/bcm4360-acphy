
void FUN_0010f3af(long param_1,int param_2,uint param_3)

{
  uint uVar1;
  long lVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x40) == '\0') {
    iVar3 = *(int *)(param_1 + 0xf4);
    if ((iVar3 == 0) || ((param_3 & 0xc0000000) == 0)) {
      if (param_2 == 1) {
        lVar2 = *(long *)(param_1 + 0x48);
      }
      else {
        lVar2 = *(long *)(param_1 + 0x50);
      }
      lVar2 = lVar2 + 4;
      param_3 = iVar3 + param_3;
      goto LAB_0010f4f7;
    }
    if (param_2 != 1) {
      iVar3 = iVar3 + (param_3 & 0x3fffffff);
      lVar2 = *(long *)(param_1 + 0x50) + 4;
      goto LAB_0010f4d5;
    }
    iVar3 = iVar3 + (param_3 & 0x3fffffff);
    lVar2 = *(long *)(param_1 + 0x48) + 4;
LAB_0010f4c0:
    osl_writel(iVar3,lVar2);
    lVar2 = *(long *)(param_1 + 0x48);
  }
  else {
    if (*(char *)(param_1 + 0x104) == '\0') {
      if (param_2 == 1) {
        *(uint *)(param_1 + 0xa0) = param_3;
      }
      else {
        *(uint *)(param_1 + 0xe0) = param_3;
      }
    }
    iVar3 = *(int *)(param_1 + 0xf4);
    if ((iVar3 == 0) || ((param_3 & 0xc0000000) == 0)) {
      if (param_2 == 1) {
        osl_writel(iVar3 + param_3,*(long *)(param_1 + 0x48) + 8);
        lVar2 = *(long *)(param_1 + 0x48);
      }
      else {
        osl_writel(iVar3 + param_3,*(long *)(param_1 + 0x50) + 8);
        lVar2 = *(long *)(param_1 + 0x50);
      }
      lVar2 = lVar2 + 0xc;
      param_3 = *(uint *)(param_1 + 0xf8);
      goto LAB_0010f4f7;
    }
    if (param_2 == 1) {
      osl_writel(iVar3 + (param_3 & 0x3fffffff),*(long *)(param_1 + 0x48) + 8);
      iVar3 = *(int *)(param_1 + 0xf8);
      lVar2 = *(long *)(param_1 + 0x48) + 0xc;
      goto LAB_0010f4c0;
    }
    osl_writel(iVar3 + (param_3 & 0x3fffffff),*(long *)(param_1 + 0x50) + 8);
    iVar3 = *(int *)(param_1 + 0xf8);
    lVar2 = *(long *)(param_1 + 0x50) + 0xc;
LAB_0010f4d5:
    osl_writel(iVar3,lVar2);
    lVar2 = *(long *)(param_1 + 0x50);
  }
  uVar1 = osl_readl(lVar2);
  param_3 = uVar1 & 0xfffcffff | (param_3 >> 0x1e) << 0x10;
LAB_0010f4f7:
  osl_writel(param_3,lVar2);
  return;
}

