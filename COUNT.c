//
// Created by calle on 24-11-3.
//

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ERR.h"
#include "Mione.h"
#include "SYMBOL_DEF.h"



CountObj COUNT(MioneObj*Pack,int PackSize)
{
    SymbolGetObj SymbolGet = GetSymbols();

    int FirstBracketIndex = 0;
    int IfBrackets = 0; // 0 = 0 1 = only ( 2 = ()
    int PairsOfBrackets = 0;


    MioneObj* inBracket = malloc(0);
    int inBracketSize = 0;

    int CalculateType = 0;

    int CalculateLevel = 0;

    for(int i = 0; i < PackSize; i++)
    {

        int PastCost = 0;//符號所前扣之值

        if (Pack[i].ObjType == 3) // Symbol
        {

            if (strcmp(Pack[i].Symbol.Name, "(") == 0)
            {

                FirstBracketIndex = i;
                IfBrackets = 1;

            }
            else if (strcmp(Pack[i].Symbol.Name, ")") == 0)
            {

                if (IfBrackets)
                {
                    PairsOfBrackets++;
                    IfBrackets = 0;

                    int FunctionCalled = 0;

                    CountObj ChildCount = COUNT(inBracket, inBracketSize);

                    if (FirstBracketIndex > 0)
                    {

                        if (Pack[FirstBracketIndex - 1].ObjType == 4 || Pack[FirstBracketIndex - 1].ObjType == 5)
                        {

                            if (Pack[FirstBracketIndex - 1].ObjType == 4)
                            {

                                if (Pack[FirstBracketIndex - 1].Var.V.ValueType == 4)
                                {


                                  printf("errr I didnt expect this to happen");
                                    exit(99);
                                }
                                else
                                {
                                    char *str1 = "The Type of `";
                                    char *str2 = "` isn't a FUNCTION";
                                    char *VName = Pack[FirstBracketIndex - 1].Var.Name;

                                    char *REASON = malloc(sizeof(char) * (int)(strlen(str1) + strlen(str2) + strlen(VName) + 1));
                                    strcpy(REASON, str1);
                                    strcat(REASON, VName);
                                    strcat(REASON, str2);

                                    ErrCall(
                                        REASON,
                                            "MG001",
                                        "Maybe you can change the Variable Type to FUNCTION.",
                                        Pack[FirstBracketIndex - 1].Line,
                                        Pack[FirstBracketIndex - 1].Column
                                    );
                                }
                            }
                            else
                            {

                                if (Pack[FirstBracketIndex - 1].Val.ValueType == 4)
                                {





                                    ValueReturnObj V = Function(
                                        Pack[FirstBracketIndex - 1].Val.Area.Area,
                                        Pack[FirstBracketIndex - 1].Val.Area.Size,
                                        ChildCount.Value,
                                        ChildCount.ValueSize
                                        );

                                    MioneObj* NewPack = malloc(0);
                                    int NewPackSize = 0;

                                    for (int index = 0; index < FirstBracketIndex-1; index++)
                                    {
                                        NewPackSize++;
                                        NewPack = realloc(NewPack, sizeof(MioneObj) * (NewPackSize));
                                        NewPack[NewPackSize - 1] = Pack[index];
                                    }

                                    printf("sizoe of fuc returned : %d\n",V.ValueSize);

                                    if (V.ValueSize)
                                    {
                                        for (int index = 0; index < V.ValueSize; index++)
                                        {
                                            NewPackSize++;
                                            NewPack = realloc(NewPack, sizeof(MioneObj) * (NewPackSize));
                                            NewPack[NewPackSize - 1] = (MioneObj){
                                                .ObjType = 5,
                                                .Val = V.Value[index]
                                            };

                                        }

                                    }else
                                    {
                                        NewPackSize++;
                                        NewPack = realloc(NewPack, sizeof(MioneObj) * (NewPackSize));
                                        NewPack[NewPackSize - 1] = (MioneObj){
                                            .ObjType = 5,
                                            .Val = (ValueObj){
                                            .ValueType = 2,.NPNumber = 0}
                                        };
                                    }


                                    for (int index = i+1 ; index < PackSize; index++)
                                    {

                                        NewPackSize++;
                                        NewPack = realloc(NewPack, sizeof(MioneObj) * (NewPackSize));
                                        NewPack[NewPackSize - 1] = Pack[index];
                                    }

                                    PackSize = NewPackSize;
                                    Pack = NewPack;


                                    i = FirstBracketIndex - 1;





                                    //todo function call
                                    FunctionCalled = 1;
                                }
                                else
                                {
                                    ErrCall(
                                        "The Value before `()` Isn't a Function",
                                        "MG002",
                                        "Maybe you can try `function() <...:Mione> end()`.",
                                        Pack[FirstBracketIndex - 1].Line,
                                        Pack[FirstBracketIndex - 1].Column
                                    );
                                }
                            }
                        }
                    }

                    if (!FunctionCalled)
                    {
                        MioneObj* NewPack = malloc(0);
                        int NewPackSize = 0;

                        for (int index = 0; index < FirstBracketIndex; index++)
                        {
                            NewPackSize++;
                            NewPack = realloc(NewPack, NewPackSize * sizeof(MioneObj));
                            NewPack[NewPackSize - 1] = Pack[index];
                        }

                        for (int index = 0; index < ChildCount.ValueSize; index++)
                        {
                            NewPackSize++;
                            NewPack = realloc(NewPack, NewPackSize * sizeof(MioneObj));
                            NewPack[NewPackSize - 1] = (MioneObj){
                                .ObjType = 5,
                                .Val = ChildCount.Value[index]
                            };
                        }

                        for (int index = i + 1; index < PackSize; index++)
                        {
                            NewPackSize++;
                            NewPack = realloc(NewPack, NewPackSize * sizeof(MioneObj));
                            NewPack[NewPackSize - 1] = Pack[index];
                        }

                        Pack = NewPack;
                        PackSize = NewPackSize;

                        i = FirstBracketIndex -1;
                    }
                }

            }
            else
            {

                if(!IfBrackets)
                {
                    switch (Pack[i].Symbol.SymbolType)
                    {
                    case 1:

                        if (i == PackSize - 1 || i - 1 <0)
                        {
                            ErrCall(
                                "You can't connect any Two-side-count-SymbolGet.a to VOID (Meaning Nothing, even no Mione Object).",
                                "MG003",
                                "Maybe you can try `1+1` or anything else.",
                                Pack[i].Line,
                                Pack[i].Column
                            );
                        }
                        for (int index = 0; index < SymbolGet.aSize; index++)
                        {
                            if (SymbolGet.a[index].xIndex == CalculateLevel) if (strcmp(SymbolGet.a[index].Name, Pack[i].Symbol.Name) == 0)CalculateType = SymbolGet.a[index].CurNumber;
                        }
                        break;
                    case 2:

                        if (i == PackSize - 1)
                        {
                            ErrCall(
                                "bbbbb",
                                "MG007",
                                "Maybe you can try `typeof 1` or anything else.",
                                Pack[i].Line,
                                Pack[i].Column
                            );
                        }
                        for (int index = 0; index < SymbolGet.aSize; index++)
                        {
                            if (SymbolGet.a[index].xIndex == CalculateLevel) if (strcmp(SymbolGet.a[index].Name, Pack[i].Symbol.Name) == 0)CalculateType = SymbolGet.a[index].CurNumber;
                        }
                       break;
                    case 3:

                        if (i == PackSize - 1)
                        {
                            ErrCall(
                               "ccccc",
                               "MG008",
                               "Maybe you can try `- 1` or anything else.",
                                Pack[i].Line,
                                Pack[i].Column
                           );
                        }


                        for (int index = 0; index < SymbolGet.aSize; index++)
                        {
                            if (strcmp(SymbolGet.a[index].Name, Pack[i].Symbol.Name) == 0)
                            {

                                if (i-1>=0 && (Pack[i-1].ObjType == 4 || Pack[i-1].ObjType == 5))
                                {

                                    if (SymbolGet.a[index].yIndex == CalculateLevel)  CalculateType = SymbolGet.a[index].CurNumber;

                                }else
                                {

                                    if (SymbolGet.a[index].xIndex == CalculateLevel) CalculateType = SymbolGet.a[index].CurNumber;

                                }

                            }

                        }
                        break;


                    }

                }
            }
        }else if (Pack[i].ObjType == 4 || Pack[i].ObjType == 5)
        {
            if (CalculateType)
            {
                MioneObj Out;
                int UsePointNumber = 0;

                switch (CalculateType)
                {
                    case 1: // +
                        if (Pack[i - 2].ObjType == 4 || Pack[i - 2].ObjType == 5)
                        {
                            ValueObj Target1 ;
                            ValueObj Target2 ;





                            if (Pack[i - 2].ObjType == 4) Target1 = Pack[i - 2].Var.V; else Target1 = Pack[i - 2].Val;
                            if (Pack[i].ObjType == 4) Target2 = Pack[i].Var.V; else Target2 = Pack[i].Val;




                            if (!(Target1.ValueType == 2 || Target1.ValueType == 3)){ ErrCall("Type Error","MG0011111","",
                                Pack[i].Line,
                                Pack[i].Column);}
                            if (!(Target2.ValueType == 2 || Target2.ValueType == 3)) {ErrCall("Type Error","MG0011111","",
                                Pack[i].Line,
                                Pack[i].Column);}

                            if (Target1.ValueType == 3) UsePointNumber = 1;
                            if (Target2.ValueType == 3) UsePointNumber = 1;

                            if (UsePointNumber)
                            {
                                long double Value1 = 0;
                                long double Value2 = 0;



                                if (Target2.ValueType == 3)
                                {
                                    if (Target1.ValueType == 3) Value1 = Target1.PNumber; else Value1 = (long double)Target1.NPNumber;
                                    Value2 = Target2.PNumber;
                                }
                                else
                                {
                                    Value1 = Target1.PNumber;
                                    Value2 = (long double)Target2.NPNumber;

                                }

                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 3,
                                        .PNumber = Value1 + Value2,
                                    }
                                };

                                PastCost = 2;
                            }
                            else
                            {
                                long int Value1 = 0;
                                long int Value2 = 0;

                                Value1 = Target1.NPNumber;
                                Value2 = Target2.NPNumber;




                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 2,
                                        .NPNumber = Value1 + Value2,
                                    }
                                };

                                PastCost = 2;
                            }
                        }
                        else
                        {
                            ErrCall(
                                "You must only connect Two-side-count-SymbolGet.a to VV(Variable or Value).",
                                "MG005",
                                "Maybe you can try `1+1` or anything else.",
                                Pack[i].Line,
                                Pack[i].Column
                            );
                        }
                        CalculateType = 0;
                        break;
                    case 3: // *
                        if (Pack[i - 2].ObjType == 4 || Pack[i - 2].ObjType == 5)
                        {
                            ValueObj Target1 ;
                            ValueObj Target2 ;

                            if (Pack[i - 2].ObjType == 4) Target1 = Pack[i - 2].Var.V; else Target1 = Pack[i - 2].Val;
                            if (Pack[i].ObjType == 4) Target2 = Pack[i].Var.V; else Target2 = Pack[i].Val;

                            if (!(Target1.ValueType == 2 || Target1.ValueType == 3)) ErrCall("Type Error 1","MG0011113","",
                                Pack[i].Line,
                                Pack[i].Column);
                            if (!(Target2.ValueType == 2 || Target2.ValueType == 3)) ErrCall("Type Error 2","MG0011113","",
                                Pack[i].Line,
                                Pack[i].Column);

                            if (Target1.ValueType == 3) UsePointNumber = 1;
                            if (Target2.ValueType == 3) UsePointNumber = 1;


                            if (UsePointNumber)
                            {
                                long double Value1 = 0;
                                long double Value2 = 0;



                                if (Target2.ValueType == 3)
                                {
                                    if (Target1.ValueType == 3) Value1 = Target1.PNumber; else Value1 = (long double)Target1.NPNumber;
                                    Value2 = Target2.PNumber;
                                }
                                else
                                {
                                    Value1 = Target1.PNumber;
                                    Value2 = (long double)Target2.NPNumber;

                                }

                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 3,
                                        .PNumber = Value1 * Value2,
                                    }
                                };

                                PastCost = 2;
                            }
                            else
                            {
                                long int Value1 = 0;
                                long int Value2 = 0;

                                Value1 = Target1.NPNumber;
                                Value2 = Target2.NPNumber;




                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 2,
                                        .NPNumber = Value1 * Value2,
                                    }
                                };

                                PastCost = 2;
                            }
                        }
                        else
                        {
                            ErrCall(
                                "You must only connect Two-side-count-SymbolGet.a to VV(Variable or Value).",
                                "MG005",
                                "Maybe you can try `1*1` or anything else.",
                                Pack[i].Line,
                                Pack[i].Column
                            );
                        }
                        CalculateType = 0;
                        break;

                case 6: //-
                    if (i-2>=0 && (Pack[i - 2].ObjType == 4 || Pack[i - 2].ObjType == 5))
                    {
                        // 1- 1
                         ValueObj Target1 ;
                            ValueObj Target2 ;





                            if (Pack[i - 2].ObjType == 4) Target1 = Pack[i - 2].Var.V; else Target1 = Pack[i - 2].Val;
                            if (Pack[i].ObjType == 4) Target2 = Pack[i].Var.V; else Target2 = Pack[i].Val;

                        if (!(Target1.ValueType == 2 || Target1.ValueType == 3)) ErrCall("Type Error 3","MG0011116","",
                            Pack[i].Line,
                            Pack[i].Column);
                        if (!(Target2.ValueType == 2 || Target2.ValueType == 3)) ErrCall("Type Error 4","MG0011116","",
                            Pack[i].Line,
                            Pack[i].Column);

                            if (Target1.ValueType == 3) UsePointNumber = 1;
                            if (Target2.ValueType == 3) UsePointNumber = 1;

                            if (UsePointNumber)
                            {
                                long double Value1 = 0;
                                long double Value2 = 0;



                                if (Target2.ValueType == 3)
                                {
                                    if (Target1.ValueType == 3) Value1 = Target1.PNumber; else Value1 = (long double)Target1.NPNumber;
                                    Value2 = Target2.PNumber;
                                }
                                else
                                {
                                    Value1 = Target1.PNumber;
                                    Value2 = (long double)Target2.NPNumber;

                                }

                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 3,
                                        .PNumber = Value1 -  Value2,
                                    }
                                };

                                PastCost = 2;
                            }
                            else
                            {
                                long int Value1 = 0;
                                long int Value2 = 0;

                                Value1 = Target1.NPNumber;
                                Value2 = Target2.NPNumber;




                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 2,
                                        .NPNumber = Value1 - Value2,
                                    }
                                };

                                PastCost = 2;
                            }
                    }else
                    {
                        // -1
                        ValueObj Target;



                        if (Pack[i].ObjType == 4) Target = Pack[i].Var.V;
                        if (Pack[i].ObjType == 5) Target = Pack[i].Val;

                        if (Target.ValueType == 3) UsePointNumber = 1;


                        if (Target.ValueType == 2 || Target.ValueType == 3){}else
                        {
                            ErrCall("Type error aaaa","MG00111","aa",
                                Pack[i].Line,
                                Pack[i].Column);
                        }


                        if (UsePointNumber)
                        {
                            long double Value1 = 0;

                            Value1 = Target.PNumber*-1;


                            Out = (MioneObj){
                                .ObjType = 5,
                                .Val = (ValueObj){
                                    .ValueType = 3,
                                    .PNumber = Value1
                                }
                            };

                            PastCost = 1;
                        }else
                        {
                            long int Value1 = 0;

                            Value1 = Target.NPNumber*-1;


                            Out = (MioneObj){
                                .ObjType = 5,
                                .Val = (ValueObj){
                                    .ValueType = 2,
                                    .NPNumber = Value1
                                }
                            };

                            PastCost = 1;
                        }

                    }
                    CalculateType = 0;
                    break;
                case 7: // .

                    if (i-2>=0 && (Pack[i - 2].ObjType == 4 || Pack[i - 2].ObjType == 5))
                    {
                        // 1.1
                            ValueObj Target1 ;
                            ValueObj Target2 ;


                        if (Pack[i - 2].ObjType == 4) ErrCall("to do ; Variable can`t be Point Number","MG00111","IT IS TODO NOT ERROR",
                            Pack[i].Line,
                            Pack[i].Column); else Target1 = Pack[i - 2].Val;
                        if (Pack[i].ObjType == 4) ErrCall("to do ; Variable can`t be Point Number","MG00111","IT IS TODO NOT ERROR",
                            Pack[i].Line,
                            Pack[i].Column); else Target2 = Pack[i].Val;

                        if (!(Target1.ValueType == 2 || Target1.ValueType == 3)) ErrCall("TODO!!!","MG001131211","",
                            Pack[i].Line,
                            Pack[i].Column);
                        if (!(Target2.ValueType == 2 || Target2.ValueType == 3)) ErrCall("TODO!!!","MG001131211","",
                            Pack[i].Line,
                            Pack[i].Column);

                            if (Target1.ValueType == 3) UsePointNumber = 1;
                            if (Target2.ValueType == 3) UsePointNumber = 1;

                            if (UsePointNumber)
                            {
                                ErrCall("Point Number can`t change in to another Point Number","123456","",
                                Pack[i].Line,
                                Pack[i].Column);
                            }
                            else
                            {
                                long double Value1 = 0;
                                long double Value2 = 0;

                                Value1 = Target1.NPNumber;
                                Value2 = Target2.NPNumber;

                                long double Points = 0;
                                //LOCKED MAX NUMBER = 10^10
                                for (int x = 1; x < 10; x++)
                                {
                                    int cmp=1;
                                    for (int y = 1; y < x; y++)cmp*=10;

                                    if (cmp>Value2)
                                    {
                                        Points = Value2/cmp;
                                        break;
                                    }
                                }


                                Out = (MioneObj){
                                    .ObjType = 5,
                                    .Val = (ValueObj){
                                        .ValueType = 3,
                                        .PNumber = Value1*1 + Points,
                                    }
                                };

                                PastCost = 2;
                            }
                    }else
                    {
                        // .1
                        ValueObj Target;

                        if (Pack[i].ObjType == 4) ErrCall("to do ; Variable can`t be Point Number","MG00111","IT IS TODO NOT ERROR",
                                Pack[i].Line,
                                Pack[i].Column);
                        if (Pack[i].ObjType == 5) Target = Pack[i].Val;

                        if (Target.ValueType == 3) UsePointNumber = 1;

                        if (Target.ValueType == 2 || Target.ValueType == 3){}else
                        {
                            ErrCall("Type error aaaabbbbbb","MG00111","aa",
                                Pack[i].Line,
                                Pack[i].Column);
                        }


                        if (UsePointNumber)
                        {
                            ErrCall("Point Number can`t change in to another Point Number","123456","",
                                Pack[i].Line,
                                Pack[i].Column);
                        }else
                        {
                            long int Value1 = 0;

                            Value1 = Target.NPNumber;

                            long double Points = 0;
                            //LOCKED MAX NUMBER = 10^10
                            for (int x = 1; x < 10; x++)
                            {
                                int cmp=1;
                                for (int y = 1; y < x; y++)cmp*=10;

                                if (cmp>Value1)
                                {

                                    Points = (long double)Value1/cmp;

                                    break;
                                }
                            }

                            Out = (MioneObj){
                                .ObjType = 5,
                                .Val = (ValueObj){
                                    .ValueType = 3,
                                    .PNumber = Points
                                }
                            };

                            PastCost = 1;
                        }

                    }
                    CalculateType = 0;
                    break;
                    default:
                        break;
                }

                MioneObj* NewPack = malloc(0);
                int NewPackSize = 0;


                for (int index = 0; index < i - PastCost; index++)
                {
                    NewPackSize++;
                    NewPack = realloc(NewPack, sizeof(MioneObj) * (NewPackSize));
                    NewPack[NewPackSize - 1] = Pack[index];
                }

                NewPackSize++;
                NewPack = realloc(NewPack, sizeof(MioneObj) * (NewPackSize));
                NewPack[NewPackSize - 1] = Out;
                int ToIndex = NewPackSize - 1;

                for (int index = i + 1; index < PackSize; index++)
                {
                    NewPackSize++;
                    NewPack = realloc(NewPack, sizeof(MioneObj) * (NewPackSize));
                    NewPack[NewPackSize - 1] = Pack[index];
                }

                PackSize = NewPackSize;
                Pack = NewPack;

                i = ToIndex-1;
            }
        }

        if (IfBrackets)
        {
            if (Pack[i].ObjType == 3 && strcmp(Pack[i].Symbol.Name, "(") == 0) {}
            else
            {
                inBracketSize++;
                inBracket = realloc(inBracket, sizeof(MioneObj) * (inBracketSize));
                inBracket[inBracketSize - 1] = Pack[i];
            }
        }

        if (i == PackSize - 1)
        {
            CalculateLevel++;
            i = -1;// ...困擾了我好久
            if (CalculateLevel > 3) { break; }

        }
    }

    ValueObj * VPack = malloc(0);
    int VPackSize = 0;


    for (int i = 0; i < PackSize; i++)
    {

        if ( Pack[i].ObjType == 5)
        {
            VPackSize ++;
            VPack = realloc(VPack, sizeof(MioneObj) * (VPackSize));
            VPack[VPackSize-1] = Pack[i].Val;
            printf("d %Lf\n",(long double)Pack[i].Val.PNumber);
        }

    }


    CountObj Returns = (CountObj){
        .Value = VPack,
        .ValueSize= VPackSize
    };


    return Returns;
}


