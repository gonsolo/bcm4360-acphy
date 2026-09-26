
void si_pci_sleep(long param_1)

{
  do_4360_pcie2_war = 0;
  pcicore_sleep(*(undefined8 *)(param_1 + 0x90));
  return;
}

