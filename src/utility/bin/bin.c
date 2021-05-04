#include <stdio.h>
#include <stdlib.h>
#include "bin.h"

bin leggere_bin(bin num)
{
  return num;
}

bin scrivere_bin(bin * num, bin i, bin c)
{

	  *num = c;

	  return *num;
}


bin allocare_bin(bin num, bin dimensione)
{
  if(dimensione == 0)
  {
    num =  malloc(sizeof(int) * DIM);
  }
  else
  {
    num = realloc(num, sizeof(num) * sizeof(dimensione));
  }

  return num;
}


