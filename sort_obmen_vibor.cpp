/*
 ��������� ����	�������� ������ - ��� ������, ������ ������ - ����� �����, ����
 ������ ������� ������ ������� �������� ���������� N
 ���������� �������� � ������������ �������
 ���������, ��� ������ ��������� ��������
 ������� ��� �����
	1. ������ � ���������� �������
 ������� �����
	2. � ������� �������� �����������
 ������� �����
 ���� ��������� ��� ������
 
 int atoi(char*s) - ������ ��������� � ����� �����
 int strcmp(char*s, char*t) - ���������� ������ s � t
 s=t - =0
 s<t - <0
 s>t - >0
 */
#define N 4
#define M 10
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct best // ���������:  ��� � ����
{
    int sc;
    char *name;
};
void obmen(best b[]);
void vibor (best b[]);
char *create(int sz)  //��������� ������
{
    return (char*)malloc (sz*sizeof(char));
}
void erase (char *name)//������������ ������ (1 �������)
{
    free(name);
}
int check(FILE *f) // ������� ���������� ���-�� ����� � �����
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
void copyb(best b[],best cb[]) // �������� ����������� �� b[]  � cb[]
{
    for (int i=0;i<N;i++)
        cb[i].name=create(M); // ��������� ������ ��� ���
    for (int i=0;i<N;i++) // ����������� �����
    {
        strcpy(cb[i].name, b[i].name);
        cb[i].sc=b[i].sc; // ����������� �����
    }
}
void read(FILE*f,best b[])//������ ����� � ����� (���� ���������)
{
    for (int i=0;i<N;i++)
    {
        b[i].name=create(M);
        fscanf (f,"%s\n %i",b[i].name,&b[i].sc);
    }
}
void print(FILE*f,best b[])// ����� �� ������ ���� ���������
{
    for (int i=0;i<N;i++)
    {
        fprintf(f,"%s\n%i\n",b[i].name,b[i].sc);
    }
}
void ers(FILE*f,best b[]) // ������������ ������ (��� ��������)
{
    for (int i=0;i<N;i++)
        erase(b[i].name);
}
void vibor (best *b) // ������� �����
{
    int no;
    best copysc;
    for (int i=0;i<N-1;i++)
    {
        no=i; // min-�����������, no-��� ����� � �������
        copysc=b[no];
        for (int j=no+1;j<N;j++) // ���� ���������� ������������
            if (strcmp(b[j].name,copysc.name)<0)
            {
                copysc=b[j];
                no=j;
            }
        b[no]=b[i]; // ������ ������� ���������� � ����������
        b[i]=copysc;
    }
}
void obmen(best b[]) // ������� �����
{
    best cname;
    for (int i=0; i<N-1; i++)
        for (int j=N-1; j>i; j--)
            if (b[j].sc<b[j-1].sc)// ������ ������� ��� ��������
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
                best b[M]; // ��������� ��� ���������� �� �����
                read(f,b);
                best cb[M]; // ��������� ��� ���������� �� �����
                copyb(b,cb);
                vibor(b);
                if ((f1=fopen("//Users//okot444//Desktop//name.txt","w"))!=NULL)
                {
                    print (f1,b);// ����� �� ������ ����������������
                    ers(f1,b); // ������������ ������
                }
                else
                    printf ("error w name");
                fclose(f1);
                obmen (cb);
                if ((f2=fopen("//Users//okot444//Desktop//score.txt","w"))!=NULL)
                {
                    print (f2,cb);// ����� �� ������ ����������������
                    ers(f2,cb); // ������������ ������
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