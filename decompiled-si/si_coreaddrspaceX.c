
void si_coreaddrspaceX(int *param_1,undefined8 param_2,undefined8 param_3,undefined4 *param_4)

{
  if ((*param_1 == 3) || (*param_1 == 1)) {
    ai_coreaddrspaceX();
  }
  else {
    *param_4 = 0;
  }
  return;
}

