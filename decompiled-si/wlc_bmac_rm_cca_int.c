
void wlc_bmac_rm_cca_int(undefined8 *param_1)

{
  undefined2 uVar1;
  undefined2 local_2a [5];
  
  wlc_bmac_copyfrom_objmem(param_1,0x4d8,local_2a,2,0x30000);
  uVar1 = local_2a[0];
  wlc_bmac_copyfrom_objmem(param_1,0x4dc,local_2a,2,0x30000);
  wlc_rm_cca_complete(*param_1,CONCAT22(local_2a[0],uVar1) >> 3);
  return;
}

