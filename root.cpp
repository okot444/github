/*
 ”даление элемента из дерева по значению.
 —верхну вниз.
 —низу вверх.
 ”дал-е дерева.
 */
#include <iostream>
#include <stdio.h>
#include<stdlib.h>
struct node // структура узла
{
    int info;
    node *left,*right; //на левое и правое поддерево
    int count;//кол-во повторов
};

node*insert(node*r,int v)//вставка в дерево поиска, возвращает ук-ль на корень, указатель на корень и значение при вставке
{
    if (r==0)
    {
        r=(node*)malloc(sizeof (node)); // выделение пам€ти
        r->info=v;
        r->count=1;
        r->left=r->right=0;
        return r; // возвращаем корень
    }
    if(r->info>v) // вставл€емое значение меньше
        r->left=insert(r->left,v); // вставл€ем в левое поддерево
    else
        if (r->info<v)  // вставл€емое значение больше
            r->right=insert(r->right,v); // вставл€ем в правое поддерево
        else // значени€ совпадают
            r->count++; // увеличивем count (кол-во повторов)
    return r; // возвращаем корень
    
}
node* dlt_root(node*r) // удаление дерева
{
    if (r)
    {
        dlt_root(r->left); //удаление слева
        node *p=r->right;
        free(r);
        dlt_root(p); // удаление справа
    }
    return 0;
}
void lrprn(node*r)// функ-€ левого обхода
{
    if (r)
    {
        lrprn(r->left);
        printf ("%i count_%i\n",r->info,r->count);
        lrprn(r->right);
    }
}
void udprn(node*r)// функ-€  обхода сверху вниз
{
    if (r)
    {
        printf ("%i count_%i\n",r->info,r->count);
        udprn(r->left);
        udprn(r->right);
    }
}
void duprn(node*r)// функ-€  обхода сверху вниз
{
    if (r)
    {
        duprn(r->left);
        duprn(r->right);
        printf ("%i count_%i\n",r->info,r->count);
    }
}
node* search_p(node*r, int v, node  **q)// нахождение родител€ заданного элемента, функция возвращает ук-ль на потомка
{
    if(r==0) //
        return 0;
    if (r->info>v) //  значение меньше эл-та
    {
        (*q)=r;
        r=search_p(r->left, v, q); // находим слева
    }
    else
        if (r->info<v) //  значение больше эл-та
        {
            (*q)=r;
            r=search_p(r->right, v, q); // находим справа
        }
        //else  //( r->info == v) //  значение равно эл-ту
          //  return r;
    return r;
}

node* search_replace(node*r,node**q)// нахождение максимального элемента в левом поддереве(r), изменяет ук-ль на родителя возвращает ук-ль на макс элемент(q)
{
    (*q)=r; //начинаем с корня
    r=r->left; // нахождение в левом поддереве
    while (r->right!=NULL) // ищем самый правый (максимальный)
    {
        (*q)=r;
        r=r->right;
    }
    return r;
}
node* dlt_01_root (node*r,node*p) // удаление корня с одним потомком, r- корень, ф-я возвращает ук-ль на корень
{
    if (p->left !=NULL)
        r=p->left;
    else
        r=p->right;
    free(p);
    return r;
}
void dlt_01(node*p,node*q) // удаление из дерева с 1 потомком или 0, r- корень,p- указатель на удаляемое, q- указатель на родителя удаляемого,ф-я возвращает корень
{
    if (q->left==p) // если удаляемый элемент слева от родителя
        if (p->left !=NULL)
            q->left=p->left;
        else
            q->left=p->right; //
    else // если удаляемый элемент справа от родителя
        if (p->left !=NULL)
            q->right=p->left;
        else
            q->right=p->right; //
}
node*dlt(node*r,int v)//удаление из дерева поиска, указатель на корень(r) и удал€емое значение(v),  возвращает ук-ль на корень
{
    
    node*p,*q=0; // p-потомок (ук-ль на удаляемое значение) q - родитель
    p=search_p(r, v, &q); // родитель (ук-ль родителя удаляемого значения)
    if(p!=0)// значение найдено
    {
        if ( q==NULL  && (p->left==NULL || p->right==NULL))// удаление корня с одним потомком (отдельный случай) нет родителя, 1 потомок  ???
        {
            r=dlt_01_root (r,p);
            return r;
        }
        if (p->left!=NULL && p->right!=NULL) // 2 потомка
        {
            node*rp=0;  // максимальный элемент (для замены)
            rp=search_replace(p,&q); //  найденный максимальный элемент
            p->info=rp->info;
            p=rp;
        }
        dlt_01(p, q);
        return r;
    }
    else
        printf ("error find v");
    return 0;
}
int main()
{
    
    node*root=0;
    printf ("v -");
    int v; // значение с клавиатуры - v
    scanf("%i",&v);
    int s;
    for (int i=1; i<6; i++) //
    {
        scanf("%i",&s);
        root=insert(root,s);
    }
    printf("\n . \n");
    lrprn(root);
    root=dlt(root,v);
    printf("\n . \n");
    lrprn(root);
    dlt_root(root);
}


/*else{ // ?????
 node*rp=0;  // максимальный элемент (для замены)
 rp=search_replace(p,&q); //  найденный максимальный элемент
 p->info=rp->info;
 p=rp;
 if(q->left==rp)
 q->left=NULL;
 else
 q->right=NULL;
 }*/
/*node* search_replace(node*r, node**p)// нахождение максимального элемента в левом поддереве, возвращает ук-ль на родителя
 {
 (*p)=r; // указатель, который найдет максимальный эл-т в левом поддереве
 node*q=r; // ук-ль на родителя
 (*p)=(*p)->left; // нахождение в левом поддереве
 while ((*p)->right!=NULL) // ищем самый правый
 {
 q=(*p);
 (*p)=(*p)->right;
 }
 return q;
 }*/
