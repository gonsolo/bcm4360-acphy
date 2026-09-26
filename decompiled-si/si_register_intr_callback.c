
void si_register_intr_callback
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5)

{
  *(undefined8 *)(param_1 + 0x70) = param_5;
  *(undefined8 *)(param_1 + 0x78) = param_2;
  *(undefined8 *)(param_1 + 0x80) = param_3;
  *(undefined8 *)(param_1 + 0x88) = param_4;
  *(undefined4 *)(param_1 + 0x68) =
       *(undefined4 *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4);
  return;
}

