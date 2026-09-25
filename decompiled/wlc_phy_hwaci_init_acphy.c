
void wlc_phy_hwaci_init_acphy(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x138);
  *(undefined2 *)(lVar1 + 0x672) = 300;
  *(undefined2 *)(lVar1 + 0x674) = 1000;
  *(undefined2 *)(lVar1 + 0x676) = 500;
  *(undefined2 *)(lVar1 + 0x678) = 1;
  *(undefined1 *)(lVar1 + 0x67a) = 0xf;
  *(undefined1 *)(lVar1 + 0x67b) = 0xf;
  *(undefined1 *)(lVar1 + 0x67c) = 1;
  *(undefined1 *)(lVar1 + 0x67d) = 0;
  *(undefined1 *)(lVar1 + 0x67e) = 0;
  *(undefined1 *)(lVar1 + 0x67f) = 0;
  *(undefined1 *)(lVar1 + 0x680) = 4;
  *(undefined1 *)(lVar1 + 0x6c2) = 4;
  osl_memset(lVar1 + 0x682,0,0x20);
  *(undefined2 *)(lVar1 + 0x682) = 0xffff;
  *(undefined1 *)(lVar1 + 0x686) = 0;
  *(undefined1 *)(lVar1 + 0x687) = 0x1e;
  *(undefined1 *)(lVar1 + 0x688) = 4;
  *(undefined1 *)(lVar1 + 0x684) = 5;
  *(undefined1 *)(lVar1 + 0x685) = 6;
  *(undefined2 *)(lVar1 + 0x68a) = 4000;
  *(undefined1 *)(lVar1 + 0x68e) = 0;
  *(undefined1 *)(lVar1 + 0x68f) = 0x1e;
  *(undefined1 *)(lVar1 + 0x690) = 4;
  *(undefined1 *)(lVar1 + 0x68c) = 5;
  *(undefined1 *)(lVar1 + 0x68d) = 4;
  *(undefined2 *)(lVar1 + 0x692) = 8000;
  *(undefined1 *)(lVar1 + 0x696) = 1;
  *(undefined1 *)(lVar1 + 0x697) = 0x16;
  *(undefined1 *)(lVar1 + 0x698) = 4;
  *(undefined1 *)(lVar1 + 0x694) = 4;
  *(undefined1 *)(lVar1 + 0x695) = 4;
  *(undefined2 *)(lVar1 + 0x69a) = 11000;
  *(undefined1 *)(lVar1 + 0x69e) = 2;
  *(undefined1 *)(lVar1 + 0x69f) = 10;
  *(undefined1 *)(lVar1 + 0x6a0) = 4;
  *(undefined1 *)(lVar1 + 0x69c) = 3;
  *(undefined1 *)(lVar1 + 0x69d) = 4;
  *(undefined1 *)(lVar1 + 0x6c3) = 4;
  osl_memset(lVar1 + 0x6a2,0,0x20);
  *(undefined2 *)(lVar1 + 0x6a2) = 0xffff;
  *(undefined1 *)(lVar1 + 0x6a6) = 0;
  *(undefined1 *)(lVar1 + 0x6a7) = 0x1e;
  *(undefined1 *)(lVar1 + 0x6a8) = 4;
  *(undefined1 *)(lVar1 + 0x6a4) = 5;
  *(undefined1 *)(lVar1 + 0x6a5) = 6;
  *(undefined2 *)(lVar1 + 0x6aa) = 1000;
  *(undefined1 *)(lVar1 + 0x6ae) = 0;
  *(undefined1 *)(lVar1 + 0x6af) = 0x1e;
  *(undefined1 *)(lVar1 + 0x6b0) = 4;
  *(undefined1 *)(lVar1 + 0x6ac) = 5;
  *(undefined1 *)(lVar1 + 0x6ad) = 4;
  *(undefined2 *)(lVar1 + 0x6b2) = 6000;
  *(undefined1 *)(lVar1 + 0x6b6) = 1;
  *(undefined1 *)(lVar1 + 0x6b7) = 0x19;
  *(undefined1 *)(lVar1 + 0x6b8) = 4;
  *(undefined1 *)(lVar1 + 0x6b4) = 4;
  *(undefined1 *)(lVar1 + 0x6b5) = 4;
  *(undefined2 *)(lVar1 + 0x6ba) = 10000;
  *(undefined1 *)(lVar1 + 0x6be) = 2;
  *(undefined1 *)(lVar1 + 0x6bf) = 0xf;
  *(undefined1 *)(lVar1 + 0x6c0) = 4;
  *(undefined1 *)(lVar1 + 0x6bc) = 3;
  *(undefined1 *)(lVar1 + 0x6bd) = 4;
  return;
}

