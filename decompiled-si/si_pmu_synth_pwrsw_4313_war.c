
void si_pmu_synth_pwrsw_4313_war(long param_1)

{
  long lVar1;
  undefined4 uVar2;
  undefined1 extraout_AL;
  undefined1 extraout_AL_00;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined4 extraout_var_01;
  
  uVar2 = *(undefined4 *)(param_1 + 0x1c0);
  si_setcore(param_1,0x800,0);
  if ((*(uint *)(CONCAT44(extraout_var_01,CONCAT22(extraout_var,CONCAT11(extraout_AH,extraout_AL)))
                + 0x618) & 0x800) == 0) {
    lVar1 = CONCAT44(extraout_var_01,CONCAT22(extraout_var,CONCAT11(extraout_AH,extraout_AL))) +
            0x618;
    osl_readl(lVar1);
    osl_writel(CONCAT22(extraout_var_00,CONCAT11(extraout_AH_00,extraout_AL_00)) | 0x800,lVar1);
  }
  si_setcoreidx(param_1,uVar2);
  return;
}

