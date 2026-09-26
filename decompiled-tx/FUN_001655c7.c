
undefined8 FUN_001655c7(long param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  ulong uVar3;
  undefined8 uVar4;
  int iVar5;
  long lVar6;
  undefined8 uStack_28;
  
  if ((*(byte *)(*(long *)(param_1 + 0xb8) + 0x1b) & 0x10) == 0) {
    uVar2 = *(uint *)(param_1 + 0x84);
    if ((uVar2 < 9) && (*(char *)(param_1 + 0x10c) != '\0')) {
      wlc_ucode_wake_override_set(param_1,1);
    }
    cVar1 = si_clkctl_cc(*(undefined8 *)(param_1 + 0xb8),param_2);
    *(char *)(param_1 + 0x185) = cVar1;
    if (*(uint *)(param_1 + 0x84) < 0xb) {
      if (cVar1 == '\0') {
        uVar4 = 0;
      }
      else {
        uVar4 = 0x400;
      }
      wlc_bmac_mhf(param_1,0,0x400,uVar4,3);
    }
    if (*(char *)(param_1 + 0x185) == '\0') {
      *(uint *)(param_1 + 0x170) = *(uint *)(param_1 + 0x170) & 0xffffffef;
    }
    else {
      *(uint *)(param_1 + 0x170) = *(uint *)(param_1 + 0x170) | 0x10;
    }
    if ((*(char *)(param_1 + 0x10c) != '\0') && (uVar2 < 9)) {
      wlc_ucode_wake_override_clear(param_1,1);
    }
  }
  else {
    if (*(char *)(param_1 + 0x186) != '\0') {
      if (param_2 == 0) {
        lVar6 = *(long *)(param_1 + 0xd0) + 0x1e0;
        uVar2 = osl_readl(lVar6);
        osl_writel(uVar2 | 2,lVar6);
        osl_delay(0x40);
        for (iVar5 = 0x4e29;
            (uVar3 = osl_readl(*(long *)(param_1 + 0xd0) + 0x1e0), (uVar3 & 0x20000) == 0 &&
            (iVar5 != 9)); iVar5 = iVar5 + -10) {
          osl_delay(10);
        }
      }
      else {
        if (*(int *)(*(long *)(param_1 + 0xb8) + 0x20) == 0) {
          iVar5 = 0x4e29;
          uVar3 = osl_readl(*(long *)(param_1 + 0xd0) + 0x1e0);
          if ((uVar3 & 0x12) != 0) {
            for (; (uVar3 = osl_readl(*(long *)(param_1 + 0xd0) + 0x1e0), (uVar3 & 0x20000) == 0 &&
                   (iVar5 != 9)); iVar5 = iVar5 + -10) {
              osl_delay(10);
            }
          }
        }
        lVar6 = *(long *)(param_1 + 0xd0) + 0x1e0;
        uVar2 = osl_readl(lVar6);
        osl_writel(uVar2 & 0xfffffffd,lVar6);
      }
    }
    *(bool *)(param_1 + 0x185) = param_2 == 0;
  }
  return uStack_28;
}

