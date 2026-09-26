
void FUN_001614f0(long param_1)

{
  uint uVar1;
  short sVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  bool bVar5;
  
  if (*(char *)(param_1 + 0xae) != '\0') {
    return;
  }
  uVar1 = *(uint *)(param_1 + 0x84);
  if (uVar1 == 0x2b) {
    if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 0xb) goto LAB_00161964;
    puVar4 = d11ucode43;
    uVar3 = d11ucode43sz;
  }
  else if (uVar1 == 0x2a) {
    if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 0xb) goto LAB_00161964;
    puVar4 = d11ucode42;
    uVar3 = d11ucode42sz;
  }
  else if ((((uVar1 == 0x2c) || (uVar1 == 0x29)) || (uVar1 == 0x2e)) ||
          ((uVar1 == 0x2d || (uVar1 == 0x2f)))) {
    if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 0xb) goto LAB_00161964;
    puVar4 = d11ucode41;
    uVar3 = d11ucode41sz;
  }
  else if (uVar1 == 0x28) {
    if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 0xb) goto LAB_00161964;
    puVar4 = d11ucode40;
    uVar3 = d11ucode40sz;
  }
  else if (uVar1 == 0x22) {
    if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 4) goto LAB_00161964;
    puVar4 = d11ucode34_mimo;
    uVar3 = d11ucode34_mimosz;
  }
  else {
    if (uVar1 == 0x21) {
      if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 10) goto LAB_00161964;
      puVar4 = d11ucode33_lcn40;
      uVar3 = d11ucode33_lcn40sz;
      goto LAB_00161866;
    }
    if (uVar1 == 0x20) {
      if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 4) goto LAB_00161964;
      puVar4 = d11ucode32_mimo;
      uVar3 = d11ucode32_mimosz;
    }
    else if (uVar1 == 0x1f) {
      bVar5 = *(short *)(*(long *)(param_1 + 0xe8) + 0x1c) == 4;
LAB_0016168f:
      if (!bVar5) goto LAB_00161964;
      puVar4 = d11ucode29_mimo;
      uVar3 = d11ucode29_mimosz;
    }
    else if (uVar1 == 0x1e) {
      if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 4) goto LAB_00161964;
      puVar4 = d11ucode30_mimo;
      uVar3 = d11ucode30_mimosz;
    }
    else {
      if (uVar1 == 0x1d) {
        bVar5 = *(short *)(*(long *)(param_1 + 0xe8) + 0x1c) == 7;
        goto LAB_0016168f;
      }
      if (uVar1 != 0x1a) {
        if ((uVar1 == 0x1c) || (uVar1 == 0x19)) {
          sVar2 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
          if (sVar2 == 4) {
            puVar4 = d11ucode25_mimo;
            uVar3 = d11ucode25_mimosz;
            goto LAB_0016195c;
          }
          if (sVar2 != 8) goto LAB_00161964;
          puVar4 = d11ucode25_lcn;
          uVar3 = d11ucode25_lcnsz;
        }
        else if (uVar1 == 0x18) {
          sVar2 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
          if (sVar2 == 8) {
            puVar4 = d11ucode24_lcn;
            uVar3 = d11ucode24_lcnsz;
          }
          else {
            if (sVar2 == 4) {
              puVar4 = d11ucode24_mimo;
              uVar3 = d11ucode24_mimosz;
              goto LAB_0016195c;
            }
            if (sVar2 != 6) goto LAB_00161964;
LAB_001617fe:
            puVar4 = d11ucode20_sslpn;
            uVar3 = d11ucode20_sslpnsz;
          }
        }
        else {
          if (uVar1 == 0x17) {
            if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 4) goto LAB_00161964;
LAB_00161841:
            puVar4 = d11ucode16_mimo;
            uVar3 = d11ucode16_mimosz;
            goto LAB_0016195c;
          }
          if (uVar1 == 0x16) {
            sVar2 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
            if (sVar2 == 4) {
              puVar4 = d11ucode22_mimo;
              uVar3 = d11ucode22_mimosz;
              goto LAB_0016195c;
            }
            if (sVar2 != 6) goto LAB_00161964;
            puVar4 = d11ucode22_sslpn;
            uVar3 = d11ucode22_sslpnsz;
          }
          else if (uVar1 == 0x15) {
            if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 6) goto LAB_00161964;
            puVar4 = d11ucode21_sslpn;
            uVar3 = d11ucode21_sslpnsz;
          }
          else {
            if (uVar1 < 0x14) {
              if (uVar1 == 0x13) {
                if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) == 6) {
                  puVar4 = d11ucode19_sslpn;
                  uVar3 = d11ucode19_sslpnsz;
                  goto LAB_00161866;
                }
              }
              else if (uVar1 < 0x10) {
                if (uVar1 == 0xf) {
                  if (*(int *)(*(long *)(param_1 + 0xb0) + 4) == 2) {
                    puVar4 = d11ucode_2w15;
                    uVar3 = d11ucode_2w15sz;
                  }
                  else {
                    puVar4 = d11ucode15;
                    uVar3 = d11ucode15sz;
                  }
                }
                else if (uVar1 == 0xe) {
                  puVar4 = d11ucode14;
                  uVar3 = d11ucode14sz;
                }
                else if (uVar1 == 0xd) {
                  if (*(int *)(*(long *)(param_1 + 0xb0) + 4) == 2) {
                    puVar4 = d11ucode_2w13;
                    uVar3 = d11ucode_2w13sz;
                  }
                  else {
                    puVar4 = d11ucode13;
                    uVar3 = d11ucode13sz;
                  }
                }
                else if (uVar1 < 0xb) {
                  if (uVar1 < 5) {
                    if (uVar1 != 4) goto LAB_00161964;
                    puVar4 = d11ucode4;
                    uVar3 = d11ucode4sz;
                  }
                  else {
                    puVar4 = d11ucode5;
                    uVar3 = d11ucode5sz;
                  }
                }
                else if (*(int *)(*(long *)(param_1 + 0xb0) + 4) == 2) {
                  puVar4 = d11ucode_2w11;
                  uVar3 = d11ucode_2w11sz;
                }
                else {
                  puVar4 = d11ucode11;
                  uVar3 = d11ucode11sz;
                }
                goto LAB_0016195c;
              }
            }
            else if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) == 6) goto LAB_001617fe;
            sVar2 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
            if (sVar2 == 4) goto LAB_00161841;
            if (sVar2 != 6) {
              if (sVar2 != 5) goto LAB_00161964;
              puVar4 = d11ucode16_lp;
              uVar3 = d11ucode16_lpsz;
              goto LAB_0016195c;
            }
            puVar4 = d11ucode16_sslpn;
            uVar3 = d11ucode16_sslpnsz;
          }
        }
LAB_00161866:
        FUN_001613ce(param_1,puVar4,uVar3);
        goto LAB_00161964;
      }
      if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 7) goto LAB_00161964;
      puVar4 = d11ucode26_mimo;
      uVar3 = d11ucode26_mimosz;
    }
  }
LAB_0016195c:
  FUN_00161484(param_1,puVar4,uVar3);
LAB_00161964:
  *(undefined1 *)(param_1 + 0xae) = 1;
  return;
}

