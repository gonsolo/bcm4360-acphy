
undefined8 si_setcore(int *param_1,int param_2,int param_3)

{
  undefined8 uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  uVar3 = 0;
  iVar2 = 0;
  piVar4 = param_1;
  do {
    if ((uint)param_1[0x71] <= uVar3) {
      return 0;
    }
    if (piVar4[0x72] == param_2) {
      if (iVar2 == param_3) {
        if (0x1f < uVar3) {
          return 0;
        }
        iVar2 = *param_1;
        if (iVar2 != 0) {
          if ((iVar2 != 3) && (iVar2 != 1)) {
            return 0;
          }
          uVar1 = ai_setcoreidx();
          return uVar1;
        }
        uVar1 = sb_setcoreidx();
        return uVar1;
      }
      iVar2 = iVar2 + 1;
    }
    uVar3 = uVar3 + 1;
    piVar4 = piVar4 + 1;
  } while( true );
}

