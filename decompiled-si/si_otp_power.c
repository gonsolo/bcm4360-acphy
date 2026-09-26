
void si_otp_power(long param_1,undefined1 param_2)

{
  if ((*(byte *)(param_1 + 0x1b) & 0x10) != 0) {
    si_pmu_otp_power(param_1,*(undefined8 *)(param_1 + 0x58),param_2);
  }
  osl_delay(1000);
  return;
}

