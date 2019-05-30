
// ��������� - ����� ��������� ������ ����, �� ���� �������� ������ �� �����������
// ��� int, ������� �� ����� {1,2,3} = {2,3,1} ...
/* 1. ����������� (+)
	{1,2,3} + {2,7,1} = {1,2,3,7}
 2. ����������� (^)
 {1,2,3} ^ {2,7,1} = {1,2}
 3. �������� (-)
 {1,2,3} - {2,7,1} = {3}  �������� 1 ����-�� ������� ��� �� 2
 4. ������������ �������� (&)
 {1,2,3} - {2,7,1} =  {3,7} �������� ��� � 1 ��� �� 2
 5. ���������� �������� � ��������� (+)
 � + ��-� = { 1,2,3,��-� }
	��-� + � = { ��-�,1,2,3 }
 6. �������� ()
 � = ��-�
	{1,2,3} - 2 = {1,3}
 7. -- ���������
 ���������� ������� 1-�� ��-�
	����������� ������� ���������
 8. ������������ � �������������� �������� ��������� (int) <
 � < B , ���� ��� �������� ���������� B
 ��-� < � , ���� ��-� ����������� B
 A == B , ��������������
 9. �������� ��-�� (���-�� ���������) (int)
 10.=, +=, -=, &=, ^= ������������
 11. ����� � ����� <<
 ������ ��������� - ��������� , � ������� ��� ���������
 
 ��������� ������ �� ������� ������ � �����������
 ������� � ����������
 
 const elem * t ��� elem const *t- ������, �������� ���������
 elem*const t - ��-��, ������ �������� t
 
 */
#include <iostream>
using namespace std;


struct elem
{
    int info;
    elem*next;
};
class vect
{
public:
    vect() { t=NULL; }
    ~vect() {};
    vect (const vect& tail); // ����������� ����������
    
    void print();
    void addfirst(int i);
    void add(int i);
    
    vect& operator -- ();
    vect& operator -- (int);
    vect operator + (const vect &m);
    vect& operator += (const vect &m);
    
    
private:
    elem*t;
    void o_addafter(elem*p,int i);
    elem* o_addfirst(int i);
    elem* o_delhead (elem*t); // �������� ������
    elem* o_search(elem* const t, int i) const; // ����� ��������
    elem* o_cpylst(const elem*t); // �����������
    void o_addhead(elem*t,int i);//
    elem* o_addtail(elem*t,int i);
    void o_prnlist(elem*t);
    elem* o_pred(elem*q,elem*p);
    elem* o_deltail(elem*t);
    elem* add(elem*t1,const elem*t2);
    elem* addcheck(elem*t1,const elem*t2);
    elem* o_delel(elem* t, int i);
};
vect::vect(const vect& tail) // ����������� ����������
{
    if (&tail != this)// �� �������� ������ � ����
        t = o_cpylst(tail.t);
}
vect &vect:: operator --() // ���������� ���������
{
    o_delhead(t);
    return *this;
}
vect &vect:: operator --(int) // ����������� ���������
{
    t = o_deltail(t);
    return *this;
}
vect vect:: operator +(const vect &m) //�����������
{
    vect temp(*this); // ������ �����
    temp+=m; //  �������� � ����
    return temp; // ���������� ����� ������
}
vect& vect:: operator += (const vect &m)
{
    t = add (t, m.t);
    return *this;
}
/*
elem* vect:: add(elem *t1, const elem *t2) // ���������� � ���������
 // ��� ������?
 {
 if (t1 == 0){ // ���� ������ ������, �� ������ ��������
 t1 = o_cpylst(t2);
 return t1;
 }
 if (t2 == 0) // ���� ������ ������, �� ������ �� ����������
 return t1;
 t1 = addcheck(t1, t2);
 elem*p2=t2->next;
 elem*p1=t1->next; // �������� � ������
 //while (m!=t2) {
 //k=m;
 //m=m->next;
 //if (search(t1,m->info)==0) //���� �������� �� ������� ������ ��� � //������ - ��������
 //t1=addtail(t1,m->info);
 }
 //k=m;
 //m=m->next;
 if (search(t1,m->info)==0) //���� �������� �� ������� ������ ��� � ������ - ��������
 t1=addtail(t1,m->info);
 return t1;
 }
 while (p2!=t2){
 cout<<"!"<<endl;
 if (p1->info != p2->info)// ����� ������� (�� ���������)
 if ( p1 == t1 ) // ���� ��������� ��� ��������, ���������
 t1=o_addtail(t1, p2->info);
 p2 = p2->next;
 }
 if (p1->info != p2->info)// ����� ������� (�� ���������)
 if ( p1 == t1 ) // ���� ��������� ��� ��������, ���������
 t1=o_addtail(t1, p2->info);
 
 return t1;
 }*/
