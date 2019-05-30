
// Множество - набор элементов одного типа, ни одно значение дважды не встречается
// тип int, порядок не важен {1,2,3} = {2,3,1} ...
/* 1. Объединение (+)
	{1,2,3} + {2,7,1} = {1,2,3,7}
 2. Пересечение (^)
 {1,2,3} ^ {2,7,1} = {1,2}
 3. Разность (-)
 {1,2,3} - {2,7,1} = {3}  элементы 1 множ-ва которых нет во 2
 4. Симметричная разность (&)
 {1,2,3} - {2,7,1} =  {3,7} элементы или в 1 или во 2
 5. Добавление элемента к множеству (+)
 ј + эл-т = { 1,2,3,эл-т }
	эл-т + ј = { эл-т,1,2,3 }
 6. Удаление ()
 ј = эл-т
	{1,2,3} - 2 = {1,3}
 7. -- Декремент
 Префиксная удаляет 1-ый эл-т
	Постфиксная удаляет последний
 8. Подмножество и принадлежность элемента множеству (int) <
 ј < B , если все элементы содержатся B
 эл-т < В , если эл-т принадлежит B
 A == B , эквивалетность
 9. Мощность мн-ва (кол-во элементов) (int)
 10.=, +=, -=, &=, ^= Присваивания
 11. Вывод в поток <<
 Пустое множество - множество , в котором нет элементов
 
 Кольцевой список не объекты работа с указателями
 объекты в операторах
 
 const elem * t или elem const *t- данные, значения элементов
 elem*const t - ук-ль, нельзя изменить t
 
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
    vect (const vect& tail); // конструктор копирующий
    
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
    elem* o_delhead (elem*t); // удаление головы
    elem* o_search(elem* const t, int i) const; // поиск элемента
    elem* o_cpylst(const elem*t); // копирование
    void o_addhead(elem*t,int i);//
    elem* o_addtail(elem*t,int i);
    void o_prnlist(elem*t);
    elem* o_pred(elem*q,elem*p);
    elem* o_deltail(elem*t);
    elem* add(elem*t1,const elem*t2);
    elem* addcheck(elem*t1,const elem*t2);
    elem* o_delel(elem* t, int i);
};
vect::vect(const vect& tail) // конструктор копирующий
{
    if (&tail != this)// не копируем самого в себя
        t = o_cpylst(tail.t);
}
vect &vect:: operator --() // префиксный декремент
{
    o_delhead(t);
    return *this;
}
vect &vect:: operator --(int) // постфиксный декремент
{
    t = o_deltail(t);
    return *this;
}
vect vect:: operator +(const vect &m) //объединение
{
    vect temp(*this); // создаём новый
    temp+=m; //  копируем в него
    return temp; // возвращаем новый объект
}
vect& vect:: operator += (const vect &m)
{
    t = add (t, m.t);
    return *this;
}
/*
elem* vect:: add(elem *t1, const elem *t2) // добавление в множество
 // оба пустые?
 {
 if (t1 == 0){ // если первое пустое, то просто копируем
 t1 = o_cpylst(t2);
 return t1;
 }
 if (t2 == 0) // если второе пустое, то ничего не изменяется
 return t1;
 t1 = addcheck(t1, t2);
 elem*p2=t2->next;
 elem*p1=t1->next; // начинаем с головы
 //while (m!=t2) {
 //k=m;
 //m=m->next;
 //if (search(t1,m->info)==0) //если элемента из второго списка нет в //первом - добавл€ем
 //t1=addtail(t1,m->info);
 }
 //k=m;
 //m=m->next;
 if (search(t1,m->info)==0) //если элемента из второго списка нет в первом - добавл€ем
 t1=addtail(t1,m->info);
 return t1;
 }
 while (p2!=t2){
 cout<<"!"<<endl;
 if (p1->info != p2->info)// числа совпали (не добавляем)
 if ( p1 == t1 ) // если проверили все элементы, добавляем
 t1=o_addtail(t1, p2->info);
 p2 = p2->next;
 }
 if (p1->info != p2->info)// числа совпали (не добавляем)
 if ( p1 == t1 ) // если проверили все элементы, добавляем
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
void vect:: addfirst(int i)// добавление первого эл-та в пустое множество
{
    t = o_addfirst(i);
}
void vect:: add(int i)// добавление эл-та в мн-во
{
    t=o_addtail(t, i);
}
void vect::print()
{
    o_prnlist(t);
}
void vect ::o_prnlist(elem*t) // печать кольцевого списка
{
    if (t!=0) // проверка на непустоту списка
    {
        elem*p=t->next; // начинаем с головы
        while (p!=t) // проходим до хвоста
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
elem* vect::o_pred(elem*q,elem*p) //(кольц.список) нахождение предыдущего элемента в списке
//p - элемент, на который есть указатель, q - элемент, находящийся перед p, (возвращает указатель на найденный ук-ль q)
{
    while(q->next!=p)
        q=q->next;
    return q;
}
elem* vect::o_deltail(elem*t) //(кольц.список) удаление хвоста ,  ф-я используется в списках с 2 и более элементами
{
    elem*p=t;
    p=o_pred(t,p);// нахождение предыдущего (перед хвостом)
    p->next=t->next;
    free(t);
    return (p); //возвращаем новый хвост
}
elem* vect::o_delhead(elem*t) // (кольц.список) удаление головы , ф-я используется в списках с 2 и более элементами
{
    elem*q=t->next;
    t->next=q->next;// изменяем голову на новую
    free(q);// удаляем старую голову
    return q;
}
void vect::o_addhead(elem*t,int i) //(кольц.список) вставка в голову  , ф-я используется в непустых списках
{
    elem*p=(elem*)malloc(sizeof(elem)); // выдел€ем пам€ть
    p->info=i; // записываем значение
    p->next=t->next;
    t->next=p;
}
void vect::o_addafter(elem*p,int i) // (кольц.список) вставка после элемента с указ-м, p - не хвост (и p-не голова ?) , ф-я используется в непустых списках
{
    o_addhead(p,i);
}
elem* vect::o_addtail(elem*t,int i) //(кольц.список) вставка в хвост , ф-я используется в непустых списках
{
    o_addhead(t,i);
    return t->next;
}
elem* vect::o_addfirst(int i) //(кольц.список)  добавление первого элемента (возвращает указатель на хвост) ф-я используется в пустых списках
{
    elem*t=(elem*)malloc(sizeof(elem));
    t->info=i;
    t->next=t;
    return t;
}
elem* vect::o_cpylst(const elem*t) //(кольц.список) копирование , (возвращает указатель на новый список)
{
    if (t!=0)// проверка на непустоту списка
    {
        elem*t2=o_addfirst(t->info); // добавляем первый элемент(хвост)
        elem*p=t->next;
        while (p!=t) // проходим до хвоста
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
elem* o_unite(elem**t1,elem *t2) //(кольц.список) сцепление 2-ух кольцевых списков t1  и t2,  возвращает  ук-ль t2,
{
    if ((*t1)!=0)// проверка на непустоту списка
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
    if (t!=0){      // проверка на непустоту списка
        p = o_search(t,i);					//
        if (p!=0){  // элемент есть
            if (p==(p->next)){		// элемент единственный - удаляем список полностью
                free(p);
                return 0;
            }
            k=p->next;
            p->next=k->next;
            if (k==t){					//если нужно удалить хвост - измен€ем его
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
    
    
}elem* o_dellist(elem*t)//(кольц.список) удаление списка
{
    if (t!=0) // проверка на непустоту списка
    {
        elem*q=t->next; // сохран€ем голову
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
        if (h->info == i)// если нашли выходим из цикла
            return h;
    }
    if (h->info != i)// проверяем хвост
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






