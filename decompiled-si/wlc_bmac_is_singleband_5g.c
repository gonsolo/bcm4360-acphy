
bool wlc_bmac_is_singleband_5g(int param_1)

{
  bool bVar1;
  
  if (((((param_1 == 0x4313) || (param_1 == 0x4321)) || (param_1 == 0x432a)) ||
      ((((param_1 == 0x431a || (param_1 == 0x431d)) ||
        ((param_1 == 0x4316 || ((param_1 == 0x4352 || (param_1 == 0x432d)))))) ||
       (param_1 == 0x4348)))) ||
     ((((param_1 == 0x435a || (param_1 == 0x43a2)) || (param_1 == 0x4333)) ||
      ((param_1 == 0x43b3 || (param_1 == 0x43b0)))))) {
    bVar1 = true;
  }
  else {
    bVar1 = param_1 == 0x434f;
  }
  return bVar1;
}

