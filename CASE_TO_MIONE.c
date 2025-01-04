//
// Created by calle on 24-12-28.
//

#include <tgmath.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "OBJECTS.h"
#include "SYMBOL_DEF.h"
#include "HeadFile/AllHeads.h"




char* Prompts[] =
{
    "=",
    "then",
    "else"
};


MioneObj *CMO(CaseObj*CASES,int CASESIZE,
    int * SIZE,int LineADD,int ColumnADD)
{

    HeadGetObj HeadGet = GetHeads();
    SymbolGetObj SymbolGet = GetSymbols();

    MioneObj *MIONE = 0;
    int MIONESIZE = 0;

    int ChildCount = 0; //子項數量






    int LastPaired = 0;


    int Lock = -1; //被封鎖到...

    int RF = 0; //Range Function

    VariableObj* Vars = malloc(0);
    int VarsSize = 0;

    CaseObj* Area = malloc(0);
    int AreaSize = 0;

    int Line = 0+LineADD;
    int Column = 0+ColumnADD;


    for (int i = 0; i <CASESIZE; i++)
    {

       if (Lock != i)
       {
            int Paired =0; //Head Symbol Prompt Variable Value

           if (CASES[i].ObjType == 13 || CASESIZE-1 == i)
           {
               Line++;
               Column = 0;
           };




        //HEAD
         if (ChildCount == 0) for (int Ci = 0; Ci < HeadGet.aSize; Ci++) if (strcmp(CASES[i].ObjName,HeadGet.a[Ci].Name) == 0)
        {

            HeadObj Head = (HeadObj){
                .Name = CASES[i].ObjName,
            };

             Column++;

            (MIONESIZE)++;
             (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
             (MIONE)[(MIONESIZE)-1] = (MioneObj){
                .ObjType= 1,
                .Head = Head,
                 .Line = Line,
                 .Column = Column
            };

            Paired = 1;

        }
        //PROMPT
         if (ChildCount == 0) for (int Ci = 0; Ci < sizeof( Prompts)/sizeof( Prompts[0]); Ci++) if (strcmp(CASES[i].ObjName,Prompts[Ci]) == 0)
        {

            PromptObj Prompt = (PromptObj){
                .Name = CASES[i].ObjName,
            };
             Column++;
            (MIONESIZE)++;
            (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
            (MIONE)[(MIONESIZE)-1] = (MioneObj){
                .ObjType= 2,
                .Prompt = Prompt,
                 .Line = Line,
                .Column = Column
            };
            Paired = 2;

        }


        //SYMBOL
         if (ChildCount == 0) for (int Ci = 0; Ci <SymbolGet.aSize; Ci++) if (strcmp(CASES[i].ObjName,SymbolGet.a[Ci].Name) == 0)
        {


            SymbolObj Symbol = (SymbolObj){
                .Name = CASES[i].ObjName,
                .SymbolType = SymbolGet.a[Ci].SymbolType,
                .CurNumber = SymbolGet.a[Ci].CurNumber,
            };
             Column++;

            (MIONESIZE)++;
            (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
            (MIONE)[(MIONESIZE)-1] = (MioneObj){
                .ObjType= 3,
                .Symbol = Symbol
                ,.Line = Line,
                .Column = Column
            };
            Paired = 3;

        }

        //Value : String
         if (ChildCount == 0) if (CASES[i].ObjType == 3)
        {

            Paired = 5;
            ValueObj Value = (ValueObj){.ValueType = 1, .String = CASES[i].ObjName};
             Column++;

            (MIONESIZE)++;
            (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
            (MIONE)[(MIONESIZE)-1] = (MioneObj){
                .ObjType= 5,
                .Val = Value,
                .Line = Line,
                .Column = Column
            };

        }



           //Value : Function or range END
           if (strcmp(CASES[i].ObjName,"end") == 0)
           {

               ChildCount--;
               if (ChildCount == 0) //僅包覆最高層的子向
               {
                   Paired = 5;

                   int MioObjSize = 0;

                   MioneObj * MioObj = CMO(Area,AreaSize,&MioObjSize,MIONE[MIONESIZE-1].Line,MIONE[MIONESIZE-1].Column);

                   AreaObj eArea = (AreaObj){
                       .Area =MioObj,
                       .Size = MioObjSize,
                       .Index = MIONESIZE,
                   };



                   ValueObj Value = (ValueObj){
                       .ValueType = RF == 1 ? 5 : 4,
                       .Area = eArea,
                   };


                   Column++;

                   (MIONESIZE)++ ;
                   (MIONE) = (MioneObj*)realloc(MIONE, (MIONESIZE)*sizeof(MioneObj));
                   (MIONE)[(MIONESIZE)-1] = (MioneObj){
                       .ObjType = 5,
                       .Val = Value,
                       .Line = Line,
                       .Column = Column
                   };

                   Area = NULL;
                   Area = malloc(0);
                   AreaSize = 0;




               }else
               {
                   AreaSize++;
                   Area = realloc(Area,AreaSize*sizeof(CaseObj));
                   Area[AreaSize-1] = CASES[i];
               }
           }else
           {
               if (ChildCount)
               {
                   AreaSize++;
                   Area = realloc(Area,AreaSize*sizeof(CaseObj));
                   Area[AreaSize-1] = CASES[i];


               }

           }

           //Value : Function
           if (strcmp(CASES[i].ObjName,"function") == 0)
           {
               ChildCount++;
               if (ChildCount == 1)
               {
                   RF = 2;
                   Paired = 5;

               }
           }


           //Value : Range


           if (strcmp(CASES[i].ObjName,"range") == 0)
           {
               ChildCount++;
               if (ChildCount == 1)
               {
                   RF = 1;
                   Paired = 5;

               }
           }




        //Value : NPNumber
            if (ChildCount == 0) if(CASES[i].ObjType == 2)
           {
               Paired = 5;


               long int V = 0;
               V=V+atoi(CASES[i].ObjName);

               ValueObj Value = (ValueObj){
                   .ValueType = 2,
                   .NPNumber = V
               };
                Column++;


               (MIONESIZE)++;
               (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
               (MIONE)[(MIONESIZE)-1] = (MioneObj){
                   .ObjType = 5,
                   .Val = Value,
                   .Line = Line,
                   .Column = Column
               };

           }

        //Variable



         if (ChildCount == 0) if (Paired == 0 && (CASES[i].ObjType != 13))
        {
            Paired = 4;

            int NewVar = 1;

            VariableObj Variable;

            for (int j = 0; j < VarsSize; j++)   if (Vars[j].Name == CASES[i].ObjName)
            {

                NewVar = 0;

                Variable = Vars[i];

                break;
            }

            if (NewVar)
            {
                Variable = (VariableObj){
                    .Name = CASES[i].ObjName,
                };

                VarsSize++;
                Vars = realloc(Vars,VarsSize*sizeof(VariableObj));
                Vars[VarsSize-1] = Variable;
            }

             Column++;

            (MIONESIZE)++;
            (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
            (MIONE)[(MIONESIZE)-1] = (MioneObj){
                .ObjType = 4,
                .Var = Variable,
                .Line = Line,
                 .Column = Column
            };
        };

        if (!ChildCount) //一班執行的子項內容
        {
        }
        LastPaired = Paired;
       }
    }



    (*SIZE) = (MIONESIZE);
    return MIONE;
}