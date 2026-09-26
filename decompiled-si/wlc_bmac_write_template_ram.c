
void wlc_bmac_write_template_ram(long param_1,undefined4 param_2,int param_3,long param_4)

{
  long lVar1;
  uint uVar2;
  uint local_3c [3];
  
  lVar1 = *(long *)(param_1 + 0xd0);
  osl_writel(param_2,lVar1 + 0x130);
  uVar2 = osl_readl(lVar1 + 0x120);
  for (; 0 < param_3; param_3 = param_3 + -4) {
    osl_memcpy(local_3c,param_4,4);
    if ((uVar2 & 0x10000) != 0) {
      local_3c[0] = local_3c[0] >> 0x18 | local_3c[0] << 0x18 | (local_3c[0] & 0xff00) << 8 |
                    (local_3c[0] & 0xff0000) >> 8;
    }
    param_4 = param_4 + 4;
    osl_writel(local_3c[0],lVar1 + 0x134);
  }
  return;
}

