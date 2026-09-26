
long * dma_attach(long param_1,undefined8 param_2,long param_3,long param_4,long param_5,
                 uint param_6,uint param_7,uint param_8,int param_9,ushort param_10,byte param_11,
                 undefined *param_12)

{
  undefined1 uVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  byte extraout_var;
  byte extraout_var_00;
  int iVar5;
  long *plVar6;
  undefined *puVar7;
  long lVar8;
  short sVar9;
  
  plVar6 = (long *)osl_malloc(param_1,0x130);
  if (plVar6 == (long *)0x0) {
    return (long *)0x0;
  }
  osl_memset(plVar6,0,0x130);
  puVar7 = &DAT_006f0750;
  if (param_12 != (undefined *)0x0) {
    puVar7 = param_12;
  }
  plVar6[4] = (long)puVar7;
  uVar3 = si_core_sflags(param_3,0,0);
  *(byte *)(plVar6 + 8) = (byte)(uVar3 >> 0xc) & 1;
  if ((uVar3 >> 0xc & 1) == 0) {
    plVar6[10] = param_5;
    *plVar6 = (long)&PTR_FUN_00509cb0;
    plVar6[9] = param_4;
  }
  else {
    plVar6[10] = param_5;
    *plVar6 = (long)dma64proc;
    plVar6[9] = param_4;
  }
  (**(code **)(*plVar6 + 0x118))(plVar6,3,0);
  osl_strncpy(plVar6 + 5,param_2,8);
  *(undefined1 *)((long)plVar6 + 0x2f) = 0;
  plVar6[7] = param_3;
  *(short *)((long)plVar6 + 0x6a) = (short)param_6;
  *(short *)((long)plVar6 + 0xa4) = (short)param_7;
  plVar6[6] = param_1;
  iVar5 = 0xcc;
  if (param_9 != -1) {
    iVar5 = param_9;
  }
  *(int *)(plVar6 + 0x1d) = iVar5;
  sVar9 = (short)param_8;
  if (0xcc < param_8) {
    sVar9 = sVar9 - (short)iVar5;
  }
  *(short *)((long)plVar6 + 0xe4) = sVar9;
  *(uint *)((long)plVar6 + 0xec) = (uint)param_10;
  *(uint *)(plVar6 + 0x1e) = (uint)param_11;
  if (param_5 != 0) {
    if ((char)plVar6[8] != '\0') {
      osl_writel(0xffffffff,plVar6[10] + 8);
      uVar3 = osl_readl(plVar6[10] + 8);
      uVar4 = 0x1fff;
      if ((uVar3 & 0xfff) != 0) {
        uVar4 = osl_readl(plVar6[10] + 4);
        uVar4 = uVar4 | 0xf;
      }
      *(uint *)((long)plVar6 + 0x124) = uVar4;
    }
    uVar3 = osl_readl(plVar6[10]);
    *(char *)((long)plVar6 + 0x105) = (char)((uVar3 & 0x1c0000) >> 0x12);
    uVar3 = osl_readl(plVar6[10]);
    *(char *)((long)plVar6 + 0x10a) = (char)((uVar3 & 0xe00000) >> 0x15);
    osl_readl(plVar6[10]);
    *(byte *)((long)plVar6 + 0x10b) = extraout_var & 3;
  }
  if (param_4 != 0) {
    if ((char)plVar6[8] != '\0') {
      osl_writel(0xffffffff,plVar6[9] + 8);
      uVar3 = osl_readl(plVar6[9] + 8);
      uVar4 = 0x1fff;
      if ((uVar3 & 0xfff) != 0) {
        uVar4 = osl_readl(plVar6[9] + 4);
        uVar4 = uVar4 | 0xf;
      }
      *(uint *)((long)plVar6 + 0x11c) = uVar4;
      *(uint *)(plVar6 + 0x24) = uVar4;
    }
    uVar3 = osl_readl(plVar6[9]);
    *(char *)((long)plVar6 + 0x106) = (char)((uVar3 & 0x1c0000) >> 0x12);
    uVar3 = osl_readl(plVar6[9]);
    *(char *)((long)plVar6 + 0x107) = (char)((uVar3 & 0xc0) >> 6);
    uVar3 = osl_readl(plVar6[9]);
    *(char *)(plVar6 + 0x21) = (char)((uVar3 & 0xe00000) >> 0x15);
    osl_readl(plVar6[9]);
    *(byte *)((long)plVar6 + 0x109) = extraout_var_00 & 3;
  }
  *(undefined4 *)((long)plVar6 + 0xf4) = 0;
  *(undefined4 *)((long)plVar6 + 0xfc) = 0;
  if (*(int *)(param_3 + 4) == 1) {
    if (((*(int *)(param_3 + 8) == 0x83c) || (*(int *)(param_3 + 8) == 0x820)) &&
       ((char)plVar6[8] != '\0')) {
      *(undefined4 *)((long)plVar6 + 0xf4) = 0;
      *(undefined4 *)(plVar6 + 0x1f) = 0x80000000;
    }
    else {
      iVar5 = *(int *)(param_3 + 0x3c);
      if (((((iVar5 == 0x10f6) || (iVar5 == 0x4322)) ||
           ((iVar5 == 0xa8d5 || ((iVar5 == 0xa8df || (iVar5 == 0xa867)))))) || (iVar5 == 0xa868)) ||
         (iVar5 == 0xa8d6)) {
        *(undefined4 *)((long)plVar6 + 0xf4) = 0x80000000;
      }
      else {
        *(undefined4 *)((long)plVar6 + 0xf4) = 0x40000000;
      }
      *(undefined4 *)(plVar6 + 0x1f) = 0;
    }
    *(undefined4 *)((long)plVar6 + 0xfc) = *(undefined4 *)((long)plVar6 + 0xf4);
    *(int *)(plVar6 + 0x20) = (int)plVar6[0x1f];
  }
  iVar5 = si_coreid(param_3);
  if ((((iVar5 == 0x829) && (iVar5 = si_corerev(param_3), iVar5 != 0)) &&
      (uVar3 = si_corerev(param_3), uVar3 < 3)) ||
     ((iVar5 = si_coreid(param_3), iVar5 == 0x834 &&
      ((iVar5 = si_corerev(param_3), iVar5 == 0 || (iVar5 = si_corerev(param_3), iVar5 == 1)))))) {
    *(undefined1 *)((long)plVar6 + 0x41) = 0;
  }
  else {
    if ((char)plVar6[8] == '\0') {
      if ((plVar6[9] == 0) && (plVar6[10] == 0)) goto LAB_001114a9;
      uVar1 = FUN_0010f6ff(plVar6[6]);
    }
    else if ((plVar6[9] == 0) && (plVar6[10] == 0)) {
LAB_001114a9:
      uVar1 = 0;
    }
    else {
      FUN_0010f930(plVar6[6]);
      uVar1 = 1;
    }
    *(undefined1 *)((long)plVar6 + 0x41) = uVar1;
  }
  if ((char)plVar6[8] == '\0') {
LAB_001114ff:
    cVar2 = '\x01';
  }
  else {
    if (plVar6[9] == 0) {
      if (plVar6[10] == 0) goto LAB_001114ff;
      osl_writel(0xff0,plVar6[10] + 8);
      lVar8 = plVar6[10];
    }
    else {
      osl_writel(0xff0,plVar6[9] + 8);
      lVar8 = plVar6[9];
    }
    iVar5 = osl_readl(lVar8 + 8);
    if (iVar5 == 0) goto LAB_001114ff;
    cVar2 = '\0';
  }
  *(char *)((long)plVar6 + 0x104) = cVar2;
  if (cVar2 == '\0') {
    *(undefined2 *)(plVar6 + 0xd) = 4;
  }
  else if (((char)plVar6[8] == '\0') ||
          ((*(undefined2 *)(plVar6 + 0xd) = 0xd, param_7 < 0x100 && (param_6 < 0x100)))) {
    *(undefined2 *)(plVar6 + 0xd) = 0xc;
  }
  if (param_6 != 0) {
    lVar8 = osl_malloc(param_1,param_6 * 8);
    plVar6[0xe] = lVar8;
    if (lVar8 == 0) goto LAB_001115f9;
    osl_memset(lVar8,0,param_6 * 8);
  }
  if (param_7 != 0) {
    lVar8 = osl_malloc(param_1,param_7 * 8);
    plVar6[0x16] = lVar8;
    if (lVar8 == 0) goto LAB_001115f9;
    osl_memset(lVar8,0,param_7 * 8);
  }
  if (((param_6 == 0) || (cVar2 = FUN_00110e4c(plVar6,1), cVar2 != '\0')) &&
     ((param_7 == 0 || (cVar2 = FUN_00110e4c(plVar6,2), cVar2 != '\0')))) {
    if (*(int *)((long)plVar6 + 0xf4) == 0) {
      return plVar6;
    }
    if (*(char *)((long)plVar6 + 0x41) != '\0') {
      return plVar6;
    }
    if (((ulong)plVar6[0x11] < 0x40000001) && ((ulong)plVar6[0x19] < 0x40000001)) {
      return plVar6;
    }
  }
LAB_001115f9:
  FUN_00110c0f(plVar6);
  return (long *)0x0;
}

