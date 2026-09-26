
void FUN_001672ac(long param_1,ushort param_2,char param_3)

{
  ushort *puVar1;
  uint uVar2;
  long lVar3;
  short sVar4;
  ulong uVar5;
  undefined8 uVar6;
  undefined1 uVar7;
  undefined1 *puVar8;
  bool bVar9;
  
  lVar3 = *(long *)(param_1 + 0xb8);
  if (((*(int *)(lVar3 + 0x3c) == 0xa9a7) || (*(int *)(lVar3 + 0x3c) == 0x4331)) &&
     (*(int *)(lVar3 + 0x28) != 0xd6)) {
    si_seci_upd(lVar3,(param_2 & 0xc000) == 0);
  }
  osl_readw(*(long *)(param_1 + 0xd0) + 0x3e0);
  FUN_001634a6(param_1,*(long *)(param_1 + 0xe8) + 8);
  uVar2 = *(uint *)(param_1 + 0x84);
  if (uVar2 == 0x2b) {
    puVar8 = d11ac3bsinitvals43;
    sVar4 = *(short *)(*(long *)(param_1 + 0xe8) + 0x1c);
joined_r0x001673b6:
    if (sVar4 != 0xb) goto LAB_00167702;
  }
  else {
    if (uVar2 == 0x2a) {
      puVar8 = d11ac1bsinitvals42;
      sVar4 = *(short *)(*(long *)(param_1 + 0xe8) + 0x1c);
      goto joined_r0x001673b6;
    }
    if (((uVar2 == 0x2c) || (uVar2 == 0x29)) ||
       ((uVar2 == 0x2e || ((uVar2 == 0x2f || (uVar2 == 0x2d)))))) {
      puVar8 = d11ac2bsinitvals41;
      sVar4 = *(short *)(*(long *)(param_1 + 0xe8) + 0x1c);
      goto joined_r0x001673b6;
    }
    if (uVar2 == 0x28) {
      puVar8 = d11ac0bsinitvals40;
      sVar4 = *(short *)(*(long *)(param_1 + 0xe8) + 0x1c);
      goto joined_r0x001673b6;
    }
    if (uVar2 == 0x22) {
      puVar8 = d11n19bsinitvals34;
      sVar4 = *(short *)(*(long *)(param_1 + 0xe8) + 0x1c);
joined_r0x00167455:
      if (sVar4 != 4) goto LAB_00167702;
    }
    else {
      if (uVar2 == 0x21) {
        puVar8 = d11lcn400bsinitvals33;
        if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 10) goto LAB_00167702;
        goto LAB_001676fa;
      }
      if (uVar2 == 0x20) {
        puVar8 = d11n18bsinitvals32;
        sVar4 = *(short *)(*(long *)(param_1 + 0xe8) + 0x1c);
        goto joined_r0x00167455;
      }
      if (uVar2 == 0x1f) {
        bVar9 = *(short *)(*(long *)(param_1 + 0xe8) + 0x1c) == 4;
LAB_00167471:
        if (!bVar9) goto LAB_00167702;
        puVar8 = d11ht0bsinitvals29;
      }
      else {
        if (uVar2 == 0x1e) {
          puVar8 = d11n16bsinitvals30;
          sVar4 = *(short *)(*(long *)(param_1 + 0xe8) + 0x1c);
          goto joined_r0x00167455;
        }
        if (uVar2 == 0x1d) {
          bVar9 = *(short *)(*(long *)(param_1 + 0xe8) + 0x1c) == 7;
          goto LAB_00167471;
        }
        if (uVar2 == 0x1a) {
          puVar8 = d11ht0bsinitvals26;
          if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 7) goto LAB_00167702;
        }
        else if ((uVar2 == 0x1c) || (uVar2 == 0x19)) {
          puVar8 = d11n0bsinitvals25;
          sVar4 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
          if (sVar4 != 4) {
            puVar8 = d11lcn0bsinitvals25;
joined_r0x001674d6:
            if (sVar4 != 8) goto LAB_00167702;
          }
        }
        else if (uVar2 == 0x18) {
          puVar8 = d11n0bsinitvals24;
          sVar4 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
          if (sVar4 != 4) {
            puVar8 = d11lcn0bsinitvals24;
            goto joined_r0x001674d6;
          }
        }
        else if (uVar2 < 0x16) {
          if (uVar2 == 0x15) {
            puVar8 = d11sslpn3bsinitvals21;
            if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 6) goto LAB_00167702;
          }
          else if (uVar2 == 0x14) {
            puVar8 = d11sslpn1bsinitvals20;
            if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 6) {
LAB_001675a1:
              sVar4 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
              if (sVar4 == 4) goto LAB_001675b1;
              puVar8 = d11sslpn0bsinitvals16;
              if (sVar4 != 6) {
                puVar8 = d11lp0bsinitvals16;
                goto joined_r0x001675f9;
              }
            }
          }
          else {
            if (0xf < uVar2) goto LAB_001675a1;
            if (uVar2 == 0xf) {
              puVar8 = d11lp0bsinitvals15;
              sVar4 = *(short *)(*(long *)(param_1 + 0xe8) + 0x1c);
            }
            else {
              if (uVar2 != 0xe) {
                if (uVar2 == 0xd) {
                  puVar8 = d11lp0bsinitvals13;
                  sVar4 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
                  if ((sVar4 != 5) && (puVar8 = d11b0g0bsinitvals13, sVar4 != 2)) {
                    if (sVar4 != 0) goto LAB_00167702;
                    uVar5 = si_core_sflags(*(undefined8 *)(param_1 + 0xb8),0,0);
                    puVar8 = d11a0g1bsinitvals13;
                    if ((uVar5 & 1) == 0) goto LAB_00167702;
                  }
                }
                else {
                  if (10 < uVar2) {
                    puVar8 = d11n0bsinitvals11;
                    sVar4 = *(short *)(*(long *)(param_1 + 0xe8) + 0x1c);
                    goto joined_r0x00167455;
                  }
                  if (uVar2 < 5) {
                    if (uVar2 != 4) goto LAB_00167702;
                    puVar8 = d11a0g0bsinitvals4;
                    if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 0) {
                      puVar8 = d11b0g0bsinitvals4;
                    }
                  }
                  else {
                    puVar8 = d11b0g0bsinitvals5;
                    if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) == 0) {
                      uVar5 = si_core_sflags(*(undefined8 *)(param_1 + 0xb8),0,0);
                      puVar8 = d11a0g1bsinitvals5;
                      if ((uVar5 & 1) == 0) {
                        puVar8 = d11a0g0bsinitvals5;
                      }
                    }
                  }
                }
                goto LAB_001676fa;
              }
              puVar8 = d11lp0bsinitvals14;
              sVar4 = *(short *)(*(long *)(param_1 + 0xe8) + 0x1c);
            }
