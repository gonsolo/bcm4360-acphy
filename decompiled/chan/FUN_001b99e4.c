
void FUN_001b99e4(long param_1,long param_2,long param_3)

{
  long lVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  undefined1 uVar5;
  ushort uVar6;
  uint uVar7;
  int iVar8;
  long lVar9;
  char *pcVar10;
  char *pcVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  ushort uVar15;
  ushort *puVar16;
  uint uVar17;
  char *pcVar18;
  int iVar19;
  ushort *puVar20;
  undefined4 *puVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  ushort uVar24;
  undefined8 uVar25;
  bool bVar26;
  undefined1 uVar27;
  byte bVar28;
  int local_9c;
  ushort local_98 [3];
  undefined1 local_92;
  undefined1 local_91;
  ushort auStack_90 [20];
  char local_68 [8];
  char acStack_60 [8];
  char local_58 [7];
  char acStack_51 [9];
  char local_48 [4];
  char acStack_44 [4];
  char acStack_40 [7];
  char local_39 [9];
  
  bVar28 = 0;
  local_39[0] = '\0';
  lVar1 = *(long *)(param_1 + 0x138);
  iVar8 = *(int *)(*(long *)(param_1 + 0x20) + 0x58);
  if ((iVar8 == 0x58b) || (bVar26 = false, iVar8 == 0x539)) {
    bVar26 = (*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000;
  }
  uVar27 = 2;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if (uVar6 != 0x2000) {
    uVar27 = uVar6 == 0x1800;
  }
  lVar9 = ppr_create(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),uVar27);
  if (lVar9 == 0) {
    return;
  }
  if ((param_2 != 0) && (ppr_copy_struct(param_2,lVar9), *(int *)(param_1 + 0x160) == 4)) {
    local_9c = 0;
    uVar22 = 1;
    uVar23 = 0;
    uVar25 = 0;
LAB_001b9b94:
    ppr_get_ht_mcs(param_2,uVar25,1,uVar23,uVar22,local_58);
    ppr_get_ofdm(param_2,uVar25,uVar23,uVar22,local_48);
    pcVar18 = local_58;
    local_68[0] = local_58[0];
    pcVar10 = pcVar18;
    pcVar11 = local_68;
    do {
      pcVar11 = pcVar11 + 1;
      cVar2 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      *pcVar11 = cVar2;
    } while (pcVar10 != acStack_51);
    puVar20 = local_98;
    pcVar11 = local_48 + 1;
    puVar16 = puVar20;
    do {
      cVar2 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      *(char *)puVar16 = cVar2;
      puVar16 = (ushort *)((long)puVar16 + 1);
    } while (pcVar11 != acStack_40);
    pcVar11 = local_68;
    local_91 = local_92;
    pcVar10 = local_48;
    do {
      cVar2 = *pcVar11;
      if (*pcVar10 <= *pcVar11) {
        cVar2 = *pcVar10;
      }
      pcVar11 = pcVar11 + 1;
      *pcVar10 = cVar2;
      pcVar10 = pcVar10 + 1;
    } while (pcVar11 != acStack_60);
    do {
      cVar2 = (char)*puVar20;
      if (*pcVar18 <= (char)*puVar20) {
        cVar2 = *pcVar18;
      }
      puVar20 = (ushort *)((long)puVar20 + 1);
      *pcVar18 = cVar2;
      pcVar18 = pcVar18 + 1;
    } while (puVar20 != auStack_90);
    ppr_set_ofdm(lVar9,uVar25,uVar23,uVar22,local_48);
    ppr_set_ht_mcs(lVar9,uVar25,1,uVar23,uVar22,local_58);
    iVar8 = local_9c + 1;
    if (iVar8 == 6) goto LAB_001b9ca9;
    switch(local_9c) {
    case 0:
      uVar22 = 2;
      uVar23 = 2;
      break;
    case 1:
      uVar22 = 1;
      uVar23 = 0;
      goto LAB_001b9b6f;
    case 2:
      uVar22 = 2;
      uVar23 = 2;
LAB_001b9b6f:
      uVar25 = 1;
      local_9c = iVar8;
      goto LAB_001b9b94;
    case 3:
      uVar22 = 1;
      uVar23 = 0;
      goto LAB_001b9b8e;
    case 4:
      uVar22 = 2;
      uVar23 = 2;
LAB_001b9b8e:
      uVar25 = 3;
      local_9c = iVar8;
      goto LAB_001b9b94;
    default:
      uVar22 = 1;
      uVar23 = 0;
    }
    uVar25 = 0;
    local_9c = iVar8;
    goto LAB_001b9b94;
  }
LAB_001b9ca9:
  uVar6 = *(ushort *)(param_1 + 0x17e);
  cVar2 = wf_chspec_ctlchan(uVar6);
  uVar27 = 2;
  uVar24 = uVar6 & 0x3800;
  if (uVar24 != 0x2000) {
    uVar27 = uVar24 == 0x1800;
  }
  lVar12 = ppr_create(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),uVar27);
  if (lVar12 == 0) {
    uVar22 = *(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10);
    lVar13 = lVar9;
  }
  else {
    uVar27 = 2;
    if (uVar24 != 0x2000) {
      uVar27 = uVar24 == 0x1800;
    }
    lVar13 = ppr_create(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),uVar27);
    if (lVar13 != 0) {
      if (*(long *)(param_1 + 0x1c8) != 0) {
        uVar7 = ppr_get_ch_bw();
        uVar17 = 2;
        if (uVar24 != 0x2000) {
          uVar17 = (uint)(uVar24 == 0x1800);
        }
        if (uVar7 != uVar17) {
          ppr_delete(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),
                     *(undefined8 *)(param_1 + 0x1c8));
          *(undefined8 *)(param_1 + 0x1c8) = 0;
        }
      }
      if (*(long *)(param_1 + 0x1c8) == 0) {
        uVar27 = 2;
        if (uVar24 != 0x2000) {
          uVar27 = uVar24 == 0x1800;
        }
        lVar14 = ppr_create(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),uVar27);
        *(long *)(param_1 + 0x1c8) = lVar14;
        if (lVar14 == 0) {
          ppr_delete(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),lVar9);
          ppr_delete(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),lVar12);
          uVar22 = *(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10);
          goto LAB_001b9d5c;
        }
      }
      ppr_clear(*(undefined8 *)(param_1 + 0x1c8));
      uVar24 = *(ushort *)(param_1 + 0x17e);
      puVar21 = &DAT_0055b090;
      puVar20 = local_98;
      for (lVar14 = 0xc; lVar14 != 0; lVar14 = lVar14 + -1) {
        *(undefined4 *)puVar20 = *puVar21;
        puVar21 = puVar21 + (ulong)bVar28 * -2 + 1;
        puVar20 = puVar20 + ((ulong)bVar28 * -2 + 1) * 2;
      }
      puVar20 = &DAT_0055ad40;
      uVar7 = 0;
      do {
        if (*puVar20 == (uVar24 & 0xff)) {
          uVar15 = (&DAT_0055ad42)[(ulong)uVar7 * 2];
          goto LAB_001b9e78;
        }
        uVar7 = uVar7 + 1;
        puVar20 = puVar20 + 2;
      } while (uVar7 != 0x43);
      uVar15 = 0;
