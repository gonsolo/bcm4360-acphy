
void si_deregister_intr_callback(long param_1)

{
  *(undefined8 *)(param_1 + 0x78) = 0;
  return;
}

