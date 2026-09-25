
void wlc_phy_hirssi_elnabypass_apply_acphy(long param_1)

{
  if (*(char *)(*(long *)(param_1 + 0x20) + 0x31) != '\0') {
    wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
    wlc_phy_desense_aci_reset_params_acphy
              (param_1,0,(*(ushort *)(param_1 + 0x17e) & 0xc000) == 0,
               (*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000);
    FUN_0019173d(param_1);
    FUN_0019b279(param_1,0);
    FUN_0019bc45(param_1,1,1,1);
    FUN_0019ae61(param_1);
    wlc_phy_resetcca_acphy(param_1);
    wlc_phy_force_rfseq_acphy(param_1,2);
    wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  }
  return;
}

