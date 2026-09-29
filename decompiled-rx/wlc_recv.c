
void wlc_recv(long *param_1,undefined8 param_2)

{
  int *piVar1;
  ushort uVar2;
  ushort uVar3;
  undefined2 uVar4;
  long lVar5;
  ushort uVar6;
  byte bVar7;
  byte bVar8;
  char cVar9;
  bool bVar10;
  short sVar11;
  short sVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  undefined4 uVar17;
  long lVar18;
  long lVar19;
  long lVar20;
  undefined8 uVar21;
  long lVar22;
  byte *pbVar23;
  uint uVar24;
  ushort uVar25;
  long *plVar26;
  bool bVar27;
  bool bVar28;
  bool bVar29;
  ulong in_stack_fffffffffffffef8;
  undefined8 in_stack_ffffffffffffff00;
  long lStack_b8;
  long lStack_90;
  long lStack_70;
  undefined1 auStack_68 [24];
  long lStack_50;
  long lStack_48;
  long alStack_40 [2];
  
  lVar5 = param_1[1];
  lVar18 = osl_pktdata(lVar5);
  osl_pktpull(lVar5,param_2,*(undefined4 *)((long)param_1 + 0x6bc));
  if ((*(byte *)(lVar18 + 0x10) & 4) != 0) {
    uVar13 = osl_pktlen(lVar5,param_2);
    if (1 < uVar13) {
      osl_pktpull(lVar5,param_2,2);
      goto LAB_0014ceee;
    }
    goto LAB_0014d7bb;
  }
LAB_0014ceee:
  lVar19 = osl_pktdata(lVar5,param_2);
  uVar13 = osl_pktlen(lVar5,param_2);
  sVar11 = (short)*(undefined4 *)(param_1[8] + 8);
  if (((sVar11 == 8) || (sVar11 == 10)) && ((*(ushort *)(lVar18 + 4) & 0x100) != 0)) {
    *(ushort *)(lVar18 + 4) = *(ushort *)(lVar18 + 4) & 0xfeff;
  }
  if ((*(ushort *)(lVar18 + 4) & 0x310) != 0) goto LAB_0014e0f2;
  if ((int)param_1[0x51] != 0) {
    if ((*(byte *)(lVar18 + 0x12) & 1) == 0) {
      func_0x0013dbf2(param_1,lVar18,param_2);
    }
    else {
      lVar20 = osl_pktdup(param_1[1],param_2);
      if (lVar20 == 0) {
        lVar20 = param_1[0xe2];
        if (lVar20 != 0) {
LAB_0014d027:
          osl_pktfree(param_1[1],lVar20,0);
        }
        param_1[0xe2] = 0;
      }
      else {
        sVar11 = (short)((*(ushort *)(lVar18 + 0x12) & 6) >> 1);
        if ((sVar11 == 1) || (sVar11 == 3)) {
          if (param_1[0xe2] != 0) {
            osl_pktfree(param_1[1],param_1[0xe2],0);
            param_1[0xe2] = 0;
          }
          if (sVar11 != 1) {
            func_0x0013dbf2(param_1,lVar18,lVar20);
            lVar22 = param_1[1];
            goto LAB_0014d03f;
          }
          param_1[0xe2] = lVar20;
        }
        else {
          lVar22 = param_1[1];
          if (param_1[0xe2] == 0) {
LAB_0014d03f:
            osl_pktfree(lVar22,lVar20,0);
          }
          else {
            uVar21 = pktlast(lVar22);
            osl_pktsetnext(uVar21,lVar20);
            if (sVar11 == 2) {
              func_0x0013dbf2(param_1,lVar18,param_1[0xe2]);
              lVar20 = param_1[0xe2];
              goto LAB_0014d027;
            }
          }
        }
      }
    }
  }
  if ((*(byte *)(lVar18 + 0x10) & 1) != 0) goto LAB_0014e0f2;
  if (uVar13 < 8) goto LAB_0014d7bb;
  if ((*(byte *)(lVar18 + 0x12) & 1) != 0) {
    if (*(char *)((long)param_1 + 0x292) != '\0') {
      wlc_recvamsdu(param_1[0x2f],lVar18,param_2);
      return;
    }
    goto LAB_0014e0f2;
  }
  uVar13 = (int)(*(ushort *)(lVar19 + 6) & 0xc) >> 2;
  if ((uVar13 == 0) || (uVar13 == 2)) {
    if (((*(char *)(lVar19 + 0x11) == '\0') &&
        ((((*(byte *)(lVar19 + 0x10) == 0 && (*(char *)(lVar19 + 0x12) == '\0')) &&
          (*(char *)(lVar19 + 0x13) == '\0')) &&
         ((*(char *)(lVar19 + 0x14) == '\0' && (*(char *)(lVar19 + 0x15) == '\0')))))) ||
       ((*(byte *)(lVar19 + 0x10) & 1) != 0)) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x74);
      *piVar1 = *piVar1 + 1;
      goto LAB_0014e0f2;
    }
    piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x1cc);
    *piVar1 = *piVar1 + 1;
  }
  wlc_amsdu_flush(param_1[0x2f]);
  if (uVar13 == 2) {
    wlc_recvdata(param_1,lVar5,lVar18,param_2);
    return;
  }
  if (1 < uVar13) goto LAB_0014e0e5;
  alStack_40[0] = 0;
  lStack_48 = 0;
  lStack_50 = 0;
  lVar19 = osl_pktdata(lVar5,param_2);
  uVar2 = *(ushort *)(lVar19 + 6);
  lVar20 = lVar19 + 6;
  uVar3 = *(ushort *)(lVar18 + 4);
  sVar11 = (short)((uVar2 & 0xc) >> 2);
  if (((uVar3 & 3) == 2) && ((short)uVar2 < 0)) {
    bVar10 = sVar11 == 0;
  }
  else {
    bVar10 = false;
  }
  iVar14 = osl_pktlen(lVar5,param_2);
  iVar15 = iVar14 + -10;
  if ((sVar11 != 0) || ((int)(((int)((uint)bVar10 << 0x1f) >> 0x1f & 4U) + 0x18) <= iVar15)) {
    uVar25 = uVar2 & 0xfc;
    bVar27 = uVar25 == 0xa4;
    uVar6 = uVar2 & 0xfc;
    bVar28 = uVar25 == 0x84;
    if (((!bVar28 && !bVar27) && (uVar25 != 0x94)) || (0xf < iVar15)) {
      bVar7 = *(byte *)(lVar19 + 10) & 1;
      if (bVar7 == 0) {
        lStack_90 = wlc_bsscfg_find_by_hwaddr(param_1,lVar19 + 10);
        bVar29 = lStack_90 != 0;
      }
      else {
        lStack_90 = 0;
        bVar29 = false;
      }
      if (sVar11 == 0) {
        if (bVar7 == 0) {
          alStack_40[0] =
               wlc_scbbssfindband(param_1,lVar19 + 10,lVar19 + 0x10,0xe < *(byte *)(lVar18 + 0x16),
                                  &lStack_48);
        }
        else {
          lVar22 = param_1[0x5e];
          if (((lVar22 != 0) && (iVar16 = osl_memcmp(lVar22 + 0xf0,lVar19 + 0x16,6), iVar16 == 0))
             && ((*(char *)(lVar22 + 0x22) == '\0' ||
                 (alStack_40[0] = wlc_scbfind(param_1,lVar22,lVar19 + 0x10), alStack_40[0] != 0))))
          {
            lStack_48 = lVar22;
          }
        }
        lStack_50 = lStack_48;
        if (lStack_48 != 0) goto LAB_0014d33a;
        lStack_b8 = wlc_bsscfg_find_by_target_bssid(param_1,lVar19 + 0x16);
        lStack_50 = lStack_b8;
      }
      else {
LAB_0014d33a:
        lStack_b8 = 0;
      }
      if (((int)param_1[0x51] == 0) && (*(char *)(*param_1 + 0x4c) == '\0')) {
        if ((!bVar29) && (bVar7 == 0)) {
          piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x78);
          *piVar1 = *piVar1 + 1;
          goto LAB_0014e0f2;
        }
LAB_0014d412:
        if (((sVar11 == 1) && (uVar6 != 0xd4)) && (uVar6 != 0xc4)) {
          if ((((*(char *)(lVar19 + 0x11) == '\0') && (*(byte *)(lVar19 + 0x10) == 0)) &&
              ((*(char *)(lVar19 + 0x12) == '\0' &&
               ((*(char *)(lVar19 + 0x13) == '\0' && (*(char *)(lVar19 + 0x14) == '\0')))))) &&
             (*(char *)(lVar19 + 0x15) == '\0')) goto LAB_0014e0f2;
          bVar8 = *(byte *)(lVar19 + 0x10) & 1;
LAB_0014d460:
          if (bVar8 != 0) goto LAB_0014e0f2;
        }
      }
      else {
        if ((((bVar28 || bVar27) || (uVar6 == 0x94)) && (bVar29)) ||
           ((uVar6 == 0x50 || (uVar6 == 0x80)))) goto LAB_0014d412;
        if (sVar11 != 0) goto LAB_0014e0f2;
        if (!bVar29) {
          if ((*(byte *)(lVar19 + 0xb) & *(byte *)(lVar19 + 10) & *(byte *)(lVar19 + 0xc) &
               *(byte *)(lVar19 + 0xd) & *(byte *)(lVar19 + 0xe) & *(byte *)(lVar19 + 0xf)) != 0xff)
          goto LAB_0014e0f2;
          if (lStack_50 != 0) goto LAB_0014d466;
          bVar8 = (*(byte *)(lVar19 + 0x17) & *(byte *)(lVar19 + 0x16) & *(byte *)(lVar19 + 0x18) &
                   *(byte *)(lVar19 + 0x19) & *(byte *)(lVar19 + 0x1a) & *(byte *)(lVar19 + 0x1b)) +
                  1;
          goto LAB_0014d460;
        }
      }
LAB_0014d466:
      osl_pktpull(lVar5,param_2,6);
      osl_pktsetlen(lVar5,param_2,iVar15);
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x4c);
      *piVar1 = *piVar1 + 1;
      uVar17 = osl_pktlen(lVar5,param_2);
      sVar12 = func_0x001445cf(param_1,&lStack_50,lVar20,lVar18,alStack_40,uVar17);
      uVar17 = (undefined4)((ulong)in_stack_ffffffffffffff00 >> 0x20);
      if (sVar12 != 0) {
        piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x7c);
        *piVar1 = *piVar1 + 1;
        goto LAB_0014e0f2;
      }
      if (alStack_40[0] != 0) {
        *(undefined4 *)(alStack_40[0] + 0x2c) = *(undefined4 *)(*param_1 + 0x48);
      }
      if (sVar11 == 1) {
        if (((uVar6 == 0x84) || (uVar6 == 0xa4)) || (uVar6 == 0x94)) {
          uVar21 = osl_pktpull(lVar5,param_2,0x10);
          if (bVar10) {
            uVar21 = osl_pktpull(lVar5,param_2,4);
          }
          uVar17 = osl_pktlen(lVar5,param_2);
          if (((!bVar27) && (*(char *)(*param_1 + 0x5e) != '\0')) &&
             ((*(char *)(*param_1 + 0x5f) != '\0' && ((uVar6 == 0x94 || (bVar28)))))) {
            wlc_ampdu_recv_ctl(param_1,alStack_40[0],uVar21,uVar17,uVar2 & 0xfc);
          }
        }
        goto LAB_0014e0f2;
      }
      bVar27 = (*(ushort *)(lVar18 + 0x16) & 0xc000) != 0;
      if (bVar7 == 0) {
        sVar11 = *(short *)(lVar19 + 0x1c);
        lVar22 = alStack_40[0];
        if ((alStack_40[0] == 0) && (lVar22 = 0, lStack_50 != 0)) {
          lVar22 = wlc_scbfindband(param_1,lStack_50,lVar19 + 0x10,bVar27);
        }
        alStack_40[0] = lVar22;
        uVar17 = (undefined4)((ulong)in_stack_ffffffffffffff00 >> 0x20);
        if ((((uVar2 & 0x800) != 0) && (alStack_40[0] != 0)) &&
           (*(short *)(alStack_40[0] + 0xd8) == sVar11)) {
LAB_0014d6e3:
          piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x1bc);
          *piVar1 = *piVar1 + 1;
          goto LAB_0014e0f2;
        }
        if (alStack_40[0] == 0) {
          for (bVar7 = 0; uVar17 = (undefined4)((ulong)in_stack_ffffffffffffff00 >> 0x20),
              bVar7 <= *(byte *)(param_1 + 0xd1); bVar7 = bVar7 + 1) {
            lVar22 = (long)(int)(uint)bVar7;
            if ((((*(char *)((long)param_1 + lVar22 * 8 + 0x639) == '\0') &&
                 ((char)param_1[lVar22 + 199] == '\0')) &&
                ((*(char *)((long)param_1 + lVar22 * 8 + 0x63a) == '\0' &&
                 ((*(char *)((long)param_1 + lVar22 * 8 + 0x63b) == '\0' &&
                  (*(char *)((long)param_1 + lVar22 * 8 + 0x63c) == '\0')))))) &&
               (*(char *)((long)param_1 + lVar22 * 8 + 0x63d) == '\0')) break;
            iVar15 = osl_memcmp(lVar19 + 0x10,param_1 + (long)(int)(uint)bVar7 + 199,6);
            uVar17 = (undefined4)((ulong)in_stack_ffffffffffffff00 >> 0x20);
            if (iVar15 == 0) {
              plVar26 = param_1 + (ulong)bVar7 + 199;
              if (plVar26 != (long *)0x0) {
                if (((uVar2 & 0x800) != 0) && (*(short *)((long)plVar26 + 6) == sVar11))
                goto LAB_0014d6e3;
                if (plVar26 != (long *)0x0) goto LAB_0014d73f;
              }
              break;
            }
          }
          plVar26 = param_1 + (ulong)*(byte *)(param_1 + 0xd1) + 199;
          *(byte *)(param_1 + 0xd1) = *(byte *)(param_1 + 0xd1) + 1;
          osl_memcpy(plVar26,lVar19 + 0x10,6);
          *(byte *)(param_1 + 0xd1) = *(byte *)(param_1 + 0xd1) % 10;
LAB_0014d73f:
          *(short *)((long)plVar26 + 6) = sVar11;
        }
        else {
          *(short *)(alStack_40[0] + 0xd8) = sVar11;
        }
      }
      if (((bVar29) && (lStack_48 != 0)) && (*(char *)(*(long *)(lStack_50 + 0x338) + 0xc) != '\0'))
      {
        func_0x0013f9d7(lStack_50,(uint)uVar2);
      }
      pbVar23 = (byte *)osl_pktpull(lVar5,param_2,0x18);
      if (bVar10) {
        pbVar23 = (byte *)osl_pktpull(lVar5,param_2,4);
      }
      iVar15 = osl_pktlen(lVar5,param_2);
      lVar22 = alStack_40[0];
      if ((uVar2 & 0x4000) != 0) {
        if (7 < iVar15) {
          if (uVar6 != 0xb0) {
            piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x1dc);
            *piVar1 = *piVar1 + 1;
            goto LAB_0014e0f2;
          }
LAB_0014d88b:
          if (*(short *)(pbVar23 + 2) == 1) {
            lStack_50 = wlc_bsscfg_find_by_bssid(param_1,lVar19 + 0x16);
          }
          if ((lStack_50 != 0) && (*(char *)(param_1[0x83] + 0x34) != '\0')) {
            wlc_authresp_client(lStack_50,lVar20,pbVar23,iVar15,uVar3 >> 7 & 1);
          }
          goto LAB_0014e0f2;
        }
        goto LAB_0014d7bb;
      }
      if (uVar6 == 0x50) {
        if (0xb < iVar15) {
          cVar9 = wlc_has_restricted_chanspec(param_1[0x34]);
          if (cVar9 != '\0') {
            func_0x0012f804(param_1,lVar18,lVar20,pbVar23,iVar15);
          }
          if (((param_1[0x37] != 0) && (bVar29)) && (*(char *)(param_1[0x37] + 10) != '\0')) {
            func_0x0012ffa3(param_1,lVar18,lVar19,lVar20,pbVar23,iVar15);
          }
          goto LAB_0014e0f2;
        }
      }
      else if (uVar6 < 0x51) {
        if (uVar6 == 0x20) {
LAB_0014dbf2:
          if (3 < iVar15) goto LAB_0014e0f2;
        }
        else {
          if (uVar6 < 0x21) {
            if (uVar6 == 0) goto LAB_0014dbf2;
            if (uVar6 != 0x10) goto LAB_0014e0f2;
          }
          else if (uVar6 != 0x30) {
            if ((uVar6 == 0x40) && (iVar14 = wlc_eventq_test_ind(param_1[0x62],0x2c), iVar14 != 0))
            {
              wlc_bss_mac_event(param_1,param_1[0x5f],0x2c,lVar19 + 0x10,0,0,
                                in_stack_fffffffffffffef8 & 0xffffffff00000000,lVar20,iVar15 + 0x18)
              ;
            }
            goto LAB_0014e0f2;
          }
          if (5 < iVar15) {
            if (lStack_50 != 0) {
              wlc_assocresp_client(lStack_50,lVar20,pbVar23,iVar15,alStack_40[0]);
            }
            goto LAB_0014e0f2;
          }
        }
      }
      else if (uVar6 == 0xb0) {
        if (5 < iVar15) goto LAB_0014d88b;
      }
      else if (uVar6 < 0xb1) {
        if (uVar6 == 0x80) {
          func_0x0014b8d3(param_1,lStack_48,lStack_b8,lVar18,lVar19,iVar14);
          goto LAB_0014e0f2;
        }
        if (uVar6 != 0xa0) goto LAB_0014e0f2;
        if (1 < iVar15) {
          if (lStack_50 == 0) goto LAB_0014e0f2;
          uVar4 = *(undefined2 *)pbVar23;
          wlc_scb_disassoc_cleanup(param_1,alStack_40[0]);
          if (((*(byte *)(alStack_40[0] + 0x2a) & 2) != 0) &&
             (wlc_scb_clearstatebit(alStack_40[0],2), (*(byte *)(alStack_40[0] + 0x2a) & 8) == 0)) {
            wlc_disassoc_ind_complete
                      (param_1,lStack_50,0,lVar19 + 0x10,uVar4,0,pbVar23,CONCAT44(uVar17,iVar15));
          }
          if (lStack_48 == 0) goto LAB_0014e0f2;
          if (*(int *)(*(long *)(lStack_50 + 800) + 0xc) != 0) {
            wlc_assoc_abort();
          }
          uVar21 = 3;
          goto LAB_0014dbe4;
        }
      }
      else if (uVar6 == 0xc0) {
        if (1 < iVar15) {
          lVar18 = lStack_50;
          if ((lStack_50 == 0) && (lVar18 = lStack_90, lStack_90 == 0)) goto LAB_0014e0f2;
          sVar11 = *(short *)pbVar23;
          if (alStack_40[0] == 0) {
            alStack_40[0] = wlc_scbfindband(param_1,lVar18,lVar19 + 0x10,bVar27);
          }
          if (alStack_40[0] != 0) {
            wlc_scb_disassoc_cleanup(param_1);
          }
          if ((alStack_40[0] != 0) &&
             ((wlc_scb_clearstatebit(alStack_40[0],0x12), (*(byte *)(alStack_40[0] + 0x2a) & 1) != 0
              || ((*(byte *)(alStack_40[0] + 0xb) & 0x20) != 0)))) {
            wlc_scb_clearstatebit(alStack_40[0],1);
            if ((ushort)(sVar11 - 0xdU) < 10) {
              piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x1f8);
              *piVar1 = *piVar1 + 1;
            }
            if ((*(char *)(*param_1 + 0xc2) != '\0') && (*(char *)(lVar18 + 0x20) == '\x02')) {
              wlc_wpa_send_sup_status(*(undefined8 *)(lVar18 + 0x18),0xe);
            }
            if ((*(byte *)(alStack_40[0] + 0x2a) & 4) == 0) {
              wlc_deauth_ind_complete
                        (param_1,lVar18,0,lVar19 + 0x10,sVar11,
                         *(uint *)(alStack_40[0] + 8) >> 0x1d & 1,pbVar23,CONCAT44(uVar17,iVar15));
            }
            *(uint *)(alStack_40[0] + 8) = *(uint *)(alStack_40[0] + 8) & 0xdfffffff;
          }
          if (((lStack_48 == 0) || (*(char *)(lStack_50 + 0x22) == '\0')) ||
             ((lVar18 = *(long *)(lStack_50 + 800), *(int *)(lVar18 + 8) == 2 &&
              (9 < *(uint *)(lVar18 + 0xc))))) goto LAB_0014e0f2;
          if (*(int *)(lVar18 + 0xc) != 0) {
            wlc_assoc_abort();
          }
          uVar21 = 2;
LAB_0014dbe4:
          wlc_roamscan_start(lStack_50,uVar21);
          goto LAB_0014e0f2;
        }
      }
      else {
        if (uVar6 != 0xd0) goto LAB_0014e0f2;
        cVar9 = wlc_lq_rssi_pktrxh_cal(param_1,lVar18);
        uVar17 = wlc_recv_compute_rspec(lVar18,lVar19);
        if (0 < iVar15) {
          bVar7 = *pbVar23;
          bVar8 = 0;
          if (iVar15 != 1) {
            bVar8 = pbVar23[1];
          }
          if (lVar22 == 0) {
            lStack_70 = wlc_bsscfg_find_by_bssid(param_1,lVar19 + 0x16);
            if (lStack_70 == 0) {
              lStack_70 = wlc_bsscfg_find_by_hwaddr(param_1,lVar19 + 10);
            }
          }
          else {
            lStack_70 = *(long *)(lVar22 + 0x18);
          }
          if (((bVar7 == 0x7f) || (bVar7 == 4)) || (bVar7 == 10)) {
            in_stack_fffffffffffffef8 = in_stack_fffffffffffffef8 & 0xffffffff00000000;
            wlc_bss_mac_event(param_1,lStack_70,0x3b,lVar19 + 0x10,0,0,in_stack_fffffffffffffef8,
                              pbVar23,iVar15);
            iVar14 = wlc_eventq_test_ind(param_1[0x62],0x4b);
            if (iVar14 != 0) {
              wlc_recv_prep_event_rx_frame_data(param_1,lVar18,lVar19,auStack_68);
              wlc_bss_mac_rxframe_event
                        (param_1,lStack_70,0x4b,lVar19 + 0x10,0,0,
                         in_stack_fffffffffffffef8 & 0xffffffff00000000,pbVar23,iVar15,auStack_68);
            }
          }
          if (bVar7 == 7) {
            if (((*(byte *)(*param_1 + 0x68) & 3) == 0) || (lVar22 == 0)) goto LAB_0014e0f2;
            if (bVar8 == 0) {
              uVar13 = *(uint *)(lVar22 + 8);
              if ((pbVar23[2] == 0) || ((*(byte *)(lVar22 + 0x122) & 2) == 0)) {
                uVar24 = uVar13 & 0xfff7ffff;
              }
              else {
                uVar24 = uVar13 | 0x80000;
              }
              *(uint *)(lVar22 + 8) = uVar24;
              if ((uVar13 & 0x80000) == (*(uint *)(lVar22 + 8) & 0x80000)) goto LAB_0014e0f2;
            }
            else {
              if (bVar8 != 1) goto LAB_0014e0f2;
              if (iVar15 == 3) {
                bVar27 = (bool)(pbVar23[2] & 1);
                bVar10 = (bool)(pbVar23[2] >> 1 & 1);
              }
              else {
                if (iVar15 != 4) goto LAB_0014e0f2;
                bVar27 = pbVar23[2] != 0;
                bVar10 = pbVar23[3] != 0;
              }
              if (((bool)*(byte *)(lVar22 + 0x120) == bVar27) &&
                 ((bool)*(byte *)(lVar22 + 0x121) == bVar10)) goto LAB_0014e0f2;
              *(bool *)(lVar22 + 0x120) = bVar27;
              *(bool *)(lVar22 + 0x121) = bVar10;
            }
            wlc_scb_ratesel_init(param_1,lVar22);
            goto LAB_0014e0f2;
          }
          if (bVar7 < 8) {
            if (bVar7 == 0) {
              if (*(char *)(*param_1 + 200) == '\0') goto LAB_0014e0f2;
              if (iVar15 != 1) {
                wlc_recv_frameaction_specmgmt(param_1[0x39],lVar20,pbVar23,iVar15,(int)cVar9,uVar17)
                ;
                goto LAB_0014e0f2;
              }
LAB_0014e0d4:
              wlc_send_action_err(param_1,lVar20,pbVar23,iVar15);
              goto LAB_0014e0e5;
            }
            if (bVar7 == 4) {
              if ((1 < iVar15) && ((*(byte *)(*param_1 + 0x68) & 3) != 0)) {
                if (pbVar23[1] == 0) {
                  uVar2 = *(ushort *)((long)param_1 + 0x516);
                  lVar20 = bcm_parse_tlvs(pbVar23 + 2,iVar15 + -2,0x48);
                  if ((lVar20 == 0) || (*(char *)(lVar20 + 1) == '\0')) {
                    bVar7 = 0;
                  }
                  else {
                    bVar8 = *(byte *)(lVar20 + 2);
                    bVar7 = ~-((bVar8 & 2) == 0) & 2;
                    if ((bVar8 & 4) != 0) {
                      bVar7 = bVar7 | 4;
                    }
                    if (((((bVar8 & 1) != 0) || (bVar7 != 0)) &&
                        (bVar8 = wf_chspec_ctlchan(uVar2), bVar8 < 0xf)) && ((uVar2 & 0xc000) == 0))
                    {
                      *(byte *)(param_1[0x77] + 3 + (ulong)bVar8) = bVar7;
                    }
                  }
                  if ((bVar7 & 2) != 0) {
                    wlc_bsscfg_find_by_hwaddr(param_1,lVar19 + 10);
                  }
                  if ((bVar7 & 4) != 0) {
                    wlc_scbfindband(param_1,lStack_70,lVar19 + 0x10,
                                    (*(ushort *)(lVar18 + 0x16) & 0xc000) != 0);
                  }
                  bcm_parse_tlvs(pbVar23 + 2,iVar15 + -2,0x49);
                }
                else if ((pbVar23[1] == 4) && (*(char *)(*param_1 + 200) != '\0')) {
                  wlc_recv_public_csa_action(param_1[0x3b],lVar20,pbVar23,iVar15);
                }
              }
              goto LAB_0014e0f2;
            }
          }
          else {
            if (bVar7 == 0x15) {
              if (*(char *)(*param_1 + 0x6a) != '\0') {
                wlc_frameaction_vht(param_1,bVar8,lVar22,lVar20,pbVar23,iVar15);
              }
              goto LAB_0014e0f2;
            }
            if (bVar7 == 0x7f) goto LAB_0014e0f2;
            if (bVar7 == 0x11) {
              if ((lStack_70 != 0) && (*(int *)(*param_1 + 0x54) == 0)) goto LAB_0014e0f2;
              if (0x42 < iVar15) {
                if (*(char *)(*param_1 + 0x61) != '\0') {
                  wlc_frameaction_cac(lStack_70,bVar8,param_1[0x36],lVar20,pbVar23,iVar15);
                }
                goto LAB_0014e0f2;
              }
              goto LAB_0014e0d4;
            }
          }
          if ((bVar7 & 0x7f) == 3) {
            wlc_frameaction_ampdu(param_1,lVar22,lVar20,pbVar23,iVar15);
          }
          else if (-1 < (char)bVar7) {
            wlc_send_action_err(param_1,lVar20,pbVar23,iVar15);
          }
          goto LAB_0014e0f2;
        }
      }
LAB_0014e0e5:
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x70);
      *piVar1 = *piVar1 + 1;
      goto LAB_0014e0f2;
    }
  }
LAB_0014d7bb:
  piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 100);
  *piVar1 = *piVar1 + 1;
LAB_0014e0f2:
  osl_pktfree(lVar5,param_2,0);
  return;
}

