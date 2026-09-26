
uint FUN_00132062(long *param_1,undefined8 param_2,long param_3,char param_4,uint param_5,
                 uint param_6,uint param_7,undefined4 param_8,long param_9,uint param_10,
                 undefined8 param_11)

{
  int *piVar1;
  short *psVar2;
  long lVar3;
  long lVar4;
  bool bVar5;
  undefined1 uVar6;
  byte bVar7;
  byte bVar8;
  char cVar9;
  byte bVar10;
  byte bVar11;
  bool bVar12;
  char cVar13;
  undefined1 uVar14;
  char cVar15;
  ushort uVar16;
  short sVar17;
  undefined2 uVar18;
  ushort uVar19;
  ushort uVar20;
  short sVar21;
  uint uVar22;
  int iVar23;
  int iVar24;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  uint uVar28;
  ushort *puVar29;
  uint *puVar30;
  long lVar31;
  long lVar32;
  uint *puVar33;
  byte *pbVar34;
  ushort *puVar35;
  ushort uVar36;
  uint uVar37;
  ushort *puVar38;
  undefined8 uVar39;
  byte bVar40;
  long lVar41;
  long lVar42;
  bool bVar43;
  bool bVar44;
  bool bVar45;
  bool bVar46;
  bool bVar47;
  bool bVar48;
  bool bVar49;
  undefined8 in_stack_fffffffffffffe48;
  undefined4 uVar50;
  uint local_160;
  ushort local_158;
  int local_124;
  short local_120;
  undefined1 local_118;
  char local_ed;
  bool local_c9;
  int local_c8;
  char local_b0;
  ushort *local_a8;
  uint local_a0;
  ushort local_9c;
  uint local_98;
  uint local_94;
  undefined1 local_88;
  undefined1 local_87;
  undefined1 local_84;
  uint local_78 [4];
  undefined1 local_68;
  undefined1 local_67;
  byte local_64;
  undefined1 local_58 [20];
  uint local_44;
  undefined4 local_40;
  undefined4 local_3c;
  
  uVar50 = (undefined4)((ulong)in_stack_fffffffffffffe48 >> 0x20);
  lVar41 = *(long *)(param_3 + 0x18);
  lVar31 = param_1[1];
  if (*(short *)(param_1[8] + 8) != 0xb) {
    local_3c._0_3_ = CONCAT12(0xff,(short)local_3c);
    local_3c = CONCAT13(0xff,(undefined3)local_3c);
    cVar13 = **(char **)(lVar41 + *(int *)param_1[0xa8]);
    cVar15 = **(char **)(lVar41 + *(int *)param_1[0xa9]);
    lVar3 = *(long *)(lVar41 + 0x570);
    puVar29 = (ushort *)osl_pktdata(lVar31,param_2);
    puVar30 = (uint *)osl_pkttag(param_2);
    uVar20 = *puVar29;
    uVar19 = (ushort)((uVar20 & 0xc) >> 2);
    bVar7 = 0;
    if (uVar19 == 2) {
      bVar7 = (byte)(uVar20 >> 7) & 1;
    }
    bVar44 = (uVar20 & 0x300) == 0x300;
    local_c8 = pkttotlen(lVar31,param_2);
    local_c8 = local_c8 + 4;
    if (param_9 != 0) {
      local_c8 = local_c8 + *(char *)(param_9 + 0xf);
    }
    lVar32 = *param_1;
    if ((((*(uint *)(lVar32 + 0x14) < 0xd) || (param_9 == 0)) || (-1 < (int)param_1[0x46])) ||
       (((*(char *)(param_9 + 8) != '\x02' || ((char)param_1[0x68] != '\0')) ||
        ((*(byte *)(lVar41 + 0x90) & 8) != 0)))) {
LAB_00133566:
      bVar43 = false;
    }
    else {
      bVar8 = *(byte *)(param_9 + 6);
      uVar22 = 5;
      if (*(char *)(lVar32 + 0x5d) == '\0') {
        uVar22 = *(uint *)(lVar32 + 0xd4);
      }
      if (((uVar22 <= bVar8) || (bVar8 < 4)) || ((param_6 != 1 || (0xb < bVar8))))
      goto LAB_00133566;
      local_c8 = local_c8 + 8;
      bVar43 = true;
    }
    pbVar34 = (byte *)osl_pktpush(lVar31,param_2,6);
    puVar35 = (ushort *)osl_pktpush(lVar31,param_2,0x70);
    osl_memset(puVar35,0,0x70);
    if ((*puVar30 & 0x400) == 0) {
      if ((((*(uint *)(param_3 + 8) & 0x10040) != 0) && ((uVar20 & 0xfc) == 0x88)) &&
         ((puVar29[2] & 1) == 0)) {
        uVar22 = osl_pktprio();
        uVar22 = (uint)*(ushort *)(param_3 + 0xda + (ulong)uVar22 * 2);
        if (param_5 == param_6 - 1) {
          uVar37 = osl_pktprio();
          psVar2 = (short *)(param_3 + 0xda + (ulong)uVar37 * 2);
          *psVar2 = *psVar2 + 1;
        }
        goto LAB_0013363f;
      }
      if (uVar19 != 1) {
        uVar36 = 0x10;
        uVar22 = 0;
        goto LAB_0013364b;
      }
LAB_00133669:
      uVar36 = 0;
    }
    else {
      uVar22 = puVar30[1];
LAB_0013363f:
      if (uVar19 == 1) goto LAB_00133669;
      uVar36 = 0;
LAB_0013364b:
      puVar29[0xb] = (ushort)(uVar22 << 4) | (ushort)param_5 & 0xf;
    }
    if (param_7 == 4) {
      iVar23 = *(int *)((long)param_1 + 0x424);
      uVar16 = puVar35[0x26];
      *(short *)((long)param_1 + 0x424) = (short)iVar23 + 1;
      uVar16 = uVar16 & 0x8018 | 4 | (ushort)(iVar23 << 5) & 0x7fe0;
    }
    else {
      uVar16 = *(ushort *)((long)param_1 + 0x422);
      if (param_5 == param_6 - 1) {
        *(ushort *)((long)param_1 + 0x422) = uVar16 + 1;
      }
      uVar16 = (ushort)((param_5 & 0xf | (uint)uVar16 << 4) << 5) & 0x7fe0 | (ushort)param_7 & 7;
    }
    local_3c = CONCAT22(local_3c._2_2_,uVar16);
    local_9c = uVar36 | 0x20;
    if (((param_10 & 0xc00000ff) == 0) && ((param_10 & 0x3000000) != 0x1000000)) {
      if ((uVar19 < 2) ||
         (((((uVar20 & 0xfc) == 0x48 || ((uVar20 & 0xfc) == 200)) &&
           ((*(byte *)(param_3 + 9) & 1) == 0)) ||
          (((*puVar30 & 0x10) != 0 || (*(short *)((long)puVar30 + 6) < 0)))))) {
LAB_001337f3:
        param_10 = *(byte *)(param_3 + 0x44) & 0x7f;
        goto LAB_0013388a;
      }
      param_10 = *(uint *)(param_1[8] + 0x54);
      if ((((param_10 & 0xc00000ff) != 0) || ((param_10 & 0x3000000) == 0x1000000)) &&
         ((puVar29[2] & 1) != 0)) goto LAB_0013388a;
      param_10 = *(uint *)(param_1[8] + 0x50);
      if (((param_10 & 0xc00000ff) != 0) || ((param_10 & 0x3000000) == 0x1000000)) {
        bVar8 = (byte)puVar29[2];
        goto LAB_001337b3;
      }
      if (((puVar29[2] & 1) != 0) || ((*(byte *)(param_3 + 0xc) & 8) != 0)) goto LAB_001337f3;
      local_84 = 2;
      wlc_scb_ratesel_gettxrate(param_1[0x35],param_3,&local_3c,&local_98,(long)&local_40 + 2);
      *puVar30 = *puVar30 | 0x8000000;
      if ((local_40 & 0x10000) != 0) {
        puVar33 = (uint *)osl_pkttag(param_2);
        *puVar33 = *puVar33 | 0x2000;
      }
      lVar31 = (long)&local_3c + 2;
      wlc_antsel_antcfg_get(param_1[0x33],0,1,local_88,local_87,(long)&local_3c + 3,lVar31);
      uVar50 = (undefined4)((ulong)lVar31 >> 0x20);
      bVar45 = param_5 == 0;
      param_10 = local_98;
    }
    else {
      bVar8 = (byte)puVar29[2];
LAB_001337b3:
      if ((bVar8 & 1) == 0) {
        lVar31 = (long)&local_3c + 2;
        wlc_antsel_antcfg_get(param_1[0x33],0,0,0,0,(long)&local_3c + 3,lVar31);
        uVar50 = (undefined4)((ulong)lVar31 >> 0x20);
      }
LAB_0013388a:
      bVar45 = false;
      local_94 = param_10;
    }
    lVar31 = param_1[0xaa];
    bVar8 = *(byte *)(*param_1 + 0x68);
    cVar9 = *(char *)(lVar31 + 0xc);
    if ((bVar8 & 3) == 0) {
      uVar22 = param_10 & 0xfff8ffff | 0x10000;
      uVar37 = local_94 & 0xfff8ffff | 0x10000;
      sVar17 = (short)*(undefined4 *)(param_1[8] + 8);
      if ((sVar17 == 7) || (sVar17 == 4)) {
        if (((param_10 & 0x3000000) == 0) && ((char)(&rate_info)[param_10 & 0xff] < '\0')) {
          uVar22 = param_10 & 0xfff8fcff | 0x10000;
          if (cVar9 == '\x01') {
            uVar22 = param_10 & 0xfff8fcff | 0x10100;
          }
        }
        if (((local_94 & 0x3000000) == 0) && ((char)(&rate_info)[local_94 & 0xff] < '\0')) {
          uVar37 = local_94 & 0xfff8fcff | 0x10000;
          if (cVar9 == '\x01') {
            uVar37 = local_94 & 0xfff8fcff | 0x10100;
          }
        }
      }
      param_10 = uVar22;
      bVar46 = false;
      bVar48 = false;
      local_ed = '\0';
      cVar9 = '\0';
      local_c9 = false;
      bVar5 = false;
    }
    else {
      bVar48 = false;
      if (((*(byte *)(lVar31 + 2) < 2) ||
          (bVar48 = *(char *)(param_1[8] + 0x59) == '\x01', *(char *)(param_1[8] + 0x59) != -1)) ||
         ((*(byte *)(param_3 + 0xb) & 0x40) == 0)) {
        bVar40 = 0;
      }
      else {
        bVar40 = *(byte *)(lVar31 + 0xe) >> 2 & 1;
      }
      if ((param_10 & 0x3000000) == 0) {
        if ((char)(&rate_info)[param_10 & 0xff] < '\0') goto LAB_0013391b;
      }
      else if (((param_10 & 0xff) == 0x20) || ((param_10 & 0xff) < 8)) {
LAB_0013391b:
        if (-1 < (int)param_10) {
          uVar22 = param_10 & 0xffeffcff;
          if (((param_10 & 0x3000000) == 0) ||
             ((!bVar48 && ((bVar40 == 0 || ((param_10 & 0x3000000) != 0x1000000)))))) {
            param_10 = uVar22;
            if (cVar9 == '\x01') {
              param_10 = uVar22 | 0x100;
            }
          }
          else {
            param_10 = uVar22 | 0x100000;
          }
        }
      }
      if ((local_94 & 0x3000000) == 0) {
        if ((char)(&rate_info)[local_94 & 0xff] < '\0') goto LAB_00133988;
      }
      else if (((local_94 & 0xff) == 0x20) || ((local_94 & 0xff) < 8)) {
LAB_00133988:
        if (-1 < (int)param_10) {
          uVar22 = local_94 & 0xffeffcff;
          if (((local_94 & 0x3000000) == 0) ||
             ((!bVar48 && ((bVar40 == 0 || ((local_94 & 0x3000000) != 0x1000000)))))) {
            local_94 = uVar22;
            if (cVar9 == '\x01') {
              local_94 = uVar22 | 0x100;
            }
          }
          else {
            local_94 = uVar22 | 0x100000;
          }
        }
      }
      bVar46 = false;
      uVar37 = local_94;
      if ((*puVar30 & 0x8000000) == 0) {
        if ((*(ushort *)(param_1 + 0xa3) & 0x3800) == 0x1800) {
          uVar22 = param_10 & 0x70000;
          if ((uVar22 == 0) &&
             (((param_10 & 0x3000000) == 0 || (uVar22 = 0x20000, (*(byte *)(param_3 + 10) & 8) == 0)
              ))) {
            uVar22 = 0x10000;
          }
          if (((param_10 & 0x3000000) != 0) && ((char)param_10 == ' ')) {
            uVar22 = 0x20000;
          }
          bVar46 = uVar22 != 0x20000;
        }
        else {
          uVar22 = 0x10000;
          if ((char)param_10 == ' ') {
            param_10 = 0x1000000;
          }
          bVar46 = false;
          if ((char)local_94 == ' ') {
            local_94 = 0x1000000;
          }
        }
        param_10 = param_10 & 0xfff8ffff | uVar22;
        uVar37 = uVar22 | local_94 & 0xfff8ffff;
        if ((local_94 & 0x3000000) == 0) {
          uVar37 = local_94 & 0xfff8ffff | 0x10000;
        }
      }
      if (((*(uint *)(param_1[8] + 0x50) & 0xc00000ff) == 0) &&
         ((*(uint *)(param_1[8] + 0x50) & 0x3000000) != 0x1000000)) {
        if (((param_10 & 0x3000000) == 0) || ((char)param_1[0x54] != '\x01')) {
          uVar22 = param_10;
          if ((char)param_1[0x54] == '\0') {
            uVar22 = param_10 & 0xff7fffff;
          }
        }
        else {
          uVar22 = param_10 | 0x800000;
        }
        if (((uVar37 & 0x3000000) == 0) || ((char)param_1[0x54] != '\x01')) {
          uVar25 = uVar37;
          if ((char)param_1[0x54] == '\0') {
            uVar25 = uVar37 & 0xff7fffff;
          }
        }
        else {
          uVar25 = uVar37 | 0x800000;
        }
        param_10 = uVar22 & 0xffbfffff;
        uVar37 = uVar25 & 0xffbfffff;
        if ((*(char *)(lVar31 + 0x14) == '\x01') ||
           (((*(ulong *)(param_3 + 8) & 0x8000010000) == 0x8000010000 &&
            (*(char *)(lVar31 + 0x14) == -1)))) {
          if ((uVar22 & 0x3000000) != 0) {
            param_10 = param_10 | 0x400000;
          }
          if ((uVar25 & 0x3000000) != 0) {
            uVar37 = uVar37 | 0x400000;
          }
        }
      }
      local_ed = FUN_0012580c(param_1,param_3);
      if ((param_10 & 0x3000000) == 0) {
        bVar48 = false;
        local_c9 = false;
        bVar5 = false;
        cVar9 = '\0';
      }
      else {
        local_c9 = cVar15 == '\x02' && (param_10 & 0x70000) == 0x20000;
        uVar22 = param_10 & 0xff;
        if ((((uVar22 == 0x20) || (uVar22 < 8)) || (*(char *)(param_3 + 0x120) == '\0')) ||
           (*(char *)(param_3 + 0x121) == '\0')) {
          bVar48 = false;
          bVar5 = false;
        }
        else {
          bVar48 = true;
          bVar5 = true;
        }
        cVar9 = local_ed;
        if (((param_10 & 0x800000) != 0) && ((uVar22 == 0x20 || (uVar22 < 8)))) {
          cVar9 = '\x04';
        }
      }
      if ((uVar37 & 0x3000000) == 0) {
        local_ed = '\0';
      }
      else if (((uVar37 & 0x800000) != 0) && (((uVar37 & 0xff) == 0x20 || ((uVar37 & 0xff) < 8)))) {
        local_ed = '\x04';
      }
    }
    if (bVar45) {
      if (((bVar8 & 3) != 0) && (-1 < (short)local_3c)) {
        wlc_antsel_set_unicast(param_1[0x33],local_3c._3_1_);
      }
      *(uint *)(lVar41 + 0x360 + (ulong)*(uint *)(lVar41 + 0x35c) * 8) = param_10;
      *(uint *)(lVar41 + 0x364 + (ulong)*(uint *)(lVar41 + 0x35c) * 8) = param_6 & 0xff;
      *(uint *)(lVar41 + 0x35c) = *(int *)(lVar41 + 0x35c) + 1U & 0x3f;
    }
    uVar22 = *(uint *)(param_1[8] + 0x50);
    if (((uVar22 & 0xc00000ff) != 0) || ((uVar22 & 0x3000000) == 0x1000000)) {
      *(uint *)(param_1[8] + 0x114) = param_10;
    }
    if ((param_10 & 0x3000000) == 0) {
      local_160 = param_10 & 0xff;
    }
    else {
      local_160 = wlc_rate_rspec2rate(param_10);
    }
    uVar22 = param_10 & 0x3000000;
    if ((((uVar19 == 0) || (uVar19 == 2)) &&
        (((int)(uint)*(ushort *)(param_1 + 0xa5) < local_c8 || ((*puVar30 & 0x4000000) != 0)))) &&
       ((puVar29[2] & 1) == 0)) {
      bVar5 = true;
    }
    bVar45 = cVar13 == '\0';
    bVar49 = *(char *)(param_1[8] + 0x19) != '\0';
    if ((((bVar49 && !bVar45) && (uVar22 == 0)) && ((char)(&rate_info)[param_10 & 0xff] < '\0')) ||
       ((((*(byte *)(*param_1 + 0x68) & 3) != 0 && (uVar22 != 0)) && (cVar15 != '\0')))) {
      if (param_6 < 2) {
        if ((bVar49 && !bVar45) &&
           ((uVar22 != 0 ||
            (((uVar22 = param_10 & 0x7f, uVar22 != 4 && (uVar22 != 2)) &&
             ((uVar22 != 0xb && (uVar22 != 0x16)))))))) {
          local_c9 = true;
        }
      }
      else {
        *puVar30 = *puVar30 & 0xf7ffffff;
        param_10 = (-(uint)bVar45 & 0x1a) + 0x16;
        sVar17 = (short)*(undefined4 *)(param_1[8] + 8);
        if (((((sVar17 == 6) || (sVar17 == 4)) || (sVar17 == 8)) ||
            ((sVar17 == 10 || (sVar17 == 0xb)))) || (uVar37 = param_10, sVar17 == 7)) {
          param_10 = param_10 | 0x10000;
          uVar37 = param_10;
        }
      }
    }
    uVar22 = param_10 & 0x3000000;
    if ((uVar22 == 0) &&
       (((uVar25 = param_10 & 0x7f, uVar25 == 4 || (uVar25 == 2)) ||
        ((uVar25 == 0xb || (uVar25 == 0x16)))))) {
      if ((param_4 == '\0') || ((char)param_10 == '\x02')) {
        cVar9 = '\0';
      }
      else {
        cVar9 = *(char *)(*(long *)(param_3 + 0x18) + 0x358) != '\x01';
      }
    }
    uVar25 = uVar37 & 0x3000000;
    if ((uVar25 == 0) &&
       ((((uVar26 = uVar37 & 0x7f, uVar26 == 4 || (uVar26 == 2)) || (uVar26 == 0xb)) ||
        (uVar26 == 0x16)))) {
      if ((param_4 == '\0') || ((char)uVar37 == '\x02')) {
        local_ed = '\0';
      }
      else {
        local_ed = *(char *)(*(long *)(param_3 + 0x18) + 0x358) != '\x01';
      }
    }
    if ((((((*(byte *)(param_3 + 10) & 1) == 0) || (*(char *)((long)param_1 + 0x291) == '\0')) ||
         ((cVar15 == '\x03' || (*(char *)((long)param_1 + 0x295) == '\0')))) ||
        ((uVar22 == 0 &&
         ((((uVar26 = param_10 & 0x7f, uVar26 == 4 || (uVar26 == 2)) || (uVar26 == 0xb)) ||
          (uVar26 == 0x16)))))) || (((puVar29[2] & 1) != 0 || ((uVar20 & 0xfc) != 0x88)))) {
      bVar45 = false;
    }
    else {
      puVar33 = (uint *)osl_pkttag(param_2);
      *puVar33 = *puVar33 | 0x1000;
      local_9c = uVar36 | 0x5020;
      puVar38 = (ushort *)((long)puVar29 + (-(ulong)!bVar44 & 0xfffffffffffffffa) + 0x1e);
      *puVar38 = *puVar38 & 0xff9f | 0x20;
      bVar45 = true;
    }
    wlc_compute_plcp(param_1,param_10,local_c8,uVar20,pbVar34);
    wlc_compute_plcp(param_1,uVar37,local_c8,uVar20,local_58);
    osl_memcpy(puVar35 + 0x1b,local_58,6);
    if ((uVar25 == 0) &&
       (((uVar26 = uVar37 & 0x7f, uVar26 == 4 || (uVar26 == 2)) ||
        ((uVar26 == 0xb || (uVar26 == 0x16)))))) {
      *(undefined1 *)(puVar35 + 0x1d) = (undefined1)local_c8;
      *(char *)((long)puVar35 + 0x3b) = (char)((uint)local_c8 >> 8);
    }
    if ((*puVar30 & 0x400) == 0) {
      if (uVar22 == 0) goto LAB_0013418a;
LAB_001341b1:
      uVar36 = (ushort)*pbVar34;
    }
    else {
      if (uVar22 != 0) {
        if ((param_9 == 0) || (*(char *)(param_9 + 8) == '\x04')) {
          puVar33 = (uint *)osl_pkttag(param_2);
          *puVar33 = *puVar33 | 0x800;
          if (*(char *)((long)param_1 + 0x37a) != '\0') {
            bVar5 = true;
          }
        }
        goto LAB_001341b1;
      }
LAB_0013418a:
      if (-1 < (char)(&rate_info)[param_10 & 0xff]) goto LAB_001341b1;
      uVar36 = *pbVar34 & 0xf;
    }
    if (uVar20 == 0xa4) {
      if (bVar45) goto LAB_00134229;
LAB_00134259:
      uVar16 = puVar29[1];
LAB_001342b5:
      puVar35[0x1e] = uVar16;
    }
    else {
      if (bVar45) {
LAB_00134229:
        sVar17 = wlc_calc_frame_time(param_1,param_10,cVar9,0x92a);
        puVar29[1] = sVar17 + 2;
LAB_0013424e:
        if (uVar20 == 0xa4) goto LAB_00134259;
        if (!bVar45) goto LAB_0013426f;
      }
      else {
        if ((puVar29[2] & 1) != 0) goto LAB_0013424e;
        if ((*puVar30 & 0x400) == 0) {
          uVar16 = FUN_001299d2(param_1,param_10,cVar9,param_8);
        }
        else {
          uVar16 = FUN_00129a3e(param_1,param_10);
        }
        puVar29[1] = uVar16;
LAB_0013426f:
        if ((puVar29[2] & 1) == 0) {
          if ((*puVar30 & 0x400) == 0) {
            uVar16 = FUN_001299d2(param_1,uVar37,local_ed,param_8);
          }
          else {
            uVar16 = FUN_00129a3e(param_1,uVar37);
          }
          goto LAB_001342b5;
        }
      }
      puVar35[0x1e] = 0;
    }
    if ((*puVar30 & 0x200) != 0) {
      puVar35[0x21] = (ushort)puVar30[3];
      puVar35[0x22] = *(ushort *)((long)puVar30 + 0xe);
      local_9c = local_9c | 0x2000;
    }
    if (param_5 == 0) {
      local_9c = local_9c | 8;
    }
    if (((((puVar29[2] & 1) == 0) && (uVar26 = *puVar30, (uVar26 & 0x1000) == 0)) &&
        ((*(char *)((long)param_1 + 0x294) == '\0' || ((uVar26 & 0x40) == 0)))) &&
       (((bVar7 == 0 || ((uVar26 & 0x400) != 0)) || (*(char *)(lVar3 + 0x2c) == '\0')))) {
      local_9c = local_9c | 1;
    }
    uVar26 = (uint)*(byte *)((long)&wme_fifo2ac + (ulong)param_7);
    if (((uVar19 == 2) && (4 < local_160)) &&
       (((*(char *)((long)param_1 + 0x291) != '\0' &&
         (cVar13 = wlc_ampdu_frameburst_override(param_1[0x30]), cVar13 == '\0')) &&
        (((*(short *)(lVar3 + 0x20 + (ulong)uVar26 * 2) == 0 || ((*puVar30 & 0x400) != 0)) &&
         (!bVar48)))))) {
      local_9c = local_9c | 0x1000;
    }
    if (*(int *)param_1[8] == 1) {
      local_9c = local_9c | 0x80;
    }
    uVar27 = wlc_phy_chanspec_get(*(undefined8 *)((int *)param_1[8] + 4));
    if ((uVar27 & 0x3800) == 0x1800) {
      local_9c = local_9c | 0x100;
    }
    if (bVar43) {
      local_9c = local_9c | 0x8000;
    }
    *puVar35 = local_9c;
    if (((param_9 == 0) || ((char)param_1[0x68] != '\0')) || ((*(byte *)(lVar41 + 0x90) & 8) != 0))
    {
LAB_00134490:
      local_9c = 0;
    }
    else {
      uVar27 = 5;
      if (*(char *)(*param_1 + 0x5d) == '\0') {
        uVar27 = *(uint *)(*param_1 + 0xd4);
      }
      if (uVar27 <= *(byte *)(param_9 + 6)) goto LAB_00134490;
      local_9c = (ushort)*(byte *)(param_9 + 6) << 4 | *(byte *)(param_9 + 0xc) & 7;
    }
    if ((byte)(local_ed - 1U) < 2) {
      local_9c = local_9c | 0x2000;
    }
    osl_memcpy(puVar35 + 2,puVar29,2);
    puVar35[3] = 0;
    puVar35[0x16] = 0;
    if (((param_9 != 0) && ((char)param_1[0x68] == '\0')) && ((*(byte *)(lVar41 + 0x90) & 8) == 0))
    {
      uVar27 = 5;
      if (*(char *)(*param_1 + 0x5d) == '\0') {
        uVar27 = *(uint *)(*param_1 + 0xd4);
      }
      if (*(byte *)(param_9 + 6) < uVar27) {
        puVar38 = puVar29 + 0xc;
        if (bVar44) {
          puVar38 = puVar29 + 0xf;
        }
        if (bVar7 != 0) {
          puVar38 = puVar38 + 1;
        }
        FUN_001274a3(param_1,puVar35,puVar38,param_9,0);
      }
    }
    puVar38 = puVar29 + 2;
    osl_memcpy(puVar35 + 0x13,puVar38,6);
    puVar35[0x26] = (ushort)local_3c;
    if (local_3c._3_1_ == -1) {
      lVar31 = (long)&local_3c + 2;
      wlc_antsel_antcfg_get(param_1[0x33],1,0,0,0,(long)&local_3c + 3,lVar31);
      uVar50 = (undefined4)((ulong)lVar31 >> 0x20);
    }
    uVar19 = wlc_antsel_buildtxh(param_1[0x33],local_3c._3_1_,local_3c._2_1_);
    puVar35[0x27] = 0;
    puVar35[0x23] = uVar19;
    if (0xf < *(uint *)(*param_1 + 0x14)) {
      puVar35[0x28] = 0;
      puVar35[0x29] = 0;
      puVar35[0x2a] = 0;
      puVar35[0x2b] = 0;
    }
    if (bVar5) {
      local_c9 = false;
LAB_0013461f:
      local_a0 = wlc_rspec_to_rts_rspec(lVar41,param_10,0);
      uVar27 = wlc_rspec_to_rts_rspec(lVar41,uVar37,0);
      if ((local_a0 & 0x3000000) == 0) {
        if (-1 < (char)(&rate_info)[local_a0 & 0xff]) {
          bVar44 = (char)local_a0 == '\x02';
          goto LAB_0013468c;
        }
LAB_001346b2:
        local_118 = 0;
      }
      else {
        iVar23 = wlc_rate_rspec2rate(local_a0);
        bVar44 = iVar23 == 2;
LAB_0013468c:
        if ((bVar44) || (*(char *)(*(long *)(param_3 + 0x18) + 0x358) == '\x01')) goto LAB_001346b2;
        local_9c = local_9c | 0x4000;
        local_118 = 1;
      }
      if ((uVar27 & 0x3000000) == 0) {
        if (-1 < (char)(&rate_info)[uVar27 & 0xff]) {
          local_b0 = (char)uVar27;
          bVar44 = local_b0 == '\x02';
          goto LAB_001346f0;
        }
LAB_00134716:
        uVar6 = 0;
      }
      else {
        iVar23 = wlc_rate_rspec2rate(uVar27);
        bVar44 = iVar23 == 2;
LAB_001346f0:
        if ((bVar44) || (*(char *)(*(long *)(param_3 + 0x18) + 0x358) == '\x01')) goto LAB_00134716;
        local_9c = local_9c | 0x8000;
        uVar6 = 1;
      }
      if (local_c9 == false) {
        *puVar35 = *puVar35 | 6;
      }
      else {
        *puVar35 = *puVar35 | 0x800;
      }
      cVar13 = (-(local_c9 == false) & 6U) + 0xe;
      wlc_compute_plcp(param_1,local_a0,cVar13,uVar20,puVar35 + 0x2c);
      wlc_compute_plcp(param_1,uVar27,cVar13,uVar20,local_78);
      osl_memcpy(puVar35 + 0x17,local_78,6);
      uVar20 = wlc_compute_rtscts_dur
                         (param_1,local_c9,local_a0,param_10,local_118,cVar9,
                          CONCAT44(uVar50,local_c8),0);
      puVar35[0x30] = uVar20;
      uVar20 = wlc_compute_rtscts_dur(param_1,local_c9,uVar27,uVar37,uVar6,local_ed,local_c8,0);
      puVar35[0x1a] = uVar20;
      if (local_c9 == false) {
        puVar35[0x2f] = 0xb4;
        uVar39 = 0xc;
      }
      else {
        puVar35[0x2f] = 0xc4;
        uVar39 = 6;
        puVar38 = puVar29 + 5;
      }
      osl_memcpy(puVar35 + 0x31,puVar38,uVar39);
      if (((local_a0 & 0x3000000) == 0) && ((char)(&rate_info)[local_a0 & 0xff] < '\0')) {
        uVar20 = (byte)puVar35[0x2c] & 0xf;
      }
      else {
        uVar20 = (ushort)(byte)puVar35[0x2c];
      }
      local_a8 = puVar35 + 0x2f;
      uVar36 = uVar36 | uVar20 << 8;
    }
    else {
      if (local_c9 != false) goto LAB_0013461f;
      osl_memset(puVar35 + 0x2c,0,6);
      osl_memset(puVar35 + 0x2f,0,0x10);
      osl_memset(puVar35 + 0x17,0,6);
      puVar35[0x1a] = 0;
      uVar27 = 0;
      local_a0 = 0;
      local_a8 = (ushort *)0x0;
      uVar6 = 0;
      local_118 = 0;
    }
    if (((*puVar30 & 0x400) != 0) && (uVar22 != 0)) {
      local_40 = local_40 & 0xffff0000;
      uVar14 = wlc_ampdu_null_delim_cnt(param_1[0x30],param_3,param_10,local_c8,&local_40);
      *(undefined1 *)((long)puVar35 + 0x33) = uVar14;
      if (*(char *)(*param_1 + 0xc0) == '\x02') {
        puVar35[0x2b] = (ushort)local_40;
      }
    }
    uVar20 = 3;
    puVar35[1] = local_9c;
    puVar35[9] = uVar36;
    if (((uVar25 != 0x2000000) && (uVar20 = 2, uVar25 != 0x1000000)) && (uVar20 = 1, uVar25 == 0)) {
      uVar28 = uVar37 & 0x7f;
      if (((uVar28 == 4) || (uVar28 == 2)) || (uVar28 == 0xb)) {
        uVar20 = 0;
      }
      else {
        uVar20 = (ushort)(uVar28 != 0x16);
      }
    }
    uVar19 = 0xc;
    uVar28 = local_a0 & 0x3000000;
    if ((uVar28 != 0x2000000) && (uVar19 = 8, uVar28 != 0x1000000)) {
      uVar19 = 1;
      if (uVar28 == 0) {
        uVar28 = local_a0 & 0x7f;
        if (((uVar28 == 4) || (uVar28 == 2)) || (uVar28 == 0xb)) {
          uVar19 = 0;
        }
        else {
          uVar19 = (ushort)(uVar28 != 0x16);
        }
      }
      uVar19 = uVar19 * 4;
    }
    uVar36 = 0x30;
    if (((uVar27 & 0x3000000) != 0x2000000) && (uVar36 = 0x20, (uVar27 & 0x3000000) != 0x1000000)) {
      uVar36 = 1;
      if ((uVar27 & 0x3000000) == 0) {
        uVar28 = uVar27 & 0x7f;
        if (((uVar28 == 4) || (uVar28 == 2)) || (uVar28 == 0xb)) {
          uVar36 = 0;
        }
        else {
          uVar36 = (ushort)(uVar28 != 0x16);
        }
      }
      uVar36 = uVar36 << 4;
    }
    sVar17 = wlc_phy_chanspec_get(*(undefined8 *)(param_1[8] + 0x10));
    uVar16 = 3;
    puVar35[10] = sVar17 << 8 | uVar20 | uVar19 | uVar36;
    if (((uVar22 != 0x2000000) && (uVar16 = 2, uVar22 != 0x1000000)) && (uVar16 = 1, uVar22 == 0)) {
      uVar28 = param_10 & 0x7f;
      if (((uVar28 == 4) || (uVar28 == 2)) || (uVar28 == 0xb)) {
        uVar16 = 0;
      }
      else {
        uVar16 = (ushort)(uVar28 != 0x16);
      }
    }
    if ((byte)(cVar9 - 1U) < 2) {
      uVar16 = uVar16 | 0x10;
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x18);
      *piVar1 = *piVar1 + 1;
    }
    uVar20 = wlc_stf_d11hdrs_phyctl_txant(param_1,param_10);
    uVar20 = uVar20 | uVar16;
    if ((*(short *)(param_1[8] + 8) == 4) && (8 < *(byte *)(*param_1 + 0x94))) {
      sVar17 = wlc_stf_get_pwrperrate(param_1,param_10,0);
      uVar20 = uVar20 | sVar17 << 10;
      sVar17 = wlc_stf_get_pwrperrate(param_1,uVar37,0);
      puVar35[0x2b] = puVar35[0x2b] | sVar17 << 10;
    }
    puVar35[4] = uVar20;
    sVar17 = (short)*(undefined4 *)(param_1[8] + 8);
    if ((((((sVar17 == 6) || (sVar17 == 4)) || (sVar17 == 8)) || ((sVar17 == 10 || (sVar17 == 0xb)))
         ) || (sVar17 == 7)) || (sVar17 == 5)) {
      uVar19 = wlc_phytxctl1_calc(param_1,param_10,(short)param_1[0xa3]);
      puVar35[5] = uVar19;
      uVar19 = wlc_phytxctl1_calc(param_1,uVar37,(short)param_1[0xa3]);
      puVar35[6] = uVar19;
      if ((local_c9 != false) || (bVar5)) {
        uVar19 = wlc_phytxctl1_calc(param_1,local_a0,(short)param_1[0xa3]);
        puVar35[7] = uVar19;
        uVar19 = wlc_phytxctl1_calc(param_1,uVar27,(short)param_1[0xa3]);
        puVar35[8] = uVar19;
      }
      if ((cVar9 == '\x04') && (uVar22 != 0)) {
        uVar19 = wlc_calc_lsig_len(param_1,param_10,local_c8);
        puVar35[0x1f] = uVar19;
      }
      if ((local_ed == '\x04') && (uVar25 != 0)) {
        uVar19 = wlc_calc_lsig_len(param_1,uVar37,local_c8);
        puVar35[0x20] = uVar19;
      }
    }
    if (*(short *)(param_1[8] + 8) == 6) {
      if (uVar22 == 0) {
        if ((!bVar46) || (sVar17 = 0x20, -1 < (char)(&rate_info)[param_10 & 0xff])) {
          sVar17 = 0;
        }
      }
      else {
        cVar13 = wlc_phy_get_tx_power_offset(*(undefined8 *)(param_1[8] + 0x10),param_10 & 0xff);
        cVar15 = wlc_phy_get_tx_power_offset_by_mcs
                           (*(undefined8 *)(param_1[8] + 0x10),param_10 & 0xff);
        sVar17 = (short)cVar13 - (short)cVar15;
        if (sVar17 < 0x20) {
          if (sVar17 < -0x20) {
            sVar17 = -0x20;
          }
        }
        else {
          sVar17 = 0x1f;
        }
        if (bVar46) {
          sVar17 = sVar17 + 0x20;
        }
      }
      puVar35[4] = sVar17 << 10 | uVar20 & 0x3ff;
    }
    if ((bVar7 == 0) || ((*(byte *)(param_3 + 8) & 0x40) == 0)) goto LAB_00135004;
    if (*(short *)(lVar3 + 0x20 + (ulong)uVar26 * 2) == 0) {
      if ((3 < param_7) || (*(char *)(*param_1 + 0x61) == '\0')) goto LAB_00135004;
      bVar7 = *(byte *)((long)&wme_fifo2ac + (ulong)param_7);
      if (local_a8 == (ushort *)0x0) {
        iVar23 = wlc_calc_frame_time(param_1,param_10,cVar9,local_c8);
        uVar20 = FUN_001299d2(param_1,param_10,cVar9,0);
        local_a0 = (uint)uVar20 + iVar23;
      }
      else {
        iVar23 = FUN_0012992d(param_1,local_a0,local_118);
        local_a0 = iVar23 + (uint)local_a8[1];
      }
      uVar26 = (uint)bVar7;
      lVar41 = param_1[0x36];
    }
    else {
      if ((param_5 != 0) || ((*puVar30 & 0x400) != 0)) goto LAB_00135004;
      iVar23 = wlc_calc_frame_time(param_1,param_10,cVar9,local_c8);
      if (local_a8 == (ushort *)0x0) {
        if (bVar45) {
          uVar20 = 0;
          local_a0 = iVar23;
        }
        else {
          uVar20 = FUN_001299d2(param_1,param_10,cVar9,0);
          local_a0 = (uint)uVar20 + iVar23;
          sVar17 = wlc_calc_frame_time(param_1,uVar37,local_ed,local_c8);
          sVar21 = FUN_001299d2(param_1,uVar37,local_ed,0);
          uVar20 = sVar21 + sVar17;
        }
      }
      else {
        iVar24 = FUN_0012992d(param_1,local_a0,local_118);
        sVar17 = FUN_0012992d(param_1,uVar27,uVar6);
        uVar20 = sVar17 + puVar35[0x1a];
        local_a0 = iVar24 + (uint)local_a8[1];
      }
      puVar35[0x16] = uVar20;
      puVar35[3] = (ushort)local_a0;
      sVar17 = ((short)iVar23 + *(short *)(lVar3 + 0x20 + (ulong)uVar26 * 2)) - (ushort)local_a0;
      if (sVar17 < 0) {
LAB_00134f32:
        if (3 < param_7) goto LAB_00135004;
      }
      else {
        if ((param_7 != 1) || ((*puVar30 & 0x40) == 0)) {
          uVar37 = FUN_0012962f(param_1,param_10,cVar9,sVar17);
          uVar22 = 0x100;
          if ((0xff < uVar37) &&
             (uVar22 = (uint)*(ushort *)((long)param_1 + 0x51a),
             uVar37 <= *(ushort *)((long)param_1 + 0x51a))) {
            uVar22 = uVar37;
          }
          if (*(short *)((long)param_1 + ((ulong)param_7 + 0x288) * 2 + 0xc) != (short)uVar22) {
            *(short *)((long)param_1 + ((ulong)param_7 + 0x288) * 2 + 0xc) = (short)uVar22;
          }
          goto LAB_00134f32;
        }
        wlc_amsdu_txop_upd(param_1[0x2f]);
      }
      if (*(char *)(*param_1 + 0x61) == '\0') goto LAB_00135004;
      lVar41 = param_1[0x36];
    }
    wlc_cac_update_used_time(lVar41,uVar26,local_a0,param_3);
LAB_00135004:
    puVar30 = (uint *)osl_pkttag(param_2);
    *puVar30 = *puVar30 | 0x84;
    return local_3c;
  }
  local_40 = local_40 & 0xffffff00;
  local_3c._0_3_ = CONCAT12(0xff,(short)local_3c);
  local_3c = CONCAT13(0xff,(undefined3)local_3c);
  cVar13 = **(char **)(lVar41 + *(int *)param_1[0xa8]);
  cVar15 = **(char **)(lVar41 + *(int *)param_1[0xa9]);
  lVar3 = *(long *)(lVar41 + 0x570);
  puVar29 = (ushort *)osl_pktdata(lVar31,param_2);
  puVar30 = (uint *)osl_pkttag(param_2);
  uVar20 = *puVar29;
  uVar19 = (ushort)((uVar20 & 0xc) >> 2);
  bVar7 = 0;
  if (uVar19 == 2) {
    bVar7 = (byte)(uVar20 >> 7) & 1;
  }
  bVar44 = (uVar20 & 0x300) != 0x300;
  local_c8 = pkttotlen(lVar31,param_2);
  local_c8 = local_c8 + 4;
  if (param_9 != 0) {
    local_c8 = local_c8 + *(char *)(param_9 + 0xf);
  }
  lVar32 = *param_1;
  if ((((*(uint *)(lVar32 + 0x14) < 0xd) || (param_9 == 0)) || (-1 < (int)param_1[0x46])) ||
     (((*(char *)(param_9 + 8) != '\x02' || ((char)param_1[0x68] != '\0')) ||
      ((*(byte *)(lVar41 + 0x90) & 8) != 0)))) {
LAB_00132225:
    bVar43 = false;
  }
  else {
    bVar8 = *(byte *)(param_9 + 6);
    uVar22 = 5;
    if (*(char *)(lVar32 + 0x5d) == '\0') {
      uVar22 = *(uint *)(lVar32 + 0xd4);
    }
    if (((uVar22 <= bVar8) || (bVar8 < 4)) || ((param_6 != 1 || (0xb < bVar8)))) goto LAB_00132225;
    local_c8 = local_c8 + 8;
    bVar43 = true;
  }
  lVar31 = osl_pktpush(lVar31,param_2,0x7c);
  osl_memset(lVar31,0,0x7c);
  uVar36 = uVar20 & 0xfc;
  local_9c = 0x200;
  if (uVar36 != 0x80) {
    local_9c = 0;
  }
  if (bVar43) {
    local_9c = local_9c | 0x2000;
  }
  if (param_5 == 0) {
    local_9c = local_9c | 0x4000;
  }
  if ((((puVar29[2] & 1) == 0) && (uVar22 = *puVar30, (uVar22 & 0x1000) == 0)) &&
     (((*(char *)((long)param_1 + 0x294) == '\0' || ((uVar22 & 0x40) == 0)) &&
      (((bVar7 == 0 || ((uVar22 & 0x400) != 0)) || (*(char *)(lVar3 + 0x2c) == '\0')))))) {
    local_9c = local_9c | 0x80;
  }
  *(short *)(lVar31 + 6) = (short)(int)param_1[0xa3];
  if (uVar19 == 2) {
    bVar8 = (-bVar44 & 0xfaU) + 0x1e + bVar7 * '\x02';
  }
  else {
    bVar8 = (uVar19 != 1) * '\b' + 0x10;
  }
  *(byte *)(lVar31 + 8) = bVar8;
  *(short *)(lVar31 + 10) = (short)local_c8;
  if ((*puVar30 & 0x400) == 0) {
    if ((((*(uint *)(param_3 + 8) & 0x10040) != 0) && (uVar36 == 0x88)) && ((puVar29[2] & 1) == 0))
    {
      uVar22 = osl_pktprio(param_2);
      uVar22 = (uint)*(ushort *)(param_3 + 0xda + (ulong)uVar22 * 2);
      if (param_5 == param_6 - 1) {
        uVar37 = osl_pktprio(param_2);
        psVar2 = (short *)(param_3 + 0xda + (ulong)uVar37 * 2);
        *psVar2 = *psVar2 + 1;
      }
      goto LAB_001323d2;
    }
    if (uVar19 != 1) {
      local_9c = local_9c | 0x800;
      uVar22 = 0;
      goto LAB_001323dc;
    }
  }
  else {
    uVar22 = puVar30[1];
LAB_001323d2:
    if (uVar19 != 1) {
LAB_001323dc:
      puVar29[0xb] = (ushort)(uVar22 << 4) | (ushort)param_5 & 0xf;
    }
  }
  if (param_7 == 4) {
    iVar23 = *(int *)((long)param_1 + 0x424);
    uVar16 = *(ushort *)(lVar31 + 0xc);
    *(short *)((long)param_1 + 0x424) = (short)iVar23 + 1;
    uVar16 = uVar16 & 0x8018 | 4 | (ushort)(iVar23 << 5) & 0x7fe0;
  }
  else {
    uVar16 = *(ushort *)((long)param_1 + 0x422);
    if (param_5 == param_6 - 1) {
      *(ushort *)((long)param_1 + 0x422) = uVar16 + 1;
    }
    uVar16 = (ushort)((param_5 & 0xf | (uint)uVar16 << 4) << 5) & 0x7fe0 | (ushort)param_7 & 7;
  }
  local_40 = CONCAT22(uVar16,(undefined2)local_40);
  *(ushort *)(lVar31 + 0xe) = puVar29[0xb];
  if ((*puVar30 & 0x200) != 0) {
    *(short *)(lVar31 + 0x10) = (short)(puVar30[3] >> 8);
    local_9c = local_9c | 0x1000;
  }
  *(undefined2 *)(lVar31 + 0x12) = 0;
  local_64 = 1;
  if ((*(char *)(*param_1 + 0x140) == '\0') ||
     (cVar9 = wlc_olpc_eng_tx_cal_pkts(param_1[0x104]), cVar9 == '\0')) {
    if (((param_10 & 0xc00000ff) == 0) && ((param_10 & 0x3000000) != 0x1000000)) {
      if ((uVar19 < 2) ||
         ((((uVar36 == 0x48 || (uVar36 == 200)) && ((*(byte *)(param_3 + 9) & 1) == 0)) ||
          (((*puVar30 & 0x10) != 0 || (*(short *)((long)puVar30 + 6) < 0)))))) {
LAB_001325db:
        uVar22 = *(byte *)(param_3 + 0x44) & 0x7f;
      }
      else {
        uVar22 = *(uint *)(param_1[8] + 0x54);
        if ((((uVar22 & 0xc00000ff) == 0) && ((uVar22 & 0x3000000) != 0x1000000)) ||
           ((puVar29[2] & 1) == 0)) {
          uVar22 = *(uint *)(param_1[8] + 0x50);
          if (((uVar22 & 0xc00000ff) != 0) || ((uVar22 & 0x3000000) == 0x1000000)) {
            local_78[0] = uVar22;
            bVar40 = (byte)puVar29[2];
            goto LAB_0013259b;
          }
          if (((puVar29[2] & 1) == 0) && ((*(byte *)(param_3 + 0xc) & 8) == 0)) {
            local_64 = (-(*(char *)((long)param_1 + 0x759) == '\0') & 0xfeU) + 4;
            wlc_scb_ratesel_gettxrate(param_1[0x35],param_3,(long)&local_40 + 2,local_78,&local_3c);
            *puVar30 = *puVar30 | 0x8000000;
            if ((local_3c & 1) != 0) {
              puVar33 = (uint *)osl_pkttag(param_2);
              *puVar33 = *puVar33 | 0x2000;
            }
            wlc_antsel_antcfg_get
                      (param_1[0x33],0,1,local_68,local_67,(long)&local_3c + 2,(long)&local_3c + 3);
            bVar43 = param_5 == 0;
            local_158 = 0;
            goto LAB_00132683;
          }
          goto LAB_001325db;
        }
      }
      local_78[0] = uVar22;
    }
    else {
      local_78[0] = param_10;
      bVar40 = (byte)puVar29[2];
LAB_0013259b:
      if ((bVar40 & 1) == 0) {
        wlc_antsel_antcfg_get(param_1[0x33],0,0,0,0,(long)&local_3c + 2,(long)&local_3c + 3);
      }
    }
  }
  else {
    uVar22 = wlc_lowest_basic_rspec(param_1,param_3 + 0x40);
    local_78[0] = uVar22 & 0x7f;
    *puVar30 = *puVar30 & 0xf7ffffff;
  }
  bVar43 = false;
  local_158 = 2;
