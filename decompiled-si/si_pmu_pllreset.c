
void si_pmu_pllreset(undefined8 param_1)

{
  long lVar1;
  undefined8 uVar2;
  long lVar3;
  undefined1 extraout_AL;
  undefined1 extraout_AL_00;
  undefined1 extraout_AL_01;
  undefined1 extraout_AL_02;
  undefined1 extraout_AL_03;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  undefined2 extraout_var_03;
  undefined4 extraout_var_04;
  undefined4 extraout_var_05;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c [3];
  
  FUN_0011192d();
  if ((CONCAT22(extraout_var,CONCAT11(extraout_AH,extraout_AL)) &
      CONCAT22(extraout_var,CONCAT11(extraout_AH,extraout_AL))) != 0) {
    si_osh(param_1);
    uVar2 = CONCAT44(extraout_var_04,
                     CONCAT22(extraout_var_00,CONCAT11(extraout_AH_00,extraout_AL_00)));
    si_coreidx(param_1);
    si_setcoreidx(param_1,0);
    lVar3 = CONCAT44(extraout_var_05,
                     CONCAT22(extraout_var_02,CONCAT11(extraout_AH_02,extraout_AL_02)));
    lVar1 = lVar3 + 0x600;
    FUN_001133d7(param_1,uVar2,
                 CONCAT44(extraout_var_05,
                          CONCAT22(extraout_var_02,CONCAT11(extraout_AH_02,extraout_AL_02))),
                 &local_40,local_3c,&local_44);
    osl_readl(lVar1);
    osl_writel(CONCAT22(extraout_var_03,CONCAT11(extraout_AH_03,extraout_AL_03)) | 0x400,lVar1);
    FUN_00113316(param_1,uVar2,lVar3,local_40,local_3c[0],local_44);
    si_setcoreidx(param_1,CONCAT22(extraout_var_01,CONCAT11(extraout_AH_01,extraout_AL_01)));
  }
  return;
}