// cout<<"!"<<endl;
elem* vect:: addcheck(elem *t1, const elem *t2)
{
    if ( t1 == 0 )
    {
        cout<<"t1=0"<<endl;
        t1 = o_addfirst(t2->info);
    }
    return t1;
}
void vect:: addfirst(int i)// ���������� ������� ��-�� � ������ ���������
{
    t = o_addfirst(i);
}
void vect:: add(int i)// ���������� ��-�� � ��-��
{
    t=o_addtail(t, i);
}
void vect::print()
{
    o_prnlist(t);
}
void vect ::o_prnlist(elem*t) // ������ ���������� ������
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
    printf (".\n");
}
elem* vect::o_pred(elem*q,elem*p) //(�����.������) ���������� ����������� �������� � ������
//p - �������, �� ������� ���� ���������, q - �������, ����������� ����� p, (���������� ��������� �� ��������� ��-�� q)
{
    while(q->next!=p)
        q=q->next;
    return q;
}
elem* vect::o_deltail(elem*t) //(�����.������) �������� ������ ,  �-� ������������ � ������� � 2 � ����� ����������
{
    elem*p=t;
    p=o_pred(t,p);// ���������� ����������� (����� �������)
    p->next=t->next;
    free(t);
    return (p); //���������� ����� �����
}
elem* vect::o_delhead(elem*t) // (�����.������) �������� ������ , �-� ������������ � ������� � 2 � ����� ����������
{
    elem*q=t->next;
    t->next=q->next;// �������� ������ �� �����
    free(q);// ������� ������ ������
    return q;
}
void vect::o_addhead(elem*t,int i) //(�����.������) ������� � ������  , �-� ������������ � �������� �������
{
    elem*p=(elem*)malloc(sizeof(elem)); // ������� �����
    p->info=i; // ���������� ��������
    p->next=t->next;
    t->next=p;
}
void vect::o_addafter(elem*p,int i) // (�����.������) ������� ����� �������� � ����-�, p - �� ����� (� p-�� ������ ?) , �-� ������������ � �������� �������
{
    o_addhead(p,i);
}
elem* vect::o_addtail(elem*t,int i) //(�����.������) ������� � ����� , �-� ������������ � �������� �������
{
    o_addhead(t,i);
    return t->next;
}
elem* vect::o_addfirst(int i) //(�����.������)  ���������� ������� �������� (���������� ��������� �� �����) �-� ������������ � ������ �������
{
    elem*t=(elem*)malloc(sizeof(elem));
    t->info=i;
    t->next=t;
    return t;
}
elem* vect::o_cpylst(const elem*t) //(�����.������) ����������� , (���������� ��������� �� ����� ������)
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
elem* vect::o_delel(elem* t, int i){
    elem *p=0, *k=0;
    if (t!=0){      // �������� �� ��������� ������
        p = o_search(t,i);					//
        if (p!=0){  // ������� ����
            if (p==(p->next)){		// ������� ������������ - ������� ������ ���������
                free(p);
                return 0;
            }
            k=p->next;
            p->next=k->next;
            if (k==t){					//���� ����� ������� ����� - ������� ���
                free (k);
                return p;
            }
            delete k;
        }
        return t;
    }
    else
        printf ("empty list");
    return 0;
    
    
}elem* o_dellist(elem*t)//(�����.������) �������� ������
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
elem* o_search(elem* const t, int i) {
    elem *h = t;
    while ((h=h->next) != t) {
        if (h->info == i)// ���� ����� ������� �� �����
            return h;
    }
    if (h->info != i)// ��������� �����
        return 0;
    return h;
}
int main()
{
    vect b;
    
    b.addfirst(6);
    b.add(3);
    b.print();
    vect c;
    c.addfirst(5);
    c.add(2);
    c.add(3);
    c.add(3);
    c.add(4);
    c.add(7);
    c.print();
    b=b+c;
    cout << endl;
    b.print();
    
    
}