joined_r0x001675f9:
            if (sVar4 != 5) goto LAB_00167702;
          }
        }
        else {
          sVar4 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
          if (sVar4 == 4) {
            puVar8 = d11n0bsinitvals22;
            if (uVar2 == 0x17) {
LAB_001675b1:
              puVar8 = d11n0bsinitvals16;
            }
          }
          else if ((sVar4 != 6) || (puVar8 = d11sslpn4bsinitvals22, uVar2 != 0x16))
          goto LAB_00167702;
        }
      }
    }
  }
LAB_001676fa:
  FUN_00161ca7(param_1,puVar8);
LAB_00167702:
  if ((param_3 == '\0') || (*(uint *)(param_1 + 0x84) < 0x28)) {
    wlc_phy_init(*(undefined8 *)(*(long *)(param_1 + 0xe8) + 0x28),param_2);
  }
  FUN_001633c4(param_1);
  wlc_bmac_set_cwmin(param_1,*(undefined2 *)(*(long *)(param_1 + 0xe8) + 0x14));
  wlc_bmac_set_cwmax(param_1,*(undefined2 *)(*(long *)(param_1 + 0xe8) + 0x16));
  uVar7 = 1;
  if (**(int **)(param_1 + 0xe8) != 1) {
    uVar7 = *(undefined1 *)(param_1 + 0x102);
  }
  FUN_00163456(param_1,uVar7);
  wlc_bmac_write_shm(param_1,0x52,*(undefined2 *)(*(long *)(param_1 + 0xe8) + 0x1c));
  wlc_bmac_write_shm(param_1,0x50,*(undefined2 *)(*(long *)(param_1 + 0xe8) + 0x1e));
  FUN_00163143(param_1);
  if ((*(int *)(param_1 + 0x84) == 4) && (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) == 0)) {
    wlc_bmac_write_shm(param_1,0x3c,0x1d);
  }
  FUN_00163509(param_1);
  if (**(int **)(param_1 + 0xe8) == 1) {
    uVar6 = 8;
  }
  else {
    uVar6 = 0;
  }
  wlc_bmac_mhf(param_1,4,8,uVar6,3);
  FUN_00161dab(param_1);
  if ((((**(int **)(param_1 + 0xe8) == 1) &&
       (lVar3 = *(long *)(param_1 + 0xb8), *(int *)(lVar3 + 4) == 1)) &&
      ((*(int *)(lVar3 + 0x3c) == 0xa9a7 || (*(int *)(lVar3 + 0x3c) == 0x4331)))) &&
     (*(int *)(lVar3 + 0x44) == 9 || *(int *)(lVar3 + 0x44) == 0xb)) {
    puVar1 = (ushort *)(*(int **)(param_1 + 0xe8) + 2);
    *puVar1 = *puVar1 & 0xfff7;
    FUN_001634a6(param_1,*(long *)(param_1 + 0xe8) + 8);
  }
  wlc_bmac_set_extlna_pwrsave_shmem(param_1);
  return;
}

