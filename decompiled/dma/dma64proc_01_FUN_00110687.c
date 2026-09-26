
void FUN_00110687(long param_1)

{
  undefined8 uVar1;
  uint uVar2;
  uint uVar3;
  
  if (*(short *)(param_1 + 0x6a) != 0) {
    *(undefined2 *)(param_1 + 0x12a) = 0;
    *(undefined2 *)(param_1 + 0x6e) = 0;
    *(undefined2 *)(param_1 + 0x6c) = 0;
    *(uint *)(param_1 + 8) = *(ushort *)(param_1 + 0x6a) - 1;
    osl_memset(*(undefined8 *)(param_1 + 0x58),0,(ulong)*(ushort *)(param_1 + 0x6a) << 4);
    uVar2 = osl_readl(*(undefined8 *)(param_1 + 0x48));
    osl_writel(((uVar2 & 0xffe3ff3f | (uint)*(byte *)(param_1 + 0x106) << 0x12) & 0xff1fffff |
                (uint)*(byte *)(param_1 + 0x107) << 6 | (uint)*(byte *)(param_1 + 0x108) << 0x15) &
               0xfcffffff | (uint)*(byte *)(param_1 + 0x109) << 0x18,*(undefined8 *)(param_1 + 0x48)
              );
    if (*(char *)(param_1 + 0x104) == '\0') {
      FUN_0010f3af(param_1,1,*(undefined8 *)(param_1 + 0x88));
    }
    uVar2 = *(uint *)(param_1 + 0xc);
    uVar1 = *(undefined8 *)(param_1 + 0x48);
    uVar3 = osl_readl(uVar1);
    osl_writel(uVar3 | (-(uint)((uVar2 & 1) == 0) & 0x800) + 1,uVar1);
    if (*(char *)(param_1 + 0x104) != '\0') {
      FUN_0010f3af(param_1,1,*(undefined8 *)(param_1 + 0x88));
    }
  }
  return;
}

