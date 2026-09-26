
void FUN_0019173d(long param_1)

{
  long lVar1;
  byte bVar2;
  byte *pbVar3;
  bool bVar4;
  
  lVar1 = *(long *)(param_1 + 0x138);
  pbVar3 = (byte *)(lVar1 + 0x65f);
  if (*(long *)(lVar1 + 0x8a8) != 0) {
    pbVar3 = (byte *)(*(long *)(lVar1 + 0x8a8) + 0x10);
  }
  if (*(int *)(lVar1 + 0x8b0) != 0) {
    bVar4 = false;
    if ((*(uint *)(param_1 + 0x19c) & 0x206) != 0) {
      bVar4 = *(char *)(param_1 + 0x240) != (char)*(undefined2 *)(param_1 + 0x17e);
    }
    if ((!bVar4) && ((*(ushort *)(param_1 + 0x17e) & 0xc000) != 0xc000)) {
      bVar2 = *(byte *)(lVar1 + 0x8b4);
      if (*(byte *)(lVar1 + 0x8b4) <= *pbVar3) {
        bVar2 = *pbVar3;
      }
      *(byte *)(lVar1 + 0x668) = bVar2;
      bVar2 = *(byte *)(lVar1 + 0x8b5);
      if (*(byte *)(lVar1 + 0x8b5) <= pbVar3[1]) {
        bVar2 = pbVar3[1];
      }
      *(byte *)(lVar1 + 0x669) = bVar2;
      bVar2 = *(byte *)(lVar1 + 0x8b6);
      if (*(byte *)(lVar1 + 0x8b6) <= pbVar3[2]) {
        bVar2 = pbVar3[2];
      }
      *(byte *)(lVar1 + 0x66a) = bVar2;
      bVar2 = *(byte *)(lVar1 + 0x8b7);
      if (*(byte *)(lVar1 + 0x8b7) <= pbVar3[3]) {
        bVar2 = pbVar3[3];
      }
      *(byte *)(lVar1 + 0x66b) = bVar2;
      bVar2 = *(byte *)(lVar1 + 0x8b8);
      if (*(byte *)(lVar1 + 0x8b8) <= pbVar3[4]) {
        bVar2 = pbVar3[4];
      }
      *(byte *)(lVar1 + 0x66c) = bVar2;
      bVar2 = *(byte *)(lVar1 + 0x8b9);
      if (*(byte *)(lVar1 + 0x8b9) <= pbVar3[5]) {
        bVar2 = pbVar3[5];
      }
      *(byte *)(lVar1 + 0x66d) = bVar2;
      bVar2 = *(byte *)(lVar1 + 0x8ba);
      if (*(byte *)(lVar1 + 0x8ba) <= pbVar3[6]) {
        bVar2 = pbVar3[6];
      }
      *(byte *)(lVar1 + 0x66e) = bVar2;
      bVar2 = *(byte *)(lVar1 + 0x8bb);
      if (*(byte *)(lVar1 + 0x8bb) <= pbVar3[7]) {
        bVar2 = pbVar3[7];
      }
      *(byte *)(lVar1 + 0x66f) = bVar2;
      *(byte *)(lVar1 + 0x670) = *(byte *)(lVar1 + 0x8bc) | pbVar3[8];
      goto LAB_0019186e;
    }
  }
  osl_memcpy(lVar1 + 0x668,pbVar3,9);
LAB_0019186e:
  if (((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) && (-1 < *(short *)(lVar1 + 0x914))) {
    *(undefined1 *)(lVar1 + 0x66e) = 1;
  }
  if (((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000) && (-1 < *(short *)(lVar1 + 0x916))) {
    *(undefined1 *)(lVar1 + 0x66e) = 1;
  }
  return;
}

