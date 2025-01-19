//
// Created by calle on 24-12-28.
//

#include <inttypes.h>

#include "../OBJECTS.h"
#include "../REQUEST.h"
#include "../COUNT.h"

#include "../ERR.h"

#include <stdio.h>
#include <stdlib.h>

HeadReturnObj SET(struct _PairObject*Pairs,int PairsSize)
{
    HeadReturnObj ToReturn;
    ToReturn.ToState = 0;

    //set x
    //1   2

    VariableRequestUPObj Request = {.VariablesSize = 0};
    CountObj Counted = {.ValueSize = 0};

    for (int i = 0; i < PairsSize; i++)
    {

        MioneObj Prompt = Pairs[i].Prompt;

        if (Prompt.ObjType == 1) //Head代替Prompt
        {
            Request = REQUEST(Pairs[i].Source, Pairs[i].SourceSize);
        }
        if (Prompt.ObjType == 2)
        {
            switch (Prompt.Prompt.CurNumber)
            {
            case 1:

                Counted = COUNT(Pairs[i].Source, Pairs[i].SourceSize);

                if (Counted.ValueSize>Request.VariablesSize) ErrCall("More variables than values","M111",NULL,Prompt.Line,Prompt.Column);

                for(int CountedIndex = 0; CountedIndex < Counted.ValueSize; CountedIndex++)
                {
                    Request.VariableUPs[CountedIndex]->Val = Counted.Value[CountedIndex];

                }
            break;

            default:
                ErrCall("unsupported prompt type","M111",NULL,Prompt.Line,Prompt.Column);
                break;
            }
        }
    }

    return ToReturn;
}
