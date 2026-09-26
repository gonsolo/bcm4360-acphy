
void si_sdiod_drive_strength_init(long param_1,undefined8 param_2,uint param_3)

{
  long lVar1;
  uint uVar2;
  uint uVar3;
  undefined1 *puVar4;
  int iVar5;
  sbyte sVar6;
  bool bVar7;
  undefined4 local_40;
  undefined4 local_3c [3];
  
  local_40 = 0;
  if ((*(byte *)(param_1 + 0x1b) & 0x10) == 0) {
    return;
  }
  lVar1 = si_switch_core(param_1,0x800,local_3c,&local_40);
  uVar3 = *(uint *)(param_1 + 0x20);
  uVar2 = *(int *)(param_1 + 0x3c) << 0x10 | uVar3;
  if (uVar2 < 0x43250004) {
    if ((uVar2 < 0x43250002) && (uVar2 != 0x43150004)) {
      if (uVar2 != 0x43250001) goto LAB_001149dd;
      sVar6 = 0x1c;
      uVar3 = 0x30000000;
      puVar4 = &DAT_0050a400;
    }
    else {
      sVar6 = 0xb;
      uVar3 = 0x3800;
      puVar4 = &DAT_0050a408;
    }
  }
  else {
    if (uVar2 == 0x43360008) {
LAB_00114922:
      if (uVar3 == 8) {
        sVar6 = 0xb;
        uVar3 = 0x3800;
        puVar4 = &DAT_0050a420;
        goto LAB_0011496a;
      }
      bVar7 = uVar3 == 0xb;
    }
    else {
      if (0x43360008 < uVar2) {
        if (uVar2 != 0x4336000b) {
          if (uVar2 != 0xa962000d) goto LAB_001149dd;
          sVar6 = 0xb;
          uVar3 = 0x3800;
          puVar4 = &DAT_0050a440;
          goto LAB_0011496a;
        }
        goto LAB_00114922;
      }
      bVar7 = uVar2 == 0x4330000c;
    }
    if (!bVar7) goto LAB_001149dd;
    sVar6 = 0xb;
    uVar3 = 0x3800;
    puVar4 = &DAT_0050a430;
  }
LAB_0011496a:
  iVar5 = 0;
  if (lVar1 != 0) {
    while (param_3 < (byte)puVar4[(long)iVar5 * 2]) {
      iVar5 = iVar5 + 1;
    }
    if (iVar5 != 0) {
      iVar5 = iVar5 - (uint)((byte)puVar4[(long)iVar5 * 2] < param_3);
    }
    osl_writel(1,lVar1 + 0x650);
    uVar2 = osl_readl(lVar1 + 0x654);
    osl_writel(uVar2 & ~uVar3 | (uint)(byte)puVar4[(long)iVar5 * 2 + 1] << sVar6,lVar1 + 0x654);
  }
LAB_001149dd:
  si_restore_core(param_1,local_3c[0],local_40);
  return;
}

