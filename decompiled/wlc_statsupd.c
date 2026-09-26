
void wlc_statsupd(long *param_1)

{
  int *piVar1;
  short sVar2;
  short *psVar3;
  long *plVar4;
  long lVar5;
  int iVar6;
  long lVar7;
  int iVar8;
  ushort uVar9;
  undefined1 local_98 [2];
  short sStack_96;
  undefined4 local_94;
  short sStack_92;
  undefined4 local_90;
  short sStack_8e;
  short asStack_8c [9];
  short sStack_7a;
  undefined4 local_78;
  short sStack_76;
  undefined4 local_74;
  short sStack_72;
  undefined4 local_70;
  short sStack_6e;
  undefined4 local_6c;
  short sStack_6a;
  undefined4 local_68;
  short sStack_66;
  undefined4 local_64;
  short sStack_62;
  undefined4 local_60;
  short sStack_5e;
  undefined4 local_5c;
  short sStack_5a;
  undefined4 local_58;
  short sStack_56;
  undefined4 local_54;
  short sStack_52;
  undefined4 local_50;
  short sStack_4e;
  undefined4 local_4c;
  short sStack_4a;
  undefined4 local_48;
  short sStack_46;
  undefined4 local_44;
  short sStack_42;
  short local_3e;
  undefined4 local_3c;
  short sStack_3a;
  undefined4 local_38;
  short sStack_36;
  undefined4 local_34;
  short sStack_32;
  undefined4 local_30;
  short sStack_2e;
  undefined4 local_2c;
  short sStack_2a;
  undefined4 local_28;
  short sStack_26;
  undefined4 local_24;
  short sStack_22;
  undefined4 local_20;
  short sStack_1e;
  short local_1a;
  
  if ((*(char *)(*param_1 + 0x34) != '\0') && (*(char *)((long)param_1 + 0x31) != '\0')) {
    wlc_bmac_copyfrom_objmem(param_1[4],0xe0,local_98,0x80,0x10000);
    psVar3 = *(short **)(param_1[7] + 0x48);
    uVar9 = (short)_local_98 - *psVar3;
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0xc4);
      *piVar1 = *piVar1 + (uint)uVar9;
      *psVar3 = (short)_local_98;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_96 - *(short *)(lVar7 + 2);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 200);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 2) = sStack_96;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_94 - *(short *)(lVar7 + 4);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0xcc);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 4) = (short)local_94;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_92 - *(short *)(lVar7 + 6);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0xd0);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 6) = sStack_92;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_90 - *(short *)(lVar7 + 8);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0xd4);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 8) = (short)local_90;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_8e - *(short *)(lVar7 + 10);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0xd8);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 10) = sStack_8e;
    }
    iVar6 = 6;
    iVar8 = 0;
    do {
      lVar5 = (long)iVar8;
      lVar7 = *(long *)(param_1[7] + 0x48);
      sVar2 = asStack_8c[lVar5];
      uVar9 = sVar2 - *(short *)(lVar7 + 0xc + lVar5 * 2);
      if (uVar9 != 0) {
        piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0xdc + lVar5 * 4);
        *piVar1 = *piVar1 + (uint)uVar9;
        *(short *)(lVar7 + 0xc + lVar5 * 2) = sVar2;
      }
      iVar8 = iVar8 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)stack0xffffffffffffff84 - *(short *)(lVar7 + 0x1c);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0xfc);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x1c) = (short)stack0xffffffffffffff84;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_7a - *(short *)(lVar7 + 0x1e);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x38);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x1e) = sStack_7a;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_74 - *(short *)(lVar7 + 0x24);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x104);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x24) = (short)local_74;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_72 - *(short *)(lVar7 + 0x26);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x108);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x26) = sStack_72;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_70 - *(short *)(lVar7 + 0x28);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x10c);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x28) = (short)local_70;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_6e - *(short *)(lVar7 + 0x2a);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x110);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x2a) = sStack_6e;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_6c - *(short *)(lVar7 + 0x2c);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x114);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x2c) = (short)local_6c;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_6a - *(short *)(lVar7 + 0x2e);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x118);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x2e) = sStack_6a;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_20 - *(short *)(lVar7 + 0x78);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x298);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x78) = (short)local_20;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = local_1a - *(short *)(lVar7 + 0x7e);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x29c);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x7e) = local_1a;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_68 - *(short *)(lVar7 + 0x30);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x11c);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x30) = (short)local_68;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_66 - *(short *)(lVar7 + 0x32);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x120);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x32) = sStack_66;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_64 - *(short *)(lVar7 + 0x34);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x124);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x34) = (short)local_64;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_62 - *(short *)(lVar7 + 0x36);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x128);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x36) = sStack_62;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_60 - *(short *)(lVar7 + 0x38);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 300);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x38) = (short)local_60;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_5e - *(short *)(lVar7 + 0x3a);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x130);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x3a) = sStack_5e;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_5c - *(short *)(lVar7 + 0x3c);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x134);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x3c) = (short)local_5c;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_5a - *(short *)(lVar7 + 0x3e);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x138);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x3e) = sStack_5a;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_58 - *(short *)(lVar7 + 0x40);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x13c);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x40) = (short)local_58;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_56 - *(short *)(lVar7 + 0x42);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x140);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x42) = sStack_56;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_54 - *(short *)(lVar7 + 0x44);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x144);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x44) = (short)local_54;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_52 - *(short *)(lVar7 + 0x46);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x148);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x46) = sStack_52;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_50 - *(short *)(lVar7 + 0x48);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x14c);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x48) = (short)local_50;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_4e - *(short *)(lVar7 + 0x4a);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x150);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x4a) = sStack_4e;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_4c - *(short *)(lVar7 + 0x4c);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x154);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x4c) = (short)local_4c;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_4a - *(short *)(lVar7 + 0x4e);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x158);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x4e) = sStack_4a;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_48 - *(short *)(lVar7 + 0x50);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x15c);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x50) = (short)local_48;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_46 - *(short *)(lVar7 + 0x52);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x160);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x52) = sStack_46;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_44 - *(short *)(lVar7 + 0x54);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x164);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x54) = (short)local_44;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_42 - *(short *)(lVar7 + 0x56);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x168);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x56) = sStack_42;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = local_3e - *(short *)(lVar7 + 0x5a);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x16c);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x5a) = local_3e;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_3c - *(short *)(lVar7 + 0x5c);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x170);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x5c) = (short)local_3c;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_3a - *(short *)(lVar7 + 0x5e);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x174);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x5e) = sStack_3a;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_38 - *(short *)(lVar7 + 0x60);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x178);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x60) = (short)local_38;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_36 - *(short *)(lVar7 + 0x62);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x17c);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x62) = sStack_36;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_34 - *(short *)(lVar7 + 100);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x180);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 100) = (short)local_34;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_32 - *(short *)(lVar7 + 0x66);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x184);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x66) = sStack_32;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_30 - *(short *)(lVar7 + 0x68);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x188);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x68) = (short)local_30;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_2e - *(short *)(lVar7 + 0x6a);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x18c);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x6a) = sStack_2e;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_2c - *(short *)(lVar7 + 0x6c);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 400);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x6c) = (short)local_2c;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_2a - *(short *)(lVar7 + 0x6e);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x194);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x6e) = sStack_2a;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_28 - *(short *)(lVar7 + 0x70);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x198);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x70) = (short)local_28;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_26 - *(short *)(lVar7 + 0x72);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x19c);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x72) = sStack_26;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_24 - *(short *)(lVar7 + 0x74);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x1a0);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x74) = (short)local_24;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_22 - *(short *)(lVar7 + 0x76);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x1a4);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x76) = sStack_22;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_1e - *(short *)(lVar7 + 0x7a);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x218);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x7a) = sStack_1e;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = (short)local_78 - *(short *)(lVar7 + 0x20);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x28c);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x20) = (short)local_78;
    }
    lVar7 = *(long *)(param_1[7] + 0x48);
    uVar9 = sStack_76 - *(short *)(lVar7 + 0x22);
    if (uVar9 != 0) {
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x290);
      *piVar1 = *piVar1 + (uint)uVar9;
      *(short *)(lVar7 + 0x22) = sStack_76;
    }
    iVar6 = 0;
    lVar7 = *(long *)(*param_1 + 0xa0);
    *(int *)(lVar7 + 0x1c0) = *(int *)(lVar7 + 0x130) - *(int *)(lVar7 + 0x9c);
    lVar7 = *(long *)(*param_1 + 0xa0);
    *(int *)(lVar7 + 0x1d4) = *(int *)(lVar7 + 0x110) - *(int *)(lVar7 + 0xa0);
    lVar7 = *(long *)(*param_1 + 0xa0);
    *(int *)(lVar7 + 0x1c4) =
         (*(int *)(lVar7 + 200) - *(int *)(lVar7 + 0x130)) - *(int *)(lVar7 + 0xa4);
    do {
      plVar4 = *(long **)(param_1[5] + (long)iVar6 * 8);
      if (plVar4 != (long *)0x0) {
        piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x20);
        *piVar1 = *piVar1 + (int)plVar4[3];
        piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x50);
        *piVar1 = *piVar1 + *(int *)((long)plVar4 + 0x14);
        piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x68);
        *piVar1 = *piVar1 + (int)plVar4[2];
        (**(code **)(*plVar4 + 0x110))();
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 != 6);
    lVar7 = *(long *)(*param_1 + 0xa0);
    *(int *)(lVar7 + 0x10) =
         *(int *)(lVar7 + 0x24) + *(int *)(lVar7 + 0x20) + *(int *)(lVar7 + 0x34) +
         *(int *)(lVar7 + 0x28) + *(int *)(lVar7 + 0xa8) + *(int *)(lVar7 + 0xac) +
         *(int *)(lVar7 + 0xb0);
    lVar7 = *(long *)(*param_1 + 0xa0);
    *(int *)(lVar7 + 0x48) =
         *(int *)(lVar7 + 0x50) + *(int *)(lVar7 + 0x80) + *(int *)(lVar7 + 0x60) +
         *(int *)(lVar7 + 100) + *(int *)(lVar7 + 0x68) + *(int *)(lVar7 + 0x6c) +
         *(int *)(lVar7 + 0x74);
    iVar6 = 0;
    do {
      lVar7 = (long)iVar6;
      iVar6 = iVar6 + 1;
      piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x48);
      *piVar1 = *piVar1 + *(int *)(*(long *)(*param_1 + 0xa0) + 0x84 + lVar7 * 4);
    } while (iVar6 != 6);
  }
  return;
}

