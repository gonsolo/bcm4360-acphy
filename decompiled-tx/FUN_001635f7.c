
void FUN_001635f7(long param_1,undefined8 param_2,uint param_3)

{
  uint uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0xd0) + 0x124;
  wlc_bmac_write_template_ram
            (param_1,(-(uint)(*(uint *)(param_1 + 0x84) < 0x28) & 0xffffffe8) + 0x480,
             param_3 + 3 & 0xfffffffc,param_2);
  wlc_bmac_write_shm(param_1,0x1a,param_3 & 0xffff);
  uVar1 = osl_readl(lVar2);
  osl_writel(uVar1 | 2,lVar2);
  return;
}

