//
// Created by calle on 24-12-28.
//

#include <inttypes.h>

#include "../OBJECTS.h"
#include "../REQUEST.h"
#include "../COUNT.h"

#include "../ERR.h"

#include <stdio.h>

HeadReturnObj SET(struct _PairObject*Pairs,int PairsSize)
{
    HeadReturnObj ToReturn;
    ToReturn.ToState = 0;


    //set x
    //1   2

    for (int i = 0; i < PairsSize; i++)
    {

        MioneObj Prompt = Pairs[i].Prompt;

        if (Prompt.ObjType == 1) //Head代替Prompt
        {

            VariableRequestObj Request = REQUEST(Pairs[i].Source, Pairs[i].SourceSize);
        }
        if (Prompt.ObjType == 2)
        {

            CountObj Counted = COUNT(Pairs[i].Source, Pairs[i].SourceSize);

        }

    }

    return ToReturn;
}