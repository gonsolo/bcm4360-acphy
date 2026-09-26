
undefined4 wlc_bmac_detach(long param_1)

{
  long lVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  long lVar5;
  
  uVar2 = 0;
  lVar1 = *(long *)(param_1 + 0x20);
  if (lVar1 != 0) {
    if (*(long *)(lVar1 + 0xb8) != 0) {
      si_deregister_intr_callback();
      if (*(int *)(*(long *)(lVar1 + 0xb8) + 4) == 1) {
        si_pci_sleep();
      }
    }
    iVar3 = 0;
    lVar5 = lVar1;
    do {
      if (*(undefined8 **)(lVar5 + 0x20) != (undefined8 *)0x0) {
        (**(code **)**(undefined8 **)(lVar5 + 0x20))();
        wlc_hw_set_di(lVar1,iVar3,0);
      }
      iVar3 = iVar3 + 1;
      lVar5 = lVar5 + 8;
    } while (iVar3 != 6);
    lVar5 = *(long *)(lVar1 + 0xe8);
    for (uVar4 = 0; uVar4 < *(uint *)(lVar1 + 0x118); uVar4 = uVar4 + 1) {
      iVar3 = wlc_is_singleband_5g(*(undefined2 *)(lVar1 + 0x82));
      if (iVar3 != 0) {
        uVar4 = 1;
      }
      if (*(long *)(lVar5 + 0x28) != 0) {
        wlc_phy_detach();
        *(undefined8 *)(lVar5 + 0x28) = 0;
      }
      lVar5 = *(long *)(lVar1 + 0xf0 + (ulong)(*(int *)(*(long *)(param_1 + 0x40) + 4) != 1) * 8);
    }
    wlc_phy_shared_detach(*(undefined8 *)(lVar1 + 0xe0));
    wlc_phy_shim_detach(*(undefined8 *)(lVar1 + 0xd8));
    uVar2 = 0;
    *(undefined8 *)(lVar1 + 0xc0) = 0;
    *(undefined8 *)(lVar1 + 0xb8) = 0;
    if (*(long *)(lVar1 + 0x198) != 0) {
      uVar2 = wlc_bmac_led_detach(lVar1);
      *(undefined8 *)(lVar1 + 0x198) = 0;
    }
    wlc_hw_detach(lVar1);
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  return uVar2;
}

