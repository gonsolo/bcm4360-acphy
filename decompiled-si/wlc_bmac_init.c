
/* WARNING: Type propagation algorithm not settling */

void wlc_bmac_init(long *param_1,ushort param_2,char param_3)

{
  ushort *puVar1;
  char cVar2;
  char cVar3;
  long lVar4;
  long lVar5;
  long *plVar6;
  ulong uVar7;
  ushort uVar8;
  undefined2 uVar9;
  short sVar10;
  undefined4 uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  ulong uVar16;
  undefined4 uVar17;
  undefined8 uVar18;
  undefined1 *puVar19;
  long lVar20;
  undefined *puVar21;
  ushort uVar22;
  int iVar23;
  long lVar24;
  uint uVar25;
  int iVar26;
  long lVar27;
  ushort uVar28;
  bool bVar29;
  ushort local_70;
  undefined2 local_58;
  undefined2 local_56;
  undefined2 local_54;
  undefined2 local_52;
  undefined2 local_50;
  undefined2 local_4e;
  undefined4 local_3c [3];
  
  lVar4 = *param_1;
  cVar2 = *(char *)((long)param_1 + 0x185);
  if (cVar2 == '\0') {
    FUN_001655c7(param_1,0);
  }
  uVar11 = wl_intrsoff(*(undefined8 *)(lVar4 + 0x10));
  iVar23 = *(int *)(param_1[0x17] + 0x3c);
  if (((iVar23 == 0x4352) || (iVar23 == 0x4360)) || (iVar23 == 0xaa06)) {
    si_pmu_rfldo(param_1[0x17],1);
  }
  wlc_setxband(param_1,(param_2 & 0xc000) == 0xc000);
  wlc_phy_chanspec_radio_set(*(undefined8 *)(param_1[0x1d] + 0x28),param_2);
  wlc_phy_cal_init(*(undefined8 *)(param_1[0x1d] + 0x28));
  lVar24 = *param_1;
  local_3c[0] = 0;
  lVar5 = param_1[0x1a];
  wlc_bmac_mctrl(param_1,0xffffffff,0x4000404);
  wlc_bmac_btc_mode_set(param_1,*(undefined4 *)param_1[0x16]);
  if ((char)param_1[0x12] < '\0') {
    iVar23 = *(int *)(param_1[0x17] + 0x3c);
    if (((iVar23 == 0x4331) || (iVar23 == 0x4313)) || (iVar23 == 0xa9a7)) {
      si_btc_enable_chipcontrol();
    }
    iVar23 = *(int *)(param_1[0x17] + 0x3c);
    if (((iVar23 == 0xa8d1) || (iVar23 == 0xa87b)) ||
       ((iVar23 == 0xa8db || ((iVar23 == 0xa8dc || (iVar23 == 0xa9a4)))))) {
      si_btc_enable_chipcontrol();
      si_pmu_chipcontrol(param_1[0x17],1,0x10,0x10);
    }
    if ((*(int *)(param_1[0x17] + 0x3c) == 0x4313) && (*(int *)param_1[0x16] != 0)) {
      wlc_phy_btclock_war(*(undefined8 *)(param_1[0x1d] + 0x28),(char)param_1[0x35]);
    }
  }
  if ((*(byte *)((long)param_1 + 0x8c) & 1) != 0) {
    if ((char)param_1[0x12] < '\0') {
      lVar20 = param_1[0x17];
      uVar18 = 3;
      if (*(int *)(lVar20 + 0x3c) != 0x4331) {
LAB_001691e8:
        si_seci_init(lVar20,uVar18);
      }
    }
    else if ((((*(uint *)((long)param_1 + 0x84) < 0xf) ||
              ((*(byte *)(param_1[0x17] + 0x1b) & 0x20) == 0)) ||
             ((*(byte *)(param_1[0x17] + 0x1c) & 1) != 0)) ||
            ((*(byte *)((long)param_1 + 0xa7) & 0x20) == 0)) {
      lVar20 = param_1[0x17];
      if (((*(uint *)(lVar20 + 0x1c) & 1) != 0) && ((*(byte *)((long)param_1 + 0xa7) & 0x20) != 0))
      {
        uVar18 = 1;
        goto LAB_001691e8;
      }
      if (((*(uint *)(lVar20 + 0x1c) & 4) != 0) && ((*(byte *)((long)param_1 + 0xa7) & 0x20) != 0))
      {
        si_gci_init();
      }
    }
    else {
      si_eci_init();
    }
  }
  FUN_001614f0(param_1);
  if (*(uint *)((long)param_1 + 0x84) == 4) {
    puVar19 = d11pcm4;
    uVar17 = d11pcm4sz;
LAB_00169235:
    FUN_0016196f(param_1,puVar19,uVar17);
  }
  else if (*(uint *)((long)param_1 + 0x84) < 0xb) {
    puVar19 = d11pcm5;
    uVar17 = d11pcm5sz;
    goto LAB_00169235;
  }
  wlc_bmac_wowlucode_start(param_1);
  lVar20 = param_1[0x1a];
  wlc_bmac_mctrl(param_1,0xc000,0);
  if (*(int *)(param_1[0x16] + 0x10) != 0) {
    FUN_00161dab(param_1);
  }
  cVar3 = *(char *)((long)param_1 + 0x1a1);
  if (((byte)(cVar3 - 2U) < 2) || (cVar3 == '\x06')) {
    wlc_bmac_mhf(param_1,2,1,1,3);
    wlc_bmac_mhf(param_1,2,2,2,3);
    wlc_phy_antsel_init(*(undefined8 *)(param_1[0x1d] + 0x28),0);
LAB_001692d4:
    uVar25 = 0;
    uVar15 = 0;
  }
  else {
    if (cVar3 != '\x01') goto LAB_001692d4;
    uVar8 = osl_readw(lVar20 + 0x49e);
    osl_writew(uVar8 | 0x3000,lVar20 + 0x49e);
    uVar8 = osl_readw(lVar20 + 0x49c);
    uVar25 = 0x3000;
    osl_writew(uVar8 | 0x3000,lVar20 + 0x49c);
    wlc_bmac_mhf(param_1,2,1,1,3);
    wlc_bmac_mhf(param_1,2,2,0,3);
    wlc_bmac_write_shm(param_1,0xc2,6);
    uVar15 = 0x3000;
  }
  if ((*(byte *)((long)param_1 + 0x8c) & 2) != 0) {
    uVar15 = uVar15 | 0x200;
    uVar25 = uVar25 | uVar15;
  }
  lVar27 = param_1[0x17];
  if ((((*(int *)(lVar27 + 0x28) == 0x4b0) || (*(int *)(lVar27 + 0x28) == 0x4a4)) &&
      (0x1ff < (*(ushort *)((long)param_1 + 0x8a) & 0xfff))) &&
     ((*(int *)(lVar27 + 0x3c) == 0x4322 && (*(int *)(lVar27 + 0x40) == 0)))) {
    uVar15 = uVar15 | 0x1000;
    uVar25 = uVar25 | uVar15;
    uVar8 = osl_readw(lVar20 + 0x49e);
    osl_writew(uVar8 | 0x1000,lVar20 + 0x49e);
    uVar12 = osl_readw(lVar20 + 0x49c);
    osl_writew(uVar12 & 0xefff,lVar20 + 0x49c);
  }
  si_gpiocontrol(param_1[0x17],uVar25,uVar15,0);
  if (0x27 < *(uint *)((long)param_1 + 0x84)) {
    iVar23 = 0;
    do {
      iVar26 = iVar23 + 1;
      wlc_bmac_write_amt(param_1,iVar23,&DAT_00510bd4,0);
      iVar23 = iVar26;
    } while (iVar26 != 0x40);
  }
  if (*(int *)((long)param_1 + 0x1a4) != 0) {
    lVar20 = param_1[0x17];
    iVar23 = *(int *)(lVar20 + 0x3c);
    if ((iVar23 - 0xa8e2U < 3) || (iVar23 == 0xa8e6)) {
      si_corereg(lVar20,0,0x28,8,8);
    }
    else if (((iVar23 == 0x4749) || (iVar23 == 0x5357)) || (iVar23 == 0xd144)) {
      si_pmu_chipcontrol(lVar20,1,0x8000,0x8000);
    }
  }
  wlc_bmac_copyfrom_objmem(*(undefined8 *)(lVar24 + 0x20),0x24,local_3c,4,0x20000);
  uVar16 = si_core_sflags(param_1[0x17],0,0);
  uVar15 = *(uint *)((long)param_1 + 0x84);
  if (uVar15 == 0x2b) {
    puVar19 = d11ac3initvals43;
    sVar10 = *(short *)(param_1[0x1d] + 0x1c);
joined_r0x0016957b:
    if (sVar10 == 0xb) {
LAB_001698d5:
      FUN_00161ca7(param_1,puVar19);
    }
  }
  else {
    if (uVar15 == 0x2a) {
      puVar19 = d11ac1initvals42;
      sVar10 = *(short *)(param_1[0x1d] + 0x1c);
      goto joined_r0x0016957b;
    }
    if (((uVar15 == 0x2c) || (uVar15 == 0x29)) ||
       ((uVar15 == 0x2e || ((uVar15 == 0x2d || (uVar15 == 0x2f)))))) {
      puVar19 = d11ac2initvals41;
      sVar10 = *(short *)(param_1[0x1d] + 0x1c);
      goto joined_r0x0016957b;
    }
    if (uVar15 == 0x28) {
      puVar19 = d11ac0initvals40;
      sVar10 = *(short *)(param_1[0x1d] + 0x1c);
      goto joined_r0x0016957b;
    }
    if (uVar15 == 0x22) {
      puVar19 = d11n19initvals34;
      sVar10 = *(short *)(param_1[0x1d] + 0x1c);
joined_r0x0016963f:
      if (sVar10 != 4) goto LAB_001698dd;
      goto LAB_001698d5;
    }
    if (uVar15 != 0x21) {
      if (uVar15 == 0x20) {
        puVar19 = d11n18initvals32;
        sVar10 = *(short *)(param_1[0x1d] + 0x1c);
        goto joined_r0x0016963f;
      }
      if (uVar15 == 0x1f) {
        bVar29 = *(short *)(param_1[0x1d] + 0x1c) == 4;
LAB_0016965b:
        if (!bVar29) goto LAB_001698dd;
        puVar19 = d11ht0initvals29;
      }
      else {
        if (uVar15 == 0x1e) {
          puVar19 = d11n16initvals30;
          sVar10 = *(short *)(param_1[0x1d] + 0x1c);
          goto joined_r0x0016963f;
        }
        if (uVar15 == 0x1d) {
          bVar29 = *(short *)(param_1[0x1d] + 0x1c) == 7;
          goto LAB_0016965b;
        }
        if (uVar15 == 0x1a) {
          puVar19 = d11ht0initvals26;
          if (*(short *)(param_1[0x1d] + 0x1c) != 7) goto LAB_001698dd;
        }
        else if ((uVar15 == 0x1c) || (uVar15 == 0x19)) {
          puVar19 = d11n0initvals25;
          sVar10 = (short)*(undefined4 *)(param_1[0x1d] + 0x1c);
          if (sVar10 != 4) {
            puVar19 = d11lcn0initvals25;
joined_r0x001696c0:
            if (sVar10 != 8) goto LAB_001698dd;
          }
        }
        else if (uVar15 == 0x18) {
          puVar19 = d11n0initvals24;
          sVar10 = (short)*(undefined4 *)(param_1[0x1d] + 0x1c);
          if (sVar10 != 4) {
            puVar19 = d11lcn0initvals24;
            goto joined_r0x001696c0;
          }
        }
        else if (uVar15 < 0x16) {
          if (uVar15 == 0x15) {
            puVar19 = d11sslpn3initvals21;
            sVar10 = *(short *)(param_1[0x1d] + 0x1c);
          }
          else if (uVar15 == 0x14) {
            puVar19 = d11sslpn1initvals20;
            sVar10 = *(short *)(param_1[0x1d] + 0x1c);
          }
          else {
            if (uVar15 != 0x13) {
              if (uVar15 < 0x10) {
                if (uVar15 == 0xf) {
                  puVar19 = d11lp0initvals15;
                  sVar10 = *(short *)(param_1[0x1d] + 0x1c);
                }
                else {
                  if (uVar15 != 0xe) {
                    if (uVar15 == 0xd) {
                      puVar19 = d11lp0initvals13;
                      sVar10 = (short)*(undefined4 *)(param_1[0x1d] + 0x1c);
                      if (((sVar10 != 5) && (puVar19 = d11b0g0initvals13, sVar10 != 2)) &&
                         ((sVar10 != 0 || (puVar19 = d11a0g1initvals13, (uVar16 & 1) == 0))))
                      goto LAB_001698dd;
                    }
                    else {
                      if (10 < uVar15) {
                        puVar19 = d11n0initvals11;
                        sVar10 = *(short *)(param_1[0x1d] + 0x1c);
                        goto joined_r0x0016963f;
                      }
                      if (uVar15 == 4) {
                        puVar19 = d11a0g0initvals4;
                        if (*(short *)(param_1[0x1d] + 0x1c) != 0) {
                          puVar19 = d11b0g0initvals4;
                        }
                      }
                      else {
                        puVar19 = d11b0g0initvals5;
                        if ((*(short *)(param_1[0x1d] + 0x1c) == 0) &&
                           (puVar19 = d11a0g1initvals5, (uVar16 & 1) == 0)) {
                          puVar19 = d11a0g0initvals5;
                        }
                      }
                    }
                    goto LAB_001698d5;
                  }
                  puVar19 = d11lp0initvals14;
                  sVar10 = *(short *)(param_1[0x1d] + 0x1c);
                }
              }
              else {
                sVar10 = (short)*(undefined4 *)(param_1[0x1d] + 0x1c);
                if (sVar10 == 4) goto LAB_001697c5;
                puVar19 = d11sslpn0initvals16;
                if (sVar10 == 6) goto LAB_001698d5;
                puVar19 = d11lp0initvals16;
              }
              if (sVar10 != 5) goto LAB_001698dd;
              goto LAB_001698d5;
            }
            puVar19 = d11sslpn2initvals19;
            sVar10 = *(short *)(param_1[0x1d] + 0x1c);
          }
          if (sVar10 != 6) goto LAB_001698dd;
        }
        else {
          sVar10 = (short)*(undefined4 *)(param_1[0x1d] + 0x1c);
          if (sVar10 == 4) {
            puVar19 = d11n0initvals22;
            if (uVar15 == 0x17) {
LAB_001697c5:
              puVar19 = d11n0initvals16;
            }
          }
          else if ((sVar10 != 6) || (puVar19 = d11sslpn4initvals22, uVar15 != 0x16))
          goto LAB_001698dd;
        }
      }
      goto LAB_001698d5;
    }
    if (*(short *)(param_1[0x1d] + 0x1c) == 10) {
      FUN_00161ca7(param_1,d11lcn400initvals33);
      wlc_bmac_mhf(param_1,4,0x800,0x800,2);
    }
  }
LAB_001698dd:
  uVar15 = *(uint *)((long)param_1 + 0x84);
  if (uVar15 < 0x28) {
    lVar20 = param_1[0x1a];
    if (8 < uVar15) {
      if (uVar15 == 0x1c) {
        local_58 = 0x1e;
        local_56 = 0x2f;
        local_54 = 0x16;
        local_52 = 0xe;
        puVar21 = &DAT_0059c900;
LAB_00169983:
        local_4e = 1;
        local_50 = 8;
        osl_memcpy(puVar21,&local_58,0xc);
      }
      else if (uVar15 - 0x10 < 2) {
        local_58 = 0x62;
        local_56 = 0x9f;
        local_54 = 0xa0;
        local_52 = 0x15;
        puVar21 = &DAT_0059c7e0 + (ulong)(uVar15 - 4) * 0xc;
        goto LAB_00169983;
      }
      if (*(int *)(param_1[0x17] + 0x3c) == 0xa8ea) {
        local_58 = 0x12;
        local_56 = 0xfe;
        local_54 = 0x19;
        local_52 = 0x11;
        local_50 = 0x11;
        local_4e = 8;
        osl_memcpy(&DAT_0059c7e0 + (ulong)(*(int *)((long)param_1 + 0x84) - 4) * 0xc,&local_58,0xc);
      }
      lVar27 = 0;
      iVar23 = 0;
      uVar16 = 6;
      while( true ) {
        uVar22 = (ushort)(iVar23 << 8) | 0x8000;
        uVar8 = *(short *)(param_1[0x2a] + lVar27) + (short)uVar16;
        osl_writew(uVar22,lVar20 + 0x540);
        osl_writew((uint)uVar16 & 0xff | (uVar8 - 1 & 0xff) << 8,lVar20 + 0x520);
        if (0xf < *(uint *)((long)param_1 + 0x84)) {
          osl_writew((uint)(uVar8 - 1 & 0x300) | (uint)(uVar16 >> 8) & 3,lVar20 + 0x52c);
        }
        osl_writew(uVar22,lVar20 + 0x540);
        puVar1 = (ushort *)(param_1[0x2a] + lVar27);
        iVar23 = iVar23 + 1;
        lVar27 = lVar27 + 2;
        if (iVar23 == 6) break;
        uVar16 = (ulong)((uint)uVar16 + (uint)*puVar1);
      }
    }
    wlc_bmac_write_shm(param_1,0x98,*(undefined2 *)(param_1[0x2a] + 2));
    wlc_bmac_write_shm(param_1,0x9a,*(undefined2 *)(param_1[0x2a] + 4));
    wlc_bmac_write_shm(param_1,0x9c,((ushort *)param_1[0x2a])[3] << 8 | *(ushort *)param_1[0x2a]);
    wlc_bmac_write_shm(param_1,0x9e,
                       *(short *)(param_1[0x2a] + 10) << 8 | *(ushort *)(param_1[0x2a] + 8));
    lVar20 = param_1[0x1a];
    if (0xc < *(uint *)((long)param_1 + 0x84)) {
      uVar25 = 0;
      uVar12 = 0;
      local_70 = (ushort)(*(uint *)((long)param_1 + 0xa4) >> 2) & 0x3fe;
      uVar8 = osl_readw(lVar20 + 0x540);
      uVar15 = 0;
      uVar22 = 0;
      do {
        osl_writew((uVar15 & 7) << 8 | uVar8 & 0xf8ff,lVar20 + 0x540);
        uVar13 = osl_readw(lVar20 + 0x520);
        uVar14 = 0;
        if (0xf < *(uint *)((long)param_1 + 0x84)) {
          uVar14 = osl_readw(lVar20 + 0x52c);
        }
        if ((short)uVar15 == 0) {
          uVar25 = (uVar14 & 0xffff) << 8;
          if (((short)uVar25 == 0) && ((char)uVar13 == '\0')) goto LAB_00169cab;
          uVar25 = (uVar13 & 0xff | uVar25) - 1;
          uVar22 = ((short)uVar25 - (short)uVar12) + 1 + uVar22;
        }
        uVar12 = uVar14 << 8 | uVar13 & 0xff;
        uVar28 = (ushort)uVar12;
        if ((uVar28 < (ushort)uVar25) ||
           ((uVar14 << 8 & 0xffff | uVar13 & 0xff) != (uVar25 & 0xffff) + 1)) goto LAB_00169cab;
        uVar25 = uVar14 & 0xffffff00 | uVar13 >> 8 & 0xff;
        if (((ushort)uVar25 < uVar28) ||
           ((uVar22 = ((ushort)uVar25 - uVar28) + 1 + uVar22, local_70 < uVar22 ||
            (uVar15 = uVar15 + 1, uVar15 == 6)))) goto LAB_00169cab;
      } while( true );
    }
    goto LAB_00169cbf;
  }
  FUN_00168c3d(param_1);
LAB_00169d22:
  wlc_bmac_write_shm(param_1,0x80,8);
  wlc_bmac_write_shm(param_1,0x5c,10);
  osl_writel(*(undefined4 *)((long)param_1 + 0x1ac),param_1[0x1a] + 0x100);
  if (*(int *)((long)param_1 + 0x84) == 4) {
    osl_writel(0x1000000,lVar5 + 0x10c);
  }
  wlc_bmac_mctrl(param_1,0x40060000,0x40020000);
  osl_writel(0x80000000,lVar5 + 0x188);
  osl_writel(0x2000000,lVar5 + 0x18c);
  osl_writel(0x4000,lVar5 + 0x128);
  osl_writel(0x10000,lVar5 + 0x24);
  if (*(int *)((long)param_1 + 0x84) == 4) {
    osl_writel(0x10000,lVar5 + 0x3c);
  }
  wlc_bmac_macphyclk_set(param_1,1);
  if (4 < *(uint *)((long)param_1 + 0x84)) {
    uVar9 = si_clkctl_fast_pwrup_delay(param_1[0x17]);
    *(undefined2 *)((long)param_1 + 0x192) = uVar9;
    osl_writew(uVar9,lVar5 + 0x6a8);
    if (0x28 < *(uint *)((long)param_1 + 0x84)) {
      sVar10 = FUN_00160b0a(param_1);
      *(short *)((long)param_1 + 0x192) = *(short *)((long)param_1 + 0x192) + sVar10;
    }
  }
  wlc_bmac_write_shm(param_1,0x16,*(undefined2 *)((long)param_1 + 0x84));
  if (0xc < *(uint *)((long)param_1 + 0x84)) {
    wlc_bmac_write_shm(param_1,0xc0,*(undefined2 *)((long)param_1 + 0xa4));
    wlc_bmac_write_shm(param_1,0xc2,*(undefined2 *)((long)param_1 + 0xa6));
  }
  wlc_bmac_copyto_objmem(param_1,0x18,(long)param_1 + 0x104,2,0x20000);
  wlc_bmac_copyto_objmem(param_1,0x1c,(long)param_1 + 0x106,2,0x20000);
  if (*(char *)(lVar24 + 0x718) == '\0') {
    wlc_bmac_copyto_objmem(*(undefined8 *)(lVar24 + 0x20),0x24,local_3c,4,0x20000);
  }
  else {
    *(undefined1 *)(lVar24 + 0x718) = 0;
  }
  wlc_bmac_write_shm(param_1,0x44,(short)param_1[0x21]);
  wlc_bmac_write_shm(param_1,0x46,*(undefined2 *)((long)param_1 + 0x10a));
  if (0xf < *(uint *)((long)param_1 + 0x84)) {
    uVar15 = osl_readw(lVar5 + 0x688);
    osl_writew(uVar15 & 0xfff,lVar5 + 0x688);
    osl_writew(1,lVar5 + 0x69c);
  }
  *(undefined4 *)(lVar24 + 0x68) = 0;
  lVar24 = 0;
  do {
    plVar6 = *(long **)((long)param_1 + lVar24 + 0x20);
    if (plVar6 != (long *)0x0) {
      (**(code **)(*plVar6 + 8))();
    }
    lVar24 = lVar24 + 8;
  } while (lVar24 != 0x30);
  (**(code **)(*(long *)param_1[4] + 0xa0))();
  (**(code **)(*(long *)param_1[4] + 0xd8))();
  if (*(int *)((long)param_1 + 0x84) == 4) {
    (**(code **)(*(long *)param_1[7] + 0xa0))();
    (**(code **)(*(long *)param_1[7] + 0xd8))();
  }
  iVar23 = *(int *)(param_1[0x17] + 0x3c);
  if (((iVar23 == 0x4748) || (iVar23 == 0x4716)) || (iVar23 == 0xb83a)) {
    osl_writew(0x3127,lVar5 + 0x62e);
    uVar16 = 8;
  }
  else {
    if (((iVar23 != 0x4314) && (iVar23 != 0x4334)) && ((iVar23 != 0xa886 && (iVar23 != 0xa887))))
    goto LAB_0016a04e;
    uVar16 = si_clock();
    uVar7 = (uVar16 & 0xffffffff) / 1000000;
    uVar16 = 0x4000000 / uVar7;
    osl_writew(uVar16 & 0xffff,lVar5 + 0x62e,0x4000000 % uVar7);
    uVar16 = uVar16 >> 0x10;
  }
  osl_writew(uVar16,lVar5 + 0x630);
LAB_0016a04e:
  lVar24 = param_1[0x16];
  sVar10 = wlc_bmac_read_shm(param_1,0x92);
  *(short *)(lVar24 + 0x1a) = sVar10 * 2;
  if (*(short *)(param_1[0x16] + 0x1a) != 0) {
    iVar23 = 0;
    do {
      osl_snprintf(&local_58,0xf,"btc_params%d",iVar23);
      lVar24 = getvar(param_1[0x18],&local_58);
      if (lVar24 != 0) {
        uVar9 = getintvar(param_1[0x18],&local_58);
        wlc_bmac_write_shm(param_1,(uint)*(ushort *)(param_1[0x16] + 0x1a) + iVar23 * 2,uVar9);
      }
      iVar23 = iVar23 + 1;
    } while (iVar23 != 0x77);
    if ((*(int *)(param_1[0x17] + 0x3c) == 0x4352) || (*(int *)(param_1[0x17] + 0x3c) == 0xa8dc)) {
      wlc_bmac_write_shm(param_1,*(ushort *)(param_1[0x16] + 0x1a) + 2,30000);
      wlc_bmac_write_shm(param_1,*(ushort *)(param_1[0x16] + 0x1a) + 0x10,20000);
      wlc_bmac_write_shm(param_1,*(ushort *)(param_1[0x16] + 0x1a) + 0x12,30000);
      wlc_bmac_write_shm(param_1,*(ushort *)(param_1[0x16] + 0x1a) + 0x2c,0x753);
    }
    lVar24 = getvar(param_1[0x18],"btc_flags");
    if (lVar24 != 0) {
      lVar24 = param_1[0x16];
      uVar9 = getintvar(param_1[0x18],"btc_flags");
      *(undefined2 *)(lVar24 + 8) = uVar9;
      FUN_001638b9(param_1);
    }
    if (0x27 < *(uint *)((long)param_1 + 0x84)) {
      lVar24 = *(long *)*param_1;
      wlc_bmac_write_shm(param_1,0x78c,*(undefined2 *)(lVar24 + 8));
      wlc_bmac_write_shm(param_1,0x78e,*(undefined2 *)(lVar24 + 10));
      wlc_bmac_write_shm(param_1,0x790,*(undefined2 *)(lVar24 + 0xc));
    }
  }
  lVar24 = *(long *)(*param_1 + 0x550);
  iVar23 = wlc_bmac_read_shm(param_1,0x8e);
  if (*(int *)((long)param_1 + 0x84) == 0x21) {
    uVar15 = iVar23 * 2 & 0xffff;
    if (*(char *)(lVar24 + 0xf4) == '\0') {
      iVar23 = uVar15 + 0x4c;
      uVar9 = 0;
    }
    else {
      wlc_bmac_write_shm(param_1,uVar15 + 0x50,1 << (*(byte *)(lVar24 + 0xbc) & 0x1f) & 0xffff);
      wlc_bmac_write_shm(param_1,uVar15 + 0x94,0);
      uVar9 = *(undefined2 *)(lVar24 + 0x104);
      iVar23 = uVar15 + 0x96;
    }
    wlc_bmac_write_shm(param_1,iVar23,uVar9);
  }
  *(undefined4 *)((long)param_1 + 0x16c) = 1;
  if (param_3 != '\0') {
    wlc_bmac_mute(param_1,1,1);
  }
  if (*(short *)(param_1[0x1d] + 0x1c) == 7) {
    wlc_phy_switch_radio(*(undefined8 *)(param_1[0x1d] + 0x28),0);
  }
  iVar23 = *(int *)(param_1[0x17] + 0x3c);
  if ((((iVar23 == 0xa9c4) || (iVar23 == 0x4360)) || (iVar23 == 0xaa06)) ||
     ((iVar23 == 0x4352 || (iVar23 == 0x4350)))) {
    wlc_bmac_switch_macfreq(param_1,0);
  }
  FUN_001672ac(param_1,param_2,0);
  wl_intrsrestore(*(undefined8 *)(lVar4 + 0x10),uVar11);
  *(uint *)(param_1 + 0x2e) = *(uint *)(param_1 + 0x2e) | 4;
  if (cVar2 == '\0') {
    FUN_001655c7(param_1,2);
  }
  iVar23 = *(int *)(param_1[0x17] + 0x3c);
  if ((iVar23 == 0xa886) || (iVar23 == 0x4314)) {
    uVar15 = si_pcielcreg(param_1[0x17],0,0);
    si_pcielcreg(param_1[0x17],3,uVar15 & 0xfffffffe);
  }
  return;
LAB_00169cab:
  osl_writew(uVar8,lVar20 + 0x540);
LAB_00169cbf:
  wlc_bmac_read_shm(param_1,0x98);
  wlc_bmac_read_shm(param_1,0x9a);
  wlc_bmac_read_shm(param_1,0x9c);
  wlc_bmac_read_shm(param_1,0x9e);
  lVar20 = param_1[0x2a];
  lVar27 = 0;
  do {
    *(short *)((long)param_1 + lVar27 + 0x158) =
         (short)((int)((uint)*(ushort *)(lVar20 + lVar27) * 0x100 + -0x514) / 0x672);
    lVar27 = lVar27 + 2;
  } while (lVar27 != 8);
  goto LAB_00169d22;
}

