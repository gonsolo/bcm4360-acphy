
void dma_txpioloopback(undefined8 param_1,undefined8 param_2)

{
  uint uVar1;
  
  uVar1 = osl_readl(param_2);
  osl_writel(uVar1 | 4,param_2);
  return;
}

