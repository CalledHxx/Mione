//
// Created by calle on 24-12-28.
//
#include <stdlib.h>

#include "../OBJECTS.h"

#include "SET.h"
#include "RETURN.h"

HeadFucObj HeadFucs[]  = {
    (HeadFucObj){
        .Fuc = SET,
        .Name = "set"
    },
    (HeadFucObj){
        .Fuc = RETURN,
        .Name = "return"
    },
};

HeadGetObj GetHeads()
{
    int aSize = 0;
    HeadFucObj * a = malloc(0);



    for (int i = 0; i < sizeof(HeadFucs)/sizeof(HeadFucs[0]); i++)
    {
        aSize++;
        a = realloc(a, aSize * sizeof(HeadFucObj));
        a[aSize-1] = HeadFucs[i];
    }


    return (HeadGetObj){
        .a = a,
        .aSize = aSize,
    };
}