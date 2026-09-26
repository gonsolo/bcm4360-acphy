
int si_tcm_size(long param_1)

{
  undefined4 uVar1;
  char cVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  long lVar6;
  uint uVar7;
  undefined4 local_3c;
  
  if ((*(code **)(param_1 + 0x78) == (code *)0x0) ||
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) != *(int *)(param_1 + 0x68))
     ) {
    uVar3 = 0;
  }
  else {
    uVar3 = (**(code **)(param_1 + 0x78))(*(undefined8 *)(param_1 + 0x70));
  }
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  lVar6 = si_setcore(param_1,0x83e,0);
  local_3c = 0;
  if (lVar6 != 0) {
    cVar2 = si_iscoreup(param_1);
    if (cVar2 == '\0') {
      si_core_reset(param_1,0x20,0x20);
    }
    uVar4 = osl_readl(lVar6 + 4);
    local_3c = 0;
    uVar7 = 0;
    while( true ) {
      if (((uVar4 & 0xf0) >> 4) + (uVar4 & 0xf) <= uVar7) break;
      osl_writel(uVar7,lVar6 + 0x40);
      uVar5 = osl_readl(lVar6 + 0x44);
      local_3c = (uVar5 & 0x3f) * 0x2000 + 0x2000 + local_3c;
      uVar7 = uVar7 + 1;
    }
    if (cVar2 == '\0') {
      si_core_disable(param_1,0);
    }
    si_setcoreidx(param_1,uVar1);
  }
  if ((*(code **)(param_1 + 0x80) != (code *)0x0) &&
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) == *(int *)(param_1 + 0x68))
     ) {
    (**(code **)(param_1 + 0x80))(*(undefined8 *)(param_1 + 0x70),uVar3);
  }
  return local_3c;
}

