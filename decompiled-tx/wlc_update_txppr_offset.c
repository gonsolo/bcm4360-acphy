
void wlc_update_txppr_offset(long *param_1,undefined8 param_2)

{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  uint uVar4;
  long lVar5;
  int iVar6;
  byte bVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  uint uVar10;
  undefined8 uVar11;
  byte *pbVar12;
  byte *pbVar13;
  undefined1 uVar14;
  uint local_78;
  byte abStack_74 [44];
  byte local_48 [16];
  byte local_38 [8];
  int local_30;
  char local_29;
  
  pbVar12 = (byte *)param_1[0xaa];
  wlc_iovar_getint(param_1,"min_txpower",&local_30);
  local_30 = local_30 << 2;
  cVar2 = wlc_phy_txpower_get_target_max(*(undefined8 *)(param_1[8] + 0x10));
  wlc_ol_curpwr_upd(param_1[0xea],(int)cVar2,(short)param_1[0xa3]);
  if (*(long *)(pbVar12 + 0x30) != 0) {
    uVar4 = ppr_get_ch_bw();
    uVar10 = 2;
    if ((*(ushort *)(param_1 + 0xa3) & 0x3800) != 0x2000) {
      uVar10 = (uint)((*(ushort *)(param_1 + 0xa3) & 0x3800) == 0x1800);
    }
    if (uVar4 != uVar10) {
      ppr_delete(param_1[1],*(undefined8 *)(pbVar12 + 0x30));
      pbVar12[0x30] = 0;
      pbVar12[0x31] = 0;
      pbVar12[0x32] = 0;
      pbVar12[0x33] = 0;
      pbVar12[0x34] = 0;
      pbVar12[0x35] = 0;
      pbVar12[0x36] = 0;
      pbVar12[0x37] = 0;
    }
  }
  if (*(long *)(pbVar12 + 0x30) == 0) {
    uVar14 = 2;
    if ((*(ushort *)(param_1 + 0xa3) & 0x3800) != 0x2000) {
      uVar14 = (*(ushort *)(param_1 + 0xa3) & 0x3800) == 0x1800;
    }
    lVar5 = ppr_create(param_1[1],uVar14);
    *(long *)(pbVar12 + 0x30) = lVar5;
    if (lVar5 == 0) {
      return;
    }
  }
  if (*(long *)(param_1[0xaa] + 0x30) != 0) {
    local_29 = (char)(cVar2 - (char)local_30) >> 1;
    if (local_29 < '\0') {
      local_29 = '\0';
    }
    if ('\x1f' < local_29) {
      local_29 = '\x1f';
    }
    *(char *)(param_1[0xaa] + 0x88) = local_29;
    ppr_map_vec_all(&LAB_002739ac,&local_29,param_2);
  }
  cVar2 = wlc_phy_txpower_get_target_min(*(undefined8 *)(param_1[8] + 0x10));
  uVar4 = (uint)*pbVar12;
  iVar6 = 0;
  do {
    if ((int)cVar2 + (int)(char)pbVar12[100] < local_30) {
      uVar4 = uVar4 & ~(1 << ((byte)iVar6 & 0x1f));
    }
    iVar6 = iVar6 + 1;
    pbVar12 = pbVar12 + 1;
  } while (iVar6 != 4);
  wlc_stf_txchain_set(param_1,uVar4,1,3);
  FUN_00275a15(param_1,(short)param_1[0xa3]);
  if (*(long *)(param_1[0xaa] + 0x30) == 0) {
    return;
  }
  if (*(char *)((long)param_1 + 0x31) == '\0') {
    return;
  }
  if (*(uint *)(*param_1 + 0x14) < 0x16) {
    return;
  }
  uVar4 = *(uint *)(param_1 + 0xa3) & 0x3800;
  wlc_rateset_copy(cck_ofdm_rates,&local_78);
  cVar2 = bcm_bitcount(param_1[0xaa] + 0x17,1);
  uVar10 = 4;
  if (uVar4 != 0x2000) {
    uVar10 = (int)((uint)(uVar4 == 0x1800) << 0x1f) >> 0x1f & 3;
  }
  if (cVar2 == '\x01') {
    uVar8 = 1;
    uVar11 = *(undefined8 *)(param_1[0xaa] + 0x30);
LAB_002764a9:
    ppr_get_dsss(uVar11,uVar10,uVar8,local_38);
  }
  else {
    if (cVar2 == '\x02') {
      uVar8 = 2;
      uVar11 = *(undefined8 *)(param_1[0xaa] + 0x30);
      goto LAB_002764a9;
    }
    if (cVar2 == '\x03') {
      uVar8 = 3;
      uVar11 = *(undefined8 *)(param_1[0xaa] + 0x30);
      goto LAB_002764a9;
    }
  }
  cVar2 = bcm_bitcount(param_1[0xaa] + 0x19,1);
  uVar14 = 2;
  if (uVar4 != 0x2000) {
    uVar14 = uVar4 == 0x1800;
  }
  if (cVar2 == '\x01') {
    uVar8 = 1;
    uVar9 = 0;
    uVar11 = *(undefined8 *)(param_1[0xaa] + 0x30);
  }
  else {
    if (cVar2 == '\x02') {
      uVar8 = 2;
      uVar11 = *(undefined8 *)(param_1[0xaa] + 0x30);
    }
    else {
      if (cVar2 != '\x03') goto LAB_0027652b;
      uVar8 = 3;
      uVar11 = *(undefined8 *)(param_1[0xaa] + 0x30);
    }
    uVar9 = 2;
  }
  ppr_get_ofdm(uVar11,uVar14,uVar9,uVar8,local_48);
LAB_0027652b:
  lVar5 = osl_malloc(param_1[1],local_78 * 6);
  if (lVar5 != 0) {
    pbVar12 = local_38;
    pbVar13 = local_48;
    osl_memset(lVar5,0,(ulong)local_78 * 6);
    wlc_bmac_stf_get_rateset_shm_offset
              (param_1[4],&local_78,*(undefined2 *)(param_1[0xaa] + 0x6c),lVar5);
    for (bVar7 = 0; bVar7 < local_78; bVar7 = bVar7 + 1) {
      if ((char)(&rate_info)[abStack_74[bVar7] & 0x7f] < '\0') {
        bVar1 = *pbVar13;
        pbVar13 = pbVar13 + 1;
      }
      else {
        bVar1 = *pbVar12;
        pbVar12 = pbVar12 + 1;
      }
      if (bVar1 == 0x80) {
        bVar1 = *(byte *)(param_1[0xaa] + 0x88);
      }
      uVar3 = (ushort)bVar1;
      if (0x27 < *(uint *)(*param_1 + 0x14)) {
        uVar3 = (bVar1 & 0x3f) << 3 | *(ushort *)((ulong)bVar7 * 6 + 4 + lVar5) & 0xfe07;
      }
      *(ushort *)((ulong)bVar7 * 6 + 4 + lVar5) = uVar3;
    }
    wlc_bmac_stf_set_rateset_shm_offset
              (param_1[4],&local_78,*(undefined2 *)(param_1[0xaa] + 0x6c),lVar5);
    osl_mfree(param_1[1],lVar5,local_78 * 6);
  }
  return;
}

