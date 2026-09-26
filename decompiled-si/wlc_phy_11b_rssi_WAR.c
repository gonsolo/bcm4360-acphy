
undefined4 wlc_phy_11b_rssi_WAR(long param_1,long param_2)

{
  ushort uVar1;
  long lVar2;
  uint uVar3;
  int iVar4;
  ushort uVar5;
  char cVar6;
  ushort uVar7;
  undefined4 in_R10D;
  
  lVar2 = *(long *)(param_1 + 0x138);
  uVar5 = *(ushort *)(param_2 + 10) & 0xff;
  uVar3 = *(ushort *)(param_2 + 10) & 0xff00;
  uVar7 = uVar5 | (ushort)uVar3;
  uVar1 = *(ushort *)(param_2 + 0xc);
  if (*(char *)(lVar2 + 0x460) == '\x01') {
    cVar6 = *(char *)(lVar2 + 0x45e) - *(char *)(lVar2 + 0x45f);
    if ((uVar1 & 1) == 0) {
      cVar6 = *(char *)(lVar2 + 0x45e);
    }
  }
  else {
    cVar6 = '\0';
    if ((uVar1 & 1) != 0) {
      cVar6 = -*(char *)(lVar2 + 0x45f);
    }
  }
  iVar4 = -(((ushort)((short)(uVar1 & 0xff | (ushort)*(byte *)(param_2 + 9) << 8) >> 2) & 0xf) *
           CONCAT31((int3)((uint)in_R10D >> 8),3));
  iVar4 = CONCAT31((int3)((uint)iVar4 >> 8),
                   (char)iVar4 - *(char *)(lVar2 + 0x474 + (ulong)(uVar5 & 7))) + 2;
  return CONCAT31((int3)((uint)iVar4 >> 8),
                  (((((char)iVar4 -
                     *(char *)(lVar2 + 0x47e + (ulong)((ushort)((short)uVar7 >> 3) & 7))) -
                    *(char *)(lVar2 + 0x488 + (ulong)((ushort)((short)uVar7 >> 6) & 0xf))) -
                   *(char *)(lVar2 + 0x492 + (ulong)((ushort)((short)uVar7 >> 10) & 7))) -
                  *(char *)(lVar2 + 0x49c + (long)(char)((byte)(uVar3 >> 8) >> 5))) - cVar6);
}

