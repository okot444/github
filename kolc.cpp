#include <stdio.h>
#include <stdlib.h>
struct elem
{
    int info;
    elem*next;
};
elem* o_addfirst(int i) //(кольц.список)  добавление первого элемента (возвращает указатель на хвост) ф-я используется в пустых списках
{
    elem*t=(elem*)malloc(sizeof(elem));
    t->info=i;
    t->next=t;
    return t;
}
elem* o_pred(elem*q,elem*p) //(кольц.список) нахождение предыдущего элемента в списке
//p - элемент, на который есть указатель, q - элемент, находящийся перед p, (возвращает указатель на найденный ук-ль q)
{
    while(q->next!=p)
        q=q->next;
    return q;
}
void o_addhead(elem*t,int i) //(кольц.список) вставка в голову  , ф-я используется в непустых списках
{
    elem*p=(elem*)malloc(sizeof(elem)); // выдел€ем пам€ть
    p->info=i; // записываем значение
    p->next=t->next;
    t->next=p;
}
elem* o_addtail(elem*t,int i) //(кольц.список) вставка в хвост , ф-я используется в непустых списках
{
    o_addhead(t,i);
    return t->next;
}
void o_addafter(elem*p,int i) // (кольц.список) вставка после элемента с указ-м, p - не хвост (и p-не голова ?) , ф-я используется в непустых списках
{
    o_addhead(p,i);
}
void o_delhead(elem*t) // (кольц.список) удаление головы , ф-я используется в списках с 2 и более элементами
{
    elem*q=t->next;
    t->next=q->next;// изменяем голову на новую
    free(q);// удаляем старую голову
}
elem* o_deltail(elem*t) //(кольц.список) удаление хвоста ,  ф-я используется в списках с 2 и более элементами
{
    elem*p=t;
    p=o_pred(t,p);// нахождение предыдущего (перед хвостом)
    p->next=t->next;
    free(t);
    return (p); //возвращаем новый хвост
}
void o_delelem(elem*p) //(кольц.список) удаление элемента на который есть ук-ль p, p не хвост , p-не голова, ф-я используется в списках с 2 и более элементами
{
    elem*q=p;
    q=o_pred(q,p);
    q->next=p->next;
    free(p);
}
elem* o_cpylst(elem*t) //(кольц.список) копирование , (возвращает указатель на новый список)
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
    else
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
void o_prnlist(elem*t) // печать кольцевого списка
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
    printf ("\n");
}
elem* o_dellist(elem*t)//(кольц.список) удаление списка
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
/*elem* search(elem* const t, int el) {
    elem *h = t->next, *p=0;
    while (h!=t) {	//проходим до хвоста
        if (h->info==el)// если нашли выходим из цикла
            break;
        p=h;
        h=h->next;
        
    }
    p=h;
    h=h->next;
    if (h==t && h->info!=el) // элемент не найден
        return 0;
    return p;
}*/
elem* search(elem* const t, int el) {
    elem *h = t;
    while ((h=h->next)!=t) {
        if (h->info==el)// если нашли выходим из цикла
            return h;
    }
    if (h->info!=el)// если нашли выходим из цикла
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
 void o_addafter(elem*p,int i) // вставка после элемента с указ-м, не в хвост(кольц.список), ф-я используется в непустых списках
 {
    elem*q=(elem*)malloc(sizeof(elem)); // выдел€ем пам€ть
    q->info=i; // записываем значение
    q->next=p->next;
    p->next=q;
 */


/*
 void o_prnlist(elem*t) // печать кольцевого списка
 {
 if (t!=0) // проверка на непустоту списка
    {
        elem*p=t; //
        while ((p=p->next)!=t) //  начинаем с головы и проходим до хвоста
            printf ("%i ",p->info);
        printf ("%i ",p->info);
    }
    printf ("\n");
*/
