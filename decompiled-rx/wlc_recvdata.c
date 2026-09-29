
void wlc_recvdata(long *param_1,undefined8 param_2,long param_3,undefined8 param_4)

{
  int *piVar1;
  byte bVar2;
  ushort uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  ushort uVar6;
  bool bVar7;
  ushort uVar8;
  char cVar9;
  short sVar10;
  short sVar11;
  uint uVar12;
  undefined4 uVar13;
  uint uVar14;
  int iVar15;
  char *pcVar16;
  long lVar17;
  uint *puVar18;
  undefined8 uVar19;
  byte bVar20;
  int iVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  ulong uVar25;
  long lVar26;
  ushort *puVar27;
  bool bVar28;
  byte bStack_110;
  ushort *puStack_108;
  ushort *puStack_100;
  int iStack_f8;
  int iStack_f4;
  int iStack_f0;
  undefined8 uStack_e8;
  long lStack_e0;
  ushort uStack_d8;
  undefined2 uStack_d6;
  undefined2 uStack_d4;
  undefined1 uStack_d2;
  uint uStack_d0;
  undefined1 uStack_cc;
  char cStack_cb;
  char cStack_ca;
  undefined1 uStack_c9;
  byte bStack_c8;
  byte bStack_c7;
  bool bStack_c4;
  undefined8 uStack_b8;
  undefined8 uStack_90;
  byte bStack_88;
  undefined2 uStack_80;
  ushort uStack_5a;
  long lStack_58;
  long lStack_48;
  long alStack_40 [2];
  
  alStack_40[0] = 0;
  uVar3 = *(ushort *)(param_3 + 0x16);
  uStack_b8 = 0;
  uStack_d2 = 0;
  uStack_d0 = 0;
  uStack_c9 = 0;
  uStack_cc = 0;
  bStack_88 = 0;
  bStack_c8 = 0;
  uStack_90 = 0;
  uStack_e8 = param_4;
  lStack_e0 = param_3;
  lStack_58 = param_3;
  uVar12 = osl_pktlen(param_2,param_4);
  if (0x21 < uVar12) {
    pcVar16 = (char *)osl_pktdata(param_2,param_4);
    uVar13 = wlc_recv_compute_rspec(param_3,pcVar16);
    puStack_108 = (ushort *)(pcVar16 + 6);
    lVar17 = osl_pkttag(param_4);
    uStack_d8 = *puStack_108;
    uVar12 = (int)(uStack_d8 & 0xf0) >> 4;
    iVar21 = (int)(uStack_d8 & 0xc) >> 2;
    cStack_cb = (uStack_d8 & 0x300) == 0x300;
    uStack_d4 = (undefined2)uVar12;
    cStack_ca = '\0';
    uStack_d6 = (undefined2)iVar21;
    if (iVar21 == 2) {
      cStack_ca = (char)(uVar12 >> 3);
    }
    if (((*(ushort *)(param_3 + 4) & 3) == 2) && ((short)uStack_d8 < 0)) {
      uVar12 = uVar12 >> 3;
    }
    else {
      uVar12 = 0;
    }
    uStack_c9 = (undefined1)uVar12;
    iVar21 = (-(uint)!(bool)cStack_cb & 0xfffffffa) + 0x28;
    if (cStack_ca != '\0') {
      iVar21 = (-(uint)!(bool)cStack_cb & 0xfffffffa) + 0x2a;
    }
    uVar14 = osl_pktlen(param_2,uStack_e8);
    if (iVar21 + uVar12 * 4 <= uVar14) {
      bVar28 = (uVar3 & 0xc000) != 0;
      lStack_48 = 0;
      bStack_c8 = (byte)puStack_108[2] & 1;
      if (cStack_cb == '\0') {
        if ((uStack_d8 & 0x300) == 0) {
          puVar27 = puStack_108 + 8;
          alStack_40[0] = wlc_scbibssfindband(param_1,puStack_108 + 5,bVar28,&lStack_48);
        }
        else {
          puVar27 = puStack_108 + 2;
          if ((uStack_d8 & 0x100) == 0) {
            puVar27 = puStack_108 + 5;
          }
        }
        if (lStack_48 == 0) {
          lStack_48 = wlc_bsscfg_find_by_bssid(param_1,puVar27);
        }
        bStack_c4 = lStack_48 != 0;
      }
      else {
        bStack_c4 = false;
      }
      if (bStack_c8 == 0) {
        lVar26 = wlc_bsscfg_find_by_hwaddr(param_1,puStack_108 + 2);
        bVar7 = true;
        if (lVar26 == 0) goto LAB_00144c15;
      }
      else {
LAB_00144c15:
        bVar7 = false;
      }
      if (((int)param_1[0x51] == 0) && (*(char *)(*param_1 + 0x4c) == '\0')) {
        bVar2 = bStack_c8;
        if (bVar7) {
LAB_00144ca0:
          bVar2 = bStack_c4;
          if (cStack_cb == '\0') goto LAB_00144cb0;
        }
        else {
LAB_00144cb0:
          if (bVar2 == 0) goto LAB_00145667;
        }
LAB_00144cb6:
        bVar7 = false;
      }
      else {
        if (*(char *)(*param_1 + 0x59) == '\0') {
          bStack_c4 = false;
        }
        if (bVar7) goto LAB_00144ca0;
        if (((((uStack_d8 & 0x100) == 0) && (bStack_c8 != 0)) && (bStack_c4 != false)) ||
           ((cStack_cb != '\0' && (bStack_c8 != 0)))) goto LAB_00144cb6;
        if (*(char *)(*param_1 + 0x4c) == '\0') goto LAB_00145667;
        bVar7 = true;
        if (bStack_c4 == false) {
          wlc_lq_rssi_pktrxh_cal(param_1,param_3);
          goto LAB_00145667;
        }
      }
      osl_pktpull(param_2,uStack_e8,6);
      puStack_100 = puStack_108 + 0xc;
      if (cStack_cb != '\0') {
        puStack_100 = puStack_108 + 0xf;
      }
      bStack_c7 = 0;
      if (cStack_ca != '\0') {
        uVar8 = *puStack_100;
        uVar6 = *puStack_100;
        uVar3 = uVar6 >> 7;
        bStack_c7 = (byte)uVar3 & 1;
        uVar12 = (uint)(byte)*puStack_100;
        if ((uVar3 & 1) != 0) {
          if (*(char *)((long)param_1 + 0x292) == '\0') goto LAB_00145667;
          puVar18 = (uint *)osl_pkttag(uStack_e8);
          *puVar18 = *puVar18 | 0x40;
          uVar12 = (uint)uVar8;
        }
        uVar14 = uVar6 & 7;
        puStack_100 = puStack_100 + 1;
        uStack_d2 = (undefined1)uVar14;
        uStack_cc = (undefined1)((int)(uVar12 & 0x10) >> 4);
        bStack_88 = *(byte *)((long)&wme_fifo2ac +
                             (ulong)*(byte *)((long)&prio2fifo + (ulong)uVar14));
        uStack_d0 = (uint)bStack_88;
      }
      if (bStack_c7 == 0) {
        iVar21 = osl_pktlen(param_2);
        uVar19 = uStack_e8;
      }
      else {
        uVar19 = pktlast(param_2,uStack_e8);
        iVar21 = osl_pktlen(param_2,uVar19);
      }
      osl_pktsetlen(param_2,uVar19,iVar21 + -4);
      iStack_f4 = osl_pktlen(param_2,uStack_e8);
      iVar21 = (int)puStack_100;
      iVar15 = osl_pktdata(param_2,uStack_e8);
      iStack_f8 = iStack_f4 - (iVar21 - iVar15);
      iStack_f0 = pkttotlen(param_2,param_4);
      iStack_f0 = iStack_f0 - (iVar21 - iVar15);
      uStack_5a = puStack_108[0xb];
      if (bVar7) {
        if ((uStack_d8 & 0x300) == 0) {
          if (*(char *)(lStack_48 + 0x22) == '\0') goto LAB_00144fa5;
        }
        else if ((cStack_cb != '\0') || (*(char *)(lStack_48 + 0x22) != '\0')) {
LAB_00144fa5:
          alStack_40[0] = wlc_scblookupband(param_1,lStack_48,puStack_108 + 5,bVar28);
          if (alStack_40[0] == 0) goto LAB_00145667;
          if (*(long *)(alStack_40[0] + 0x18) == 0) {
            wlc_scb_set_bsscfg(alStack_40[0],lStack_48);
          }
          goto LAB_00144ff0;
        }
      }
      else {
        sVar10 = func_0x001445cf(param_1,&lStack_48,puStack_108,param_3,alStack_40,iStack_f4);
        if (sVar10 != 0) goto LAB_00145667;
        if ((uStack_d8 & 0x300) == 0) {
          if ((1 < *(uint *)(*param_1 + 0x44)) && (alStack_40[0] == 0)) {
            alStack_40[0] = wlc_scbibssfindband(param_1,puStack_108 + 5,!bVar28,&lStack_48);
          }
          if (alStack_40[0] == 0) {
            lVar26 = lStack_48;
            if (lStack_48 == 0) {
              lVar26 = param_1[0x5f];
            }
            alStack_40[0] = wlc_scblookupband(param_1,lVar26,puStack_108 + 5,bVar28);
            if (alStack_40[0] == 0) {
              piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x6c);
              *piVar1 = *piVar1 + 1;
              goto LAB_00145667;
            }
          }
          if (*(long *)(alStack_40[0] + 0x18) == 0) {
            lVar26 = lStack_48;
            if (lStack_48 == 0) {
              lVar26 = param_1[0x5f];
            }
            wlc_scb_set_bsscfg(alStack_40[0],lVar26);
            if (*(char *)(*param_1 + 0xe8) != '\0') {
              wlc_txbf_set_init_pending(param_1[0x102],alStack_40[0]);
            }
          }
        }
        if (lStack_48 == 0) {
          lStack_48 = *(long *)(alStack_40[0] + 0x18);
        }
LAB_00144ff0:
        lVar26 = *(long *)(lStack_48 + 0x328);
        if (((bVar7) || (cStack_cb != '\0')) ||
           (((bStack_c8 == 0 || ((uStack_d8 & 0x100) == 0)) &&
            ((uStack_d8 & 0x300) == (~-(ushort)(*(char *)(lStack_48 + 0x22) == '\0') & 0x200))))) {
          cVar9 = wlc_lq_rssi_pktrxh_cal(param_1,param_3);
          if (cVar9 != '\0') {
            *(char *)(lVar17 + 0xb) = cVar9;
          }
          wlc_lq_rssi_update_ma(lStack_48);
          wlc_lq_rssi_event_update(lStack_48);
          iVar21 = 0;
          if (*(short *)(param_1[8] + 8) == 5) {
            if ((*(byte *)(param_3 + 4) & 3) == 0) {
              iVar21 = (int)(*(byte *)(param_3 + 7) + 2) >> 2;
            }
            else {
              iVar21 = (int)((uint)*(byte *)(param_3 + 7) * 0x6e17 + 0x20000) >> 0x12;
            }
          }
          func_0x00125f5c(lStack_48,iVar21);
          if ((((bStack_c4 != false) && (*(char *)(lStack_48 + 0x22) != '\0')) &&
              (*(char *)(lStack_48 + 0xc) != '\0')) && (*(char *)(lVar26 + 5) == '\0')) {
            wlc_roamscan_start(lStack_48,1);
          }
          if (cStack_cb == '\0') {
            uStack_80 = (undefined2)*(undefined4 *)(alStack_40[0] + 0x38);
          }
          else {
            uStack_80 = *(undefined2 *)(lStack_48 + 0x9a);
          }
          if (((*(char *)(lStack_48 + 0x22) != '\0') && (!bVar7)) && (bStack_c8 == 0)) {
            *(undefined1 *)(lVar26 + 6) = 0;
          }
          if (bStack_c8 != 0) {
            if ((*(char *)(lStack_48 + 0x22) != '\0') &&
               (iVar21 = osl_memcmp(puStack_108 + 8,lStack_48 + 0xf6,6), iVar21 == 0))
            goto LAB_00145667;
            lVar26 = lStack_48;
            if (((*(byte *)((long)puStack_108 + 5) & (byte)puStack_108[2] & (byte)puStack_108[3] &
                  *(byte *)((long)puStack_108 + 7) & (byte)puStack_108[4] &
                 *(byte *)((long)puStack_108 + 9)) != 0xff) && (*(char *)(lStack_48 + 0x80) == '\0')
               ) {
              puVar27 = puStack_108 + 2;
              for (uVar25 = 0; (uint)uVar25 < *(uint *)(lVar26 + 0x84);
                  uVar25 = (ulong)((uint)uVar25 + 1)) {
                iVar21 = osl_memcmp(puVar27,uVar25 * 6 + *(long *)(lVar26 + 0x88),6);
                if (iVar21 == 0) goto LAB_001451f4;
              }
              goto LAB_00145667;
            }
          }
LAB_001451f4:
          *(undefined4 *)(lVar17 + 0x18) = uVar13;
          if ((bStack_c8 == 0) &&
             (((pcVar16[1] != '\0' || (pcVar16[2] != '\0')) || (*pcVar16 != '\0')))) {
            wlc_scb_ratesel_upd_rxstats(param_1[0x35],uVar13,*(undefined2 *)(param_3 + 0x12));
          }
          if (pcVar16[3] < '\0') {
            piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x2a8);
            *piVar1 = *piVar1 + 1;
          }
          if ((pcVar16[3] & 0x30U) != 0) {
            piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x2b0);
            *piVar1 = *piVar1 + 1;
          }
          if (bStack_c8 == 0) {
            lVar26 = *(long *)(*param_1 + 0xa0);
            if ((*(uint *)(lVar17 + 0x18) & 0x3000000) == 0) {
              uVar12 = *(uint *)(lVar17 + 0x18) & 0xff;
            }
            else {
              uVar12 = wlc_rate_rspec2rate();
            }
            if (uVar12 == 0x16) {
              *(int *)(lVar26 + 0x24c) = *(int *)(lVar26 + 0x24c) + 1;
            }
            else if ((int)uVar12 < 0x17) {
              if (uVar12 == 0xb) {
                *(int *)(lVar26 + 0x240) = *(int *)(lVar26 + 0x240) + 1;
              }
              else if ((int)uVar12 < 0xc) {
                if (uVar12 == 2) {
                  *(int *)(lVar26 + 0x238) = *(int *)(lVar26 + 0x238) + 1;
                }
                else if (uVar12 == 4) {
                  *(int *)(lVar26 + 0x23c) = *(int *)(lVar26 + 0x23c) + 1;
                }
              }
              else if (uVar12 == 0xc) {
                *(int *)(lVar26 + 0x244) = *(int *)(lVar26 + 0x244) + 1;
              }
              else if (uVar12 == 0x12) {
                *(int *)(lVar26 + 0x248) = *(int *)(lVar26 + 0x248) + 1;
              }
            }
            else if (uVar12 == 0x30) {
              *(int *)(lVar26 + 600) = *(int *)(lVar26 + 600) + 1;
            }
            else if ((int)uVar12 < 0x31) {
              if (uVar12 == 0x18) {
                *(int *)(lVar26 + 0x250) = *(int *)(lVar26 + 0x250) + 1;
              }
              else if (uVar12 == 0x24) {
                *(int *)(lVar26 + 0x254) = *(int *)(lVar26 + 0x254) + 1;
              }
            }
            else if (uVar12 == 0x60) {
              *(int *)(lVar26 + 0x260) = *(int *)(lVar26 + 0x260) + 1;
            }
            else if (uVar12 == 0x6c) {
              *(int *)(lVar26 + 0x264) = *(int *)(lVar26 + 0x264) + 1;
            }
            else if (uVar12 == 0x48) {
              *(int *)(lVar26 + 0x25c) = *(int *)(lVar26 + 0x25c) + 1;
            }
          }
          if ((bStack_c8 != 0) || (*(int *)(*(long *)(*param_1 + 0x100) + 0x3c) != 0xa886))
          goto LAB_00145623;
          uVar4 = *(undefined2 *)(param_3 + 6);
          uVar5 = *(undefined2 *)(param_3 + 4);
          cVar9 = *(char *)(param_3 + 0x1c);
          lVar17 = param_1[0xaa];
          sVar10 = *(short *)(lVar17 + 0xa6);
          uVar13 = *(undefined4 *)(lVar17 + 0xc0);
          if ((*(int *)(*param_1 + 0x14) != 0x21) || (*(char *)(lVar17 + 0xf4) == '\0'))
          goto LAB_00145623;
          if (*(char *)(lVar17 + 0xfc) != '\0') {
            wl_del_timer(param_1[2],*(undefined8 *)(lVar17 + 0x108));
            *(undefined1 *)(lVar17 + 0xfc) = 0;
          }
          bVar2 = (byte)((ushort)uVar5 >> 8);
          bVar20 = bVar2 >> 6;
          uVar14 = (uint)bVar20;
          sVar11 = wlc_bmac_read_shm(param_1[4],0x8e);
          uVar12 = wlc_bmac_read_shm(param_1[4],sVar11 * 2 + 0x4e);
          if (*(byte *)(lVar17 + 0x91) != bVar20) {
            *(byte *)(lVar17 + 0x91) = bVar2 >> 6;
            *(undefined4 *)(lVar17 + 0xac) = 0;
            *(undefined4 *)(lVar17 + 0xa8) = 0;
            *(undefined4 *)(lVar17 + 0xb0 + (long)(int)uVar14 * 4) = 0;
            *(undefined4 *)(lVar17 + 0xb0 + (ulong)(-(uint)(bVar20 == 0) & 4)) = 0;
          }
          if (cVar9 == '\0') goto LAB_00145623;
          bStack_110 = (byte)uVar13;
          lVar26 = (long)(int)uVar14;
          uVar23 = 1 << (bStack_110 & 0x1f);
          iVar21 = ((uint)(byte)((ushort)uVar4 >> 8) + *(int *)(lVar17 + 0xc + (lVar26 + 0x24) * 4))
                   - (int)*(short *)(lVar17 + 6 + (lVar26 + 0x48) * 2);
          *(int *)(lVar17 + 0xc + (lVar26 + 0x24) * 4) = iVar21;
          *(short *)(lVar17 + 6 + (lVar26 + 0x48) * 2) = (short)(iVar21 >> (bStack_110 & 0x1f));
          uVar22 = *(int *)(lVar17 + (lVar26 + 0x2c) * 4) + 1;
          *(uint *)(lVar17 + (lVar26 + 0x2c) * 4) = uVar22;
          *(uint *)(lVar17 + 0xac) = uVar22;
          if (uVar23 <= uVar22) {
            *(byte *)(lVar17 + 0x94) = bVar20;
          }
          lVar26 = (long)(int)uVar14;
          uVar24 = (uint)(bVar2 >> 6 == 0);
          sVar11 = *(short *)(lVar17 + 6 + ((long)(int)uVar24 + 0x48) * 2);
          uVar22 = *(uint *)(lVar17 + 0xac);
          if (*(uint *)(lVar17 + 0xb8) < uVar22) {
            if ((uVar12 & 0xffff) != uVar24 << (*(byte *)(lVar17 + 0xbc) & 0x1f)) {
              piVar1 = (int *)(lVar17 + 0xcc + lVar26 * 4);
              *piVar1 = *piVar1 + 1;
            }
            *(undefined4 *)(lVar17 + 0xac) = 0;
            *(undefined4 *)(lVar17 + 0xa8) = 0;
            *(undefined4 *)(lVar17 + 0xb0 + (long)(int)uVar14 * 4) = 0;
            *(undefined4 *)(lVar17 + ((long)(int)uVar24 + 0x2c) * 4) = 0;
LAB_001455c9:
            bVar28 = true;
          }
          else {
            if (((int)sVar10 <= (int)sVar11 - (int)*(short *)(lVar17 + 0x96 + lVar26 * 2)) &&
               (uVar23 <= uVar22)) {
              if ((uVar12 & 0xffff) != uVar24 << (*(byte *)(lVar17 + 0xbc) & 0x1f)) {
                piVar1 = (int *)(lVar17 + 0xd4 + lVar26 * 4);
                *piVar1 = *piVar1 + 1;
              }
              goto LAB_001455c9;
            }
            if (sVar11 == 0) goto LAB_001455c9;
            bVar28 = false;
            if (uVar23 <= uVar22) goto LAB_00145623;
          }
          if (*(char *)(lVar17 + 0xf5) != '\0') {
            *(undefined1 *)(lVar17 + 0xfc) = 1;
            wl_add_timer(param_1[2],*(undefined8 *)(lVar17 + 0x108),*(undefined4 *)(lVar17 + 0xf8),0
                        );
          }
          if ((bVar28) && (*(char *)(lVar17 + 0xf5) != '\0')) {
            wlc_swdiv_ant_set(param_1[4],'\x03' - (bVar20 == 0),0);
          }
LAB_00145623:
          if ((((*(byte *)(alStack_40[0] + 10) & 4) != 0) && (!bVar7)) && (bStack_c8 == 0)) {
            wlc_ampdu_recvdata(param_1[0x31],alStack_40[0],&puStack_108);
            return;
          }
          wlc_recvdata_ordered(param_1,alStack_40[0],&puStack_108);
          return;
        }
      }
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x58);
      *piVar1 = *piVar1 + 1;
      goto LAB_00145667;
    }
  }
  piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 100);
  *piVar1 = *piVar1 + 1;
LAB_00145667:
  if ((*(int *)(*param_1 + 0x54) != 0) && (bStack_c8 == 0)) {
    lVar17 = *(long *)(*param_1 + 0xa8);
    uVar12 = osl_pktprio(uStack_e8);
    piVar1 = (int *)(lVar17 + 100 +
                    (ulong)*(byte *)((long)&wme_fifo2ac +
                                    (ulong)*(byte *)((long)&prio2fifo + (ulong)uVar12)) * 8);
    *piVar1 = *piVar1 + 1;
    uVar12 = osl_pktprio(uStack_e8);
    lVar17 = *(long *)(*param_1 + 0xa8);
    lVar26 = (ulong)*(byte *)((long)&wme_fifo2ac +
                             (ulong)*(byte *)((long)&prio2fifo + (ulong)uVar12)) + 0xc;
    iVar21 = *(int *)(lVar17 + 8 + lVar26 * 8);
    iVar15 = pkttotlen(param_2,uStack_e8);
    *(int *)(lVar17 + 8 + lVar26 * 8) = iVar15 + iVar21;
  }
  osl_pktfree(param_2,uStack_e8,0);
  return;
}

