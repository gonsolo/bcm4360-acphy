
undefined8 FUN_00110126(long param_1,undefined8 param_2,int param_3,char param_4)

{
  undefined4 uVar1;
  undefined8 uVar2;
  uint uVar3;
  ushort uVar4;
  undefined4 local_3c [3];
  
  local_3c[0] = 0;
  uVar4 = *(ushort *)(param_1 + 0x6e);
  if ((*(ushort *)(param_1 + 0x6a) - 1 & uVar4 + 1) == (uint)*(ushort *)(param_1 + 0x6c)) {
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
    *(undefined4 *)(param_1 + 8) = 0;
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = 0;
    if (param_3 != 0) {
      uVar1 = osl_dma_map(*(undefined8 *)(param_1 + 0x30),param_2,param_3,1,0,
                          (ulong)uVar4 * 0x90 + *(long *)(param_1 + 0x80));
      local_3c[0] = 0xe0000000;
      if ((uint)uVar4 == *(ushort *)(param_1 + 0x6a) - 1) {
        local_3c[0] = 0xf0000000;
      }
      FUN_0010ea38(param_1,*(undefined8 *)(param_1 + 0x58),uVar1,uVar4,local_3c,param_3);
      *(undefined8 *)(*(long *)(param_1 + 0x70) + (ulong)uVar4 * 8) = param_2;
      uVar4 = *(short *)(param_1 + 0x6a) - 1U & uVar4 + 1;
      *(ushort *)(param_1 + 0x6e) = uVar4;
      if (param_4 != '\0') {
        osl_writel((uint)uVar4 * 0x10 + *(int *)(param_1 + 0xa0),*(long *)(param_1 + 0x48) + 4);
      }
      uVar3 = *(ushort *)(param_1 + 0x6a) - 1;
      uVar2 = 0;
      *(uint *)(param_1 + 8) =
           uVar3 - ((uint)*(ushort *)(param_1 + 0x6e) - (uint)*(ushort *)(param_1 + 0x6c) & uVar3);
    }
  }
  return uVar2;
}

