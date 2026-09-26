
void si_pcmcia_init(long param_1)

{
  byte local_19;
  
  local_19 = 0;
  osl_pcmcia_read_attr(*(undefined8 *)(param_1 + 0x58),0x380,&local_19,1);
  local_19 = local_19 | 5;
  osl_pcmcia_write_attr(*(undefined8 *)(param_1 + 0x58),0x380,&local_19,1);
  return;
}

