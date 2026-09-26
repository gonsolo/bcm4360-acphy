
undefined4 si_cis_source(long param_1)

{
  uint uVar1;
  bool bVar2;
  
  if (*(int *)(param_1 + 4) == 1) {
    return 0xffffffe2;
  }
  uVar1 = *(uint *)(param_1 + 0x3c);
  if (uVar1 != 0x4360) {
    if (uVar1 < 0x4361) {
      if (uVar1 != 0x4325) {
        if (uVar1 < 0x4326) {
          if (uVar1 != 0x4319) {
            if (uVar1 < 0x431a) {
              if (uVar1 != 0x10f6) {
                if (uVar1 != 0x4315) {
                  return 0;
                }
                goto LAB_0011f1c7;
              }
            }
            else if (uVar1 != 0x4322) {
              if (uVar1 != 0x4324) {
                return 0;
              }
              bVar2 = (*(uint *)(param_1 + 0x48) & 0x400080) == 0x80;
              goto LAB_0011f218;
            }
          }
LAB_0011f1cc:
          uVar1 = *(uint *)(param_1 + 0x48) >> 6;
          goto LAB_0011f1d3;
        }
        if (uVar1 == 0x4335) {
          bVar2 = (*(uint *)(param_1 + 0x48) & 0x60) == 0x20;
LAB_0011f218:
          if (!bVar2) {
            return 2;
          }
          return 1;
        }
        if (0x4335 < uVar1) {
          if (uVar1 == 0x4350) {
            if ((*(byte *)(param_1 + 0x48) & 0x40) != 0) {
              return 1;
            }
            return 2;
          }
          if (uVar1 != 0x4352) {
            bVar2 = uVar1 == 0x4336;
            goto LAB_0011f1bf;
          }
          goto LAB_0011f237;
        }
        if (uVar1 != 0x4329) {
          if (uVar1 != 0x4330) {
            return 0;
          }
          if ((char)*(uint *)(param_1 + 0x48) < '\0') {
            return 1;
          }
          bVar2 = (*(uint *)(param_1 + 0x48) & 0x10) == 0;
          goto LAB_0011f1f3;
        }
      }
LAB_0011f1c7:
      uVar1 = *(uint *)(param_1 + 0x48);
LAB_0011f1d3:
      return *(undefined4 *)(&DAT_0050d5a0 + (ulong)(uVar1 & 3) * 4);
    }
    if (uVar1 == 0xa8e6) {
LAB_0011f224:
      return *(undefined4 *)(&DAT_0050d590 + (ulong)(*(uint *)(param_1 + 0x48) >> 7 & 1) * 4);
    }
    if (uVar1 < 0xa8e7) {
      if (uVar1 != 0xa8df) {
        if (0xa8df < uVar1) {
          if (uVar1 < 0xa8e2) {
            return 0;
          }
          goto LAB_0011f224;
        }
        if (uVar1 == 0xa887) {
          return 2;
        }
        if (uVar1 != 0xa8d5) {
          return 0;
        }
      }
      goto LAB_0011f1cc;
    }
    if (uVar1 < 0xa8ec) {
      if (0xa8e9 < uVar1) {
        return 2;
      }
      if (uVar1 != 0xa8e7) {
        return 0;
      }
      bVar2 = (*(uint *)(param_1 + 0x48) & 6) == 2;
      goto LAB_0011f218;
    }
    if ((uVar1 != 0xa9c4) && (uVar1 != 0xaa06)) {
      bVar2 = uVar1 == 0xa962;
LAB_0011f1bf:
      if (!bVar2) {
        return 0;
      }
      if ((*(uint *)(param_1 + 0x48) & 2) != 0) {
        return 1;
      }
      bVar2 = (*(uint *)(param_1 + 0x48) & 4) == 0;
      goto LAB_0011f1f3;
    }
  }
LAB_0011f237:
  bVar2 = (*(byte *)(param_1 + 0x48) & 8) == 0;
LAB_0011f1f3:
  if (!bVar2) {
    return 2;
  }
  return 0;
}

