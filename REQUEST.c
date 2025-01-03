//
// Created by calle on 25-1-3.
//

#include "OBJECTS.h"
#include "ERR.h"
#include <stdio.h>

VariableRequestObj REQUEST(MioneObj* PACK,int PACKSize){
  VariableRequestObj VarReq;

  for (int PACKIndex = 0; PACKIndex < PACKSize;PACKIndex++) {

    if (PACK[PACKIndex].ObjType == 3){

      switch (PACK[PACKIndex].Symbol.CurNumber){
        case 2:
          break;
        default:
          ErrCall("M123","Unkown Symbol","",PACK[PACKIndex].Line,PACK[PACKIndex].Column);
          break;
      }
      if(PACK[PACKIndex].Symbol.CurNumber == 2){
        printf("Pairs\n");
      }
    }
  }

  return VarReq;
}