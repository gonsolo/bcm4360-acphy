
bool wlc_bmac_tx_fifo_suspended(long param_1,uint param_2)

{
  char cVar1;
  uint uVar2;
  bool bVar3;
  
  cVar1 = (**(code **)(**(long **)(param_1 + 0x20 + (ulong)param_2 * 8) + 0x30))();
  bVar3 = false;
  if (cVar1 != '\0') {
    uVar2 = osl_readl(*(long *)(param_1 + 0xd0) + 0x150);
    bVar3 = (uVar2 & 1 << ((byte)param_2 & 0x1f)) == 0;
  }
  return bVar3;
}

