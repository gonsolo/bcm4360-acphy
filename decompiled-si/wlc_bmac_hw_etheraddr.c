
void wlc_bmac_hw_etheraddr(long param_1,undefined8 param_2)

{
  osl_memcpy(param_2,param_1 + 0x178,6);
  return;
}

