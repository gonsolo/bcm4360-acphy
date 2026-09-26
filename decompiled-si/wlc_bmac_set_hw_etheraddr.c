
void wlc_bmac_set_hw_etheraddr(long param_1,undefined8 param_2)

{
  osl_memcpy(param_1 + 0x178,param_2,6);
  return;
}

