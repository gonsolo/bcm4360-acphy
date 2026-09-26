
undefined8 si_gci_init(long param_1)

{
  if ((*(byte *)(param_1 + 0x1c) & 4) != 0) {
    si_gci_reset();
    si_gci_direct(param_1,0xd74,0xff00,0xff00);
  }
  return 0;
}

