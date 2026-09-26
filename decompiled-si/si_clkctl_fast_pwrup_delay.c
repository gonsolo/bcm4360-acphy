
undefined2 si_clkctl_fast_pwrup_delay(long param_1)

{
  uint uVar1;
  bool bVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  code *pcVar6;
  ulong uVar7;
  undefined8 uVar8;
  long lVar9;
  uint uVar10;
  undefined1 auVar11 [16];
  undefined2 local_3a;
  
  if ((*(uint *)(param_1 + 0x18) & 0x10000000) != 0) {
    if ((*(code **)(param_1 + 0x78) == (code *)0x0) ||
       (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) !=
        *(int *)(param_1 + 0x68))) {
      uVar3 = 0;
    }
    else {
      uVar3 = (**(code **)(param_1 + 0x78))(*(undefined8 *)(param_1 + 0x70));
    }
    local_3a = si_pmu_fast_pwrup_delay(param_1,*(undefined8 *)(param_1 + 0x58));
    pcVar6 = *(code **)(param_1 + 0x80);
    if (pcVar6 == (code *)0x0) {
      return local_3a;
    }
    if (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) !=
        *(int *)(param_1 + 0x68)) {
      return local_3a;
    }
    uVar8 = *(undefined8 *)(param_1 + 0x70);
    goto LAB_001211db;
  }
  if ((*(uint *)(param_1 + 0x18) & 0x40000) == 0) {
    return 0;
  }
  if (*(int *)(param_1 + 4) == 1) {
    iVar5 = *(int *)(param_1 + 8);
    if ((iVar5 == 0x83c) || (iVar5 == 0x820)) {
      bVar2 = true;
    }
    else {
      if (iVar5 != 0x804) goto LAB_00121107;
      bVar2 = 0xc < *(uint *)(param_1 + 0xc);
    }
  }
  else {
LAB_00121107:
    bVar2 = false;
  }
  if (bVar2) {
    lVar9 = *(long *)(param_1 + 0xb8) + 0x3000;
    if (lVar9 == 0) {
      return 0;
    }
    uVar3 = 0;
    uVar10 = 0;
LAB_00121171:
    uVar4 = FUN_00120494(param_1,0,lVar9);
    iVar5 = osl_readl(lVar9 + 0xb0);
    uVar1 = uVar4 + 1999999 + iVar5 * 1000000;
    uVar7 = (ulong)uVar1 % (ulong)uVar4;
    local_3a = (undefined2)(uVar1 / uVar4);
    if (bVar2) {
      return local_3a;
    }
  }
  else {
    uVar10 = *(uint *)(param_1 + 0x1c0);
    if ((*(code **)(param_1 + 0x78) == (code *)0x0) ||
       (*(int *)(param_1 + 0x1c8 + (ulong)uVar10 * 4) != *(int *)(param_1 + 0x68))) {
      uVar3 = 0;
    }
    else {
      uVar3 = (**(code **)(param_1 + 0x78))(*(undefined8 *)(param_1 + 0x70));
    }
    auVar11 = si_setcore(param_1,0x800,0);
    uVar7 = auVar11._8_8_;
    lVar9 = auVar11._0_8_;
    local_3a = 0;
    if (lVar9 != 0) goto LAB_00121171;
  }
  si_setcoreidx(param_1,uVar10,uVar7);
  pcVar6 = *(code **)(param_1 + 0x80);
  if (pcVar6 == (code *)0x0) {
    return local_3a;
  }
  if (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) != *(int *)(param_1 + 0x68))
  {
    return local_3a;
  }
  uVar8 = *(undefined8 *)(param_1 + 0x70);
LAB_001211db:
  (*pcVar6)(uVar8,uVar3);
  return local_3a;
}

