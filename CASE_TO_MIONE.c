//
// Created by calle on 24-12-28.
//

#include <tgmath.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "OBJECTS.h"
#include "SYMBOL_DEF.h"
#include "PROMPT_DEF.h"
#include "HeadFile/AllHeads.h"




MioneObj *CMO(CaseObj*CASES,int CASESIZE,
    int * SIZE,int LineADD,int ColumnADD)
{


    MioneObj *MIONE = 0;
    int MIONESIZE = 0;

    int ChildCount = 0; //子項數量








    int Lock = -1; //被封鎖到...

    int goEndType = 0; //range or function or lights

    VariableObj* * VarsUP = malloc(0);
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
         if (ChildCount == 0) for (int Ci = 0;1; Ci++)
         {
             if (Heads[Ci].CurNumber == -1) break;

             if (strcmp(CASES[i].ObjName,Heads[Ci].Name) == 0)  {


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
         }
        //PROMPT
         if (ChildCount == 0) for (int Ci = 0;1; Ci++)
        {
             if (Prompts[Ci].CurNumber == -1) break;

             if (strcmp(CASES[i].ObjName,Prompts[Ci].Name) == 0)
             {

                 Column++;
                 (MIONESIZE)++;
                 (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
                 (MIONE)[(MIONESIZE)-1] = (MioneObj){
                     .ObjType= 2,
                     .Prompt = Prompts[Ci],
                      .Line = Line,
                     .Column = Column
                 };
                 Paired = 2;
             }


        }


        //SYMBOL
         if (ChildCount == 0) for (int Ci = 0; 1; Ci++)
        {
             if (Symbols[Ci].CurNumber == -1)  break;

             if (strcmp(CASES[i].ObjName,Symbols[Ci].Name) == 0)
             {
                 Column++;

                 (MIONESIZE)++;
                 (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
                 (MIONE)[(MIONESIZE)-1] = (MioneObj){
                     .ObjType= 3,
                     .Symbol = Symbols[Ci]
                     ,.Line = Line,
                     .Column = Column
                 };
                 Paired = 3;
             }
        }

        //Value : String
         if (ChildCount == 0) if (CASES[i].ObjType == 3|| CASES[i].ObjType == 4)
        {

            Paired = 5;
             char*str=malloc(0);

             for (int s = 1; s<strlen(CASES[i].ObjName); s++)
             {
                 str=realloc(str,s+1);
                 str[s-1] = s == strlen(CASES[i].ObjName)-1 ? '\0' :  CASES[i].ObjName[s];
             }

            ValueObj Value = (ValueObj){.ValueType = 1, .String = str};
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

           //Value : lights,function or range END 
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
                       .ValueType = goEndType == 1 ? 5 : (goEndType == 2 ? 4 : 7),
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
                   goEndType = 2;
                   Paired = 5;

               }
           }


           //Value : Range


           if (strcmp(CASES[i].ObjName,"range") == 0)
           {
               ChildCount++;
               if (ChildCount == 1)
               {
                   goEndType = 1;
                   Paired = 5;

               }
           }

           //Value : Lights


           if (strcmp(CASES[i].ObjName,"lights") == 0)
           {
               ChildCount++;
               if (ChildCount == 1)
               {
                   goEndType = 3;
                   Paired = 5;
               }
           }

           if (strcmp(CASES[i].ObjName,"true") == 0)
           {
               Paired = 5;
               ValueObj Value = (ValueObj){.ValueType = 8, .db = 1};
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
           if (strcmp(CASES[i].ObjName,"false") == 0)
           {
               Paired = 5;
               ValueObj Value = (ValueObj){.ValueType = 8, .db = 0};
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

            VariableObj* VariableUP = malloc(sizeof (VariableObj));

            for (int j = 0; j < VarsSize; j++)   if (strcmp(VarsUP[j]->Name ,CASES[i].ObjName)==0)
            {
                NewVar = 0;
                VariableUP = VarsUP[j];
                break;
            }

            if (NewVar)
            {
                *VariableUP = (VariableObj){
                    .Name = CASES[i].ObjName,
                };

                VariableObj * VUP = malloc(sizeof(VariableObj));
                VUP = VariableUP;

                VarsSize++;
                VarsUP = realloc(VarsUP,VarsSize*sizeof(VariableObj*));
                VarsUP[VarsSize-1] = VUP;
            }
             Column++;

            (MIONESIZE)++;
            (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
            (MIONE)[(MIONESIZE)-1] = (MioneObj){
                .ObjType = 4,
                .VarUP = VariableUP,
                .Line = Line,
                 .Column = Column
            };
        };
       }
    }

    (*SIZE) = (MIONESIZE);
    return MIONE;
}