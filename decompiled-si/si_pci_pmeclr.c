
void si_pci_pmeclr(long param_1)

{
  pcicore_pmeclr(*(undefined8 *)(param_1 + 0x90));
  return;
}

