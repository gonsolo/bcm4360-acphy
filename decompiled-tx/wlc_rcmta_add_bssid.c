
undefined8 wlc_rcmta_add_bssid(long *param_1,long param_2)

{
  uint uVar1;
  undefined8 uVar2;
  int iVar3;
  long lVar4;
  
  if (((((*(char *)(param_2 + 0xf1) == '\0') && (*(char *)(param_2 + 0xf0) == '\0')) &&
       (*(char *)(param_2 + 0xf2) == '\0')) &&
      ((*(char *)(param_2 + 0xf3) == '\0' && (*(char *)(param_2 + 0xf4) == '\0')))) &&
     (*(char *)(param_2 + 0xf5) == '\0')) {
LAB_0017d0f2:
    uVar2 = 0xffffffff;
  }
  else {
    lVar4 = *(long *)(param_2 + 0x350);
    if (lVar4 == 0) {
      if (((param_2 == param_1[0x5f]) || (*(int *)(param_2 + 0x90) == 0)) ||
         (iVar3 = 2, (*(byte *)(param_2 + 0x101) & 4) != 0)) {
        iVar3 = 0;
      }
      uVar1 = FUN_0017cf01(param_1,(-(uint)(*(char *)(param_2 + 0x22) == '\0') & 0xffffffde) + 0x32,
                           iVar3 + 1);
      if ((int)uVar1 < 0) goto LAB_0017d0f2;
      lVar4 = *(long *)(param_1[99] + (long)(int)uVar1 * 8);
      *(long *)(param_2 + 0x350) = lVar4;
    }
    else {
      uVar1 = (uint)*(byte *)(lVar4 + 6);
    }
    osl_memcpy(lVar4,param_2 + 0xf0,6);
    if (*(int *)(lVar4 + 0x10) == 0) {
      if (*(char *)(*param_1 + 0x34) != '\0') {
        wlc_set_rcmta(param_1,uVar1 - 4,lVar4);
      }
    }
    else {
      wlc_key_update(param_1,uVar1,param_2);
    }
    wlc_mhf(param_1,3,2,2,3);
    uVar2 = 0;
  }
  return uVar2;
}

