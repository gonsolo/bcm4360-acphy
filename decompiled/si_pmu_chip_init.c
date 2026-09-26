
void si_pmu_chip_init(long param_1,undefined8 param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  
  si_pmu_otp_chipcontrol();
  si_pmu_sprom_enable(param_1,param_2,0);
  uVar2 = si_coreidx(param_1);
  iVar1 = *(int *)(param_1 + 0x3c);
  if (iVar1 == 0x4350) {
    if ((*(uint *)(param_1 + 0x48) & 0x700000) != 0x300000) goto LAB_00116352;
    si_pmu_chipcontrol(param_1,1,0x10,0x10);
    si_pmu_regcontrol(param_1,0,0xffffffff,1);
    si_pmu_chipcontrol(param_1,2,0x3c0000,0x3c0000);
    uVar3 = 0x50;
    uVar4 = 0x50;
    uVar5 = 6;
  }
  else {
    if ((iVar1 != 0xa962) && (iVar1 != 0x4336)) goto LAB_00116352;
    uVar3 = getintvar(0,"clkreq_conf");
    uVar4 = 0x80000;
    uVar5 = 0;
    uVar3 = -(uVar3 & 1) & 0x80000;
  }
  si_pmu_chipcontrol(param_1,uVar5,uVar4,uVar3);
LAB_00116352:
  si_setcoreidx(param_1,uVar2);
  return;
}