LAB_001b9e78:
      if ((uVar24 & 0xc000) == 0) {
        cVar3 = *(char *)(param_1 + 0x1128 + (long)(int)((byte)uVar24 - 1));
      }
      else {
        puVar20 = local_98;
        iVar8 = 0;
        do {
          if (uVar15 <= *puVar20) {
            cVar3 = *(char *)(param_1 + 0x1110 + (long)iVar8);
            goto LAB_001b9eb7;
          }
          iVar8 = iVar8 + 1;
          puVar20 = puVar20 + 1;
        } while (iVar8 != 0x18);
        cVar3 = '\0';
      }
LAB_001b9eb7:
      for (bVar28 = 0; bVar28 < *(byte *)(param_1 + 0x168); bVar28 = bVar28 + 1) {
        ppr_set_cmn_val(lVar12,(int)*(char *)(param_1 + 0x1d6));
        uVar7 = (uint)bVar28;
        wlc_phy_txpower_sromlimit(param_1,uVar6,local_39,lVar13,uVar7);
        if (((*(long *)(param_1 + 0x160) == 0x300000006) && (cVar2 == '\x0e')) &&
           ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000)) {
          ppr_set_cmn_val(lVar12,0x2c);
        }
        if (*(int *)(param_1 + 0x160) == 10) {
          wlc_lcn40phy_apply_cond_chg(*(undefined8 *)(param_1 + 0x138),lVar13);
        }
        ppr_compare_min(lVar13,lVar9);
        if ((*(int *)(param_1 + 0x160) == 8) &&
           (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0x4313)) {
          wlc_lcnphy_modify_max_txpower(param_1,lVar13);
        }
        else {
          ppr_minus_cmn_val(lVar13,(int)*(char *)(param_1 + 0x10a0));
        }
        ppr_compare_min(lVar12,lVar13);
        if ((*(int *)(param_1 + 0x160) == 2) &&
           ((*(byte *)(*(long *)(param_1 + 0x20) + 100) & 2) != 0)) {
          ppr_minus_cmn_val(lVar12,3);
        }
        if (*(int *)(param_1 + 0x160) == 6) {
          wlc_sslpnphy_txpwr_target_adj(param_1,lVar12);
        }
        if (*(byte *)(param_1 + 0x184) < 100) {
          ppr_multiply_percentage(lVar12,*(byte *)(param_1 + 0x184));
        }
        if (*(int *)(param_1 + 0x160) != 8) {
          if (*(int *)(param_1 + 0x160) == 0xb) {
            ppr_force_disabled(lVar12);
          }
          else {
            ppr_apply_min(lVar12,(int)local_39[0]);
          }
        }
        if ((*(int *)(param_1 + 0x160) == 10) || (*(int *)(param_1 + 0x160) == 8)) {
          ppr_minus_cmn_val(lVar12,(int)cVar3);
        }
        if (*(int *)(param_1 + 0x160) == 7) {
          cVar4 = wlc_phy_txpwr_max_est_pwr_get_htphy(param_1);
          ppr_apply_max(lVar12,(int)cVar4);
        }
        uVar27 = ppr_get_max(lVar12);
        iVar8 = *(int *)(param_1 + 0x160);
        if (((iVar8 == 7) || (iVar8 == 2)) || (iVar19 = -0x80, iVar8 == 0xb)) {
          iVar19 = (int)local_39[0];
        }
        uVar5 = ppr_get_min(lVar12,iVar19);
        *(undefined1 *)(param_1 + 0x216 + (long)(int)uVar7) = uVar27;
        *(undefined1 *)(param_1 + 0x21a + (long)(int)uVar7) = uVar5;
        *(undefined1 *)(param_1 + 0x22f) = uVar5;
        *(undefined1 *)(param_1 + 0x234) = 0;
        if ((bVar28 == 0) && (*(undefined1 *)(param_1 + 0x21e) = 0, param_3 != 0)) {
          ppr_copy_struct(lVar12,param_3);
        }
        if (((*(char *)(param_1 + 0x220) == '\0') || (iVar8 = *(int *)(param_1 + 0x160), iVar8 == 4)
            ) || ((iVar8 == 7 || ((bVar26 || (iVar8 == 0xb)))))) {
          ppr_cmn_val_minus(lVar12,(int)*(char *)(param_1 + 0x216 + (long)(int)uVar7));
        }
        else {
          ppr_minus_cmn_val(lVar12,(int)*(char *)(param_1 + 0x21a + (long)(int)uVar7));
        }
        ppr_compare_max(*(undefined8 *)(param_1 + 0x1c8),lVar12);
        if ((*(int *)(param_1 + 0x160) == 8) &&
           (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0x4313)) {
          wlc_lcnphy_modify_rate_power_offsets(param_1);
        }
        if ((*(int *)(param_1 + 0x160) == 10) || (*(int *)(param_1 + 0x160) == 8)) {
          ppr_get_dsss(*(undefined8 *)(param_1 + 0x1c8),0,1,local_48);
          pcVar18 = local_48;
          do {
            *pcVar18 = *pcVar18 + (char)*(undefined2 *)(lVar1 + 0x3b2);
            pcVar18 = pcVar18 + 1;
          } while (pcVar18 != acStack_44);
          ppr_set_dsss(*(undefined8 *)(param_1 + 0x1c8),0,1,local_48);
        }
      }
      ppr_delete(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),lVar9);
      ppr_delete(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),lVar12);
      ppr_delete(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),lVar13);
      if (param_3 != 0) {
        return;
      }
      if (*(code **)(param_1 + 0x40) == (code *)0x0) {
        return;
      }
      (**(code **)(param_1 + 0x40))(param_1);
      return;
    }
    ppr_delete(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),lVar9);
    uVar22 = *(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10);
    lVar13 = lVar12;
  }
LAB_001b9d5c:
  ppr_delete(uVar22,lVar13);
  return;
}

