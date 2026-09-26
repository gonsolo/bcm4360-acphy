
uint si_pmu_fast_pwrup_delay(long param_1,undefined8 param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined8 uVar5;
  ulong uVar6;
  bool bVar7;
  undefined1 auVar8 [16];
  
  uVar1 = si_coreidx();
  auVar8 = si_setcoreidx(param_1,0);
  uVar6 = auVar8._8_8_;
  uVar2 = *(uint *)(param_1 + 0x3c);
  if (uVar2 < 0xa869) {
    if (uVar2 < 0xa867) {
      uVar4 = 7000;
      if (uVar2 == 0x4328) goto LAB_00116e76;
      if (0x4328 < uVar2) {
        if (uVar2 != 0x4335) {
          if (0x4335 < uVar2) {
            if (uVar2 != 0x4352) {
              if (uVar2 < 0x4353) {
                if (uVar2 != 0x4336) {
                  bVar7 = uVar2 == 0x4350;
                  goto LAB_00116cf5;
                }
                goto LAB_00116dfd;
              }
              if (uVar2 != 0x4360) {
                bVar7 = uVar2 == 0x6362;
                goto LAB_00116db9;
              }
            }
            uVar4 = (-(uint)(*(uint *)(param_1 + 0x40) < 4) & 0xfffffa24) + 3000;
            goto LAB_00116e76;
          }
          if (uVar2 == 0x4330) {
LAB_00116dfd:
            uVar2 = si_ilp_clock(param_1);
            uVar5 = 0x18;
            goto LAB_00116e43;
          }
          if (uVar2 < 0x4331) {
            bVar7 = uVar2 == 0x4329;
LAB_00116cbb:
            if (!bVar7) goto LAB_00116dc6;
            goto LAB_00116deb;
          }
          if (uVar2 == 0x4331) goto LAB_00116dbb;
          bVar7 = uVar2 == 0x4334;
LAB_00116cf5:
          if (!bVar7) goto LAB_00116dc6;
        }
LAB_00116e33:
        uVar2 = si_ilp_clock(param_1);
        uVar5 = 0x1d;
        goto LAB_00116e43;
      }
      if (uVar2 == 0x4315) {
LAB_00116deb:
        uVar2 = si_ilp_clock(param_1);
        uVar5 = 0x15;
        goto LAB_00116e43;
      }
      if (uVar2 < 0x4316) {
        if (0x4313 < uVar2) goto LAB_00116e0f;
        if (uVar2 < 0x4312) {
          bVar7 = uVar2 == 0x10f6;
          goto LAB_00116db9;
        }
      }
      else if (uVar2 != 0x4322) {
        if (0x4322 < uVar2) {
          if (uVar2 != 0x4324) {
            bVar7 = uVar2 == 0x4325;
            goto LAB_00116cbb;
          }
          goto LAB_00116e33;
        }
        bVar7 = uVar2 == 0x4319;
        goto LAB_00116db9;
      }
    }
  }
  else if (uVar2 < 0xa8e8) {
    if (uVar2 < 0xa8e2) {
      if (uVar2 < 0xa8d7) {
        if (uVar2 < 0xa8d5) {
          if (uVar2 == 0xa886) {
LAB_00116e0f:
            uVar2 = si_ilp_clock(param_1);
            uVar5 = 0x1c;
LAB_00116e43:
            iVar3 = FUN_00113084(param_1,param_2,auVar8._0_8_,uVar5);
            uVar2 = (iVar3 + 2) * 0xb * ((uVar2 + 999999) / uVar2);
            uVar4 = uVar2 / 10;
            uVar6 = (ulong)uVar2 % 10;
            goto LAB_00116e76;
          }
          if (uVar2 < 0xa887) {
            bVar7 = uVar2 == 0xa87b;
          }
          else {
            if (uVar2 == 0xa887) {
              uVar2 = si_ilp_clock(param_1);
              uVar5 = 6;
              goto LAB_00116e43;
            }
            bVar7 = uVar2 == 0xa8d1;
          }
          goto LAB_00116db9;
        }
      }
      else {
        if (uVar2 < 0xa8d8) goto LAB_00116dc6;
        if (0xa8dc < uVar2) {
          bVar7 = uVar2 == 0xa8df;
          goto LAB_00116db9;
        }
      }
    }
  }
  else if (uVar2 < 0xa99e) {
    if (uVar2 < 0xa99c) {
      if (0xa8e9 < uVar2) {
        if (uVar2 < 0xa8ec) goto LAB_00116e33;
        if (uVar2 == 0xa962) goto LAB_00116dfd;
      }
LAB_00116dc6:
      uVar4 = 20000;
      goto LAB_00116e76;
    }
  }
  else if (uVar2 != 0xa9a7) {
    if (uVar2 < 0xa9a8) {
      bVar7 = uVar2 == 0xa9a4;
    }
    else {
      if (uVar2 == 0xa9c4) goto LAB_00116dbb;
      bVar7 = uVar2 == 0xaa06;
    }
LAB_00116db9:
    if (!bVar7) goto LAB_00116dc6;
  }
LAB_00116dbb:
  uVar4 = 0xe74;
LAB_00116e76:
  si_setcoreidx(param_1,uVar1,uVar6);
  return uVar4;
}

