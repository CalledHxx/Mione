//
// Created by calle on 25-1-3.
//

#include "OBJECTS.h"
#include "ERR.h"
#include <stdio.h>
#include <stdlib.h>

VariableRequestObj REQUEST(MioneObj* PACK,int PACKSize){
  VariableRequestObj VarReq;
  VarReq.Variables = malloc(0);
  VarReq.VariablesSize = 0;

  for (int PACKIndex = 0; PACKIndex < PACKSize;PACKIndex++) {

    switch (PACK[PACKIndex].ObjType) {
      case 3:
        switch (PACK[PACKIndex].Symbol.CurNumber){
          case 2:
            break;
          default:
            ErrCall("M123","Unkown Symbol","",PACK[PACKIndex].Line,PACK[PACKIndex].Column);
        }
        break;
      case 4:
        VarReq.VariablesSize++;
        VarReq.Variables = realloc(VarReq.Variables,VarReq.VariablesSize*sizeof(VariableObj));
        VarReq.Variables[VarReq.VariablesSize-1] = PACK[PACKIndex].Var;

      printf("added a\n");


        break;
      default:
        ErrCall("M12345","Object Type Error",NULL,PACK[PACKIndex].Line,PACK[PACKIndex].Column);

    }
  }

  return VarReq;
}