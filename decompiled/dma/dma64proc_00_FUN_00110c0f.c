
void FUN_00110c0f(long param_1)

{
  if (*(long *)(param_1 + 0x58) != 0) {
    osl_dma_free_consistent
              (*(undefined8 *)(param_1 + 0x30),
               *(long *)(param_1 + 0x58) - (ulong)*(ushort *)(param_1 + 0x98),
               *(undefined4 *)(param_1 + 0x9c),*(undefined8 *)(param_1 + 0x90));
  }
  if (*(long *)(param_1 + 0x60) != 0) {
    osl_dma_free_consistent
              (*(undefined8 *)(param_1 + 0x30),
               *(long *)(param_1 + 0x60) - (ulong)*(ushort *)(param_1 + 0xd8),
               *(undefined4 *)(param_1 + 0xdc),*(undefined8 *)(param_1 + 0xd0));
  }
  if (*(long *)(param_1 + 0x70) != 0) {
    osl_mfree(*(undefined8 *)(param_1 + 0x30),*(long *)(param_1 + 0x70),
              (ulong)*(ushort *)(param_1 + 0x6a) << 3);
  }
  if (*(long *)(param_1 + 0xb0) != 0) {
    osl_mfree(*(undefined8 *)(param_1 + 0x30),*(long *)(param_1 + 0xb0),
              (ulong)*(ushort *)(param_1 + 0xa4) << 3);
  }
  if (*(long *)(param_1 + 0x80) != 0) {
    osl_mfree(*(undefined8 *)(param_1 + 0x30),*(long *)(param_1 + 0x80),
              (uint)*(ushort *)(param_1 + 0x6a) * 0x90);
  }
  if (*(long *)(param_1 + 0xc0) != 0) {
    osl_mfree(*(undefined8 *)(param_1 + 0x30),*(long *)(param_1 + 0xc0),
              (uint)*(ushort *)(param_1 + 0xa4) * 0x90);
  }
  osl_mfree(*(undefined8 *)(param_1 + 0x30),param_1,0x130);
  return;
}

