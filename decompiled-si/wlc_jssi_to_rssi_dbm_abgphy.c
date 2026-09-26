
int wlc_jssi_to_rssi_dbm_abgphy(long param_1,int param_2,int *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_18 [4];
  
  if (*(int *)(param_1 + 0x160) == 0) {
    iVar2 = (*param_3 * -5 + 8 >> 4) + -0x3e;
  }
  else {
    iVar3 = 0;
    for (iVar2 = 0; iVar2 < param_4; iVar2 = iVar2 + 1) {
      iVar1 = *param_3;
      if (-1 < iVar1) {
        if (iVar1 < 0x40) {
          iVar3 = iVar3 + (uint)(byte)(&DAT_00675be0)[iVar1];
        }
        else {
          iVar3 = iVar3 + (uint)DAT_00675c1f;
        }
      }
      param_3 = param_3 + 1;
    }
    local_18[0] = -2;
    local_18[1] = 0x13;
    local_18[2] = 0xe;
    local_18[3] = 0x19;
    iVar2 = 0;
    if (param_2 == 8) {
      iVar2 = 0x18;
    }
    iVar2 = (((((iVar3 + param_4 / 2) / param_4) * 0x7d + 0x40 >> 7) + -0x48) -
            local_18[~-(uint)(param_2 - 6U < 3) & 3]) + iVar2;
  }
  return iVar2;
}

