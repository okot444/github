/*
 ��������� ����, � ������� � ������������ ������� ������ �����.
 ��� ����������� �� �� ���-��, �� �� ������������.
 ����� �� ����� ����-� � ������������ � ����� � ���-��� �������.
 � ���������� ������� N ����� n.
 ������� � 1-�� ����������� n-�� ���������(����������� ������, �������� � ����������� ���� �� �������� 1-�.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30
struct elem
{
    char*word;
    elem*next;
    elem*pred;
};
struct pair
{
    elem*begin;
    elem*end;
};
char* wrd(char*s,char*w); //


elem* findr(int step ,pair*pr,elem*p, elem**q) // ���������� ������, p- �������, ������� ����� ������, q-����������, �-� ���������� ��-�� �� ��������� ��-�
{
    int i=1;
    for (; i<step && p->next!=NULL; i++)
        p=p->next; // �������� ������ �� �����
    if ( i<step )
    {
        p=pr->begin; // ����������� � ������
        i++;
        for (; i<step; i++)
            p=p->next; // �������� ������ �� �����
    }
    if (p==pr->begin) // ���������� ���������� ����������� ��������(��������� q)
        (*q)=pr->end;
    else
        (*q)=p->pred;
    return p;
}
elem* findl(int step ,pair*pr,elem*p, elem**q) // ���������� ����� **p ����� �������� � ������, p- �������, ������� ����� ������, q-����������,�-� ���������� ��-�� �� ��������� ��-�
{
     //printf (" step- %i\n",step);
    int i=1;
    for (; i<step && p->pred!=NULL; i++)
        p=p->pred;
    //printf ("for1 end !p %s\n",p->word);
    //printf (" i- %i\n",i);
    if ( i<step )
    {
        p=pr->end; // ����������� � ������
        i++;
        //printf (" i<step !p %s\n",p->word);
        
        for (; i<step; i++)
        {
            p=p->pred; // �������� ����� �� �����
            //printf (" for2 !p %s\n",p->word);
        }
    }
    if (p==pr->end) // ���������� ���������� ����������� ��������(��������� q)
        (*q)=pr->begin;
    else
        (*q)=p->next;
    return p;
}
void del_head(pair*pr,elem*p) // �������� � ������
{
    pr->begin=p->next;
    p->next->pred=NULL;
    printf ("delete %s\n",p->word);
    free(p);
}
void del_tail(pair*pr,elem*p) // �������� � �����
{
    pr->end=p->pred;
    p->pred->next=NULL;
    printf ("delete %s\n",p->word);
    free(p);
}
void del_mid(pair*pr,elem*p) // �������� � ��������
{
    p->pred->next=p->next;
    p->next->pred=p->pred;
    printf ("delete %s\n",p->word);
    free(p);
}
elem* del(pair*pr,elem*p, elem*q)// *p -��������� � ������, *q -����������, �-� ���������� ���������� ��-�� (����� ��������)
{
    if (p==pr->begin) // � ������
    {
        del_head(pr,p);
        p=q;
        return p; // !
    }
    if (p==pr->end) // � �����
        del_tail(pr, p);
    else       // � ��������
        del_mid(pr, p);
    p=q;
    return p; // !
}
 void deln(int step, pair*pr, int nstr) // �������� n-�� �������� (?)
{
    if (pr->begin != NULL)
    {
        elem*p=pr->begin;
        elem*q=pr->end;
        while (pr->begin!=pr->end) // ���� �� �������� ���� �������
        {
            p=findr(step%nstr ?step%nstr :nstr, pr, p, &q); // ������� ������
            p=del(pr, p, q); // ������
            nstr--;
            if (pr->begin!=pr->end)
            {
                p=findl(step%nstr ?step%nstr :nstr, pr, p, &q); //������� �����
                p=del(pr, p, q);// ������
            }
            nstr--;
        }
    }
    else
        printf ("empty file");
}
void printlist(elem*h) // ������ ���������� ������
{
    elem*p;
    for (p=h; p!=NULL; p=p->next)
        printf("%s\n",p->word);
    printf (".\n");
}
void addfirst(pair*pr,char*s) // ���������� ������� ����� � ������
{
    char*word;
    word=wrd(s,word);
    elem*h=(elem*)malloc(sizeof(elem));
    h->word=word;
    pr->begin=h;
    pr->end=h;
    h->pred=NULL;
    h->next=NULL;
}
void add(char*s,elem*p) // �������� �� ����� ��������, �� ������� ���� ��-�� *p (�������� �����)
{
    char*word;
    word=wrd(s,word);
    elem*q=(elem*)malloc(sizeof(elem)); //���-� ����� ��� ����� �������
    q->word=word;
    q->next=p;
    p->pred->next=q; //
    q->pred=p->pred;
    p->pred=q;
}
void addhead(char*s,pair*pr) // ���������� � ������ ���������� ������
{
    char*word;
    word=wrd(s,word);
    elem*q=(elem*)malloc(sizeof(elem));// ���-� ����� ��� ����� �������
    q->word=word;
    pr->begin->pred=q;
    q->next=pr->begin;
    pr->begin=q;
    q->pred=NULL;
}
void addtail(char*s, pair*pr) //���������� � �����
{
    char*w;
    w=wrd(s,w);
    elem*q=(elem*)malloc(sizeof(elem)); //���-� ����� ��� ����� �������
    pr->end->next=q;
    q->word=w;
    q->pred=pr->end;
    pr->end=q;
    q->next=NULL;
}
char* wrd(char*s,char*w) // ������� ����� ������ ����������� � ���������� ��-�� �� �����
{
    unsigned int len=strlen(s)+1;// ����� ����� + '/0'
    w=(char*)malloc((len)*sizeof(char));//
    w=strcpy(w,s);
    return w;
}
void addword(FILE*f,pair*pr) // ���������� ����� � ������ (�� ��������)
{
    char s[N+1];
    fgets(s,N,f);
    if((pr->begin)==NULL)
    {
        addfirst(pr,s); //���������� � ������(������ �����)
    }
    else
    {
        elem*copy;
        copy=pr->begin;// �������� ��������� �� ������ � ������
        while(copy!=NULL)
        {
            if (strcmp(s,pr->begin->word)<0)// ���� ����� �������� � ������ (����� < ����� � ������)
            {
                addhead(s,pr);
                return;
           	}
            if (strcmp(s, copy->word)<=0)
            {
                add(s,copy);
                return;
            }
            copy=copy->next;
        }
        addtail(s,pr); //���������� ����� � �����
    }
}
int startadd(FILE*f,char str[],pair*pr) // ���������� ���� �� ����� ����� (�-� ���������� ���-�� ���� � �����)
{
    int nstr=0; //
    if ((f=fopen(str,"r"))!=0)
    {
        while (!feof(f) )
        {
            addword(f,pr);
            nstr++;
        }
        fclose(f);
    }
    else printf ("error open");
    return nstr;
}
int main()
{
    pair pr[1]; // ���-� ����� ��� ����
    pr->begin=0;
    pr->end=0;
    char str[]="/Users/okot444/Desktop/names.txt";
    FILE*f;
    int nstr=0; //  ���-�� ���� � ������
    nstr=startadd(f, str, pr); //
    printlist(pr->begin);
    printf ("nstr -%i\n",nstr);
    int step; // ���-�� �����
    printf ("step - ");
    scanf("%i",&step);
    if (step>0)
        deln(step,pr,nstr); // ������ ����.?
    else
        printf ("step=0 error\n");
    printlist(pr->begin);
}

