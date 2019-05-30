#include <stdio.h>
#include <stdlib.h>
struct elem
{
    int info;
    elem*next;
};
elem* o_addfirst(int i) //(�����.������)  ���������� ������� �������� (���������� ��������� �� �����) �-� ������������ � ������ �������
{
    elem*t=(elem*)malloc(sizeof(elem));
    t->info=i;
    t->next=t;
    return t;
}
elem* o_pred(elem*q,elem*p) //(�����.������) ���������� ����������� �������� � ������
//p - �������, �� ������� ���� ���������, q - �������, ����������� ����� p, (���������� ��������� �� ��������� ��-�� q)
{
    while(q->next!=p)
        q=q->next;
    return q;
}
void o_addhead(elem*t,int i) //(�����.������) ������� � ������  , �-� ������������ � �������� �������
{
    elem*p=(elem*)malloc(sizeof(elem)); // ������� �����
    p->info=i; // ���������� ��������
    p->next=t->next;
    t->next=p;
}
elem* o_addtail(elem*t,int i) //(�����.������) ������� � ����� , �-� ������������ � �������� �������
{
    o_addhead(t,i);
    return t->next;
}
void o_addafter(elem*p,int i) // (�����.������) ������� ����� �������� � ����-�, p - �� ����� (� p-�� ������ ?) , �-� ������������ � �������� �������
{
    o_addhead(p,i);
}
void o_delhead(elem*t) // (�����.������) �������� ������ , �-� ������������ � ������� � 2 � ����� ����������
{
    elem*q=t->next;
    t->next=q->next;// �������� ������ �� �����
    free(q);// ������� ������ ������
}
elem* o_deltail(elem*t) //(�����.������) �������� ������ ,  �-� ������������ � ������� � 2 � ����� ����������
{
    elem*p=t;
    p=o_pred(t,p);// ���������� ����������� (����� �������)
    p->next=t->next;
    free(t);
    return (p); //���������� ����� �����
}
void o_delelem(elem*p) //(�����.������) �������� �������� �� ������� ���� ��-�� p, p �� ����� , p-�� ������, �-� ������������ � ������� � 2 � ����� ����������
{
    elem*q=p;
    q=o_pred(q,p);
    q->next=p->next;
    free(p);
}
elem* o_cpylst(elem*t) //(�����.������) ����������� , (���������� ��������� �� ����� ������)
{
    if (t!=0)// �������� �� ��������� ������
    {
        elem*t2=o_addfirst(t->info); // ��������� ������ �������(�����)
        elem*p=t->next;
        while (p!=t) // �������� �� ������
        {
            o_addafter(t2, p->info);
            t2=t2->next;
            p=p->next;
        }
        return t2->next;
    }
    else
        printf ("empty list");
    return 0;
}
elem* o_unite(elem**t1,elem *t2) //(�����.������) ��������� 2-�� ��������� ������� t1  � t2,  ����������  ��-�� t2,
{
    if ((*t1)!=0)// �������� �� ��������� ������
    {
        elem*p1=(*t1)->next;
        (*t1)->next=t2->next;
        t2->next=p1;
        *t1=0;
    }
    else
        printf ("empty list");
    return t2;
}
void o_prnlist(elem*t) // ������ ���������� ������
{
    if (t!=0) // �������� �� ��������� ������
    {
        elem*p=t->next; // �������� � ������
        while (p!=t) // �������� �� ������
        {
            printf ("%i ",p->info);
            p=p->next;
        }
        printf ("%i ",p->info);
    }
    else
        printf ("empty list");
    printf ("\n");
}
elem* o_dellist(elem*t)//(�����.������) �������� ������
{
    if (t!=0) // �������� �� ��������� ������
    {
        elem*q=t->next; // �������� ������
        while (q!=t)
        {
            t->next=q->next;
            free(q);
            q=t->next;
        }
        free(q);
    }
    else
        printf ("empty list");
    return 0;
}
/*elem* search(elem* const t, int el) {
    elem *h = t->next, *p=0;
    while (h!=t) {	//�������� �� ������
        if (h->info==el)// ���� ����� ������� �� �����
            break;
        p=h;
        h=h->next;
        
    }
    p=h;
    h=h->next;
    if (h==t && h->info!=el) // ������� �� ������
        return 0;
    return p;
}*/
elem* search(elem* const t, int el) {
    elem *h = t;
    while ((h=h->next)!=t) {
        if (h->info==el)// ���� ����� ������� �� �����
            return h;
    }
    if (h->info!=el)// ���� ����� ������� �� �����
        return 0;
    return h;
}
int main ()
{
    elem*tail1=0,*p=0;
    tail1 = o_addfirst(5);
    tail1 = o_addtail(tail1, 6);
    tail1 = o_addtail(tail1, 7);
    tail1 = o_addtail(tail1, 8);
    o_prnlist(tail1);
    p = search(tail1, 0);
    printf("p : %i ", p->info);
}




/*
 elem*p=tail1->next->next;
 printf("p: %i\n",p->info);
 o_addafter(p, 999);
 printf("tail1 addafter: ");
 o_prnlist(tail1);
 
 //o_delelem(p->next);
 printf("tail1 delhead: ");
 o_prnlist(tail1);
 tail1=o_deltail(tail1);
 printf("tail1 deltail: ");
 o_prnlist(tail1);
 o_delelem(p);
 printf("tail1 delelem p-%i: ",p->info);
 o_prnlist(tail1);
 
 //printf("tail1 addtail: ");
 //o_prnlist(tail1);
 //printf("tail1: ");
 // o_prnlist(tail1);
 o_prnlist(tail1);
 tail2=o_cpylst(tail1);
 o_prnlist(tail2);
 
 
 */

/*
 void o_addafter(elem*p,int i) // ������� ����� �������� � ����-�, �� � �����(�����.������), �-� ������������ � �������� �������
 {
    elem*q=(elem*)malloc(sizeof(elem)); // ������� �����
    q->info=i; // ���������� ��������
    q->next=p->next;
    p->next=q;
 */


/*
 void o_prnlist(elem*t) // ������ ���������� ������
 {
 if (t!=0) // �������� �� ��������� ������
    {
        elem*p=t; //
        while ((p=p->next)!=t) //  �������� � ������ � �������� �� ������
            printf ("%i ",p->info);
        printf ("%i ",p->info);
    }
    printf ("\n");
*/
