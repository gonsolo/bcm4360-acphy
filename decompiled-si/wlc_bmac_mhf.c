
void wlc_bmac_mhf(long param_1,byte param_2,ushort param_3,ushort param_4,int param_5)

{
  ushort uVar1;
  long lVar2;
  ushort uVar3;
  ushort uVar4;
  ulong uVar5;
  bool bVar6;
  undefined2 local_38 [8];
  
  uVar5 = (ulong)param_2;
  if (param_5 == 1) {
    lVar2 = *(long *)(param_1 + 0xf8);
  }
  else {
    if (param_5 < 2) {
      bVar6 = param_5 == 0;
    }
    else {
      if (param_5 == 2) {
        lVar2 = *(long *)(param_1 + 0xf0);
        goto LAB_00163726;
      }
      bVar6 = param_5 == 3;
    }
    if (!bVar6) goto LAB_00163790;
    lVar2 = *(long *)(param_1 + 0xe8);
  }
LAB_00163726:
  if (lVar2 != 0) {
    uVar1 = *(ushort *)(lVar2 + 8 + uVar5 * 2);
    uVar3 = ~param_3 & uVar1;
    uVar4 = uVar3 | param_4;
    *(ushort *)(lVar2 + 8 + uVar5 * 2) = uVar4;
    if (((*(char *)(param_1 + 0x186) != '\0') && (uVar4 != uVar1)) &&
       (lVar2 == *(long *)(param_1 + 0xe8))) {
      local_38[0] = 0x5e;
      local_38[1] = 0x60;
      local_38[2] = 0x62;
      local_38[3] = 0x78;
      local_38[4] = 0xd4;
      wlc_bmac_write_shm(param_1,local_38[uVar5],uVar3 | param_4);
    }
  }
LAB_00163790:
  if (param_5 == 3) {
    *(ushort *)(*(long *)(param_1 + 0xf0) + 8 + uVar5 * 2) =
         ~param_3 & *(ushort *)(*(long *)(param_1 + 0xf0) + 8 + uVar5 * 2) | param_4;
    *(ushort *)(*(long *)(param_1 + 0xf8) + 8 + uVar5 * 2) =
         ~param_3 & *(ushort *)(*(long *)(param_1 + 0xf8) + 8 + uVar5 * 2) | param_4;
  }
  return;
}

