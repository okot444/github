/*
 Текстовый файл	нечетные строки - имя игрока, четные строки - целое число, очки
 размер массива лучших игроков задается константой N
 Результаты хранятся в произвольном порядке
 Проверить, что массив полностью заполнен
 Создать два файла
	1. игроки в алфавитном порядке
 простой выбор
	2. в порядке убывания результатов
 простой обмен
 очки считывать как строку
 
 int atoi(char*s) - строку переводит в целое число
 int strcmp(char*s, char*t) - сравнивает строки s и t
 s=t - =0
 s<t - <0
 s>t - >0
 */
#define N 4
#define M 10
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct best // структура:  имя и очки
{
    int sc;
    char *name;
};
void obmen(best b[]);
void vibor (best b[]);
char *create(int sz)  //выделение памяти
{
    return (char*)malloc (sz*sizeof(char));
}
void erase (char *name)//освобождение памяти (1 элемент)
{
    free(name);
}
int check(FILE *f) // функция возвращает кол-во строк в файле
{
    char s[M+2];
    int i=0;
    while(!feof(f))
    {
        fgets(s, M+2, f);// \n
        i++;
    }
    //printf ("%i",i);
    return i;
}
void copyb(best b[],best cb[]) // глубокое копирование из b[]  в cb[]
{
    for (int i=0;i<N;i++)
        cb[i].name=create(M); // выделение памяти под имя
    for (int i=0;i<N;i++) // копирование имени
    {
        strcpy(cb[i].name, b[i].name);
        cb[i].sc=b[i].sc; // копирование очков
    }
}
void read(FILE*f,best b[])//чтение имени и очков (всей структуры)
{
    for (int i=0;i<N;i++)
    {
        b[i].name=create(M);
        fscanf (f,"%s\n %i",b[i].name,&b[i].sc);
    }
}
void print(FILE*f,best b[])// вывод на печать всей структуры
{
    for (int i=0;i<N;i++)
    {
        fprintf(f,"%s\n%i\n",b[i].name,b[i].sc);
    }
}
void ers(FILE*f,best b[]) // освобождение памяти (все элементы)
{
    for (int i=0;i<N;i++)
        erase(b[i].name);
}
void vibor (best *b) // простой выбор
{
    int no;
    best copysc;
    for (int i=0;i<N-1;i++)
    {
        no=i; // min-минимальное, no-его номер в массиве
        copysc=b[no];
        for (int j=no+1;j<N;j++) // цикл нахождения минимального
            if (strcmp(b[j].name,copysc.name)<0)
            {
                copysc=b[j];
                no=j;
            }
        b[no]=b[i]; // меняем местами наибольшее и наименьшее
        b[i]=copysc;
    }
}
void obmen(best b[]) // простой обмен
{
    best cname;
    for (int i=0; i<N-1; i++)
        for (int j=N-1; j>i; j--)
            if (b[j].sc<b[j-1].sc)// меняем местами два значения
            {
                cname=b[j-1];
                b[j-1]=b[j];
                b[j]=cname;
            }
}
int main()
{
    FILE*f;
    FILE*f1;
    FILE*f2;
    if((f=fopen("//Users//okot444//Desktop//t.txt","r"))!=NULL)
    {
        if (check(f)>=N)
        {
            if((f=fopen("//Users//okot444//Desktop//t.txt","r"))!=NULL)
            {
                best b[M]; // структура для сортировки по имени
                read(f,b);
                best cb[M]; // структура для сортировки по очкам
                copyb(b,cb);
                vibor(b);
                if ((f1=fopen("//Users//okot444//Desktop//name.txt","w"))!=NULL)
                {
                    print (f1,b);// вывод на печать отсортированного
                    ers(f1,b); // освобождение памяти
                }
                else
                    printf ("error w name");
                fclose(f1);
                obmen (cb);
                if ((f2=fopen("//Users//okot444//Desktop//score.txt","w"))!=NULL)
                {
                    print (f2,cb);// вывод на печать отсортированного
                    ers(f2,cb); // освобождение памяти
                }
                else
                    printf ("error r name");
                fclose(f2);
            }
        }
        else
            printf ("error N");
    }
    else
        printf("error_open");
    fclose(f);
    
}