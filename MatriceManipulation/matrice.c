#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h> 

typedef struct main_s {
    int pouce;
    int index;
    int majeur;
    int annulaire;
    int auriculaire;
}  Main_S;

#define MaxI (2)
#define MaxJ (2)

typedef Main_S Matrice[MaxI][MaxJ];
typedef Main_S MatriceDyn;

void PrintMain(Main_S *main)
{
    printf("Main: %p\n", main);
    printf("\tpouce = %d\n", main->pouce);
    printf("\tindex = %d\n", main->index);
    printf("\tmajeur = %d\n", main->majeur);
    printf("\tannulaire = %d\n", main->annulaire);
    printf("\tauriculaire = %d\n", main->auriculaire);
}

void InitMain(Main_S *main, size_t i )
{
    if ( main )
    {
        main->pouce = i;
        main->index = i+1;
        main->majeur = i+2;
        main->annulaire = i+3;
        main->auriculaire = i+4;
        PrintMain(main);
    }

}

void InitMatrice(Matrice *matr)
{
    printf("%s: \n", __func__);
    size_t len = sizeof(Matrice)/sizeof(Main_S);
    Main_S *ptr = (Main_S *)matr;

    for (size_t i=0;i<len;i++,ptr++)
    {
        InitMain(ptr, i);
    }
}

void PrintMatrice(Matrice *matr)
{
    printf("%s: \n", __func__);
    size_t len = sizeof(Matrice)/sizeof(Main_S);
    Main_S *ptr = (Main_S *)matr;
    printf("PrintMatrice: \n");
    for (size_t i=0;i<len;i++,ptr++)
        PrintMain(ptr);
    
}

void PrintMatrice1(Matrice *matr)
{
    printf("PrintMatrice1: \n");

    for (size_t i=0;i<MaxI;i++)
        for (size_t j=0;j<MaxJ;j++){
            printf("matr[%ld][%ld] = ", i, j);
            PrintMain((Main_S *)&((*matr)[i][j]));
        }
}

void InitMatriceDyn(MatriceDyn *matr, size_t maxI, size_t maxJ)
{
    printf("%s: \n", __func__);
    Main_S *ptr = (Main_S *)matr;

    for (size_t i=0;i<(maxI*maxJ);i++,ptr++)
    {
        InitMain(ptr, i);
    }
}

void PrintMatriceDyn(MatriceDyn *matr, size_t maxI, size_t maxJ)
{
    printf("%s: \n", __func__);
    Main_S *ptr = (Main_S *)matr;
    for (size_t i=0;i<(maxI*maxJ);i++,ptr++)
        PrintMain(ptr);
}

typedef struct MatriceDynData_s{
    MatriceDyn *matr;
    const size_t maxI;
    const size_t maxJ;
} MatriceDynData_t;

void InitMatriceDynData( MatriceDynData_t data)
{
    printf("%s: \n", __func__);

    Main_S *ptr = (Main_S *)data.matr;
    for (size_t i=0;i<(data.maxI*data.maxJ);i++,ptr++)
    {
        InitMain(ptr, i);
    }
}

void PrintMatriceDynData(MatriceDynData_t data)
{
    printf("%s: \n", __func__);

    Main_S *ptr = (Main_S *)data.matr;
    for (size_t i=0;i<(data.maxI*data.maxJ);i++,ptr++)
        PrintMain(ptr);
}

typedef Main_S *matrdyn[];

void PrintMatriceDynData1(MatriceDynData_t data)
{
    printf("%s: \n", __func__);
    Main_S *matr;
    for (size_t i=0;i<data.maxI;i++)
    {
        matr = (Main_S*)(&(data.matr[i*data.maxJ]));
        //matr = (Main_S*)((data.matr+=i*data.maxJ)); équivalent
        for (size_t j=0;j<data.maxJ;j++){
            printf("matr[%ld][%ld] = ", i, j);
            PrintMain((Main_S *)&(matr[j]));
        }
    }
}

