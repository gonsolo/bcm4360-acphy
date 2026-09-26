
void wlc_bmac_switch_macfreq(long param_1,char param_2)

{
  int iVar1;
  long lVar2;
  long lVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined2 local_1c;
  undefined2 local_1a;
  
  lVar2 = *(long *)(param_1 + 0xd0);
  lVar3 = *(long *)(param_1 + 0xb8);
  iVar1 = *(int *)(lVar3 + 0x3c);
  if ((iVar1 == 0xa9a7) || (iVar1 == 0x4331)) {
    if (param_2 == '\x02') {
      osl_writew(0x1862,lVar2 + 0x62e);
    }
    else {
      if (param_2 == '\x01') {
        uVar5 = 0x3e70;
      }
      else {
        uVar5 = 0x6666;
      }
      osl_writew(uVar5,lVar2 + 0x62e);
    }
    local_1a = 6;
  }
  else {
    if (((((((((iVar1 == 0xa99c) || (iVar1 == 0xa8d6)) || (iVar1 == 0xa867)) ||
            ((iVar1 == 0xa868 || (iVar1 == 0xa8d8)))) || (iVar1 == 0xa8d9)) ||
          (((iVar1 == 0xa99d || (iVar1 == 0xa8da)) ||
           ((iVar1 == 0xa87b || (((iVar1 == 0xa8d1 || (iVar1 == 0xa8db)) || (iVar1 == 0xa8dc))))))))
         || ((iVar1 == 0xa9a4 || (iVar1 == 0xa8ea)))) ||
        ((iVar1 == 0xa8eb ||
         (((iVar1 == 0xa8e2 || (iVar1 == 0xa8e3)) ||
          ((iVar1 == 0xa8e4 || (((iVar1 == 0xa8e6 || (iVar1 == 0xa8e5)) || (iVar1 == 0x6362)))))))))
        ) || ((iVar1 == 0x5357 || (iVar1 == 0x4749)))) {
      if (param_2 == '\x02') {
        uVar5 = 0x2082;
        goto LAB_00165c26;
      }
      if (param_2 == '\x01') {
        uVar5 = 0x5341;
      }
      else {
        uVar5 = 0x8889;
      }
      osl_writew(uVar5,lVar2 + 0x62e);
    }
    else {
      if (iVar1 != 0x4335) {
        if ((iVar1 == 0xa9c4) || (iVar1 == 0x4360)) {
          if (iVar1 == 0x4350) goto LAB_00165c6e;
        }
        else if ((iVar1 != 0xaa06) && (iVar1 != 0x4352)) {
          if (iVar1 != 0x4350) {
            if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 8) {
              return;
            }
            if (param_2 == '\x01') {
              uVar5 = 0x7ce0;
            }
            else {
              uVar5 = 0xcccd;
            }
            osl_writew(uVar5,lVar2 + 0x62e);
            local_1a = 0xc;
            goto LAB_00165ce9;
          }
LAB_00165c6e:
          if (*(int *)(lVar3 + 4) == 0) {
            return;
          }
        }
        uVar4 = si_pmu_get_bb_vcofreq(lVar3,*(undefined8 *)(param_1 + 0x10),0x28);
        bcm_uint64_divide(&local_1c,0x3a9,0x80000000,uVar4);
        osl_writew(local_1c,lVar2 + 0x62e);
        goto LAB_00165ce9;
      }
      switch(param_2) {
      case '\x01':
        uVar5 = 0x8889;
        break;
      case '\x02':
        uVar5 = 0x8643;
        break;
      case '\x03':
        uVar5 = 0x7f78;
        break;
      case '\x04':
        uVar5 = 0x83fe;
        break;
      case '\x05':
        uVar5 = 0x7d37;
        break;
      case '\x06':
        uVar5 = 0x7af7;
        break;
      default:
        goto switchD_00165bb1_caseD_7;
      case '\b':
        uVar5 = 0x767b;
        break;
      case '\t':
        uVar5 = 0x743e;
      }
LAB_00165c26:
      osl_writew(uVar5,lVar2 + 0x62e);
    }
    local_1a = 8;
  }
LAB_00165ce9:
  osl_writew(local_1a,lVar2 + 0x630);
switchD_00165bb1_caseD_7:
  return;
}

