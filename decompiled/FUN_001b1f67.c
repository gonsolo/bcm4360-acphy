
void FUN_001b1f67(long param_1,long param_2)

{
  ushort *puVar1;
  int iVar2;
  long lVar3;
  byte bVar4;
  char cVar5;
  ushort uVar6;
  char cVar7;
  char cVar8;
  char local_48 [24];
  
  lVar3 = *(long *)(param_1 + 0xf58);
  local_48[0] = '\x14';
  local_48[1] = 0x1e;
  local_48[2] = 0x14;
  for (bVar4 = 0; bVar4 < *(byte *)(param_1 + 0x168); bVar4 = bVar4 + 1) {
    *(undefined1 *)(lVar3 + 0x65 + (ulong)bVar4) = 0;
  }
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  cVar7 = 'P';
  if (uVar6 != 0x2000) {
    cVar7 = '\x14';
    if (uVar6 == 0x1800) {
      cVar7 = '(';
    }
  }
  iVar2 = *(int *)(param_1 + 0x164);
  if ((((iVar2 == 5) || (iVar2 == 2)) || (iVar2 == 6)) || (bVar4 = 0, iVar2 == 3)) {
    FUN_001b1195(param_1,param_2);
  }
  else {
    for (; bVar4 < *(byte *)(param_1 + 0x168); bVar4 = bVar4 + 1) {
      if (*(int *)(param_1 + 0x164) == 1) {
        cVar8 = (-(bVar4 == 0) & 0xf6U) + 0x1e;
        cVar5 = wlc_phy_get_chan_freq_range_acphy(param_1,0);
        if (cVar5 == '\x04') {
          cVar8 = local_48[bVar4];
        }
      }
      else if (((((*(char *)(param_1 + 0x16e) == '\x01') &&
                 (cVar8 = *(char *)(param_1 + 0x16c), 2 < (byte)(cVar8 - 2U))) &&
                ((cVar8 != '\x12' && ((cVar8 != '\x18' && (cVar8 != '\x1a')))))) && (cVar8 != '\"'))
              && (cVar8 != '\b')) {
        cVar8 = '\x01';
        if (((*(ushort *)(param_1 + 0x17e) & 0xc000) != 0) && (cVar8 = '\0', cVar7 != '\x14')) {
          cVar8 = (cVar7 == '(') * '\x05' + '\n';
        }
      }
      else {
        cVar8 = '\x1e';
      }
      lVar3 = param_2 + (ulong)bVar4 * 10;
      FUN_001993cf(param_1,lVar3,(int)cVar8);
      if (((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000) &&
         (*(char *)(param_1 + 0x16e) == '\x01')) {
        puVar1 = (ushort *)(lVar3 + 2);
        *puVar1 = *puVar1 | 0xff;
      }
    }
  }
  return;
}