LAB_00132683:
  lVar32 = param_1[0xaa];
  bVar40 = *(byte *)((long)&wme_fifo2ac + (ulong)param_7);
  bVar45 = false;
  if (((*(byte *)(lVar32 + 2) < 2) ||
      (bVar45 = *(char *)(param_1[8] + 0x59) == '\x01', *(char *)(param_1[8] + 0x59) != -1)) ||
     ((*(byte *)(param_3 + 0xb) & 0x40) == 0)) {
    bVar10 = 0;
  }
  else {
    bVar10 = *(byte *)(lVar32 + 0xe) >> 2 & 1;
  }
  if (((*(byte *)(lVar32 + 2) < 2) || (*(char *)(param_1[8] + 0x59) != -1)) ||
     (((*(byte *)(param_3 + 0xd) & 8) == 0 || ((*(byte *)(param_3 + 0x126) & 0x10) == 0)))) {
    bVar11 = 0;
  }
  else {
    bVar11 = *(byte *)(lVar32 + 0xe) >> 2 & 1;
  }
  local_124 = 0;
  bVar5 = false;
  local_ed = '\0';
  local_c9 = false;
  bVar48 = false;
  bVar49 = false;
  lVar32 = (ulong)(uint)bVar40 + 0x10;
  bVar46 = false;
  do {
    if ((int)(uint)local_64 <= local_124) {
      puVar29 = (ushort *)(lVar31 + 0x24 + (long)(int)(local_64 - 1) * 0x14);
      *puVar29 = *puVar29 | 0x20;
      *(ushort *)(lVar31 + 4) = local_158;
      *(ushort *)(lVar31 + 2) = local_9c;
      *(undefined2 *)(lVar31 + 0xc) = local_40._2_2_;
      local_44 = local_78[0];
      if (bVar43) {
        if (((*(byte *)(*param_1 + 0x68) & 3) != 0) && (-1 < (int)local_40)) {
          wlc_antsel_set_unicast(param_1[0x33],local_3c._2_1_);
        }
        *(uint *)(lVar41 + 0x360 + (ulong)*(uint *)(lVar41 + 0x35c) * 8) = local_44;
        *(uint *)(lVar41 + 0x364 + (ulong)*(uint *)(lVar41 + 0x35c) * 8) = param_6 & 0xff;
        *(uint *)(lVar41 + 0x35c) = *(int *)(lVar41 + 0x35c) + 1U & 0x3f;
      }
      uVar22 = *(uint *)(param_1[8] + 0x50);
      if (((uVar22 & 0xc00000ff) != 0) || ((uVar22 & 0x3000000) == 0x1000000)) {
        *(uint *)(param_1[8] + 0x114) = local_44;
      }
      if (((param_9 != 0) && ((char)param_1[0x68] == '\0')) && ((*(byte *)(lVar41 + 0x90) & 8) == 0)
         ) {
        uVar22 = 5;
        if (*(char *)(*param_1 + 0x5d) == '\0') {
          uVar22 = *(uint *)(*param_1 + 0xd4);
        }
        if (*(byte *)(param_9 + 6) < uVar22) {
          *(char *)(lVar31 + 100) = *(char *)(param_9 + 0xc) << 4;
          *(undefined1 *)(lVar31 + 0x65) = *(undefined1 *)(param_9 + 6);
          FUN_001274a3(param_1,lVar31,lVar31 + 0x7c + (ulong)bVar8,param_9,0);
        }
      }
      puVar30 = (uint *)osl_pkttag(param_2);
      *puVar30 = *puVar30 | 0x84;
      uVar22 = local_40 >> 0x10;
      if ((*(char *)((long)param_1 + 0x71a) != '\0') && (*(char *)((long)param_1 + 0x719) == '\0'))
      {
        wlc_toe_add_hdr(param_1,param_2,param_3,param_9,param_6,param_11);
      }
      return uVar22;
    }
    lVar42 = (long)local_124;
    local_44 = local_78[lVar42];
    *(undefined2 *)(lVar31 + 0x24 + lVar42 * 0x14) = 0;
    if ((*(byte *)(*param_1 + 0x68) & 3) == 0) {
      local_44 = local_44 & 0xfff8ffff | 0x10000;
    }
    else {
      uVar22 = local_44 & 0x3000000;
      if ((*puVar30 & 0x8000000) == 0) {
        uVar37 = local_44 & 0x70000;
        if (uVar37 == 0) {
          uVar16 = *(ushort *)(param_1 + 0xa3) & 0x3800;
          if (uVar16 == 0x2000) {
            uVar37 = 0x30000;
            if (uVar22 == 0x2000000) goto LAB_00132833;
          }
          else if (uVar16 != 0x1800) goto LAB_00132827;
          if (((uVar22 != 0x2000000) && (uVar22 != 0x1000000)) ||
             ((*(byte *)(param_3 + 10) & 8) == 0)) goto LAB_00132827;
LAB_0013282e:
          uVar37 = 0x20000;
        }
        else {
          uVar16 = *(ushort *)(param_1 + 0xa3) & 0x3800;
          if (uVar16 == 0x1000) {
LAB_00132827:
            uVar37 = 0x10000;
          }
          else if ((uVar16 == 0x1800) && (uVar37 == 0x30000)) goto LAB_0013282e;
        }
LAB_00132833:
        local_44 = local_44 & 0xfff8ffff | uVar37;
      }
      if (((*(uint *)(param_1[8] + 0x50) & 0xc00000ff) == 0) &&
         ((*(uint *)(param_1[8] + 0x50) & 0x3000000) != 0x1000000)) {
        if ((char)param_1[0x54] == '\0') {
          local_44 = local_44 & 0xff7fffff;
        }
        else if (((char)param_1[0x54] == '\x01') &&
                (((local_44 & 0x3000000) == 0x2000000 || ((local_44 & 0x3000000) == 0x1000000)))) {
          local_44 = local_44 | 0x800000;
        }
      }
      if (((*(uint *)(param_1[8] + 0x50) & 0xc00000ff) == 0) &&
         ((*(uint *)(param_1[8] + 0x50) & 0x3000000) != 0x1000000)) {
        uVar37 = local_44 & 0x3000000;
        local_44 = local_44 & 0xffafffff;
        if (uVar37 == 0x2000000) {
          if (((*(byte *)(param_3 + 0xd) & 8) == 0) || ((*(byte *)(param_3 + 0x126) & 1) == 0))
          goto LAB_0013291c;
LAB_00132904:
          bVar12 = *(char *)(param_1[0xaa] + 0x14) == -1 ||
                   *(char *)(param_1[0xaa] + 0x14) == '\x01';
        }
        else {
          if ((uVar37 == 0x1000000) && ((*(ulong *)(param_3 + 8) & 0x8000010000) == 0x8000010000))
          goto LAB_00132904;
LAB_0013291c:
          bVar12 = false;
        }
        if ((bVar12) && (uVar22 != 0)) {
          local_44 = local_44 | 0x400000;
        }
        iVar23 = wlc_ratespec_nsts(local_44);
        if ((iVar23 == 1) &&
           (((bVar45 ||
             (((bVar10 != 0 && ((local_44 & 0x3000000) == 0x1000000)) ||
              ((bVar11 & (local_44 & 0x3000000) == 0x2000000) != 0)))) && (uVar22 != 0)))) {
          local_44 = local_44 | 0x100000;
        }
      }
      uVar22 = local_44;
      if ((local_44 & 0x3000000) == 0x1000000) {
        local_c9 = (bool)FUN_0012580c(param_1,param_3);
        iVar23 = wlc_ratespec_nsts(uVar22);
        bVar12 = bVar49;
        if ((cVar15 == '\x02') && (bVar12 = true, (local_44 & 0x70000) != 0x20000)) {
          bVar12 = bVar49;
        }
        bVar49 = bVar12;
        bVar12 = bVar46;
        if ((1 < iVar23) && (*(char *)(param_3 + 0x120) != '\0')) {
          bVar12 = true;
          if (*(char *)(param_3 + 0x121) == '\0') {
            bVar12 = bVar5;
          }
          bVar5 = bVar12;
          bVar12 = true;
          if (*(char *)(param_3 + 0x121) == '\0') {
            bVar12 = bVar46;
          }
        }
        bVar46 = bVar12;
        if ((iVar23 == 1) && ((local_44 & 0x800000) != 0)) {
LAB_00132a59:
          local_c9 = true;
        }
      }
      else if ((local_44 & 0x3000000) == 0x2000000) goto LAB_00132a59;
    }
    if ((local_44 & 0x3000000) == 0) {
      uVar22 = local_44 & 0xff;
    }
    else {
      uVar22 = wlc_rate_rspec2rate();
    }
    bVar12 = bVar46;
    if ((((uVar19 == 0) || (uVar19 == 2)) &&
        (((int)(uint)*(ushort *)(param_1 + 0xa5) < local_c8 || ((*puVar30 & 0x4000000) != 0)))) &&
       (bVar12 = true, (puVar29[2] & 1) != 0)) {
      bVar12 = bVar46;
    }
    bVar46 = cVar13 == '\0';
    bVar47 = *(char *)(param_1[8] + 0x19) != '\0';
    if ((((bVar47 && !bVar46) && ((local_44 & 0x3000000) == 0)) &&
        ((char)(&rate_info)[local_44 & 0xff] < '\0')) ||
       ((((local_44 & 0x3000000) == 0x2000000 || ((local_44 & 0x3000000) == 0x1000000)) &&
        (cVar15 != '\0')))) {
      if (param_6 < 2) {
        if ((bVar47 && !bVar46) &&
           (((local_44 & 0x3000000) != 0 ||
            (((uVar37 = local_44 & 0x7f, uVar37 != 4 && (uVar37 != 2)) &&
             ((uVar37 != 0xb && (uVar37 != 0x16)))))))) {
          bVar49 = true;
        }
      }
      else {
        *puVar30 = *puVar30 & 0xf7ffffff;
        local_44 = (-(uint)bVar46 & 0x1a) + 0x16 | 0x10000;
      }
    }
    if (((local_44 & 0x3000000) == 0) &&
       ((((uVar37 = local_44 & 0x7f, uVar37 == 4 || (uVar37 == 2)) || (uVar37 == 0xb)) ||
        (uVar37 == 0x16)))) {
      if ((param_4 == '\0') || ((char)local_44 == '\x02')) {
        local_c9 = false;
      }
      else {
        local_c9 = *(char *)(*(long *)(param_3 + 0x18) + 0x358) != '\x01';
      }
    }
    if ((((((*(byte *)(param_3 + 10) & 1) != 0) && (*(char *)((long)param_1 + 0x291) != '\0')) &&
         ((cVar15 != '\x03' && (*(char *)((long)param_1 + 0x295) != '\0')))) &&
        (((local_44 & 0x3000000) != 0 ||
         ((((uVar37 = local_44 & 0x7f, uVar37 != 4 && (uVar37 != 2)) && (uVar37 != 0xb)) &&
          (uVar37 != 0x16)))))) && (((puVar29[2] & 1) == 0 && (uVar36 == 0x88)))) {
      puVar33 = (uint *)osl_pkttag(param_2);
      *puVar33 = *puVar33 | 0x1000;
      local_9c = local_9c | 0x8400;
      puVar35 = (ushort *)((long)puVar29 + (-(ulong)bVar44 & 0xfffffffffffffffa) + 0x1e);
      *puVar35 = *puVar35 & 0xff9f | 0x20;
      bVar48 = true;
    }
    if (((*(char *)(param_1[0xaa] + 0x77) != '\0') && (*(char *)(*param_1 + 0xe8) != '\0')) &&
       ((lVar4 = param_1[0x102], *(char *)(lVar4 + 0x1e) != '\0' &&
        (((*(char *)(lVar4 + 0x1f) != '\0' && (1 < *(byte *)(param_1[0xaa] + 2))) &&
         (local_ed = '\0', local_c9 != true)))))) {
      local_ed = wlc_txbf_check(lVar4,local_44,param_3,&local_40);
    }
    if (*(char *)(param_1[0xaa] + 0x77) == '\0') {
      if (local_ed == '\0') goto LAB_00132da1;
LAB_00132d8c:
      local_ed = wlc_check_expected_txbf_system_gain(param_1,param_3,&local_44);
    }
    else {
      if (local_ed != '\0') goto LAB_00132d8c;
      if (*(char *)(*param_1 + 0xe8) != '\0') {
        if ((*(char *)(param_1[0xaa] + 0x76) != '\0') &&
           ((((local_44 & 0x3000000) != 0 ||
             (((uVar37 = local_44 & 0x7f, uVar37 != 4 && (uVar37 != 2)) &&
              ((uVar37 != 0xb && ((uVar37 != 0x16 && (-1 < (char)(&rate_info)[local_44 & 0xff]))))))
             )) && ((iVar23 = wlc_ratespec_nss(), iVar23 == 2 &&
                    (iVar23 = bcm_bitcount(param_1[0xaa] + 1,1), iVar23 == 3)))))) {
          local_40 = CONCAT31(local_40._1_3_,5);
          goto LAB_00132d8c;
        }
        local_ed = '\0';
      }
    }
LAB_00132da1:
    if (((*(uint *)(param_1[8] + 0x50) & 0xc00000ff) != 0) ||
       ((*(uint *)(param_1[8] + 0x50) & 0x3000000) == 0x1000000)) {
      *(bool *)(param_1[0x102] + 0x98) = local_ed != '\0';
    }
    wlc_compute_plcp(param_1,local_44,local_c8,uVar20,lVar31 + 0x1a + lVar42 * 0x14);
    iVar23 = wlc_rate_rspec2rate(local_44);
    *(short *)(lVar31 + 0x22 + lVar42 * 0x14) = (short)(iVar23 / 500);
    bVar46 = bVar12;
    if ((((local_124 == 0) && ((*puVar30 & 0x400) != 0)) && ((local_44 & 0x3000000) != 0)) &&
       ((param_9 == 0 || (*(char *)(param_9 + 8) == '\x04')))) {
      puVar33 = (uint *)osl_pkttag(param_2);
      *puVar33 = *puVar33 | 0x800;
      bVar46 = true;
      if (*(char *)((long)param_1 + 0x37a) == '\0') {
        bVar46 = bVar12;
      }
    }
    if ((param_6 < 2) || (uVar20 == 0xa4)) {
      if (bVar48) goto LAB_00132ec1;
    }
    else if (bVar48) {
LAB_00132ec1:
      sVar17 = wlc_calc_frame_time(param_1,local_44,local_c9,0x92a);
      puVar29[1] = sVar17 + 2;
    }
    else if ((puVar29[2] & 1) == 0) {
      uVar16 = FUN_001299d2(param_1,local_44,local_c9,param_8);
      puVar29[1] = uVar16;
    }
    if ((((uVar19 == 2) && (4 < uVar22)) && (*(char *)((long)param_1 + 0x291) != '\0')) &&
       (((cVar9 = wlc_ampdu_frameburst_override(param_1[0x30]), cVar9 == '\0' &&
         ((*(short *)(lVar3 + lVar32 * 2) == 0 || ((*puVar30 & 0x400) != 0)))) && (!bVar5)))) {
      local_9c = local_9c | 0x400;
    }
    if ((local_44 & 0x3000000) == 0x2000000) {
      local_158 = local_158 | 4;
    }
    if (bVar46) {
      bVar49 = false;
LAB_00132f96:
      uVar22 = wlc_rspec_to_rts_rspec(lVar41,local_44,0);
      if ((uVar22 & 0x3000000) == 0) {
        uVar37 = uVar22 & 0x7f;
        if (((uVar37 == 4) || (uVar37 == 2)) || (uVar37 == 0xb)) {
          uVar16 = 0;
        }
        else {
          uVar16 = (ushort)(uVar37 != 0x16);
        }
      }
      else {
        uVar16 = 1;
      }
      *(ushort *)(lVar31 + 0x24 + lVar42 * 0x14) = uVar16;
      if (((((uVar22 & 0x3000000) != 0) || (-1 < (char)(&rate_info)[uVar22 & 0xff])) &&
          ((byte)uVar22 != 2)) && (*(char *)(*(long *)(param_3 + 0x18) + 0x358) != '\x01')) {
        *(ushort *)(lVar31 + 0x24 + lVar42 * 0x14) = uVar16 | 0x10;
      }
      if (bVar49) {
        puVar35 = (ushort *)(lVar31 + 0x24 + lVar42 * 0x14);
        *puVar35 = *puVar35 | 8;
      }
      else {
        puVar35 = (ushort *)(lVar31 + 0x24 + lVar42 * 0x14);
        *puVar35 = *puVar35 | 4;
      }
      puVar35 = (ushort *)(lVar31 + 0x24 + lVar42 * 0x14);
      *puVar35 = *puVar35 | ((byte)(&rate_info)[(byte)uVar22] & 0xf) << 8;
    }
    else if (bVar49) goto LAB_00132f96;
    if ((local_ed != '\0') && (*(char *)(*param_1 + 0xe8) != '\0')) {
      puVar35 = (ushort *)(lVar31 + 0x24 + lVar42 * 0x14);
      *puVar35 = *puVar35 | (ushort)(byte)local_40 << 0xc;
    }
    lVar42 = lVar31 + 0x10 + lVar42 * 0x14;
    uVar18 = wlc_acphy_txctl0_calc(param_1,local_44,local_c9);
    *(undefined2 *)(lVar42 + 4) = uVar18;
    uVar18 = wlc_acphy_txctl1_calc(param_1,local_44,0);
    *(undefined2 *)(lVar42 + 6) = uVar18;
    uVar18 = wlc_acphy_txctl2_calc(param_1,local_44);
    *(undefined2 *)(lVar42 + 8) = uVar18;
    if (((local_124 == 0) && (bVar7 != 0)) &&
       (((*(byte *)(param_3 + 8) & 0x40) != 0 && (*(short *)(lVar3 + lVar32 * 2) != 0)))) {
      if ((param_5 == 0) && ((*puVar30 & 0x400) == 0)) {
        iVar24 = wlc_calc_frame_time(param_1,local_44,local_c9,local_c8);
        iVar23 = iVar24;
        if (!bVar48) {
          uVar16 = FUN_001299d2(param_1,local_44,local_c9,0);
          iVar23 = (uint)uVar16 + iVar24;
        }
        local_120 = (short)iVar23;
        local_120 = ((short)iVar24 + *(short *)(lVar3 + lVar32 * 2)) - local_120;
        if (local_120 < 0) {
LAB_001331db:
          if (3 < param_7) goto LAB_00133253;
        }
        else {
          if ((param_7 != 1) || ((*puVar30 & 0x40) == 0)) {
            uVar22 = FUN_0012962f(param_1,local_44,local_c9,local_120);
            uVar16 = 0x100;
            if ((0xff < uVar22) && (uVar16 = *(ushort *)((long)param_1 + 0x51a), uVar22 <= uVar16))
            {
              uVar16 = (ushort)uVar22;
            }
            if (*(ushort *)((long)param_1 + ((ulong)param_7 + 0x288) * 2 + 0xc) != uVar16) {
              *(ushort *)((long)param_1 + ((ulong)param_7 + 0x288) * 2 + 0xc) = uVar16;
            }
            goto LAB_001331db;
          }
          wlc_amsdu_txop_upd(param_1[0x2f]);
        }
        if (*(char *)(*param_1 + 0x61) == '\0') goto LAB_00133253;
        lVar42 = param_1[0x36];
      }
      else {
        if ((3 < param_7) || (*(char *)(*param_1 + 0x61) == '\0')) goto LAB_00133253;
        iVar23 = wlc_calc_frame_time(param_1,local_44,local_c9,local_c8);
        uVar16 = FUN_001299d2(param_1,local_44,local_c9,0);
        lVar42 = param_1[0x36];
        iVar23 = (uint)uVar16 + iVar23;
      }
      wlc_cac_update_used_time(lVar42,(uint)bVar40,iVar23,param_3);
    }
LAB_00133253:
    lVar42 = (long)local_124;
    local_124 = local_124 + 1;
    local_78[lVar42] = local_44;
  } while( true );
}

