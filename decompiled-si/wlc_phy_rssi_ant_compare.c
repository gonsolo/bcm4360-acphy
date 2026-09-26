
int wlc_phy_rssi_ant_compare(long param_1)

{
  undefined8 in_RAX;
  
  return (int)CONCAT71((int7)((ulong)in_RAX >> 8),
                       *(char *)(param_1 + 0x10d9) <= *(char *)(param_1 + 0x10da)) + 1;
}

