/*
 �������� �������� �� ������ �� ��������.
 ������� ����.
 ����� �����.
 ����-� ������.
 */
#include <iostream>
#include <stdio.h>
#include<stdlib.h>
struct node // ��������� ����
{
    int info;
    node *left,*right; //�� ����� � ������ ���������
    int count;//���-�� ��������
};

node*insert(node*r,int v)//������� � ������ ������, ���������� ��-�� �� ������, ��������� �� ������ � �������� ��� �������
{
    if (r==0)
    {
        r=(node*)malloc(sizeof (node)); // ��������� �����
        r->info=v;
        r->count=1;
        r->left=r->right=0;
        return r; // ���������� ������
    }
    if(r->info>v) // ���������� �������� ������
        r->left=insert(r->left,v); // �������� � ����� ���������
    else
        if (r->info<v)  // ���������� �������� ������
            r->right=insert(r->right,v); // �������� � ������ ���������
        else // ������� ���������
            r->count++; // ���������� count (���-�� ��������)
    return r; // ���������� ������
    
}
node* dlt_root(node*r) // �������� ������
{
    if (r)
    {
        dlt_root(r->left); //�������� �����
        node *p=r->right;
        free(r);
        dlt_root(p); // �������� ������
    }
    return 0;
}
void lrprn(node*r)// ����-� ������ ������
{
    if (r)
    {
        lrprn(r->left);
        printf ("%i count_%i\n",r->info,r->count);
        lrprn(r->right);
    }
}
void udprn(node*r)// ����-�  ������ ������ ����
{
    if (r)
    {
        printf ("%i count_%i\n",r->info,r->count);
        udprn(r->left);
        udprn(r->right);
    }
}
void duprn(node*r)// ����-�  ������ ������ ����
{
    if (r)
    {
        duprn(r->left);
        duprn(r->right);
        printf ("%i count_%i\n",r->info,r->count);
    }
}
node* search_p(node*r, int v, node  **q)// ���������� ������� ��������� ��������, ������� ���������� ��-�� �� �������
{
    if(r==0) //
        return 0;
    if (r->info>v) //  �������� ������ ��-��
    {
        (*q)=r;
        r=search_p(r->left, v, q); // ������� �����
    }
    else
        if (r->info<v) //  �������� ������ ��-��
        {
            (*q)=r;
            r=search_p(r->right, v, q); // ������� ������
        }
        //else  //( r->info == v) //  �������� ����� ��-��
          //  return r;
    return r;
}

node* search_replace(node*r,node**q)// ���������� ������������� �������� � ����� ���������(r), �������� ��-�� �� �������� ���������� ��-�� �� ���� �������(q)
{
    (*q)=r; //�������� � �����
    r=r->left; // ���������� � ����� ���������
    while (r->right!=NULL) // ���� ����� ������ (������������)
    {
        (*q)=r;
        r=r->right;
    }
    return r;
}
node* dlt_01_root (node*r,node*p) // �������� ����� � ����� ��������, r- ������, �-� ���������� ��-�� �� ������
{
    if (p->left !=NULL)
        r=p->left;
    else
        r=p->right;
    free(p);
    return r;
}
void dlt_01(node*p,node*q) // �������� �� ������ � 1 �������� ��� 0, r- ������,p- ��������� �� ���������, q- ��������� �� �������� ����������,�-� ���������� ������
{
    if (q->left==p) // ���� ��������� ������� ����� �� ��������
        if (p->left !=NULL)
            q->left=p->left;
        else
            q->left=p->right; //
    else // ���� ��������� ������� ������ �� ��������
        if (p->left !=NULL)
            q->right=p->left;
        else
            q->right=p->right; //
}
node*dlt(node*r,int v)//�������� �� ������ ������, ��������� �� ������(r) � �������� ��������(v),  ���������� ��-�� �� ������
{
    
    node*p,*q=0; // p-������� (��-�� �� ��������� ��������) q - ��������
    p=search_p(r, v, &q); // �������� (��-�� �������� ���������� ��������)
    if(p!=0)// �������� �������
    {
        if ( q==NULL  && (p->left==NULL || p->right==NULL))// �������� ����� � ����� �������� (��������� ������) ��� ��������, 1 �������  ???
        {
            r=dlt_01_root (r,p);
            return r;
        }
        if (p->left!=NULL && p->right!=NULL) // 2 �������
        {
            node*rp=0;  // ������������ ������� (��� ������)
            rp=search_replace(p,&q); //  ��������� ������������ �������
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
    int v; // �������� � ���������� - v
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
 node*rp=0;  // ������������ ������� (��� ������)
 rp=search_replace(p,&q); //  ��������� ������������ �������
 p->info=rp->info;
 p=rp;
 if(q->left==rp)
 q->left=NULL;
 else
 q->right=NULL;
 }*/
/*node* search_replace(node*r, node**p)// ���������� ������������� �������� � ����� ���������, ���������� ��-�� �� ��������
 {
 (*p)=r; // ���������, ������� ������ ������������ ��-� � ����� ���������
 node*q=r; // ��-�� �� ��������
 (*p)=(*p)->left; // ���������� � ����� ���������
 while ((*p)->right!=NULL) // ���� ����� ������
 {
 q=(*p);
 (*p)=(*p)->right;
 }
 return q;
 }*/
