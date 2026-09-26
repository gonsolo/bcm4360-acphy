
int wlc_bmac_rate_shm_offset(undefined8 param_1,byte param_2)

{
  int iVar1;
  
  iVar1 = wlc_bmac_read_shm(param_1,(uint)(ushort)(((short)(char)(&rate_info)[param_2] >> 0xf &
                                                   0xffc0U) + 0x200) +
                                    ((byte)(&rate_info)[param_2] & 0xf) * 2);
  return iVar1 * 2;
}

