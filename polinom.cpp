#include <iostream>
#include <assert.h>
using namespace std;

struct elem {
	int st; // �������
	double ct; // �����������
	elem*next;
};
class polinom{
	public:
		// ��������� �� �����������
		// ���������� � �����
		// ��������� �����������
		// �������� �����������
		//polinom ();// �������� �����
		polinom operator += (const polinom &a);
		elem* add (elem* h1,elem* h2);
	private:
		elem* h;
		
};
elem* addhead(elem*h,int i, double d) // ���������� � ������
{
    elem*p = new elem;
    p->st = i;
	p->ct = d;
    p->next = h;
    return p;
}
elem* addfirst(int i, double d) // ���������� ������� (� ������ ������)
{
	elem * p=new elem;
	p->st=d;
	p->ct=i;
	p->next=NULL;
	return p;
}
void addafter(elem *h, elem *p, int i, double d) //���������� � ��������
{
	elem * q=new elem;
	q->st=i;
	q->ct=d;
	q->next=p->next;
	p->next=q;
}
elem* delhead(elem*h) 
//�������� �� ������
//���������� ���������
//���������� ������ ���� �������� 2 � ����� ���������
{
    elem*p = h->next;
    delete h;
    return p;
}

void delelem(elem *h, elem *p) // �������� � ��������
{
	elem *q=p->next;
	p->next=q->next;
	delete q;
}
elem* dellist(elem *h) 
//�������� ���������� ������  � ���������� �� ������� , ���������� �������� �� ���� ��������� ������
{
	elem *p=h; // 
	while (h)
	{
        p=h;
		h=h->next;
		delete p;
    }
    return h;
}
void prnlist(elem * h) // ����� ������
{
	if (h==0){
        cout<<"empty";
        return;
    }
	while (h!=NULL)
		{
			cout<<h->st<<"x^"<<h->ct<<"\t\t";
			h=h->next;
		}
	cout<<endl;
}
elem* add (elem* h1,elem* h2)//  �������� 2 �������
{
	
	
}


void addtail(elem*h,int i, double d)
{
    elem*p;
    do
    {
        p = h;
        h = h->next;
    }
    while(h!=0);
    h = new elem;
    h->st = i;
	h->ct = d;
    h->next = 0;
    p->next = h;
}
void deltail(elem*h)
{
    elem*p,*q=h;
    do
    {
        p=q;
        q=h;
        h=h->next;
    }
    while(h!=0);
    p->next=0;
    delete q;
}
void prnlist(elem*h)
{
    while(h!=0)
    {
        printf ("%fx^%i ",h->ct,h->st);
        h=h->next;
    }
    printf ("\n");
}
/*elem* search(elem* t, int el) {
    elem *h = t->next, *p=0;
    while (h!=t) {	//проходим до хвоста
        p=h;
        h=h->next;
        if (h->info==el)// если нашли выходим из цикла
            break;
    }
    if (h==t && h->info!=el) // элемент не найден
        return 0;
    return p;
}*/
void addafter(elem*p,int i, double d)
{
    elem*q = new elem;
    q->next = p->next;
    q->st = i;
	q->ct = d;
    p->next = q;
}
elem*cpylst(elem*h)
{
    elem*h2=0;
    h2=addhead(h2,h->st,h->ct);
    elem*p=h2;
    h=h->next;
    while(h!=0)
    {
        addafter(p,h->st,h->ct);
        p=p->next;
        h=h->next;
    }
    return h2;
}

elem * mult_num(elem * h, double a) // ��������� �� �����������
{
	elem *p=h;
	while (p)
		{
			p->ct*=a;
			p=p->next;
		}
	return h;
}
elem* multiplication(elem *h1, elem *h2)  // ��������� �����������
{
	if (!h1 || !h2)
		return 0;
	elem * h, * q, * t, *w, * p;
	int pi,qi,s;
	double c;
	//��������� ������ �������
	p=h1;
	q=h2;
	pi=p->ct;
	qi=q->ct;
	c=p->st*q->st; //��������� �������������
	h=addfirst(c, pi+qi); //  ��� ��������� ������� ������������
	t=h;
	w=t->next;
	//��� �� ������� ������
	q=q->next;
	while(p) //���������� ��� �������� ������� ������
	{
		pi=p->ct;
		while(q) //���������� ��� �������� ������� ������
		{
			qi=q->ct;
			s=pi+qi;
			c=p->st*q->st;
				//���� �������, ����� �������� ����� ��������� ����� (��� �-� �������� ������)
				if (t->next && w->ct > s){
					t=t->next;
					w=t->next;
				}
				else{
					//else // ���� ����� �������� ������� (����� �������)
					{
						addafter(h,t,c, s);
					}
					q=q->next;
				}
			q=q->next;
		}
		p=p->next;
		q=h2;	//������ �������� �� ������� ������ �
		t=h;	//�� ������������
		w=t->next;
	}
	return h;
}
int main()
{
	
}
