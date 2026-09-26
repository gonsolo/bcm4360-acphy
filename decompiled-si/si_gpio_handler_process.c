
void si_gpio_handler_process(long param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined8 *puVar7;
  
  uVar1 = si_gpioin();
  uVar2 = si_gpiointpolarity(param_1,0,0,0);
  uVar3 = si_gpioevent(param_1,0,0,0);
  uVar4 = si_gpioevent(param_1,2,0,0);
  for (puVar7 = *(undefined8 **)(param_1 + 0x98); puVar7 != (undefined8 *)0x0;
      puVar7 = (undefined8 *)puVar7[4]) {
    if ((code *)puVar7[2] != (code *)0x0) {
      uVar6 = uVar3;
      if (*(char *)(puVar7 + 1) != '\0') {
        uVar6 = uVar1;
      }
      uVar6 = uVar6 & *(uint *)(puVar7 + 3);
      uVar5 = uVar4;
      if (*(char *)(puVar7 + 1) != '\0') {
        uVar5 = uVar2;
      }
      if (uVar6 != (uVar5 & *(uint *)(puVar7 + 3))) {
        (*(code *)puVar7[2])(uVar6,*puVar7);
      }
    }
  }
  si_gpioevent(param_1,0,uVar3,uVar3);
  return;
}

