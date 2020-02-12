// ����������� ��������� ���� � ������� �����������(� ������� �������� �������)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 5
void sort(FILE*f);
int numb(FILE*f);
void slit(FILE*f,FILE*f1,FILE*f2,char m,int n,int sr);
void erase (char *name)//������������ ������ (1 �������)
{
    free(name);
}
void writef(FILE*f,FILE*ff,int n) // �-� ���������� �� f-�����  � ff-����  n ��������
{
    char s[M];
    int i=0;
    while (i<n)
    {
        fgets(s,M-1,f);
        fputs(s,ff); // ������ � 1 ����
        i++;
    }
}
void slit(FILE*f,FILE*f1,FILE*f2,int n,int sr) // ������� ��������� ��� ����� � ����
{
    char s1[M],s2[M]; // ��� �������� (������)
    fgets(s1,M-1,f1);
    fgets(s2,M-1,f2);
    do  // ���� �� ���������� ���� �� ������
    {
        int e1=0,e2=0;
        while(e1<sr && e2<sr) // ��������� �����
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
        if (!feof(f1)) // ���� 1 ���� �� ���������� ������ ��� �����
            while(e1<sr) //���������� ���������� ��������
            {
                fputs(s1,f);
                fgets(s1,M-1,f1);
                e1++;
               
            }
        if(!feof(f2)) // ���� 2 ���� �� ���������� ������ ��� �����
            while(e2<sr) //���������� ���������� ��������
            {
                fputs(s2,f);
                fgets(s2,M-1,f2);
                e2++;
            }
    }
    while (!feof(f1) && !feof(f2)); // ���� �� ����� ������-���� �����
    
     while (!feof(f1)) // ���������� �������� � 1 ����� ����� ��������� �� �����
    {
        fputs(s1,f);
        fgets(s1,M-1,f1);
    }
    while(!feof(f2))// ���������� �������� �� 2 ����� ����� ��������� �� �����
    {
        fputs(s2,f);
        fgets(s2,M-1,f2);
    }
    
}
void file(FILE*f,FILE*f1,FILE*f2,int sz1,int n,int sr) // ������ � ����� (���������� ����� �� ���)
{
    writef(f,f1,sz1*sr); // ������ � 1 ����
    writef(f,f2,n-sz1*sr);// ������ �� 2 ����
}
void sort(FILE*f) // ������� ���������� ������� ��������
{
    int n=numb(f); // ���-�� �����
    printf("n-'%i'",n);
    char s[]="//Users//okot444//Desktop//txt.txt";
    char s1[]="//Users//okot444//Desktop//1.txt";
    char s2[]="//Users//okot444//Desktop//2.txt";
    for (int sr=1; sr<n; sr*=2) // ���� �� ������
    {
        int sz1=(n/sr+1)/2; // ���-�� ����� � 1 �����
        f=fopen(s,"r");
        FILE*f1=fopen(s1,"w");
        FILE*f2=fopen(s2,"w");
        if(f1!=NULL)
        {
            if (f2!=NULL)
            {
                if (f!=NULL)
                {
                    file(f,f1,f2,sz1,n,sr);// ������ � �����
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
                    slit(f, f1, f2, n, sr); // ��������� ���������� ������� ��������
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
int numb(FILE*f) // �-� ���������� ���-�� ����� � �����
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


/*void file(FILE*f,FILE*f1,FILE*f2,int sz1,int n,int sr) // ������ � ����� (���������� ����� �� ���)
 {
 char s[M];
 int i=0;
 while (i<sz1*sr) //sz1*sr - ���-�� �������� � 1 �����
 {
 fgets(s,M-1,f);
 fputs(s,f1); // ������ � 1 ����
 i++;
 }
 while(i<n) // ��������� �������� �� 2 ����
 {
 fgets(s,M-1,f);
 fputs(s,f2); // ������ �� 2 ����
 i++;
 }
 }
 
 */