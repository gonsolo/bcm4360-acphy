
undefined8 wlc_bmac_get_txant(long *param_1)

{
  return CONCAT62((int6)((ulong)*(long *)(*param_1 + 0x550) >> 0x10),
                  (short)*(char *)(*(long *)(*param_1 + 0x550) + 8));
}

