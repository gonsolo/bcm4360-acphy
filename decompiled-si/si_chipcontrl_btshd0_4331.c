
void si_chipcontrl_btshd0_4331(long param_1,char param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  long lVar4;
  
  if ((*(code **)(param_1 + 0x78) == (code *)0x0) ||
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) != *(int *)(param_1 + 0x68))
     ) {
    uVar2 = 0;
  }
  else {
    uVar2 = (**(code **)(param_1 + 0x78))(*(undefined8 *)(param_1 + 0x70));
  }
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  lVar4 = si_setcore(param_1,0x800,0);
  uVar3 = osl_readl(lVar4 + 0x28);
  if (param_2 == '\0') {
    uVar3 = uVar3 & 0xfffeffff;
  }
  else {
    uVar3 = uVar3 | 0x10000;
  }
  osl_writel(uVar3,lVar4 + 0x28);
  si_setcoreidx(param_1,uVar1);
  if ((*(code **)(param_1 + 0x80) != (code *)0x0) &&
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) == *(int *)(param_1 + 0x68))
     ) {
    (**(code **)(param_1 + 0x80))(*(undefined8 *)(param_1 + 0x70),uVar2);
  }
  return;
}

