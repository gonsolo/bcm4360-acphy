
void wlc_bmac_info_init(long param_1)

{
  *(undefined4 *)(param_1 + 0x9c) = 0xb0e7a860;
  *(undefined4 *)(param_1 + 0x1c4) = 0;
  *(undefined1 *)(param_1 + 0x102) = 0;
  *(undefined2 *)(param_1 + 0x108) = 3;
  *(undefined2 *)(param_1 + 0x10a) = 2;
  *(undefined2 *)(param_1 + 0x104) = 7;
  *(undefined2 *)(param_1 + 0x106) = 4;
  *(undefined2 *)(param_1 + 0x11c) = 0x1001;
  *(undefined1 *)(param_1 + 0x1bc) = 0xff;
  return;
}

