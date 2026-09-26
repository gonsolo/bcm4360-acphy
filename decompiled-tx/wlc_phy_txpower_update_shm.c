
void wlc_phy_txpower_update_shm(long param_1)

{
  undefined1 uVar1;
  char cVar2;
  int iVar3;
  long lVar4;
  ushort uVar5;
  uint uVar6;
  byte *pbVar7;
  byte bVar8;
  char *pcVar9;
  undefined1 *puVar10;
  char *pcVar11;
  char local_68 [16];
  char local_58 [16];
  undefined1 local_48 [24];
  
  iVar3 = *(int *)(param_1 + 0x160);
  if ((((iVar3 != 7) && (iVar3 != 4)) && (iVar3 != 0xb)) &&
     (((iVar3 != 6 && (*(char *)(*(long *)(param_1 + 0x20) + 0x31) != '\0')) &&
      (lVar4 = *(long *)(param_1 + 0x1c8), lVar4 != 0)))) {
    if (*(char *)(param_1 + 0x220) == '\0') {
      pcVar9 = local_68;
      ppr_get_ofdm(lVar4,0,0,1,pcVar9);
      do {
        *pcVar9 = (char)((*pcVar9 + 7) / 8 << 3);
        pcVar9 = pcVar9 + 1;
      } while (pcVar9 != local_68 + 8);
      ppr_set_ofdm(*(undefined8 *)(param_1 + 0x1c8),0,0,1,local_68);
      wlapi_bmac_write_shm
                (*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0x4e,
                 local_68[0] + 7 >> 3 & 0xffff);
    }
    else {
      ppr_get_ofdm(lVar4,0,0,1,local_58);
      wlapi_bmac_write_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0x28,0x3f);
      wlapi_bmac_write_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0x24,0x10);
      pbVar7 = (byte *)(param_1 + 0x21a);
      uVar6 = 0;
      bVar8 = 0x7f;
      while( true ) {
        if (*(byte *)(param_1 + 0x168) <= (byte)uVar6) break;
        if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (uVar6 & 0x1f) & 1) != 0) {
          if (*pbVar7 < bVar8) {
            bVar8 = *pbVar7;
          }
        }
        uVar6 = uVar6 + 1;
        pbVar7 = pbVar7 + 1;
      }
      wlapi_bmac_write_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0x26,(ulong)bVar8 << 4)
      ;
      wlapi_bmac_write_shm
                (*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0x32,
                 *(undefined2 *)(param_1 + 0x238));
      if (*(int *)(param_1 + 0x160) == 2) {
        pcVar9 = local_68;
        puVar10 = local_48;
        local_48[0] = 2;
        local_48[1] = 4;
        local_48[2] = 0xb;
        local_48[3] = 0x16;
        ppr_get_dsss(*(undefined8 *)(param_1 + 0x1c8),0,1,pcVar9);
        do {
          uVar1 = *puVar10;
          puVar10 = puVar10 + 1;
          uVar5 = wlapi_bmac_rate_shm_offset
                            (*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),uVar1);
          wlapi_bmac_write_shm
                    (*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),uVar5 + 6,(short)*pcVar9);
          cVar2 = *pcVar9;
          pcVar9 = pcVar9 + 1;
          wlapi_bmac_write_shm
                    (*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),uVar5 + 0xe,
                     -(short)(cVar2 / '\x02'));
        } while (puVar10 != local_48 + 4);
        if (*(char *)(param_1 + 0x17d) != '\0') {
          uVar5 = wlapi_bmac_rate_shm_offset(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),2);
          wlapi_bmac_write_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),uVar5 + 6,0);
          wlapi_bmac_write_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),uVar5 + 0xe,0);
        }
      }
      pcVar9 = local_68;
      pcVar11 = local_58;
      do {
        builtin_strncpy(local_68,"\f\x12\x18$0H`l",8);
        cVar2 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        uVar5 = wlapi_bmac_rate_shm_offset(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),cVar2);
        wlapi_bmac_write_shm
                  (*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),uVar5 + 6,(short)*pcVar11);
        cVar2 = *pcVar11;
        pcVar11 = pcVar11 + 1;
        wlapi_bmac_write_shm
                  (*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),uVar5 + 0xe,
                   -(short)(cVar2 / '\x02'));
      } while (pcVar9 != local_68 + 8);
      wlapi_bmac_mhf(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),1,0x80,0x80,3);
    }
  }
  return;
}

