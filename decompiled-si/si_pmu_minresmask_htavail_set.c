
void si_pmu_minresmask_htavail_set(long param_1,undefined8 param_2,char param_3)

{
  long lVar1;
  undefined1 extraout_AL;
  undefined1 extraout_AL_00;
  undefined1 extraout_AL_01;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined4 extraout_var_02;
  
  si_coreidx();
  si_setcoreidx(param_1,0);
  if (((param_3 == '\0') && (*(int *)(param_1 + 0x3c) == 0x4313)) &&
     ((*(uint *)(CONCAT44(extraout_var_02,
                          CONCAT22(extraout_var_00,CONCAT11(extraout_AH_00,extraout_AL_00))) + 0x618
                ) & 0x4000) != 0)) {
    lVar1 = CONCAT44(extraout_var_02,
                     CONCAT22(extraout_var_00,CONCAT11(extraout_AH_00,extraout_AL_00))) + 0x618;
    osl_readl(lVar1);
    osl_writel(CONCAT22(extraout_var_01,CONCAT11(extraout_AH_01,extraout_AL_01)) & 0xffffbfff,lVar1)
    ;
  }
  si_setcoreidx(param_1,CONCAT22(extraout_var,CONCAT11(extraout_AH,extraout_AL)));
  return;
}

