
void FUN_00145e30(long *param_1)

{
  int iVar1;
  uint *puVar2;
  undefined4 *puVar3;
  long lVar4;
  long lVar5;
  long *plVar6;
  long *plVar7;
  code *pcVar8;
  char cVar9;
  byte bVar10;
  uint uVar11;
  undefined4 uVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  long lVar16;
  ulong uVar17;
  long lVar18;
  uint *puVar19;
  short sVar20;
  uint uVar21;
  undefined8 uVar22;
  ulong extraout_RDX;
  undefined1 uVar23;
  short *psVar24;
  int iVar25;
  char *pcVar26;
  bool bVar27;
  bool bVar28;
  ulong in_stack_ffffffffffffff48;
  ulong in_stack_ffffffffffffff50;
  undefined1 local_88 [32];
  short local_68 [16];
  char local_48 [24];
  
  if (*(char *)(*param_1 + 0x34) == '\0') {
    return;
  }
  cVar9 = wlc_hw_deviceremoved(param_1[4]);
  if (cVar9 != '\0') {
    wl_down(param_1[2]);
    return;
  }
  cVar9 = (char)param_1[0x106];
  if ((cVar9 == '\x01') && (*(char *)((long)param_1 + 0x2ad) != '\0')) {
    *(undefined1 *)(param_1 + 0x106) = 0;
    *(undefined1 *)((long)param_1 + 0x2ad) = 0;
    wlc_set_wake_ctrl(param_1);
    lVar16 = param_1[0x37];
    if ((lVar16 != 0) && (*(char *)(lVar16 + 10) != '\0')) {
      wlc_scan_abort(lVar16,4);
    }
  }
  else if ((*(char *)((long)param_1 + 0x2ad) != '\0') && (cVar9 != '\0')) {
    *(char *)(param_1 + 0x106) = cVar9 + -1;
  }
  lVar16 = *(long *)(*param_1 + 0xa0);
  puVar2 = (uint *)param_1[0x105];
  if (*puVar2 < *(uint *)(lVar16 + 8)) {
    puVar2[2] = *(uint *)(lVar16 + 8) - *puVar2;
  }
  else {
    puVar2[2] = 0;
  }
  *puVar2 = *(uint *)(lVar16 + 8);
  if (puVar2[1] < *(uint *)(lVar16 + 0x44)) {
    puVar2[3] = *(uint *)(lVar16 + 0x44) - puVar2[1];
  }
  else {
    puVar2[3] = 0;
  }
  puVar2[1] = *(uint *)(lVar16 + 0x44);
  if (puVar2[5] < *(uint *)(lVar16 + 0x40)) {
    puVar2[7] = *(uint *)(lVar16 + 0x40) - puVar2[5];
  }
  else {
    puVar2[7] = 0;
  }
  puVar2[5] = *(uint *)(lVar16 + 0x40);
  if (puVar2[4] < *(uint *)(lVar16 + 4)) {
    puVar2[6] = *(uint *)(lVar16 + 4) - puVar2[4];
  }
  else {
    puVar2[6] = 0;
  }
  psVar24 = local_68;
  puVar2[4] = *(uint *)(lVar16 + 4);
  osl_memset(psVar24,0,8);
  osl_memset(local_48,0,4);
  lVar16 = param_1[0x5e];
  if ((lVar16 == 0) || (*(char *)(lVar16 + 8) == '\0')) {
    iVar15 = 0;
  }
  else {
    iVar25 = 0;
    do {
      if (*psVar24 == 0) {
        iVar15 = 1;
        local_68[iVar25] = *(short *)(*(long *)(lVar16 + 0x318) + 0x32);
        goto LAB_00145fcd;
      }
      if (*psVar24 == *(short *)(*(long *)(lVar16 + 0x318) + 0x32)) break;
      iVar25 = iVar25 + 1;
      psVar24 = psVar24 + 1;
    } while (iVar25 != 4);
    iVar15 = 0;
LAB_00145fcd:
    wlc_scb_iterinit(param_1[0x2b],local_88);
    while (lVar16 = wlc_scb_iternext(param_1[0x2b],local_88), lVar16 != 0) {
      if (((*(byte *)(lVar16 + 0x21) & (byte)*(undefined4 *)(lVar16 + 0x20) &
            *(byte *)(lVar16 + 0x22) & *(byte *)(lVar16 + 0x23) &
            (byte)*(undefined4 *)(lVar16 + 0x24) & *(byte *)(lVar16 + 0x25)) != 0xff) &&
         (cVar9 = wlc_scb_rssi(lVar16), cVar9 < local_48[iVar25])) {
        local_48[iVar25] = cVar9;
      }
    }
  }
  psVar24 = local_68;
  for (pcVar26 = local_48; (int)pcVar26 - (int)local_48 < iVar15; pcVar26 = pcVar26 + 1) {
    sVar20 = *psVar24;
    psVar24 = psVar24 + 1;
    wlc_phy_interf_rssi_update(*(undefined8 *)(param_1[8] + 0x10),sVar20,(int)*pcVar26);
  }
  if (((char)param_1[0xf0] != '\0') &&
     (uVar17 = osl_readl(*(long *)(param_1[4] + 0xd0) + 0x124), (uVar17 & 0x40) == 0)) {
    wlc_bmac_suspend_mac_and_wait(param_1[4]);
    *(undefined1 *)(param_1 + 0xf0) = 0;
    wlc_phy_block_bbpll_change(*(undefined8 *)(param_1[8] + 0x10),0,0);
    wlc_bmac_enable_mac(param_1[4]);
  }
  *(int *)(*param_1 + 0x48) = *(int *)(*param_1 + 0x48) + 1;
  lVar16 = param_1[0xaa];
  if (*(char *)(lVar16 + 0xf4) != '\0') {
    if (*(int *)(lVar16 + 0xac) == *(int *)(lVar16 + 0xa8)) {
      FUN_001313bb(param_1,lVar16 + 0xec);
    }
    *(undefined4 *)(lVar16 + 0xa8) = *(undefined4 *)(lVar16 + 0xac);
  }
  if (*(char *)((long)param_1 + 0x2a5) == '\0') {
    *(int *)(param_1 + 0x55) = (int)param_1[0x55] + 1;
  }
  if (((*(char *)((long)param_1 + 0x253) != '\0') && (cVar9 = FUN_00125d42(param_1), cVar9 != '\0'))
     && (*(char *)((long)param_1 + 0x25c) != '\0')) {
    *(char *)((long)param_1 + 0x25c) = *(char *)((long)param_1 + 0x25c) + -1;
  }
  wlc_radio_mpc_upd(param_1);
  FUN_0013188b(param_1);
  wlc_radio_upd(param_1);
  if (*(char *)((long)param_1 + 0x253) != '\0') {
    wlc_ismpc(param_1);
  }
  if (*(int *)(*param_1 + 0x84) != 0) {
    return;
  }
  if ((**(char **)(param_1[0x5f] + 0x338) != '\0') && (*(short *)((long)param_1 + 0x6e4) != 0)) {
    uVar11 = osl_sysuptime();
    if (*(uint *)((long)param_1 + 0x6ec) < uVar11) {
      uVar14 = uVar11 - *(uint *)((long)param_1 + 0x6ec);
      if ((uint)(*(short *)((long)param_1 + 0x6e4) * 1000) <= uVar14) {
        uVar13 = wlc_get_accum_pmdur(param_1);
        uVar21 = *(uint *)(param_1 + 0xdd);
        if (((uVar21 <= uVar13) && (uVar13 - uVar21 <= uVar14)) &&
           (((int)*(short *)((long)param_1 + 0x6e6) * uVar14) / 100 <= (uVar14 + uVar21) - uVar13))
        {
          in_stack_ffffffffffffff48 = 0;
          wlc_mac_event(param_1,0x51,0,0,0,0,0,in_stack_ffffffffffffff50 & 0xffffffff00000000);
        }
        *(uint *)((long)param_1 + 0x6ec) = uVar11;
        *(uint *)(param_1 + 0xdd) = uVar13;
      }
    }
    else {
      *(uint *)((long)param_1 + 0x6ec) = uVar11;
      uVar12 = wlc_get_accum_pmdur(param_1);
      *(undefined4 *)(param_1 + 0xdd) = uVar12;
    }
  }
  iVar15 = *(int *)(param_1[0xd2] + 0xc);
  if (*(int *)param_1[8] == 2) {
    if (iVar15 != 0) {
      wlc_enable_btc_ps_protection(param_1,param_1[0x5f],1);
    }
    if (0xe < *(uint *)(*param_1 + 0x14)) {
      wlc_bmac_btc_period_get(param_1[4],param_1[0xd2],param_1[0xd2] + 2);
      *(undefined4 *)(param_1[0xd2] + 0x28) = *(undefined4 *)(param_1[0xd2] + 0x2c);
      lVar16 = param_1[0xd2];
      uVar12 = wlc_bmac_btc_params_get(param_1[4],0x27);
      *(undefined4 *)(lVar16 + 0x2c) = uVar12;
      lVar16 = param_1[0xd2];
      *(int *)(lVar16 + 0x38) = *(int *)(lVar16 + 0x2c) - *(int *)(lVar16 + 0x28);
    }
    if ((*(int *)(*(long *)(*param_1 + 0x100) + 0x3c) == 0xa886) &&
       (lVar16 = param_1[0xd2], *(char *)(lVar16 + 2) != '\0')) {
      if ((*(byte *)(lVar16 + 7) == 0) ||
         (-*(int *)(*(long *)(param_1[0x5f] + 0x330) + 0x14) <= (int)(uint)*(byte *)(lVar16 + 7))) {
        iVar25 = *(int *)(*(long *)(param_1[0x5f] + 0x330) + 0x14);
        if ((((iVar25 != 0) && (*(byte *)(lVar16 + 6) != 0)) &&
            (-iVar25 < (int)(uint)*(byte *)(lVar16 + 6))) && (*(char *)(lVar16 + 9) != '\0')) {
          wlc_btc_mode_set(param_1,*(char *)(lVar16 + 9));
          *(undefined1 *)(param_1[0xd2] + 9) = 0;
        }
        goto LAB_0014636b;
      }
      if (1 < iVar15 - 1U) {
        *(char *)(lVar16 + 9) = (char)iVar15;
        wlc_btc_mode_set(param_1,1);
        goto LAB_0014636b;
      }
    }
    else {
LAB_0014636b:
      if (iVar15 == 0) goto LAB_001463bf;
    }
    cVar9 = *(char *)(param_1[0xd2] + 8);
    if (cVar9 != '\x03') {
      if (*(char *)(param_1[0xd2] + 2) == '\0') {
        if (cVar9 != **(char **)(param_1[0x5f] + 0x338)) goto LAB_001463b7;
      }
      else if ((cVar9 == '\0') && (cVar9 = '\x02', **(char **)(param_1[0x5f] + 0x338) != '\x02')) {
LAB_001463b7:
        FUN_00140940(param_1,cVar9);
      }
    }
  }
LAB_001463bf:
  if ((*(int *)(*(long *)(*param_1 + 0x100) + 0x3c) == 0x4331) &&
     ((*(byte *)(*param_1 + 0x9a) & 0x40) != 0)) {
    if (((iVar15 != 5) && (iVar15 != 3)) ||
       ((*(int *)param_1[8] != 2 || (*(char *)(param_1[0xd2] + 2) == '\0')))) {
      uVar22 = 0;
      uVar23 = *(undefined1 *)param_1[0xaa];
    }
    else {
      if (iVar15 != 3) goto LAB_00146430;
      uVar22 = 1;
      uVar23 = 5;
    }
    wlc_stf_txchain_set(param_1,uVar23,uVar22,4);
  }
LAB_00146430:
  if ((*(int *)(*(long *)(*param_1 + 0x100) + 0x3c) == 0x4331) &&
     ((*(byte *)(*param_1 + 0x9a) & 0x40) != 0)) {
    if (((iVar15 != 5) && (iVar15 != 3)) ||
       ((*(int *)param_1[8] != 2 || (*(char *)(param_1[0xd2] + 2) == '\0')))) {
      wlc_stf_txchain_set(param_1,*(undefined1 *)param_1[0xaa],0,4);
      goto LAB_001464ac;
    }
    if (iVar15 != 3) goto LAB_001464ac;
    wlc_stf_txchain_set(param_1,5,1,4);
  }
  else {
LAB_001464ac:
    if ((iVar15 == 5) &&
       ((iVar25 = *(int *)(*(long *)(*param_1 + 0x100) + 0x3c), iVar25 == 0x4352 ||
        (iVar25 == 0xa8dc)))) {
      if ((*(char *)(param_1[0xd2] + 2) == '\0') || (*(int *)param_1[8] != 2)) {
        bVar10 = *(char *)(param_1[0xaa] + 0x11) + 1;
        *(byte *)(param_1[0xaa] + 0x11) = bVar10;
        if (bVar10 < 6) goto LAB_0014654e;
        if (*(char *)(param_1[0xaa] + 0x12) != '\0') {
          wlc_stf_rxchain_set(param_1,*(char *)(param_1[0xaa] + 0x12));
          *(undefined1 *)(param_1[0xaa] + 0x12) = 0;
        }
      }
      else {
        lVar16 = param_1[0xaa];
        if (*(char *)(lVar16 + 0x12) == '\0') {
          *(undefined1 *)(lVar16 + 0x12) = *(undefined1 *)(lVar16 + 5);
        }
        wlc_stf_rxchain_set(param_1,1);
      }
      *(undefined1 *)(param_1[0xaa] + 0x11) = 0;
    }
  }
LAB_0014654e:
  lVar16 = *param_1;
  if ((0xe < *(uint *)(lVar16 + 0x14)) && (*(int *)param_1[8] == 2)) {
    if ((iVar15 == 4) || (iVar15 == 0)) {
LAB_001466be:
      FUN_0013e169(param_1);
    }
    else if ((((*(char *)(lVar16 + 0x5e) != '\0') && (*(char *)(lVar16 + 0x5f) != '\0')) &&
             ((param_1[0x37] == 0 || (*(char *)(param_1[0x37] + 10) == '\0')))) &&
            ((*(char *)(lVar16 + 0x59) != '\0' &&
             ((short)(int)param_1[0xa3] == *(short *)(*(long *)(param_1[0x5f] + 0x318) + 0x32))))) {
      puVar3 = (undefined4 *)param_1[0xd2];
      if ((ushort)((short)*puVar3 - 1U) < 9999) {
        if ((iVar15 == 5) && (*(int *)(*(long *)(lVar16 + 0x100) + 0x3c) == 0xa8d9)) {
          wlc_stf_rxchain_set(param_1,1);
          *(undefined1 *)(param_1[0xaa] + 0x11) = 0;
        }
LAB_00146627:
        if (1 < iVar15 - 1U) goto LAB_001466be;
        FUN_0013e137(param_1);
      }
      else if (*(int *)(*(long *)(lVar16 + 0x100) + 0x3c) == 0xa886) {
        if ((uint)puVar3[0xc] < (uint)puVar3[0xe]) goto LAB_00146627;
        if ((uint)puVar3[0xe] < (uint)puVar3[0xd]) {
          FUN_0013e169(param_1);
          if (param_1[0x5e] != 0) {
            wlc_ampdu_agg_state_update_rx(param_1,param_1[0x5e],1);
          }
        }
      }
      else {
        FUN_0013e169(param_1);
        if (((iVar15 == 5) && (*(int *)(*(long *)(*param_1 + 0x100) + 0x3c) == 0xa8d9)) &&
           (bVar10 = *(char *)(param_1[0xaa] + 0x11) + 1, *(byte *)(param_1[0xaa] + 0x11) = bVar10,
           5 < bVar10)) {
          wlc_stf_rxchain_set(param_1,*(undefined1 *)(param_1[0xaa] + 3));
          *(undefined1 *)(param_1[0xaa] + 0x11) = 0;
        }
      }
    }
  }
  if (((param_1[0x37] != 0) && (*(char *)(param_1[0x37] + 10) != '\0')) ||
     ((lVar16 = param_1[0xd2], *(char *)(lVar16 + 2) == '\0' ||
      (iVar25 = *(int *)(*(long *)(param_1[0x5f] + 0x330) + 0x14), iVar25 == 0)))) {
    if (*(int *)(param_1[0xd2] + 0x20) != 0) goto LAB_001467bd;
    goto LAB_001467e0;
  }
  if (*(int *)(lVar16 + 0x20) == 0) {
    iVar1 = *(int *)param_1[8];
    if (iVar1 == 1) {
      if ((*(byte *)(lVar16 + 0x1c) & 2) != 0) {
LAB_00146758:
        iVar15 = wlc_iovar_setint(param_1,"phy_btc_restage_rxgain",*(undefined4 *)(lVar16 + 0x18));
        if (iVar15 == 0) {
          *(undefined4 *)(param_1[0xd2] + 0x20) = 1;
        }
      }
    }
    else if (((iVar1 == 2) && ((*(byte *)(lVar16 + 0x1c) & 1) != 0)) &&
            (((iVar15 == 0 || (*(byte *)(lVar16 + 0x24) == 0)) ||
             ((iVar15 == 5 && (-iVar25 < (int)(uint)*(byte *)(lVar16 + 0x24)))))))
    goto LAB_00146758;
  }
  else {
    iVar1 = *(int *)param_1[8];
    if (iVar1 == 1) {
      if ((*(byte *)(lVar16 + 0x1c) & 2) == 0) goto LAB_001467bd;
    }
    else if ((iVar1 == 2) &&
            (((*(byte *)(lVar16 + 0x1c) & 1) == 0 ||
             (((iVar15 == 5 && (*(byte *)(lVar16 + 0x25) != 0)) &&
              ((int)(uint)*(byte *)(lVar16 + 0x25) < -iVar25)))))) {
LAB_001467bd:
      iVar15 = wlc_iovar_setint(param_1,"phy_btc_restage_rxgain",0);
      if (iVar15 == 0) {
        *(undefined4 *)(param_1[0xd2] + 0x20) = 0;
      }
    }
  }
LAB_001467e0:
  wlc_bmac_watchdog(param_1);
  if (*(uint *)(*param_1 + 0x48) % 0x1e == 0) {
    wlc_statsupd(param_1);
  }
  puVar2 = (uint *)param_1[0xbd];
  if (*puVar2 != 0) {
    if (puVar2[1] % *puVar2 == 0) {
      lVar4 = *(long *)(*param_1 + 0xa0);
      puVar2[2] = puVar2[2] + 1 & 1;
      lVar5 = param_1[0xbd];
      uVar11 = *(uint *)(lVar5 + 8);
      lVar16 = lVar5 + (ulong)uVar11 * 0x70;
      *(undefined4 *)(lVar16 + 0x10) = *(undefined4 *)(lVar4 + 4);
      lVar5 = (ulong)uVar11 * 0x70 + 0x10 + lVar5;
      *(undefined4 *)(lVar16 + 0x14) = *(undefined4 *)(lVar4 + 8);
      *(undefined4 *)(lVar16 + 0x18) = *(undefined4 *)(lVar4 + 0xc);
      *(undefined4 *)(lVar5 + 0xc) = *(undefined4 *)(lVar4 + 0x1b0);
      *(undefined4 *)(lVar5 + 0x10) = *(undefined4 *)(lVar4 + 0x40);
      *(undefined4 *)(lVar5 + 0x14) = *(undefined4 *)(lVar4 + 0x44);
      *(undefined4 *)(lVar5 + 0x18) = *(undefined4 *)(lVar4 + 0x238);
      *(undefined4 *)(lVar16 + 0x2c) = *(undefined4 *)(lVar4 + 0x23c);
      *(undefined4 *)(lVar16 + 0x30) = *(undefined4 *)(lVar4 + 0x240);
      *(undefined4 *)(lVar16 + 0x34) = *(undefined4 *)(lVar4 + 0x244);
      *(undefined4 *)(lVar16 + 0x38) = *(undefined4 *)(lVar4 + 0x248);
      *(undefined4 *)(lVar16 + 0x3c) = *(undefined4 *)(lVar4 + 0x24c);
      *(undefined4 *)(lVar16 + 0x40) = *(undefined4 *)(lVar4 + 0x250);
      *(undefined4 *)(lVar16 + 0x44) = *(undefined4 *)(lVar4 + 0x254);
      *(undefined4 *)(lVar16 + 0x48) = *(undefined4 *)(lVar4 + 600);
      *(undefined4 *)(lVar16 + 0x4c) = *(undefined4 *)(lVar4 + 0x25c);
      *(undefined4 *)(lVar16 + 0x50) = *(undefined4 *)(lVar4 + 0x260);
      *(undefined4 *)(lVar16 + 0x54) = *(undefined4 *)(lVar4 + 0x264);
    }
    *(int *)(param_1[0xbd] + 4) = *(int *)(param_1[0xbd] + 4) + 1;
  }
  if ((((char)param_1[0x60] != '\0') && ((byte)((char)param_1[0xb8] - 1U) < 3)) &&
     (*(char *)((long)param_1 + 0x5c1) == '\0')) {
    if ((char)param_1[0xb7] == '\0') {
      uVar11 = *(int *)(*param_1 + 0x48) - *(int *)((long)param_1 + 0x5bc);
      bVar27 = uVar11 < 0x1e;
      bVar28 = uVar11 == 0x1e;
    }
    else {
      lVar16 = param_1[0x5e];
      if (((lVar16 == 0) || (*(char *)(lVar16 + 0xc) == '\0')) ||
         ((*(char *)(lVar16 + 0x22) == '\0' || (*(char *)(*(long *)(lVar16 + 0x328) + 6) == '\0'))))
      {
        *(undefined1 *)(param_1 + 0xb7) = 0;
        if (*(short *)(param_1[8] + 8) == 2) {
          wlc_phy_freqtrack_end(*(undefined8 *)(param_1[8] + 0x10));
        }
        goto LAB_0014695f;
      }
      uVar11 = *(int *)(*param_1 + 0x48) - *(int *)((long)param_1 + 0x5bc);
      bVar27 = uVar11 < 2;
      bVar28 = uVar11 == 2;
    }
    if (!bVar27 && !bVar28) {
      wlc_freqtrack_reset(param_1);
    }
  }
LAB_0014695f:
  lVar16 = param_1[0x5e];
  if (((lVar16 != 0) && (*(char *)(lVar16 + 0xc) != '\0')) &&
     (((*(char *)(*(long *)(lVar16 + 0x338) + 10) != '\0' &&
       ((((cVar9 = wlc_ps_allowed(lVar16), cVar9 != '\0' && (*(char *)(lVar16 + 0x22) != '\0')) &&
         (*(char *)(*(long *)(lVar16 + 0x338) + 10) != '\0')) && (*(char *)(lVar16 + 0xc) != '\0')))
       ) && (((((*(char *)(lVar16 + 0xf1) != '\0' || (*(char *)(lVar16 + 0xf0) != '\0')) ||
               (*(char *)(lVar16 + 0xf2) != '\0')) ||
              ((*(char *)(lVar16 + 0xf3) != '\0' || (*(char *)(lVar16 + 0xf4) != '\0')))) ||
             (*(char *)(lVar16 + 0xf5) != '\0')))))) {
    wlc_sendnulldata(param_1,lVar16,lVar16 + 0xf0,0,0,0xffffffff);
  }
  lVar16 = param_1[0x5e];
  if ((lVar16 != 0) && (*(char *)(lVar16 + 0xc) != '\0')) {
    puVar2 = *(uint **)(lVar16 + 0x328);
    lVar5 = *(long *)(lVar16 + 0x318);
    if (*(char *)(lVar16 + 0x22) != '\0') {
      lVar4 = lVar16 + 0xf0;
      lVar18 = wlc_scbfind(param_1,lVar16,lVar4);
      if ((puVar2[0xb] != 0) && ((char)puVar2[0xf] != '\0')) {
        puVar2[0x10] = puVar2[0x10] + 1;
      }
      if (((lVar18 != 0) && ((char)puVar2[0x17] != '\0')) &&
         (10 < (uint)(*(int *)(*param_1 + 0x48) - *(int *)(lVar18 + 0x30)))) {
        if ((puVar2[0x15] == 0) && (*(short *)(lVar5 + 0x2a) < -0x32)) {
          puVar2[0x15] = (int)*(short *)(lVar5 + 0x2a);
        }
        if (puVar2[0x15] != 0) {
          wlc_roam_motion_detect(lVar16);
        }
      }
      if (((*(byte *)(*param_1 + 0xec) & 1) != 0) &&
         (cVar9 = wlc_ol_time_since_bcn(param_1[0xea]), cVar9 != '\0')) {
        *(undefined1 *)((long)puVar2 + 6) = 0;
      }
      if (*(byte *)((long)puVar2 + 6) != 0) {
        lVar18 = *(long *)(lVar16 + 0x338);
        if (((*(char *)(lVar18 + 8) == '\0') || (*(char *)(lVar18 + 1) != '\0')) ||
           ((((*(char *)(lVar16 + 0xf1) == '\0' &&
              (((*(char *)(lVar16 + 0xf0) == '\0' && (*(char *)(lVar16 + 0xf2) == '\0')) &&
               (*(char *)(lVar16 + 0xf3) == '\0')))) &&
             ((*(char *)(lVar16 + 0xf4) == '\0' && (*(char *)(lVar16 + 0xf5) == '\0')))) ||
            (*(byte *)(lVar5 + 0x60) == 0)))) {
          uVar11 = (uint)*(ushort *)(lVar5 + 0x2e);
        }
        else {
          uVar11 = (uint)*(byte *)(lVar5 + 0x60) * (uint)*(ushort *)(lVar5 + 0x2e);
        }
        uVar14 = (uVar11 << 10) / 1000;
        uVar17 = (ulong)(uVar11 << 10) % 1000;
        uVar11 = (uint)*(ushort *)(*param_1 + 0x8e);
        if (*(ushort *)(*param_1 + 0x8e) < 2000) {
          uVar21 = *puVar2 * 1000;
          uVar17 = (ulong)uVar21;
          uVar11 = 2000;
          if (uVar21 < 0xfa2) {
            uVar11 = uVar21 >> 1;
          }
        }
        if ((uVar11 < uVar14) && (uVar11 = *puVar2 * 1000 >> 1, uVar14 <= uVar11)) {
          uVar11 = uVar14;
        }
        if ((((uVar11 >> 1 <= (uint)*(byte *)((long)puVar2 + 6) * 1000) &&
             (*(char *)(lVar18 + 8) != '\0')) && (*(char *)(lVar18 + 1) == '\0')) &&
           ((((*(char *)(lVar16 + 0xf1) != '\0' || (*(char *)(lVar16 + 0xf0) != '\0')) ||
             ((*(char *)(lVar16 + 0xf2) != '\0' ||
              ((*(char *)(lVar16 + 0xf3) != '\0' || (*(char *)(lVar16 + 0xf4) != '\0')))))) ||
            (*(char *)(lVar16 + 0xf5) != '\0')))) {
          wlc_set_uatbtt(lVar16,1,uVar17);
          uVar17 = extraout_RDX;
        }
        if ((uint)*(byte *)((long)puVar2 + 6) * 1000 < uVar11) {
          *(undefined1 *)((long)puVar2 + 0x8a) = 0;
        }
        else {
          if (*(char *)(lVar18 + 0xd) != '\0') {
            wlc_set_uatbtt(lVar16,0,uVar17);
          }
          wlc_roam_bcns_lost(lVar16);
        }
      }
      if ((((5 < *(byte *)((long)puVar2 + 6)) && (*(char *)((long)puVar2 + 0x89) == '\0')) &&
          (*(char *)((long)param_1 + 0x5c1) == '\0')) &&
         (((char)param_1[0xb7] == '\0' && ((*(ushort *)((long)param_1 + 0x516) & 0xc000) == 0)))) {
        *(undefined1 *)(param_1 + 0xb7) = 1;
        uVar12 = *(undefined4 *)(*param_1 + 0x48);
        *(char *)(param_1 + 0xb8) = (char)param_1[0xb8] + '\x01';
        *(undefined4 *)((long)param_1 + 0x5bc) = uVar12;
        if (*(short *)(param_1[8] + 8) == 2) {
          wlc_phy_freqtrack_start(*(undefined8 *)(param_1[8] + 0x10));
        }
      }
      if ((*(char *)((long)puVar2 + 6) == '\0') && (*(char *)((long)puVar2 + 0x89) != '\0')) {
        *(undefined1 *)((long)puVar2 + 0x89) = 0;
        osl_memcpy(lVar4,lVar16 + 0x114,6);
        osl_memcpy(lVar5,lVar16 + 0x114,6);
        wlc_link(param_1,1,lVar4,lVar16,0);
      }
      if (((*puVar2 < (uint)*(byte *)((long)puVar2 + 6)) && (*(char *)((long)puVar2 + 0x89) == '\0')
          ) && (*(int *)(*(long *)(lVar16 + 800) + 8) == 0)) {
        wlc_handle_ap_lost(param_1,lVar16);
      }
      if (puVar2[9] != 0) {
        puVar2[9] = puVar2[9] - 1;
      }
      if (puVar2[10] != 0) {
        puVar2[10] = puVar2[10] - 1;
      }
    }
    if (((*(char *)(lVar16 + 0x22) == '\0') && (*puVar2 < (uint)*(byte *)((long)puVar2 + 6))) &&
       (*(char *)((long)puVar2 + 0x89) == '\0')) {
      scb_ampdu_cleanup_all(param_1,lVar16);
      wlc_bss_mac_event(param_1,lVar16,0xf,0,1,0,in_stack_ffffffffffffff48 & 0xffffffff00000000,0,0)
      ;
      *(undefined1 *)((long)puVar2 + 0x89) = 1;
    }
    if ((uint)*(byte *)((long)puVar2 + 6) <= *puVar2) {
      *(byte *)((long)puVar2 + 6) = *(byte *)((long)puVar2 + 6) + 1;
    }
    if ((*(char *)(lVar16 + 0x22) != '\0') && (lVar16 != param_1[0x5f])) {
      uVar11 = (uint)*(ushort *)(*param_1 + 0x8e);
      if (*(ushort *)(*param_1 + 0x8e) < 2000) {
        uVar11 = 2000;
      }
      if (uVar11 < (uint)*(byte *)((long)puVar2 + 6) * 1000) {
        wlc_roam_bcns_lost(lVar16);
      }
    }
    if ((char)puVar2[0x14] != '\0') {
      uVar11 = puVar2[0x13];
      puVar19 = puVar2;
      for (iVar15 = 0; iVar15 < (int)uVar11; iVar15 = iVar15 + 1) {
        if (((short)puVar19[0x1a] != 0) &&
           (sVar20 = (short)puVar19[0x1a] + -1, *(short *)(puVar19 + 0x1a) = sVar20, sVar20 != 0))
        goto LAB_00146e76;
        puVar19 = (uint *)((long)puVar19 + 10);
      }
      *(undefined1 *)(puVar2 + 0x14) = 0;
    }
  }
LAB_00146e76:
  if ((((*(char *)(param_1[8] + 0x19) != '\0') && (*(uint *)(*param_1 + 0x48) % 0x3c == 0)) &&
      (plVar6 = (long *)param_1[0x5e], plVar6 != (long *)0x0)) &&
     ((*(char *)((long)plVar6 + 0xc) != '\0' && (*(char *)((long)plVar6 + 0x22) == '\0')))) {
    plVar7 = (long *)*plVar6;
    wlc_scb_iterinit(plVar7[0x2b],local_68,plVar6);
    while (lVar16 = wlc_scb_iternext(plVar7[0x2b],local_68), lVar16 != 0) {
      if ((-1 < (char)(&rate_info)[*(byte *)(lVar16 + 0x44 + (ulong)(*(int *)(lVar16 + 0x40) - 1))])
         && ((uint)(*(int *)(*plVar7 + 0x48) - *(int *)(lVar16 + 0x2c)) < 0x3c)) {
        wlc_rateprobe(plVar7,plVar6,lVar16 + 0x20,0xc);
      }
    }
  }
  lVar16 = param_1[0x5e];
  if (lVar16 != 0) {
    if (*(int *)(lVar16 + 0xd4) != 0) {
      *(int *)(lVar16 + 0xd4) = *(int *)(lVar16 + 0xd4) + -1;
    }
    if (*(int *)(lVar16 + 0xd8) != 0) {
      *(int *)(lVar16 + 0xd8) = *(int *)(lVar16 + 0xd8) + -1;
    }
  }
  lVar16 = 0;
  do {
    pcVar8 = *(code **)(lVar16 + param_1[0x6b] + 0x30);
    if ((pcVar8 != (code *)0x0) &&
       (iVar15 = (*pcVar8)(*(undefined8 *)(lVar16 + param_1[0x6b] + 0x28)), iVar15 != 0)) {
      return;
    }
    lVar16 = lVar16 + 0x50;
  } while (lVar16 != 0x1400);
  wlc_stf_pwrthrottle_upd(param_1);
  lVar16 = param_1[0x5e];
  if ((lVar16 == 0) || (*(char *)(lVar16 + 0xc) == '\0')) goto LAB_00146ffb;
  if ((*(byte *)(lVar16 + 0x56a) & 1) == 0) {
    if ((*(byte *)(lVar16 + 0x56a) & 2) != 0) {
      uVar23 = *(undefined1 *)(lVar16 + 0x569);
      goto LAB_00146fc9;
    }
  }
  else {
    uVar23 = *(undefined1 *)(lVar16 + 0x568);
LAB_00146fc9:
    wlc_mimops_action_ht_send(param_1,lVar16,uVar23);
  }
  if (((char)param_1[0xdb] != '\0') && (*(char *)(lVar16 + 8) != '\0')) {
    FUN_00140940(param_1,**(undefined1 **)(lVar16 + 0x338),lVar16);
  }
LAB_00146ffb:
  *(undefined1 *)(param_1 + 0xdb) = 0;
  wlc_stf_tempsense_upd(param_1);
  return;
}

