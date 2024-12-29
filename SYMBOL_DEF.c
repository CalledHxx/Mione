#include <stdlib.h>

#include "OBJECTS.h"

SymbolsCaseObj Symbols[] =
{
    (SymbolsCaseObj){
        .Name = "+",
        .SymbolType = 1,
        .xIndex = 2,
        .CurNumber = 1
    },

    (SymbolsCaseObj){
        .Name = ",",
        .SymbolType = 4,
        .xIndex = 0, // 1,2,3,5,8,13
        .CurNumber = 2
    },

    (SymbolsCaseObj){
        .Name = "*",
        .SymbolType = 1,
        .xIndex = 1,
        .CurNumber = 3
    },

    (SymbolsCaseObj){
        .Name = "/",
        .SymbolType = 1,
        .xIndex = 1,
        .CurNumber = 4
    },

    (SymbolsCaseObj){
        .Name = "(",
        .SymbolType = 0,
        .xIndex = 0,
        .CurNumber = 0
    },

    (SymbolsCaseObj){
        .Name = ")",
        .SymbolType = 0,
        .xIndex = 0,
        .CurNumber = 0
    },

    (SymbolsCaseObj){
        .Name = "^",
        .SymbolType = 1,
        .xIndex = 0,
        .CurNumber = 5
    },

    (SymbolsCaseObj){
        .Name = ";",
        .SymbolType = 0,
        .xIndex = 0,
        .CurNumber = 0
    },

    (SymbolsCaseObj){
        .Name = "-",
        .SymbolType = 3,
        .xIndex = 1,// -1
        .yIndex = 2,// 1-1
        .CurNumber = 6
    },

    (SymbolsCaseObj){
        .Name = ".",
        .SymbolType = 3,
        .xIndex = 0,// .1
        .yIndex = 0,// 0.1 or <TABLE>.<CHILD>
        .CurNumber = 7
    },
};

SymbolGetObj GetSymbols()
{
    int aSize = 0;
    SymbolsCaseObj * a = malloc(0);

    for (int i = 0; i < sizeof(Symbols) / sizeof(Symbols[0]); i++)
    {
        aSize++;
        a = realloc(a, aSize*sizeof(SymbolsCaseObj));
        a[aSize-1] = Symbols[i];
    }
    return (SymbolGetObj){
        .a = a,
        .aSize = aSize,
    };
}