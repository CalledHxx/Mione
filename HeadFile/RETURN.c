//
// Created by calle on 24-12-28.
//

#include "../OBJECTS.h"
#include "../COUNT.h"
#include <stdio.h>

HeadReturnObj RETURN(struct _PairObject*Pairs,int PairsSize)
{
    HeadReturnObj ToReturn;

    for (int i = 0; i < PairsSize; i++)
    {
        MioneObj Prompt = Pairs[i].Prompt;
        if (Prompt.ObjType == 0)//偽Head
        {
        }
        if (Prompt.ObjType == 2)
        {
        }

        if (i == 0) { //Head代替Prompt
            CountObj Counted = COUNT(Pairs[i].Source, Pairs[i].SourceSize);

            printf("RETURN: %d\n", Counted.Value[0].NPNumber);

            ToReturn.ToState = 1;
            ToReturn.Vs = (ValueReturnObj){
                .ValueSize = Counted.ValueSize,
               .Value = Counted.Value,
            };
        }else
        {


        }

    }

    return ToReturn;
}