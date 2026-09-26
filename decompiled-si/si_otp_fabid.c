
undefined8 si_otp_fabid(long param_1,undefined2 *param_2,char param_3)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  sbyte sVar4;
  ushort uVar5;
  ushort local_2a [5];
  
  iVar1 = *(int *)(param_1 + 0x3c);
  if (iVar1 == 0x5356) {
LAB_0011f632:
    uVar5 = 0x3c;
  }
  else {
    if (iVar1 != 0xa962) {
      if (iVar1 != 0x4329) {
        return 0xffffffe6;
      }
      if (*(uint *)(param_1 + 0x40) < 3) {
        sVar4 = 0;
        uVar5 = 0;
        uVar3 = 0;
        goto LAB_0011f643;
      }
      goto LAB_0011f632;
    }
    uVar5 = 0x7c;
  }
  sVar4 = 2;
  uVar3 = 8;
LAB_0011f643:
  uVar2 = 0;
  if ((param_3 == '\x01') && (uVar2 = otp_read_word(param_1,uVar3,local_2a), (int)uVar2 == 0)) {
    *param_2 = (short)((int)(uint)(uVar5 & local_2a[0]) >> sVar4);
  }
  return uVar2;
}

