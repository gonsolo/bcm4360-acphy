
void wlc_phy_setup_spurmode(long param_1)

{
  si_pmu_spuravoid(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x18),
                   *(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),
                   *(undefined1 *)(param_1 + 0x1164));
  wlapi_switch_macfreq
            (*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),*(undefined1 *)(param_1 + 0x1164));
  return;
}

