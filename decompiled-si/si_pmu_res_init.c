
void si_pmu_res_init(long param_1,undefined8 param_2)

{
  uint *puVar1;
  long lVar2;
  int iVar3;
  char cVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  long lVar9;
  long lVar10;
  ulong uVar11;
  undefined *puVar12;
  undefined8 uVar13;
  uint uVar14;
  undefined *puVar15;
  uint uVar16;
  byte local_50;
  undefined1 local_48 [8];
  uint local_40;
  uint local_3c [3];
  
  local_3c[0] = 0;
  local_40 = 0;
  uVar5 = si_coreidx();
  lVar9 = si_setcoreidx(param_1,0);
  lVar10 = getvar(0,&DAT_006f50fb);
  if (lVar10 != 0) {
    DAT_006f0770 = 1;
    DAT_006f0778 = bcm_strtoul(lVar10,0,0);
  }
  lVar10 = getvar(0,&DAT_006f5100);
  if (lVar10 != 0) {
    DAT_006f0771 = 1;
    DAT_006f077c = bcm_strtoul(lVar10,0,0);
  }
  uVar6 = *(uint *)(param_1 + 0x3c);
  if (uVar6 == 0x4334) {
LAB_00115d19:
    uVar14 = 0;
    puVar15 = &DAT_0050aa40;
    uVar6 = 0;
    puVar12 = &DAT_0050aa38;
  }
  else if (uVar6 < 0x4335) {
    if (uVar6 == 0x4324) {
LAB_00115c98:
      if (*(uint *)(param_1 + 0x40) < 2) {
        uVar14 = 0x10;
        puVar15 = &DAT_0050aa80;
        uVar6 = 2;
        puVar12 = &DAT_0050aa60;
      }
      else {
LAB_00115d2e:
        uVar14 = 0x10;
        puVar15 = &DAT_0050aa80;
        uVar6 = 2;
        puVar12 = &DAT_0050aa70;
      }
    }
    else if (uVar6 < 0x4325) {
      if (uVar6 == 0x4315) {
        uVar14 = 4;
        puVar15 = &DAT_0050a8d0;
        uVar6 = 1;
        puVar12 = &DAT_0050a8c0;
      }
      else {
        if (uVar6 != 0x4319) {
          if (uVar6 != 0x4314) goto LAB_00115b76;
          iVar3 = *(int *)(param_1 + 0x44);
          if (((iVar3 != 10) && (iVar3 != 8)) && (iVar3 != 0xe)) {
            osl_writel(3,lVar9 + 0x650);
            uVar6 = osl_readl(lVar9 + 0x654);
            osl_writel(uVar6 | 0x80000,lVar9 + 0x654);
          }
          goto LAB_00115d19;
        }
        uVar14 = 3;
        puVar15 = &DAT_0050a9b0;
        uVar6 = 1;
        puVar12 = &DAT_0050a9a0;
      }
    }
    else if (uVar6 == 0x4328) {
      uVar14 = 1;
      puVar15 = &DAT_0050a840;
      uVar6 = 0x14;
      puVar12 = &DAT_0050a7a0;
    }
    else if (uVar6 < 0x4329) {
      if (uVar6 != 0x4325) goto LAB_00115b76;
      uVar14 = 4;
      puVar15 = &DAT_0050a860;
      uVar6 = 1;
      puVar12 = &DAT_0050a858;
    }
    else if (uVar6 == 0x4329) {
      uVar14 = 4;
      puVar15 = &DAT_0050a940;
      uVar6 = 2;
      puVar12 = &DAT_0050a930;
    }
    else {
      if (uVar6 != 0x4330) goto LAB_00115b76;
      uVar14 = 1;
      puVar15 = &DAT_0050aa20;
      uVar6 = 1;
      puVar12 = &DAT_0050aa18;
    }
  }
  else if (uVar6 == 0x4360) {
LAB_00115cef:
    uVar14 = 0;
    puVar15 = (undefined *)0x0;
    puVar12 = &DAT_0050ac90;
    uVar6 = (-(uint)(*(uint *)(param_1 + 0x40) < 4) & 0xfffffff8) + 9;
    if (*(uint *)(param_1 + 0x40) < 4) {
      puVar12 = &DAT_0050ac88;
    }
  }
  else if (uVar6 < 0x4361) {
    if (uVar6 == 0x4336) {
LAB_00115bfd:
      uVar14 = 1;
      puVar15 = &DAT_0050aa00;
      uVar6 = 1;
      puVar12 = &DAT_0050a9f8;
    }
    else if (uVar6 < 0x4336) {
      uVar14 = 1;
      puVar15 = &DAT_0050ac10;
      uVar6 = 1;
      puVar12 = &DAT_0050ac00;
    }
    else {
      if (uVar6 != 0x4350) {
        if (uVar6 != 0x4352) goto LAB_00115b76;
        goto LAB_00115cef;
      }
      uVar14 = 0;
      puVar15 = (undefined *)0x0;
      uVar6 = 0xb;
      puVar12 = &DAT_0050ac30;
    }
  }
  else {
    if (uVar6 < 0xa8ec) {
      if (0xa8e9 < uVar6) {
        if (uVar6 == 0x4324) goto LAB_00115c98;
        goto LAB_00115d2e;
      }
      if (uVar6 == 0xa886) goto LAB_00115d19;
    }
    else if (uVar6 == 0xa962) goto LAB_00115bfd;
LAB_00115b76:
    uVar14 = 0;
    puVar15 = (undefined *)0x0;
    uVar6 = 0;
    puVar12 = (undefined *)0x0;
  }
  uVar16 = (*(uint *)(param_1 + 0x24) & 0x1f00) >> 8;
  while (uVar6 != 0) {
    uVar6 = uVar6 - 1;
    osl_writel(puVar12[(ulong)uVar6 * 8],lVar9 + 0x620);
    osl_writel(*(undefined4 *)(puVar12 + (ulong)uVar6 * 8 + 4),lVar9 + 0x628);
  }
  for (uVar6 = 0; uVar6 < uVar16; uVar6 = uVar6 + 1) {
    osl_snprintf(local_48,8,&DAT_006f5105,uVar6);
    lVar10 = getvar(0,local_48);
    if (lVar10 != 0) {
      uVar11 = bcm_strtoul(lVar10,0,0);
      uVar7 = (uint)uVar11;
      if ((0xc < *(int *)(param_1 + 0x20)) && (uVar7 < 0x10000)) {
        uVar7 = (uint)((uVar11 >> 8 & 0xff) << 0x10) | uVar7 & 0xff;
      }
      osl_writel(uVar6,lVar9 + 0x620);
      osl_writel(uVar7,lVar9 + 0x628);
    }
  }
  lVar10 = lVar9 + 0x624;
  while (uVar14 != 0) {
    uVar14 = uVar14 - 1;
    puVar1 = (uint *)(puVar15 + (ulong)uVar14 * 0x18);
    if ((*(code **)(puVar1 + 4) == (code *)0x0) ||
       (cVar4 = (**(code **)(puVar1 + 4))(param_1), cVar4 != '\0')) {
      for (uVar6 = 0; uVar6 < uVar16; uVar6 = uVar6 + 1) {
        local_50 = (byte)uVar6;
        if ((*puVar1 & 1 << (local_50 & 0x1f)) != 0) {
          osl_writel(uVar6,lVar9 + 0x620);
          cVar4 = (char)puVar1[1];
          if (cVar4 == '\0') {
            uVar7 = puVar1[2];
          }
          else if (cVar4 == '\x01') {
            uVar7 = osl_readl(lVar10);
            uVar7 = uVar7 | puVar1[2];
          }
          else {
            if (cVar4 != -1) goto LAB_00115ed6;
            uVar7 = osl_readl(lVar10);
            uVar7 = uVar7 & ~puVar1[2];
          }
          osl_writel(uVar7,lVar10);
        }
LAB_00115ed6:
      }
    }
  }
  for (uVar6 = 0; uVar6 < uVar16; uVar6 = uVar6 + 1) {
    osl_snprintf(local_48,8,&DAT_006f510a,uVar6);
    lVar10 = getvar(0,local_48);
    if (lVar10 != 0) {
      osl_writel(uVar6,lVar9 + 0x620);
      uVar8 = bcm_strtoul(lVar10,0,0);
      osl_writel(uVar8,lVar9 + 0x624);
    }
  }
  FUN_00111ef0(param_1,local_3c,&local_40);
  uVar6 = local_3c[0];
  local_3c[0] = FUN_00112632(param_1,param_2,lVar9,local_3c[0],0);
  local_3c[0] = local_3c[0] | uVar6;
  if ((*(int *)(param_1 + 0x3c) == 0x4352) || (*(int *)(param_1 + 0x3c) == 0x4360)) {
    if (*(uint *)(param_1 + 0x40) < 4) {
      if ((*(uint *)(param_1 + 0x48) & 0x20) == 0) {
        osl_writel(6,lVar9 + 0x660);
        osl_writel(0x9048562,lVar9 + 0x664);
        osl_writel(0xe,lVar9 + 0x660);
        uVar13 = 0x9048562;
LAB_001160cc:
        osl_writel(uVar13,lVar9 + 0x664);
        si_pmu_pllupd(param_1);
      }
    }
    else if ((*(uint *)(param_1 + 0x48) & 0x20) == 0) {
      lVar10 = lVar9 + 0x660;
      osl_writel(1,lVar9 + 0x650);
      uVar6 = osl_readl(lVar9 + 0x654);
      lVar2 = lVar9 + 0x664;
      osl_writel(uVar6 | 0x800,lVar9 + 0x654);
      osl_writel(6,lVar10);
      osl_writel(0x80004e2,lVar2);
      osl_writel(7,lVar10);
      osl_writel(0xe,lVar2);
      osl_writel(0xe,lVar10);
      osl_writel(0x80004e2,lVar2);
      osl_writel(0xf,lVar10);
      uVar13 = 0xe;
      goto LAB_001160cc;
    }
  }
  if (local_40 == 0) {
    if (local_3c[0] == 0) goto LAB_0011611e;
    uVar6 = osl_readl(lVar9 + 0x61c);
    uVar6 = uVar6 | local_3c[0];
  }
  else {
    local_40 = local_40 | local_3c[0];
    uVar6 = osl_readl(lVar9 + 0x61c);
    uVar6 = uVar6 | local_40;
  }
  osl_writel(uVar6,lVar9 + 0x61c);
LAB_0011611e:
  if (local_3c[0] != 0) {
    osl_writel(local_3c[0],lVar9 + 0x618);
  }
  if (local_40 != 0) {
    osl_writel(local_40,lVar9 + 0x61c);
  }
  if (((*(int *)(param_1 + 0x3c) == 0x4352) || (*(int *)(param_1 + 0x3c) == 0x4360)) &&
     (*(uint *)(param_1 + 0x40) < 4)) {
    uVar6 = si_corereg(param_1,3,0x1e0,0,0);
    si_corereg(param_1,3,0x1e0,0xffffffff,uVar6 | 0x10);
  }
  osl_delay(2000);
  si_setcoreidx(param_1,uVar5);
  return;
}

