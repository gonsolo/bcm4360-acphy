
undefined * si_kattach(long param_1)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined *puVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  
  if (DAT_006f07b8 != '\0') {
    return &DAT_006f07c0;
  }
  uVar2 = osl_reg_map(0x18000000,0x1000);
  puVar3 = (undefined *)0x0;
  puVar1 = puVar3;
  if (param_1 != 0) {
    puVar3 = &DAT_006f0868;
    puVar1 = &DAT_006f0870;
  }
  lVar4 = FUN_00123850(&DAT_006f07c0,0x4710,param_1,uVar2,0,0,puVar3,puVar1);
  if (lVar4 == 0) {
    osl_reg_unmap(uVar2);
    return (undefined *)0x0;
  }
  osl_reg_unmap(uVar2);
  if ((DAT_006f07db & 0x10) == 0) {
    if (DAT_006f07d4 < 0x12) {
      uVar5 = si_clock(&DAT_006f07c0);
    }
    else {
      uVar5 = si_alp_clock(&DAT_006f07c0);
    }
    uVar6 = 1000;
  }
  else {
    if (DAT_006f07fc != 0x5300) {
      DAT_006f0f98 = 0x20;
      goto LAB_0012456f;
    }
    uVar5 = si_alp_clock(&DAT_006f07c0);
    uVar6 = 4000;
  }
  DAT_006f0f98 = (undefined4)((uVar5 & 0xffffffff) / uVar6);
LAB_0012456f:
  DAT_006f07b8 = 1;
  return &DAT_006f07c0;
}

