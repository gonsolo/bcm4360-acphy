
undefined8
FUN_0018f6f1(long param_1,uint param_2,undefined4 *param_3,undefined8 *param_4,undefined8 *param_5,
            undefined8 *param_6,undefined8 *param_7)

{
  char cVar1;
  ushort uVar2;
  ulong uVar3;
  byte bVar4;
  undefined1 *puVar5;
  ushort *puVar6;
  undefined1 *puVar7;
  undefined1 *puVar8;
  uint uVar9;
  uint uVar10;
  long lVar11;
  ushort *local_40;
  ushort *local_38;
  
  cVar1 = *(char *)(param_1 + 0x16e);
  lVar11 = *(long *)(param_1 + 0x138);
  if (cVar1 == '\x01') {
    switch(*(undefined1 *)(param_1 + 0x16c)) {
    case 0x10:
    case 0x11:
    case 0x17:
      cVar1 = *(char *)(lVar11 + 0x8e4);
      if (*(int *)(param_1 + 0xc24) == 40000000) {
        *(char *)(lVar11 + 0x8e7) = cVar1;
        if (((byte)(cVar1 - 2U) < 2) ||
           ((*(char *)(lVar11 + 0x8e5) == '\x01' && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0)))
           ) {
LAB_0018f865:
          puVar5 = chan_tuning_2069rev_GE16_40_lp;
        }
        else {
          puVar5 = chan_tuning_2069rev_16_17_40;
        }
      }
      else {
        *(char *)(lVar11 + 0x8e7) = cVar1;
        if (((byte)(cVar1 - 2U) < 2) ||
           ((*(char *)(lVar11 + 0x8e5) == '\x01' && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0)))
           ) {
LAB_0018f853:
          puVar5 = chan_tuning_2069rev_GE16_lp;
        }
        else {
          puVar5 = chan_tuning_2069rev_16_17;
        }
      }
      break;
    case 0x12:
    case 0x18:
      cVar1 = *(char *)(lVar11 + 0x8e4);
      if (*(int *)(param_1 + 0xc24) == 40000000) {
        *(char *)(lVar11 + 0x8e7) = cVar1;
        if (((byte)(cVar1 - 2U) < 2) ||
           ((*(char *)(lVar11 + 0x8e5) == '\x01' && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0)))
           ) goto LAB_0018f865;
        puVar5 = chan_tuning_2069rev_18_40;
      }
      else {
        *(char *)(lVar11 + 0x8e7) = cVar1;
        if (((byte)(cVar1 - 2U) < 2) ||
           ((*(char *)(lVar11 + 0x8e5) == '\x01' && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0)))
           ) goto LAB_0018f853;
        puVar5 = chan_tuning_2069rev_18;
      }
      break;
    default:
      goto switchD_0018f76e_caseD_13;
    case 0x19:
    case 0x1a:
      cVar1 = *(char *)(lVar11 + 0x8e4);
      if (*(int *)(param_1 + 0xc24) == 40000000) {
        *(char *)(lVar11 + 0x8e7) = cVar1;
        if (((byte)(cVar1 - 2U) < 2) ||
           ((*(char *)(lVar11 + 0x8e5) == '\x01' && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0)))
           ) {
          puVar7 = chan_tuning_2069rev_GE_25_40MHz_lp;
        }
        else {
          puVar7 = chan_tuning_2069rev_GE_25_40MHz;
        }
      }
      else {
        *(char *)(lVar11 + 0x8e7) = cVar1;
        if (((byte)(cVar1 - 2U) < 2) ||
           ((*(char *)(lVar11 + 0x8e5) == '\x01' && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0)))
           ) {
          puVar7 = chan_tuning_2069rev_GE_25_lp;
        }
        else {
          puVar7 = chan_tuning_2069rev_GE_25;
        }
      }
      uVar10 = 0x4d;
      puVar8 = (undefined1 *)0x0;
      *(undefined1 *)(lVar11 + 0x8e6) = *(undefined1 *)(lVar11 + 0x8e4);
      goto LAB_0018f973;
    }
    uVar10 = 0x4d;
    puVar8 = (undefined1 *)0x0;
    *(undefined1 *)(lVar11 + 0x8e6) = *(undefined1 *)(lVar11 + 0x8e4);
    puVar7 = (undefined1 *)0x0;
  }
  else {
    if (cVar1 == '\0') {
      bVar4 = *(char *)(param_1 + 0x16c) - 3;
      if (bVar4 < 6) {
        puVar8 = (undefined1 *)0x0;
        puVar7 = (undefined1 *)0x0;
        puVar6 = (ushort *)(&PTR_chan_tuning_2069rev3_00559de0)[bVar4];
        uVar10 = *(uint *)(&DAT_00559e10 + (ulong)bVar4 * 4);
        puVar5 = (undefined1 *)0x0;
        goto LAB_0018f977;
      }
switchD_0018f76e_caseD_13:
      uVar10 = 0;
      puVar8 = (undefined1 *)0x0;
    }
    else {
      if (((cVar1 != '\x02') || (0x26 < *(byte *)(param_1 + 0x16c))) ||
         ((1L << (*(byte *)(param_1 + 0x16c) & 0x3f) & 0x6f00000000U) == 0))
      goto switchD_0018f76e_caseD_13;
      puVar8 = chan_tuning_2069_rev33_37;
      uVar10 = 0x4d;
      if (*(int *)(param_1 + 0xc24) == 40000000) {
        puVar8 = (undefined1 *)&chan_tuning_2069_rev33_37_40;
      }
    }
    puVar7 = (undefined1 *)0x0;
LAB_0018f973:
    puVar5 = (undefined1 *)0x0;
  }
  puVar6 = (ushort *)0x0;
