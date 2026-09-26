
undefined8 FUN_0010f9b6(long param_1,char param_2)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  long lVar6;
  
  if (*(short *)(param_1 + 0xa4) == 0) {
LAB_0010fb3e:
    uVar5 = 0;
  }
  else {
    uVar1 = *(ushort *)(param_1 + 0xa6);
    if (*(char *)(param_1 + 0x40) == '\0') {
      if (uVar1 == *(ushort *)(param_1 + 0xa8)) goto LAB_0010fb3e;
      if (uVar1 == *(ushort *)(param_1 + 0x128)) {
        uVar3 = osl_readl(*(long *)(param_1 + 0x50) + 0xc);
        uVar2 = (ushort)((uVar3 & 0xfff) >> 3);
        *(ushort *)(param_1 + 0x128) = uVar2;
        if ((uVar1 == uVar2) && (param_2 == '\0')) goto LAB_0010fb3e;
      }
      lVar6 = (ulong)uVar1 * 8;
      puVar4 = (undefined8 *)(lVar6 + *(long *)(param_1 + 0xb0));
      uVar5 = *puVar4;
      *puVar4 = 0;
      osl_dma_unmap(*(undefined8 *)(param_1 + 0x30),
                    *(int *)(lVar6 + *(long *)(param_1 + 0x60) + 4) - *(int *)(param_1 + 0xfc),
                    *(undefined2 *)(param_1 + 0xe4),2);
      *(undefined4 *)(lVar6 + *(long *)(param_1 + 0x60) + 4) = 0xdeadbeef;
    }
    else {
      if (uVar1 == *(ushort *)(param_1 + 0xa8)) goto LAB_0010fb3e;
      if (uVar1 == *(ushort *)(param_1 + 0x128)) {
        uVar3 = osl_readl(*(long *)(param_1 + 0x50) + 0x10);
        uVar2 = (ushort)(((uVar3 & *(uint *)(param_1 + 0x124)) - *(int *)(param_1 + 0xe0) &
                         *(uint *)(param_1 + 0x124)) >> 4);
        *(ushort *)(param_1 + 0x128) = uVar2;
        if ((uVar1 == uVar2) && (param_2 == '\0')) goto LAB_0010fb3e;
      }
      puVar4 = (undefined8 *)((ulong)uVar1 * 8 + *(long *)(param_1 + 0xb0));
      lVar6 = (ulong)uVar1 * 0x10;
      uVar5 = *puVar4;
      *puVar4 = 0;
      osl_dma_unmap(*(undefined8 *)(param_1 + 0x30),
                    *(int *)(lVar6 + *(long *)(param_1 + 0x60) + 8) - *(int *)(param_1 + 0xfc),
                    *(undefined2 *)(param_1 + 0xe4),2);
      *(undefined4 *)(lVar6 + *(long *)(param_1 + 0x60) + 8) = 0xdeadbeef;
      *(undefined4 *)(lVar6 + *(long *)(param_1 + 0x60) + 0xc) = 0xdeadbeef;
    }
    *(ushort *)(param_1 + 0xa6) = (short)*(undefined4 *)(param_1 + 0xa4) - 1U & uVar1 + 1;
  }
  return uVar5;
}

