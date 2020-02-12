/*
 ������, ����������� �������� �������� � ���������� ����������� ���������� ����������
 (���-�� ����� �� ����������� ����� ���-�� ��������)
 ������������� ������ �� ����������� ���� �������� ������� ������� �������.
 ������������ ������ ������� �� ������.
 
 1141  1114
 7151  1175
 3261  1236
 
 ���������� ������� ������ ����������� ���������.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int ** create (int sz1, int sz2);//��������� ������ ��� ������
int* crt (int sz);
void erase (int **m, int sz1, int sz2); //������� �� ������
void ers (int *m,int sz);  //������������ ������
void init (int **m, int sz1, int sz2); //������ ��������
void print (int **m, int sz1, int sz2); //����������
int sums( int **m,int qr, int st);
void sort(int **m,int sz1, int sz2);// ����������
void transp (int **p,int sz1, int sz2, int **m);// ������� ������ ������ � ������� � ������� m (��� ��������������)
void insert (int **p,int sz1, int sz2, int**m); // ����������(�������)
void sumst(int **m, int*s, int sz1, int sz2);
void trspn (int ** m, int sz1, int sz2); // ��� ����������� �������
int main ()
{
    int **m,r,c;// ������ m , r- ���-�� �����, �- ���-�� ��������
    scanf ("%i %i",&r,&c);
    if (r>0&&c>0)
    {
        m=create(r,c);// ��������� ������ ��� ������
        init(m,r,c); // �������������
        print(m,r,c); // ������
        sort(m,r,c); // ����������
        print (m,r,c);// ������ ���������������� �������
        printf("\n");
        erase(m,r,c); // ������������ ������
    }
    else printf ("error");
}
void sort(int **m,int sz1, int sz2) //���������� �� ����������� ���� ��������
{
    int **p=create(sz2, sz1); // ��������� ������ ��� ��������� ������
    if (sz1==sz2) // ���� ���������� ������
    {
        trspn(m,sz1,sz2);
        insert(m,sz1,sz2,m);
        trspn(m,sz1,sz2);
    }
    else // �������������
    {
        transp(p,sz2,sz1,m);
        insert(p,sz1,sz2,m);
        transp(m,sz1,sz2,p);
        erase(p,sz2,sz1);
    }
    
}
int ** create (int sz1, int sz2)// ��������� ������ ��� ��������� ������, �-� ���������� ��������� �� ������ �������
{
    int**t=(int**)malloc(sizeof(int*)*sz1); //������� ��������� �� ������ sz1-���-�� ��������� ������� ��������� ������
    int i;
    for(i=0; i<sz1; i++) //�������� �����
        t[i]=(int*)malloc(sizeof(int)*sz2);//*(t+i)
    return t;
}
void init(int**m, int sz1, int sz2)//�������������� ���������� �������
{
    srand((unsigned)time(NULL));
    int i, j;
    for(i=0; i<sz1; i++)
        for(j=0; j<sz2; j++)
            m[i][j]=rand()%10; //*(*(m+i)+j)=rand
}
int *crt(int sz)  //��������� ������
{
    return (int*)malloc (sz*sizeof(int));
}
void ers (int *m,int sz)  //������������ ������
{
    free(m);
};
void print (int ** m, int sz1, int sz2)// ������ ���������� �������
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
void erase (int **m, int sz1, int sz2)//������������ ������ (���������� ������)
{
    int i;
    for(i=0; i<sz1; i++)
        free(m[i]); //free(*(m+i));
    free(m);
}
int sums( int **m,int qr, int st) // ������� ������ �������, ������� ���������� ����� ��������� � ������� st
{
    int s=0;
    for (int i=0;i<qr;i++)
        s+=m[i][st]; //�� ������� st
    //printf ("%3d",s);
    return s;
}
void sumst(int **m, int*s, int sz1, int sz2) // ������� ���� � sz2 �������� � ������ � ������  *s
{
    for (int i=0; i<sz2; i++)
    {
        s[i]=sums(m,sz1,i);
        printf ("%3i",s[i]);
    }
    printf("\n\n");
}
void transp (int **p,int sz1, int sz2, int **m)// ������� ������ ������ � ������� � ������� m (��� ��������������)
{
    for (int i=0;i<sz1;i++)
        for (int j=0;j<sz2;j++)
            p[i][j]=m[j][i];
}
void trspn (int **m, int sz1, int sz2) // ��� ����������� �������
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
void insert (int **p,int sz1, int sz2, int**m) // ����������(�������)
{
    int *t=crt(sz2); // �������� �������, � ������� �������� ����� ��������
    sumst(m,t,sz1,sz2); //�������
    int temp,j;
    int *tem;
    for (int i=1;i<sz2;i++) //����������
    {
        temp=t[i];
        tem=p[i];
        j=i-1;
        for (;temp<t[j] && j>=0;j--)
        {
            p[j+1]=p[j];
            t[j+1]=t[j];//�������� ����������(���������)
        }
        t[j+1]=temp;//������� ��������
        p[j+1]=tem;
    }
    ers(t,sz2); // ������������ ������
}
