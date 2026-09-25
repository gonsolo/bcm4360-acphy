
void wlc_phydump_aci_acphy(long param_1,undefined8 param_2)

{
  long lVar1;
  ushort uVar2;
  char *pcVar3;
  undefined4 uVar4;
  
  lVar1 = *(long *)(param_1 + 0x138);
  pcVar3 = "Scanning is in progress. Can\'t dump aci mitigation info.\n";
  if ((*(uint *)(param_1 + 0x19c) & 0x206) == 0) {
    uVar2 = *(ushort *)(param_1 + 0x17e) & 0x3800;
    uVar4 = 0x14;
    if (uVar2 != 0x1000) {
      uVar4 = 0x50;
      if (uVar2 == 0x1800) {
        uVar4 = 0x28;
      }
    }
    bcm_bprintf(param_2,&DAT_006f6e3a);
    bcm_bprintf(param_2,"*** Channel = %d(%d mhz), Desense(mode 1) On = %d *** \n",
                *(undefined1 *)(param_1 + 0x17e),uVar4,*(undefined1 *)(lVar1 + 0x670));
    bcm_bprintf(param_2,"OFDM desense (dB) = %d\n",*(undefined1 *)(lVar1 + 0x668));
    bcm_bprintf(param_2,"BPHY desense (dB) = %d\n",*(undefined1 *)(lVar1 + 0x669));
    bcm_bprintf(param_2,"lna1 tbl desense (ticks) = %d\n",*(undefined1 *)(lVar1 + 0x66a));
    bcm_bprintf(param_2,"lna2 tbl desense (ticks) = %d\n",*(undefined1 *)(lVar1 + 0x66b));
    bcm_bprintf(param_2,"lna1 pktgain limit (ticks) = %d\n",*(undefined1 *)(lVar1 + 0x66c));
    bcm_bprintf(param_2,"lna2 pktgain limit (ticks) = %d\n",*(undefined1 *)(lVar1 + 0x66d));
    bcm_bprintf(param_2,"elna bypass = %d\n",*(undefined1 *)(lVar1 + 0x66e));
    pcVar3 = "\n";
  }
  bcm_bprintf(param_2,pcVar3);
  return;
}

