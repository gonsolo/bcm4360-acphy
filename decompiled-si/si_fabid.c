
ushort si_fabid(long param_1)

{
  uint uVar1;
  ushort uVar2;
  ushort extraout_var;
  bool bVar3;
  ushort local_a;
  
  uVar1 = *(uint *)(param_1 + 0x3c);
  local_a = 0;
  if (uVar1 == 0x4350) goto LAB_001250f1;
  if (uVar1 < 0x4351) {
    if (uVar1 == 0x4330) {
      FUN_00122a5d(param_1,0x28,0,0);
      return ((extraout_var & 0x2000) >> 0xb) + (extraout_var >> 0xe);
    }
    if (0x4330 < uVar1) {
      if (uVar1 == 0x4334) goto LAB_001250f1;
      bVar3 = uVar1 == 0x4335;
LAB_001250b2:
      if (!bVar3) {
        return 0;
      }
LAB_001250f1:
      uVar2 = FUN_00122a5d(param_1,0xf8,0,0);
      return uVar2 & 0xf;
    }
    if (uVar1 == 0x4324) goto LAB_001250f1;
    bVar3 = uVar1 == 0x4329;
  }
  else {
    if (uVar1 < 0xa8ec) {
      if (0xa8e9 < uVar1) goto LAB_001250f1;
      if (uVar1 == 0x5356) goto LAB_001250bd;
      bVar3 = uVar1 == 0xa887;
      goto LAB_001250b2;
    }
    bVar3 = uVar1 == 0xa962;
  }
  if (!bVar3) {
    return 0;
  }
LAB_001250bd:
  si_otp_fabid(param_1,&local_a,1);
  return local_a;
}