void PrintMatriceDynData2(MatriceDynData_t data)
{
    printf("%s: \n", __func__);
    for (size_t i=0;i<data.maxI;i++)
    {
        for (size_t j=0;j<data.maxJ;j++){
            printf("matr[%ld][%ld] = ", i, j);
            PrintMain((Main_S *)&(data.matr[(i*data.maxJ)+j]));
        }
    }
}

void PrintMatriceDynData3(MatriceDynData_t data)
{
    Main_S (*matrix_ptr)[data.maxJ];
    matrix_ptr = (Main_S (*)[data.maxJ])(data.matr);
    printf("%s: \n", __func__);
    for (size_t i=0;i<data.maxI;i++)
    {
        for (size_t j=0;j<data.maxJ;j++){
            printf("matr[%ld][%ld] = ", i, j);
            PrintMain((Main_S *)&(matrix_ptr[i][j]));
        }
    }
}

MatriceDyn* AllocateMatriceDyn(size_t i, size_t j)
{
    printf("%s\n", __func__);
    MatriceDyn* matr;
    matr = (MatriceDyn*)malloc(i*j*sizeof(MatriceDyn));
    printf("matr = %p\n", matr);
    printf("i=%lu, j=%lu, sizeof(MatriceDyn)=%lu, i*j*sizeof = %lu\n", i, j, sizeof(MatriceDyn), i*j*sizeof(MatriceDyn));
    return matr;
}

bool AllocateMatriceDynData(MatriceDynData_t *data)
{
    printf("%s\n", __func__);
    data->matr = (MatriceDyn*)malloc(data->maxI*data->maxJ*sizeof(MatriceDyn));
    printf("matr = %p\n", data->matr);
    printf("i=%lu, j=%lu, sizeof(MatriceDyn)=%lu, i*j*sizeof = %lu\n", data->maxI, data->maxJ, sizeof(MatriceDyn), data->maxI*data->maxJ*sizeof(MatriceDyn));
    if(data->matr != NULL)
        return true;
    return false;
}

void FreeMatriceDyn(MatriceDyn* matr)
{
    printf("%s\n", __func__);
    printf("matr = %p\n", matr);
    free(matr);
}

void TestMatrice()
{
    printf("%s\n", __func__);
    Matrice maMatrice;
    InitMatrice(&maMatrice);
    PrintMatrice(&maMatrice);
    PrintMatrice1(&maMatrice);
}

void TestMatriceDyn()
{
    printf("%s\n", __func__);
    size_t maxI = 2;
    size_t maxJ = 3;
    MatriceDyn *matrD = AllocateMatriceDyn(maxI, maxJ);
    printf("matrD %p\n", matrD);
    InitMatriceDyn(matrD, maxI, maxJ);
    PrintMatriceDyn(matrD, maxI, maxJ);

    FreeMatriceDyn(matrD);

}

void TestMatriceDynData()
{
    printf("%s\n", __func__);
    MatriceDynData_t data = { .matr = NULL, .maxI = 2, .maxJ = 3};
    if(AllocateMatriceDynData(&data))
    {
        printf("matrD %p\n", data.matr);
        InitMatriceDynData(data);
        PrintMatriceDynData(data);
        PrintMatriceDynData1(data);
        PrintMatriceDynData2(data);
        PrintMatriceDynData3(data);
        FreeMatriceDyn(data.matr);
    }
    else
    {
        printf("Grosse erreur, quitter immédiatement\n");
    }
}

int main(int argc, char* argv[], char* env[])
{
    if (false)
        TestMatrice();
    if (false)
        TestMatriceDyn();
    if (true)
        TestMatriceDynData();

    printf("Bonjour Léa!\n");
    printf("Bonjour Mathis! \n");
    printf("Bonjour Catherine!\n");
    return 0;
}

/*
typedef Main_S Matrice[MaxI][MaxJ];
void FreeMatriceDyn(MatriceDyn* matr)

void FreeMatriceDyn(Main_S* matr[MaxI][MaxJ])
void FreeMatriceDyn(struct main_s* matr[MaxI][MaxJ])
*/