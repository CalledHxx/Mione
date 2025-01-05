//
// Created by calle on 25-1-3.
//

#include "OBJECTS.h"
#include "ERR.h"
#include <stdio.h>

VariableRequestObj REQUEST(MioneObj* PACK,int PACKSize){
  VariableRequestObj VarReq;

  for (int PACKIndex = 0; PACKIndex < PACKSize;PACKIndex++) {

    switch (PACK[PACKIndex].ObjType) {
      case 3:
        switch (PACK[PACKIndex].Symbol.CurNumber){
          case 2:
            printf("Pairs\n");
            break;
          default:
            ErrCall("M123","Unkown Symbol","",PACK[PACKIndex].Line,PACK[PACKIndex].Column);
            break;
        }
        break;
      case 4:
        break;
      default:
        ErrCall("M12345","Object Type Error",NULL,PACK[PACKIndex].Line,PACK[PACKIndex].Column);
       break;

    }
  }

  return VarReq;
}