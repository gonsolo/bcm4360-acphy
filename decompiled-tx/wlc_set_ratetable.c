
void wlc_set_ratetable(long param_1)

{
  byte bVar1;
  uint uVar2;
  undefined8 uVar3;
  byte bVar4;
  long lVar5;
  uint uVar6;
  byte *pbVar7;
  uint local_68;
  byte local_64 [52];
  
  uVar3 = FUN_0012641b();
  wlc_rateset_copy(uVar3,&local_68);
  pbVar7 = local_64;
  wlc_rateset_mcs_upd(&local_68,*(undefined1 *)(*(long *)(param_1 + 0x550) + 2));
  for (uVar6 = 0; uVar6 < local_68; uVar6 = uVar6 + 1) {
    lVar5 = *(long *)(param_1 + 0x40);
    bVar4 = *pbVar7 & 0x7f;
    uVar2 = wlc_rate_rspec_reference_rate(bVar4);
    bVar1 = *(byte *)(lVar5 + 0x84 + (ulong)uVar2);
    if (bVar1 == 0) {
      bVar1 = local_64[0] & 0x7f;
    }
    lVar5 = param_1 + 0x454;
    if (-1 < (char)(&rate_info)[bVar1]) {
      lVar5 = param_1 + 0x474;
    }
    pbVar7 = pbVar7 + 1;
    wlc_bmac_write_shm(*(undefined8 *)(param_1 + 0x20),
                       (uint)(ushort)(((short)(char)(&rate_info)[bVar4] >> 0xf & 0xffc0U) + 0x220) +
                       ((byte)(&rate_info)[bVar4] & 0xf) * 2,
                       *(undefined2 *)(lVar5 + (ulong)((byte)(&rate_info)[bVar1] & 0xf) * 2));
  }
  return;
}

