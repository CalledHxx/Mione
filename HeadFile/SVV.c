#include <stdio.h>
#include "../OBJECTS.h"

HeadReturnObj SVV(struct _PairObject*Pairs,int PairsSize)
{
    printf("calledhxx\n");
    for (int i = 0; i < PairsSize; i++)
    {
        MioneObj Prompt = Pairs[i].Prompt;
        if (Prompt.ObjType == 0)//偽Head
        {
        }
        if (Prompt.ObjType == 2)
        {
            printf("%s\n",Prompt.Prompt.Name);
        }

        for (int index = 0; index < Pairs[i].SourceSize; index++)
        {
        }

    }

    return ;
}