LAB_0018f977:
  lVar11 = 0;
  uVar9 = 0;
  local_40 = puVar6;
  local_38 = (ushort *)puVar7;
  do {
    if (uVar10 <= uVar9) {
      *param_3 = 0;
      return 0;
    }
    if (*(char *)(param_1 + 0x16e) == '\x02') {
      if (*(ushort *)((long)puVar8 + lVar11) == param_2) {
        *param_7 = (undefined2 *)((long)puVar8 + (ulong)uVar9 * 0x2f * 2);
        uVar3 = (ulong)(ushort)((undefined2 *)((long)puVar8 + (ulong)uVar9 * 0x2f * 2))[1];
        goto LAB_0018fa38;
      }
    }
    else if (*(char *)(param_1 + 0x16e) == '\x01') {
      if ((byte)(*(char *)(param_1 + 0x16c) - 0x19U) < 2) {
        uVar2 = *local_38;
      }
      else {
        uVar2 = *(ushort *)(puVar5 + lVar11);
      }
      if (uVar2 == param_2) {
        if ((byte)(*(char *)(param_1 + 0x16c) - 0x19U) < 2) {
          *param_6 = (ushort *)((long)puVar7 + (ulong)uVar9 * 0x30 * 2);
          uVar3 = (ulong)((ushort *)((long)puVar7 + (ulong)uVar9 * 0x30 * 2))[1];
        }
        else {
          *param_5 = puVar5 + (ulong)uVar9 * 0x5e;
          uVar3 = (ulong)*(ushort *)(puVar5 + (ulong)uVar9 * 0x5e + 2);
        }
LAB_0018fa38:
        *param_3 = (int)uVar3;
        return CONCAT71((int7)(uVar3 >> 8),1);
      }
    }
    else if (*local_40 == param_2) {
      *param_4 = puVar6 + (ulong)uVar9 * 0x3a;
      uVar3 = (ulong)(puVar6 + (ulong)uVar9 * 0x3a)[1];
      goto LAB_0018fa38;
    }
    local_40 = local_40 + 0x3a;
    local_38 = local_38 + 0x30;
    uVar9 = uVar9 + 1;
    lVar11 = lVar11 + 0x5e;
  } while( true );
}

