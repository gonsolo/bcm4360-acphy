
void FUN_0010f330(long param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = *(uint *)(param_1 + 0xc);
  uVar3 = osl_readl(*(undefined8 *)(param_1 + 0x50));
  uVar2 = uVar3 & 0x30000 | 1;
  if ((uVar1 & 1) == 0) {
    uVar2 = uVar3 & 0x30000 | 0x801;
  }
  uVar3 = uVar2 | 0x400;
  if ((uVar1 & 2) == 0) {
    uVar3 = uVar2;
  }
  osl_writel((uint)*(byte *)(param_1 + 0x10b) << 0x18 | *(int *)(param_1 + 0xf0) * 2 |
             (uVar3 | (*(byte *)(param_1 + 0x105) & 0x3fc7) << 0x12 |
             (uint)*(byte *)(param_1 + 0x10a) << 0x15) & 0xfcffffff,*(undefined8 *)(param_1 + 0x50))
  ;
  return;
}

