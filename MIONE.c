//
// Created by calle on 24-12-28.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "OBJECTS.h"
#include "MIONE.h"
#include "HeadFile/AllHeads.h"
#include "HeadFile/SVV.h"
#include "ERR.h"



ValueReturnObj Function(const MioneObj* Objs, const int ObjsSize,const ValueObj* Request, const int RequestSize)
{
    HeadGetObj HeadGet = GetHeads();
    

    MioneObj Head = (MioneObj) {
        .ObjType = 0
    };

    HeadReturnObj (*HeadFuc)(struct _PairObject* Pairs, int PairsSize) = 0;
    PairObj *Pairs = malloc(0);
    int PairsSize = 0;

    for (int index = 0; index < ObjsSize; index++)
    {
        MioneObj Mio = Objs[index];

        if (Mio.ObjType == 1) Head = Mio;

        if ((Mio.ObjType == 3 && strcmp(Mio.Symbol.Name, ";") == 0) || Mio.ObjType == 1)
        {
            if (HeadFuc != 0) {
                HeadReturnObj a = HeadFuc(Pairs, PairsSize);

                HeadFuc = 0;
                Pairs = NULL;
                PairsSize = 0;

                switch (a.ToState)
                {
                case 1:
                    return a.Vs;
                case 2:
                    index = index - a.Useless; //-1+1
                }

                if (Mio.ObjType == 3 && strcmp(Mio.Symbol.Name, ";") == 0)continue;

            }
        }

        if (Mio.ObjType == 1) // Head
        {
            for (int i = 0; i < HeadGet.aSize; i++)
            {
                if (strcmp(Mio.Head.Name, HeadGet.a[i].Name) == 0)
                {
                    PairsSize++;
                    Pairs = realloc(Pairs, sizeof(struct _PairObject) * PairsSize);
                    Pairs[PairsSize - 1].Prompt = Mio; // Type = 1

                    Pairs[PairsSize - 1].SourceSize = 0;
                    Pairs[PairsSize - 1].Source = malloc(0);

                    HeadFuc = HeadGet.a[i].Fuc;
                }
            }
        }

        if (Mio.ObjType == 2) // PROMPT
        {
            PairsSize++;
            Pairs = realloc(Pairs, sizeof(struct _PairObject) * PairsSize);

            Pairs[PairsSize - 1].SourceSize = 0;
            Pairs[PairsSize - 1].Source = malloc(0);
            Pairs[PairsSize - 1].Prompt = Mio; // Type = 2
        }

        if (Mio.ObjType == 3 || Mio.ObjType == 4 || Mio.ObjType == 5) // SVV
        {
            if (Head.ObjType == 0) { // 偽HeadFuc
                PairsSize++;
                Pairs = realloc(Pairs, sizeof(struct _PairObject) * PairsSize);
                Pairs[PairsSize - 1].Prompt = Mio; // 自主

                Pairs[PairsSize - 1].SourceSize = 0;
                Pairs[PairsSize - 1].Source = malloc(0);




                HeadFuc = SVV;
            }

            (Pairs[PairsSize - 1].SourceSize)++;
            (Pairs[PairsSize - 1].Source) = realloc(Pairs[PairsSize - 1].Source, sizeof(MioneObj) * (Pairs[PairsSize - 1].SourceSize));
            Pairs[PairsSize - 1].Source[Pairs[PairsSize - 1].SourceSize - 1] = Mio;
        }

        if (ObjsSize - 1 == index)
        {
            if (HeadFuc != 0) {
                HeadReturnObj a = HeadFuc(Pairs, PairsSize);

                HeadFuc = 0;
                Pairs = NULL;
                PairsSize = 0;





                switch (a.ToState)
                {
                case 1:
                    return a.Vs;

                case 2:
                    index = index - a.Useless; //-1+1
                }


            }
        }
        WorkOnMioIndex++;
    }
}

ValueReturnObj mione(const MioneObj* Objs, const int ObjsSize)
{
    HeadGetObj HeadGet = GetHeads();

    // system("clear");

    MioneObj Head = (MioneObj) {
        .ObjType = 0
    };

    HeadReturnObj (*HeadFuc)(struct _PairObject* Pairs, int PairsSize) = 0;
    PairObj *Pairs = malloc(0);
    int PairsSize = 0;

    for (int index = 0; index < ObjsSize; index++)
    {
        MioneObj Mio = Objs[index];

        if (Mio.ObjType == 1) Head = Mio;

        if ((Mio.ObjType == 3 && strcmp(Mio.Symbol.Name, ";") == 0) || Mio.ObjType == 1)
        {
            if (HeadFuc != 0) {
                HeadReturnObj a = HeadFuc(Pairs, PairsSize);

                HeadFuc = 0;
                Pairs = NULL;
                PairsSize = 0;

                switch (a.ToState)
                {
                case 1:
                    return a.Vs;
                case 2:
                    index = index - a.Useless; //-1+1
                }

                if (Mio.ObjType == 3 && strcmp(Mio.Symbol.Name, ";") == 0)continue;

            }
        }

        if (Mio.ObjType == 1) // Head
        {
            for (int i = 0; i < HeadGet.aSize; i++)
            {
                if (strcmp(Mio.Head.Name, HeadGet.a[i].Name) == 0)
                {
                    PairsSize++;
                    Pairs = realloc(Pairs, sizeof(struct _PairObject) * PairsSize);
                    Pairs[PairsSize - 1].Prompt = Mio; // Type = 1

                    Pairs[PairsSize - 1].SourceSize = 0;
                    Pairs[PairsSize - 1].Source = malloc(0);

                    HeadFuc = HeadGet.a[i].Fuc;
                }
            }
        }

        if (Mio.ObjType == 2) // PROMPT
        {
            PairsSize++;
            Pairs = realloc(Pairs, sizeof(struct _PairObject) * PairsSize);

            Pairs[PairsSize - 1].SourceSize = 0;
            Pairs[PairsSize - 1].Source = malloc(0);
            Pairs[PairsSize - 1].Prompt = Mio; // Type = 2
        }

        if (Mio.ObjType == 3 || Mio.ObjType == 4 || Mio.ObjType == 5) // SVV
        {
            if (Head.ObjType == 0) { // 偽HeadFuc
                PairsSize++;
                Pairs = realloc(Pairs, sizeof(struct _PairObject) * PairsSize);
                Pairs[PairsSize - 1].Prompt = Mio; // 自主

                Pairs[PairsSize - 1].SourceSize = 0;
                Pairs[PairsSize - 1].Source = malloc(0);

                HeadFuc = SVV;
            }

            (Pairs[PairsSize - 1].SourceSize)++;
            (Pairs[PairsSize - 1].Source) = realloc(Pairs[PairsSize - 1].Source, sizeof(MioneObj) * (Pairs[PairsSize - 1].SourceSize));
            Pairs[PairsSize - 1].Source[Pairs[PairsSize - 1].SourceSize - 1] = Mio;
        }

        if (ObjsSize - 1 == index)
        {
            if (HeadFuc != 0) {
                HeadReturnObj a = HeadFuc(Pairs, PairsSize);

                HeadFuc = 0;
                Pairs = NULL;
                PairsSize = 0;


                switch (a.ToState)
                {
                case 1:
                    return a.Vs;

                case 2:
                    index = index - a.Useless; //-1+1
                    break;
                }
            }
        }
        WorkOnMioIndex++;
    }
}