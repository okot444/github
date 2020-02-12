// Упорядочить текстовый файл в порядке возрастания(с помощью простого слияния)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 5
void sort(FILE*f);
int numb(FILE*f);
void slit(FILE*f,FILE*f1,FILE*f2,char m,int n,int sr);
void erase (char *name)//освобождение памяти (1 элемент)
{
    free(name);
}
void writef(FILE*f,FILE*ff,int n) // ф-я записывает из f-файла  в ff-файл  n значений
{
    char s[M];
    int i=0;
    while (i<n)
    {
        fgets(s,M-1,f);
        fputs(s,ff); // запись в 1 файл
        i++;
    }
}
void slit(FILE*f,FILE*f1,FILE*f2,int n,int sr) // функция соединяет два файла в один
{
    char s1[M],s2[M]; // два значения (строки)
    fgets(s1,M-1,f1);
    fgets(s2,M-1,f2);
    do  // пока не закончится один из файлов
    {
        int e1=0,e2=0;
        while(e1<sr && e2<sr) // сравнение серий
        {
            if(strcmp(s1,s2)<=0) //
            {
                fputs(s1,f);
                fgets(s1,M-1,f1);
                e1++;
                if (feof(f1))
                    break;
            }
            else
            {
                fputs(s2,f);
                fgets(s2,M-1,f2);
                e2++;
                if (feof(f2))
                    break;
            }
        }
        if (!feof(f1)) // если 1 файл не закончился раньше чем серия
            while(e1<sr) //записываем оставшиеся значения
            {
                fputs(s1,f);
                fgets(s1,M-1,f1);
                e1++;
               
            }
        if(!feof(f2)) // если 2 файл не закончился раньше чем серия
            while(e2<sr) //записываем оставшиеся значения
            {
                fputs(s2,f);
                fgets(s2,M-1,f2);
                e2++;
            }
    }
    while (!feof(f1) && !feof(f2)); // цикл до конца какого-либо файла
    
     while (!feof(f1)) // оставшиеся значения в 1 файле после разбиения на серии
    {
        fputs(s1,f);
        fgets(s1,M-1,f1);
    }
    while(!feof(f2))// оставшиеся значения во 2 файле после разбиения на серии
    {
        fputs(s2,f);
        fgets(s2,M-1,f2);
    }
    
}
void file(FILE*f,FILE*f1,FILE*f2,int sz1,int n,int sr) // запись в файлы (разделение файла на два)
{
    writef(f,f1,sz1*sr); // запись в 1 файл
    writef(f,f2,n-sz1*sr);// запись во 2 файл
}
void sort(FILE*f) // функция сортировки простым слиянием
{
    int n=numb(f); // кол-во строк
    printf("n-'%i'",n);
    char s[]="//Users//okot444//Desktop//txt.txt";
    char s1[]="//Users//okot444//Desktop//1.txt";
    char s2[]="//Users//okot444//Desktop//2.txt";
    for (int sr=1; sr<n; sr*=2) // цикл по сериям
    {
        int sz1=(n/sr+1)/2; // кол-во серий в 1 файле
        f=fopen(s,"r");
        FILE*f1=fopen(s1,"w");
        FILE*f2=fopen(s2,"w");
        if(f1!=NULL)
        {
            if (f2!=NULL)
            {
                if (f!=NULL)
                {
                    file(f,f1,f2,sz1,n,sr);// запись в файлы
                    fclose(f);
                }
                fclose(f2);
            }
            fclose(f1);
        }
        else
            printf("error w");
        f=fopen(s,"w");
        f1=fopen(s1,"r");
        f2=fopen(s2,"r");
        if(f1!=NULL)
        {
            if (f2!=NULL)
            {
                if (f!=NULL)
                {
                    slit(f, f1, f2, n, sr); // выполняем сортировку простым слиянием
                    fclose(f);
                }
                fclose(f2);
            }
            fclose(f1);
        }
        else
            printf("error ");
    }
}
int numb(FILE*f) // ф-я возвращает кол-во строк в файле
{
    char s[M];
    int n=0;
    while(!feof(f))
    {
        fgets(s, M-1, f);
        if(feof(f))
            break;
        ++n;
    }
    return n;
}
int main()
{
    FILE*f;
    if((f=fopen("//Users//okot444//Desktop//txt.txt","r"))!=NULL)
    {
        sort(f);
        fclose(f);
    }
    else
        printf("error r");
}


/*void file(FILE*f,FILE*f1,FILE*f2,int sz1,int n,int sr) // запись в файлы (разделение файла на два)
 {
 char s[M];
 int i=0;
 while (i<sz1*sr) //sz1*sr - кол-во значений в 1 файле
 {
 fgets(s,M-1,f);
 fputs(s,f1); // запись в 1 файл
 i++;
 }
 while(i<n) // остальные значения во 2 файл
 {
 fgets(s,M-1,f);
 fputs(s,f2); // запись во 2 файл
 i++;
 }
 }
 
 */