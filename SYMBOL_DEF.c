#include <stdlib.h>

#include "OBJECTS.h"

SymbolObj Symbols[] =
{
    (SymbolObj){
        .Name = "+",
        .SymbolType = 1,
        .xIndex = 2,
        .CurNumber = 1,
        .CanConnect = 1
    },

    (SymbolObj){
        .Name = ",",
        .SymbolType = 4,
        .xIndex = 0, // 1,2,3,5,8,13
        .CurNumber = 2,
        .CanConnect = 1
    },

    (SymbolObj){
        .Name = "*",
        .SymbolType = 1,
        .xIndex = 1,
        .CurNumber = 3,
        .CanConnect = 1
    },

    (SymbolObj){
        .Name = "/",
        .SymbolType = 1,
        .xIndex = 1,
        .CurNumber = 4,
        .CanConnect = 1
    },

    (SymbolObj){
        .Name = "(",
        .SymbolType = 0,
        .xIndex = 0, //這邊的設定有點無效 只是標住他的確與階級0同樣層級執行
        .CurNumber = 0,
        .CanConnect = 1
    },

    (SymbolObj){
        .Name = ")",
        .SymbolType = 0,
        .xIndex = 0, //這邊的設定有點無效 只是標住他的確與階級0同樣層級執行
        .CurNumber = 0,
        .CanConnect = 1
    },

    (SymbolObj){
        .Name = "^",
        .SymbolType = 1,
        .xIndex = 0,
        .CurNumber = 5,
        .CanConnect = 1
    },

    (SymbolObj){
        .Name = ";",
        .SymbolType = 0,
        .xIndex = 0,
        .CurNumber = 0,
        .CanConnect = 1
    },

    (SymbolObj){
        .Name = "-",
        .SymbolType = 3,
        .xIndex = 1,// -1
        .yIndex = 2,// 1-1
        .CurNumber = 6,
        .CanConnect = 1
    },

    (SymbolObj){
        .Name = ".",
        .SymbolType = 3,
        .xIndex = 0,// .1
        .yIndex = 0,// 0.1 or <TABLE>.<CHILD>
        .CurNumber = 7,
        .CanConnect = 1
    },
};

SymbolGetObj GetSymbols()
{
    int aSize = 0;
    SymbolObj * a = malloc(0);

    for (int i = 0; i < sizeof(Symbols) / sizeof(Symbols[0]); i++)
    {
        aSize++;
        a = realloc(a, aSize*sizeof(SymbolObj));
        a[aSize-1] = Symbols[i];
    }
    return (SymbolGetObj){
        .a = a,
        .aSize = aSize,
    };
}