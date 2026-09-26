
void wlc_bmac_rm_cca_measure(long param_1,int param_2)

{
  uint uVar1;
  long lVar2;
  
  wlc_bmac_write_ihr(param_1,0x133,0x4000);
  wlc_bmac_write_ihr(param_1,0x134,param_2 * 8 & 0xffff);
  wlc_bmac_write_ihr(param_1,0x135,(uint)(param_2 * 8) >> 0x10);
  lVar2 = *(long *)(param_1 + 0xd0) + 0x124;
  uVar1 = osl_readl(lVar2);
  osl_writel(uVar1 | 8,lVar2);
  return;
}

