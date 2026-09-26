
void si_seci_upd(long param_1,char param_2)

{
  int iVar1;
  bool bVar2;
  char cVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  long lVar8;
  int local_44;
  long local_40;
  
  if ((*(byte *)(param_1 + 0x1c) & 1) == 0) {
    return;
  }
  if (*(int *)(param_1 + 4) == 1) {
    iVar1 = *(int *)(param_1 + 8);
    if ((iVar1 == 0x83c) || (iVar1 == 0x820)) {
      bVar2 = true;
    }
    else {
      if (iVar1 != 0x804) goto LAB_00120d7c;
      bVar2 = 0xc < *(uint *)(param_1 + 0xc);
    }
  }
  else {
LAB_00120d7c:
    bVar2 = false;
  }
  if ((*(code **)(param_1 + 0x78) == (code *)0x0) ||
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) != *(int *)(param_1 + 0x68))
     ) {
    uVar4 = 0;
  }
  else {
    uVar4 = (**(code **)(param_1 + 0x78))(*(undefined8 *)(param_1 + 0x70));
  }
  if (bVar2) {
    local_40 = *(long *)(param_1 + 0xb8) + 0x3000;
    if (local_40 == 0) goto LAB_00120ec4;
    uVar7 = 0;
LAB_00120deb:
    iVar1 = *(int *)(param_1 + 0x3c);
    if (((iVar1 == 0x4352) || (iVar1 == 0x4331)) || (iVar1 == 0x4360)) {
      uVar5 = osl_readl(local_40 + 0x28);
      uVar6 = 0x1000000;
      if (*(int *)(param_1 + 0x3c) == 0x4331) {
        uVar6 = 2;
      }
      if (param_2 == '\0') {
        uVar6 = ~uVar6 & uVar5;
      }
      else {
        uVar6 = uVar6 | uVar5;
      }
      osl_writel(uVar6,local_40 + 0x28);
      if (param_2 != '\0') {
        lVar8 = local_40 + 0x130;
        uVar6 = osl_readl(lVar8);
        osl_writel(uVar6 | 0x80,lVar8);
        for (local_44 = 0x3f1; (cVar3 = osl_readl(lVar8), cVar3 < '\0' && (local_44 != 9));
            local_44 = local_44 + -10) {
          osl_delay(10);
        }
        osl_writel(0xdb,local_40 + 0x1c0);
        osl_writel(0xda,local_40 + 0x1c0);
      }
    }
    if (bVar2) goto LAB_00120ec4;
  }
  else {
    uVar7 = *(undefined4 *)(param_1 + 0x1c0);
    local_40 = si_setcore(param_1,0x800,0);
    if (local_40 != 0) goto LAB_00120deb;
  }
  si_setcoreidx(param_1,uVar7);
LAB_00120ec4:
  if ((*(code **)(param_1 + 0x80) != (code *)0x0) &&
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) == *(int *)(param_1 + 0x68))
     ) {
    (**(code **)(param_1 + 0x80))(*(undefined8 *)(param_1 + 0x70),uVar4);
  }
  return;
}

