/*
 “екстовый файл, в котором в произвольном пор€дке хран€тс€ имена.
 Ќет ограничений ни на кол-во, ни на уникальность.
 »мена из файла счит-с€ и располагаютс€ в пам€ти в алф-ном пор€дке.
 — клавиатуры вводитс€ N число n.
 Ќачина€ с 1-го вычеркиваем n-го участника(направление мен€етс€, начинаем с предыдущего пока не останетс€ 1-н.
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


elem* findr(int step ,pair*pr,elem*p, elem**q) // нахождение справа, p- элемент, который будет удален, q-предыдущий, ф-я возвращает ук-ль на найденный эл-т
{
    int i=1;
    for (; i<step && p->next!=NULL; i++)
        p=p->next; // проходим вправо до конца
    if ( i<step )
    {
        p=pr->begin; // перемещаемс€ в начало
        i++;
        for (; i<step; i++)
            p=p->next; // проходим вправо до конца
    }
    if (p==pr->begin) // определяем нахождение предыдущего элемента(указателя q)
        (*q)=pr->end;
    else
        (*q)=p->pred;
    return p;
}
elem* findl(int step ,pair*pr,elem*p, elem**q) // нахождение слева **p адрес указател€ в списке, p- элемент, который будет удален, q-предыдущий,ф-я возвращает ук-ль на найденный эл-т
{
     //printf (" step- %i\n",step);
    int i=1;
    for (; i<step && p->pred!=NULL; i++)
        p=p->pred;
    //printf ("for1 end !p %s\n",p->word);
    //printf (" i- %i\n",i);
    if ( i<step )
    {
        p=pr->end; // перемещаемс€ в начало
        i++;
        //printf (" i<step !p %s\n",p->word);
        
        for (; i<step; i++)
        {
            p=p->pred; // проходим влево до конца
            //printf (" for2 !p %s\n",p->word);
        }
    }
    if (p==pr->end) // определяем нахождение предыдущего элемента(указателя q)
        (*q)=pr->begin;
    else
        (*q)=p->next;
    return p;
}
void del_head(pair*pr,elem*p) // удаление в начале
{
    pr->begin=p->next;
    p->next->pred=NULL;
    printf ("delete %s\n",p->word);
    free(p);
}
void del_tail(pair*pr,elem*p) // удаление в конце
{
    pr->end=p->pred;
    p->pred->next=NULL;
    printf ("delete %s\n",p->word);
    free(p);
}
void del_mid(pair*pr,elem*p) // удаление в середине
{
    p->pred->next=p->next;
    p->next->pred=p->pred;
    printf ("delete %s\n",p->word);
    free(p);
}
elem* del(pair*pr,elem*p, elem*q)// *p -указатель в списке, *q -предыдущий, ф-я возвращает предыдущий ук-ль (перед удалённым)
{
    if (p==pr->begin) // в начале
    {
        del_head(pr,p);
        p=q;
        return p; // !
    }
    if (p==pr->end) // в конце
        del_tail(pr, p);
    else       // в середине
        del_mid(pr, p);
    p=q;
    return p; // !
}
 void deln(int step, pair*pr, int nstr) // удаление n-го элемента (?)
{
    if (pr->begin != NULL)
    {
        elem*p=pr->begin;
        elem*q=pr->end;
        while (pr->begin!=pr->end) // пока не останетс€ один элемент
        {
            p=findr(step%nstr ?step%nstr :nstr, pr, p, &q); // находим справа
            p=del(pr, p, q); // удал€ем
            nstr--;
            if (pr->begin!=pr->end)
            {
                p=findl(step%nstr ?step%nstr :nstr, pr, p, &q); //находим слева
                p=del(pr, p, q);// удал€ем
            }
            nstr--;
        }
    }
    else
        printf ("empty file");
}
void printlist(elem*h) // печать двусв€зного списка
{
    elem*p;
    for (p=h; p!=NULL; p=p->next)
        printf("%s\n",p->word);
    printf (".\n");
}
void addfirst(pair*pr,char*s) // добавление первого слова в список
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
void add(char*s,elem*p) // добавить на место элемента, на который есть ук-ль *p (добавить перед)
{
    char*word;
    word=wrd(s,word);
    elem*q=(elem*)malloc(sizeof(elem)); //выд-е пам€ти под новый элемент
    q->word=word;
    q->next=p;
    p->pred->next=q; //
    q->pred=p->pred;
    p->pred=q;
}
void addhead(char*s,pair*pr) // добавление в голову дерев€нного списка
{
    char*word;
    word=wrd(s,word);
    elem*q=(elem*)malloc(sizeof(elem));// выд-е пам€ти под новый элемент
    q->word=word;
    pr->begin->pred=q;
    q->next=pr->begin;
    pr->begin=q;
    q->pred=NULL;
}
void addtail(char*s, pair*pr) //добавление в конец
{
    char*w;
    w=wrd(s,w);
    elem*q=(elem*)malloc(sizeof(elem)); //выд-е пам€ти под новый элемент
    pr->end->next=q;
    q->word=w;
    q->pred=pr->end;
    pr->end=q;
    q->next=NULL;
}
char* wrd(char*s,char*w) // создает слово нужной размерности и возвращает ук-ль на слово
{
    unsigned int len=strlen(s)+1;// длина слова + '/0'
    w=(char*)malloc((len)*sizeof(char));//
    w=strcpy(w,s);
    return w;
}
void addword(FILE*f,pair*pr) // добавление слова в список (по алфавиту)
{
    char s[N+1];
    fgets(s,N,f);
    if((pr->begin)==NULL)
    {
        addfirst(pr,s); //добавление в голову(первое слово)
    }
    else
    {
        elem*copy;
        copy=pr->begin;// начинаем проходить по списку с головы
        while(copy!=NULL)
        {
            if (strcmp(s,pr->begin->word)<0)// если слово вставл€тс€ в голову (слово < слово в начале)
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
        addtail(s,pr); //добавл€емое слово в конце
    }
}
int startadd(FILE*f,char str[],pair*pr) // добавление слов до конца файла (ф-€ возвращает кол-во слов в файле)
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
    pair pr[1]; // выд-е пам€ти под пару
    pr->begin=0;
    pr->end=0;
    char str[]="/Users/okot444/Desktop/names.txt";
    FILE*f;
    int nstr=0; //  кол-во слов в списке
    nstr=startadd(f, str, pr); //
    printlist(pr->begin);
    printf ("nstr -%i\n",nstr);
    int step; // кол-во шагов
    printf ("step - ");
    scanf("%i",&step);
    if (step>0)
        deln(step,pr,nstr); // пустой файл.?
    else
        printf ("step=0 error\n");
    printlist(pr->begin);
}

