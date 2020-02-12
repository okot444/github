/*
 Массив, размерности которого задаются с клавиатуры заполняется случайными значениями
 (кол-во строк не обязательно равно кол-ву столбцов)
 отсортировать массив по возрастанию сумм столбцов методом простой вставки.
 получившийся массив вывести на печать.
 
 1141  1114
 7151  1175
 3261  1236
 
 Заполнение массива должно происходить построчно.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int ** create (int sz1, int sz2);//выделение памяти под массив
int* crt (int sz);
void erase (int **m, int sz1, int sz2); //удалить из памяти
void ers (int *m,int sz);  //освобождение памяти
void init (int **m, int sz1, int sz2); //задать элементы
void print (int **m, int sz1, int sz2); //напечатать
int sums( int **m,int qr, int st);
void sort(int **m,int sz1, int sz2);// сортировка
void transp (int **p,int sz1, int sz2, int **m);// функция меняет строки и столбцы в массиве m (для прямоугольного)
void insert (int **p,int sz1, int sz2, int**m); // сортировка(вставка)
void sumst(int **m, int*s, int sz1, int sz2);
void trspn (int ** m, int sz1, int sz2); // для квадратного массива
int main ()
{
    int **m,r,c;// массив m , r- кол-во строк, с- кол-во столбцов
    scanf ("%i %i",&r,&c);
    if (r>0&&c>0)
    {
        m=create(r,c);// выделение памяти под массив
        init(m,r,c); // инициализация
        print(m,r,c); // печать
        sort(m,r,c); // сортировка
        print (m,r,c);// печать отсортированного массива
        printf("\n");
        erase(m,r,c); // освобождение памяти
    }
    else printf ("error");
}
void sort(int **m,int sz1, int sz2) //сортировка по возрастанию сумм столбцов
{
    int **p=create(sz2, sz1); // выделение памяти под двумерный массив
    if (sz1==sz2) // если квадратный массив
    {
        trspn(m,sz1,sz2);
        insert(m,sz1,sz2,m);
        trspn(m,sz1,sz2);
    }
    else // прямоугольный
    {
        transp(p,sz2,sz1,m);
        insert(p,sz1,sz2,m);
        transp(m,sz1,sz2,p);
        erase(p,sz2,sz1);
    }
    
}
int ** create (int sz1, int sz2)// выделение памяти под двумерный массив, ф-я возвращает указатель на первый элемент
{
    int**t=(int**)malloc(sizeof(int*)*sz1); //создать указатели на строки sz1-кол-во элементов массива хранящего адреса
    int i;
    for(i=0; i<sz1; i++) //создание строк
        t[i]=(int*)malloc(sizeof(int)*sz2);//*(t+i)
    return t;
}
void init(int**m, int sz1, int sz2)//иничицализация двумерного массива
{
    srand((unsigned)time(NULL));
    int i, j;
    for(i=0; i<sz1; i++)
        for(j=0; j<sz2; j++)
            m[i][j]=rand()%10; //*(*(m+i)+j)=rand
}
int *crt(int sz)  //выделение памяти
{
    return (int*)malloc (sz*sizeof(int));
}
void ers (int *m,int sz)  //освобождение памяти
{
    free(m);
};
void print (int ** m, int sz1, int sz2)// печать двумерного массива
{
    int i, j;
    for(i=0; i<sz1; i++)
    {
        for(j=0; j<sz2; j++)
            printf("%3i",m[i][j]); //*(*(m+i)+j)
        printf("\n");
    }
    printf("\n");
}
void erase (int **m, int sz1, int sz2)//освобождение памяти (одномерный массив)
{
    int i;
    for(i=0; i<sz1; i++)
        free(m[i]); //free(*(m+i));
    free(m);
}
int sums( int **m,int qr, int st) // подсчёт одного столбца, функция возвращает сумму элементов в столбце st
{
    int s=0;
    for (int i=0;i<qr;i++)
        s+=m[i][st]; //по столбцу st
    //printf ("%3d",s);
    return s;
}
void sumst(int **m, int*s, int sz1, int sz2) // подсчет сумм в sz2 столбцах и запись в массив  *s
{
    for (int i=0; i<sz2; i++)
    {
        s[i]=sums(m,sz1,i);
        printf ("%3i",s[i]);
    }
    printf("\n\n");
}
void transp (int **p,int sz1, int sz2, int **m)// функция меняет строки и столбцы в массиве m (для прямоугольного)
{
    for (int i=0;i<sz1;i++)
        for (int j=0;j<sz2;j++)
            p[i][j]=m[j][i];
}
void trspn (int **m, int sz1, int sz2) // для квадратного массива
{
    int i, j,temp;
    for(i=0; i<sz1; i++)
        for(j=i+1; j<sz2; j++)
        {
            temp=m[i][j];
            m[i][j]=m[j][i];
            m[j][i]=temp;
        }
}
void insert (int **p,int sz1, int sz2, int**m) // сортировка(вставка)
{
    int *t=crt(sz2); // создание массива, в котором хранятся суммы столбцов
    sumst(m,t,sz1,sz2); //подсчёт
    int temp,j;
    int *tem;
    for (int i=1;i<sz2;i++) //сортировка
    {
        temp=t[i];
        tem=p[i];
        j=i-1;
        for (;temp<t[j] && j>=0;j--)
        {
            p[j+1]=p[j];
            t[j+1]=t[j];//элементы копируются(смещаются)
        }
        t[j+1]=temp;//вставка элемента
        p[j+1]=tem;
    }
    ers(t,sz2); // освобождение памяти
}
