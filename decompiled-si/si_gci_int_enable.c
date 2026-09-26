
void si_gci_int_enable(undefined8 param_1,char param_2)

{
  FUN_00122a5d(param_1,0x24,0x10,~-(param_2 == '\0') & 0x10);
  return;
}

