
undefined8 si_pmu_set_ldo_voltage(long param_1,undefined8 param_2,byte param_3,uint param_4)

{
  uint uVar1;
  undefined1 uVar2;
  char cVar3;
  char cVar4;
  bool bVar5;
  undefined8 uStack_38;
  
  param_4 = param_4 & 0xff;
  uVar1 = *(uint *)(param_1 + 0x3c);
  if (uVar1 == 0x4352) {
LAB_00111cb0:
    if (param_3 == 4) {
      uVar2 = 1;
      uVar1 = 0xf;
    }
    else {
LAB_00111cfe:
      uVar2 = 0;
      uVar1 = 0;
    }
LAB_00111d03:
    cVar3 = '\0';
    goto LAB_00111d06;
  }
  if (uVar1 < 0x4353) {
    if (uVar1 != 0x4328) {
      if (0x4328 < uVar1) {
        if (uVar1 != 0x4331) {
          if (uVar1 == 0x4336) goto code_r0x00111c7a;
          if (uVar1 != 0x4330) {
            return uStack_38;
          }
          if (param_3 != 7) {
            if (param_3 != 8) goto LAB_00111cfe;
            goto switchD_00111c7d_caseD_8;
          }
          goto switchD_00111c7d_caseD_7;
        }
        goto LAB_00111cb0;
      }
      if (uVar1 == 0x4314) {
        if (param_3 != 2) goto LAB_00111cfe;
LAB_00111cea:
        uVar2 = 4;
        uVar1 = 7;
        cVar3 = '\x0e';
      }
      else if (uVar1 == 0x4325) {
        switch(param_3) {
        case 5:
          uVar2 = 5;
          goto LAB_00111c25;
        case 6:
          uVar2 = 5;
          uVar1 = 0xf;
          cVar3 = '\r';
          break;
        case 7:
          if ((*(byte *)(param_1 + 0x49) & 2) != 0) {
            param_4 = param_4 ^ 9;
          }
          uVar2 = 3;
          uVar1 = 0x1f;
          cVar3 = '\x14';
          break;
        case 8:
          if ((*(byte *)(param_1 + 0x49) & 2) != 0) {
            param_4 = param_4 ^ 9;
          }
          uVar2 = 3;
          uVar1 = 0x1f;
          cVar3 = '\x19';
          break;
        case 9:
          uVar2 = 5;
          uVar1 = 0x1f;
          goto LAB_00111c9f;
        case 10:
          uVar2 = 6;
          uVar1 = 1;
          goto LAB_00111d03;
        default:
          goto switchD_00111c0e_default;
        }
      }
      else {
        if (uVar1 != 0x4312) {
          return uStack_38;
        }
        if (param_3 != 4) {
          return uStack_38;
        }
        uVar2 = 0;
        uVar1 = 0x3f;
        cVar3 = '\x15';
      }
      goto LAB_00111d06;
    }
LAB_00111ba1:
    if (param_3 == 2) {
      uVar2 = 3;
      goto LAB_00111c8c;
    }
    if (2 < param_3) {
      if (param_3 != 3) {
        if (param_3 != 4) {
          return uStack_38;
        }
        uVar2 = 3;
        uVar1 = 0x3f;
        goto LAB_00111c9f;
      }
      uVar2 = 3;
LAB_00111c25:
      uVar1 = 0xf;
      cVar3 = '\t';
      goto LAB_00111d06;
    }
    if (param_3 != 1) {
      return uStack_38;
    }
    uVar2 = 2;
    uVar1 = 0xf;
    cVar3 = '\x11';
    cVar4 = '\b';
    goto LAB_00111d09;
  }
  if (uVar1 != 0xa962) {
    if (uVar1 < 0xa963) {
      if (uVar1 == 0x5354) goto LAB_00111ba1;
      if (uVar1 == 0xa887) {
        if (param_3 == 8) {
          uVar2 = 4;
          uVar1 = 0xf;
          cVar3 = '\b';
          goto LAB_00111d06;
        }
        if (param_3 == 9) goto LAB_00111cea;
        if (param_3 != 7) goto LAB_00111cfe;
        uVar2 = 0;
        goto LAB_00111cd5;
      }
      bVar5 = uVar1 == 0x4360;
    }
    else {
      if ((uVar1 == 0xa9c4) || (uVar1 == 0xaa06)) goto LAB_00111cb0;
      bVar5 = uVar1 == 0xa9a7;
    }
    if (!bVar5) {
      return uStack_38;
    }
    goto LAB_00111cb0;
  }
code_r0x00111c7a:
  switch(param_3) {
  case 5:
    uVar2 = 4;
LAB_00111c8c:
    uVar1 = 0xf;
    cVar3 = '\x01';
    goto LAB_00111d06;
  case 6:
    uVar2 = 4;
LAB_00111cd5:
    uVar1 = 0xf;
    break;
  case 7:
switchD_00111c7d_caseD_7:
    uVar2 = 3;
    uVar1 = 0x1f;
    goto LAB_00111d03;
  case 8:
switchD_00111c7d_caseD_8:
    uVar2 = 3;
    uVar1 = 0x1f;
    break;
  case 9:
    uVar2 = 4;
    uVar1 = 0xf;
    goto LAB_00111c9f;
  default:
    goto switchD_00111c0e_default;
  case 0xb:
    uVar2 = 2;
    uVar1 = 3;
LAB_00111c9f:
    cVar3 = '\x11';
    goto LAB_00111d06;
  }
  cVar3 = '\x05';
LAB_00111d06:
  cVar4 = '\0';
LAB_00111d09:
  si_corereg(param_1,0,0x658,0xffffffff,uVar2);
  si_corereg(param_1,0,0x65c,uVar1 << (cVar3 + cVar4 & 0x1fU),
             (param_4 & uVar1) << (cVar3 + cVar4 & 0x1fU));
switchD_00111c0e_default:
  return uStack_38;
}

