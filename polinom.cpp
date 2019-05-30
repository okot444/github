#include <iostream>
#include <assert.h>
using namespace std;

struct elem {
	int st; // степень
	double ct; // коэффициент
	elem*next;
};
class polinom{
	public:
		// умножение на коэффициент
		// вычисление в точке
		// умножение многочленов
		// сложение многочленов
		//polinom ();// одночлен моном
		polinom operator += (const polinom &a);
		elem* add (elem* h1,elem* h2);
	private:
		elem* h;
		
};
elem* addhead(elem*h,int i, double d) // добавление в голову
{
    elem*p = new elem;
    p->st = i;
	p->ct = d;
    p->next = h;
    return p;
}
elem* addfirst(int i, double d) // добавление первого (в пустой список)
{
	elem * p=new elem;
	p->st=d;
	p->ct=i;
	p->next=NULL;
	return p;
}
void addafter(elem *h, elem *p, int i, double d) //добавление в середину
{
	elem * q=new elem;
	q->st=i;
	q->ct=d;
	q->next=p->next;
	p->next=q;
}
elem* delhead(elem*h) 
//удаление из головы
//изменяется положение
//вызывается только если содержит 2 и более элементов
{
    elem*p = h->next;
    delete h;
    return p;
}

void delelem(elem *h, elem *p) // удаление в середине
{
	elem *q=p->next;
	p->next=q->next;
	delete q;
}
elem* dellist(elem *h) 
//удаление выделенной памяти  с указателем на элемент , необходимо пройтись по всем элементам списка
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
void prnlist(elem * h) // вывод списка
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
elem* add (elem* h1,elem* h2)//  сложение 2 списков
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
    while (h!=t) {	//РїСЂРѕС…РѕРґРёРј РґРѕ С…РІРѕСЃС‚Р°
        p=h;
        h=h->next;
        if (h->info==el)// РµСЃР»Рё РЅР°С€Р»Рё РІС‹С…РѕРґРёРј РёР· С†РёРєР»Р°
            break;
    }
    if (h==t && h->info!=el) // СЌР»РµРјРµРЅС‚ РЅРµ РЅР°Р№РґРµРЅ
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

elem * mult_num(elem * h, double a) // умножение на коэффициент
{
	elem *p=h;
	while (p)
		{
			p->ct*=a;
			p=p->next;
		}
	return h;
}
elem* multiplication(elem *h1, elem *h2)  // умножение многочленов
{
	if (!h1 || !h2)
		return 0;
	elem * h, * q, * t, *w, * p;
	int pi,qi,s;
	double c;
	//добавляем первый элемент
	p=h1;
	q=h2;
	pi=p->ct;
	qi=q->ct;
	c=p->st*q->st; //умножение коэффициентов
	h=addfirst(c, pi+qi); //  при умножении степени складываются
	t=h;
	w=t->next;
	//идём по второму списку
	q=q->next;
	while(p) //перебираем все элементы первого списка
	{
		pi=p->ct;
		while(q) //перебираем все элементы второго списка
		{
			qi=q->ct;
			s=pi+qi;
			c=p->st*q->st;
				//ищем элемент, после которого будем вставлять новый (или к-т которого менять)
				if (t->next && w->ct > s){
					t=t->next;
					w=t->next;
				}
				else{
					//else // если нужно добавить элемент (новая степень)
					{
						addafter(h,t,c, s);
					}
					q=q->next;
				}
			q=q->next;
		}
		p=p->next;
		q=h2;	//заново проходим по второму списку и
		t=h;	//по произведению
		w=t->next;
	}
	return h;
}
int main()
{
	
}
