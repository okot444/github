#include <iostream>
#include <assert.h>
// ������������� ��������� (������ ������)

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
 	���������� ������� ����������� ��-�
	����������� ������� ������������
 8. ������������ � �������������� �������� ��������� (int) <
 � < B , ���� ��� �������� ���������� B
 ��-� < � , ���� ��-� ����������� B
 A == B , ��������������
 9. �������� ��-�� (���-�� ���������) (int)
 10.=, +=, -=, &=, ^= ������������
 11. ����� � ����� <<
 ������ ��������� - ��������� , � ������� ��� ���������
 */
using namespace std;
template <class Ttype> class tree;
template <class Ttype> struct  node  // ��������� ����
{
    node *left,*right,*parent; //�� ����� � ������ ���������
    Ttype info;
};
template <class Ttype> class tree
{
	public:
		tree(Ttype v);
	
		
		friend ostream& operator << (ostream &out, const tree<Ttype> &r)
		{
			r.printtree(r.root, out);
			return out;
		}
	
		tree<Ttype>& operator += (const tree<Ttype> &t);
		tree<Ttype> operator + (const tree<Ttype> &t);
		
		tree<Ttype>& operator ^= (const tree<Ttype> &t);
		tree<Ttype> operator ^ (const tree<Ttype> &t);
		
		tree<Ttype>& operator -= (const tree<Ttype> &t);
		tree<Ttype> operator - (const tree<Ttype> &t);
		
		tree<Ttype>& operator &= (const tree<Ttype> &t);
		tree<Ttype> operator & (const tree<Ttype> &t);
		
		tree<Ttype> operator + (const Ttype i) ;
		tree<Ttype> operator - (const Ttype i) ;
		tree<Ttype>& operator -- ();
    	tree<Ttype>& operator -- (int);
    	
    	int operator < (const tree<Ttype> &t) const;
    	friend int operator < ( const tree<Ttype> &t,const int i)// �������������� ��-�� ���������
    	{
    		cout<<"friend"<<endl;
    		if (t.root->left)
				subtree(t.root->left,i);
			if (t.root->right)
				subtree(t.root->right,i);
		    if (t.root == 0) //� ������� ��-�� ��� �����������
				return 0;
			if(search(t.root,i) == 0) // �� �������
				return 0;
			return 1;
		}
    	int operator == (const tree<Ttype> &t) const;
    	operator int() const;
		
	private:
		node<Ttype> *insert(node <Ttype> *r,const Ttype v);// �������
		node<Ttype> *search(node <Ttype> * r,Ttype v)const ;// �����
		node <Ttype> *dlt(node <Ttype> *r,const Ttype v );// �������� ��������
		
		
		node<Ttype>* dlt_01_root (node <Ttype>*r);
		void dlt_01(node <Ttype> *p,node <Ttype> *q);
		node<Ttype>* search_replace(node<Ttype>*r,node<Ttype>*q);
		
		void copytree(node <Ttype>**rt,const node <Ttype>*r); // ����������� ������
		
		void copy_insert(node <Ttype>*rt,node <Ttype>*r);// �����
		node<Ttype>* add(node <Ttype> *r1,node <Ttype> *const r2);
		node<Ttype>* x(node <Ttype>*r1,node <Ttype>* const r2);
		node<Ttype>* res(node <Ttype>*r1,node <Ttype>* const r2);
		void addtotree(node <Ttype> *r1,node <Ttype> *const r2);
		node<Ttype>* symmres(node <Ttype>*r1,node <Ttype>*  r2);
		int max (const node<Ttype>*r1);
		int min (const node<Ttype>*r1);
		
		int subtree( node <Ttype>*r1,node <Ttype>*  r2, int* i )const ;// <
		int equivalence(node<Ttype>* const r1, node<Ttype>* const r2)const ;
		int count(node<Ttype>* const t, int * i) const;
	
		void printtree(node<Ttype>* const r, ostream& out) const;
		
		void lrprn(const node <Ttype>*r)const ;
		node<Ttype>* root;
};
template <class Ttype> tree<Ttype>:: tree (Ttype v) // �����������
{
	root = new node <Ttype>;
	root->info = v;
	root->right = NULL;
	root->left = NULL;
	root->parent = NULL; //??
}
template <class Ttype> node<Ttype>* tree<Ttype>:: search(node <Ttype>*r,  Ttype v) const
// ����� ��������
{
    if(r==0) //
        return 0;
        
    if (r->info>v) //  �������� ������ ��-��
        r=search(r->left, v); // ������� �����
    else
        if (r->info<v) //  �������� ������ ��-��
            r=search(r->right, v); // ������� ������
    return r;
}
/*template <class Ttype> ostream& operator <<(ostream& out, const tree<Ttype>& t){
	t.lrprn(t.root, out);
	return out;
}*/
template <class Ttype> node<Ttype>* tree<Ttype>::dlt_01_root (node <Ttype>*r) // �������� ����� � ����� ��������, r- ������,
// �-� ���������� ��-�� �� ������
{
	node<Ttype>* p = r;
    if (r->left != NULL)
        r = r->left;
    else
        r = r->right;
    delete p;
    if (r)
		r->parent=NULL;
    return r;
}
template <class Ttype> void tree<Ttype>::dlt_01(node <Ttype> *p,node <Ttype> *q) 
// �������� �� ������ � 1 �������� ��� 0
// p - ��������� �� ��������� q-��������
{
    if (q->left == p){ // ���� ��������� ������� ����� �� ��������
        if (p->left != NULL)
            q->left = p->left;
        else
            q->left = p->right; 
        }
    else // ���� ��������� ������� ������ �� ��������
        if (p->left !=NULL)
            q->right=p->left;
        else
            q->right=p->right; //
    delete p;
}
template <class Ttype> node <Ttype> * tree<Ttype>::search_replace(node<Ttype>*r,node<Ttype>*q)// ���������� ������������� �������� � ����� ���������(r), �������� ��-�� �� �������� 
//���������� ��-�� �� ���� �������(r)
{
    q=r; //�������� � �����
    r=r->left; // ���������� � ����� ���������
    while (r->right!=NULL) // ���� ����� ������ (������������)
    {
        q=r;
        r=r->right;
    }
    return r;
}
template <class Ttype> node <Ttype> *tree<Ttype>:: dlt(node <Ttype> *r,Ttype v )
//�������� �� ������ ������, ��������� �� ������(r) � ��������� ��������(v),  ���������� ��-�� �� ������
{
    node  <Ttype>* p=search(r, v); 
    //cout<<p->parent->info<<endl;
    if ( p->parent==NULL  && (p->left==NULL || p->right==NULL))// �������� ����� � ����� �������� (��������� ������) ��� ��������, 1 �������  ???
    {
        r=dlt_01_root (r);
        return r;
    }
    
    if (p->left!=NULL && p->right!=NULL) // 2 �������
    {
    //	cout<<"rp"<<endl;
        node <Ttype>*rp=0;  // ������������ ������� (��� ������)
        rp=search_replace(p,p->parent); //  ��������� ������������ �������
        p->info=rp->info;
        p=rp;
    }
    dlt_01(p, p->parent);
    return r;
}
template <class Ttype> node<Ttype>* tree<Ttype>:: insert(node <Ttype>*r,Ttype v)//������� � ������ ������,
// ���������� ��-�� �� ������, ��������� �� ������ � �������� ��� �������
//node <Ttype>*p -  �������� 
{
    if (r == 0) {
        r = new node <Ttype>; // ��������� �����
        r->info = v;
        r->left = NULL;
		r->right = NULL;
        return r; // ���������� ������
    }
    if(r->info>v) { // ���������� �������� ������	
        r->left = insert(r->left,v); // �������� � ����� ���������
        r->left->parent = r;
    }
    else
        if (r->info<v)  // ���������� �������� ������
        {
            r->right = insert(r->right,v); // �������� � ������ ���������
            r->right->parent = r;
        }
    return r; // ���������� ������
}
template <class Ttype> void tree<Ttype>::lrprn(const node <Ttype>*r)const // ����-� ������ ������ 
// node*, int , 
{
    if (r)
    {
        lrprn(r->left);
        cout<<r->info<<" ";//
        lrprn(r->right);
    }
}


template <class Ttype> void tree<Ttype>:: copytree(node <Ttype>**rt,const node <Ttype>*r) // ����������� ������ �� r � rt
{
	if (r){
		copytree(rt,r->left);
		*rt  = insert(*rt,r->info);
		copytree(rt,r->right);
	}
}

template <class Ttype> node<Ttype>* tree<Ttype>:: add(node <Ttype>*r1,node <Ttype>* const r2)
 //�����������, ���������� ��-�� �� t1
{
	if(r2){
		r1 = insert(r1,r2->info);
		r1 = add(r1,r2->left);
		r1 = add(r1,r2->right);
	}
//	if (search(r1,r2->info) == 0)
		/*insert(r1,r2->info);
	//else
		if (r2->left)
			add(r1,r2->left);
		if (r2->right)
			add (r1,r2->right);*/
	return r1;
}
template <class Ttype> node<Ttype>* tree<Ttype>:: x(node <Ttype>*r1,node <Ttype>* const r2) // �����������
//�����������, ���������� ��-�� �� r1
{
	if (r1->left)
		r1->left = x (r1->left,r2);
	if (r1->right)
		r1->right = x (r1->right,r2);
	node <Ttype>*r = search(r2,r1->info);//! ���� �� ������ ������
	if (r == 0)// ������� �� ������������
		r1 = dlt(r1,r1->info); // ������� � ������
	return r1;
}
template <class Ttype> node<Ttype>* tree<Ttype>:: res(node <Ttype>*r1,node <Ttype>* const r2) // ��������
{
	node <Ttype>*r = search(r2,r1->info);			//�������� �� ��������� ������� ������
	if (r1->left)
		r1->left = res (r1->left,r2);
	if (r1->right)
		r1->right = res (r1->right,r2);
	if (r != 0)	//�����, �������
		r1 = dlt(r1,r->info);
	return r1;
}
template <class Ttype> node<Ttype>* tree<Ttype>:: symmres(node <Ttype>*r1,node <Ttype>*  r2)  // ������������ ��������
{
	node<Ttype>*m = new node<Ttype>; // 
	m=0;
	copytree(&m,r2); // ����� ������� , ������� ��������  �� ������� ������
	r2 = res(r2,r1); // ������ ��� �������
	r1 = res(r1, m); // ������ ��� �������
	r1 = add(r1,r2); // �������� �������� � ������ 
	return r1;
}
template <class Ttype> int tree<Ttype>::max (const node<Ttype>*r1) // ���������� ������������� ��-�� � ������
{
	while(r1->right !=0 )
		r1=r1->right;
	return r1->info;
}
template <class Ttype> int tree<Ttype>::min (const node<Ttype>*r1) // ���������� ������������ ��-�� � ������
{
	while(r1->left !=0 )
		r1=r1->left;
	return r1->info;
}
template <class Ttype> int tree<Ttype>::subtree( node <Ttype>* r1, node <Ttype>* r2, int* i ) const
{
	if (r1->left)
		subtree(r1->left,r2,i);
	if (r1->right)
		subtree(r1->right,r2,i);
	if (search(r2, r1->info) == 0)// ������� �� ������ - �� ������������
		return 0;
	return ++i[0];
}
template <class Ttype> int tree<Ttype>::subtree( node <Ttype>* r1, int i ) const
{
	if (r1->left)
		subtree(r1->left,i);
	if (r1->right)
		subtree(r1->right,i);
	if (search(r1, i) == 0)// ������� �� ������ - �� ������������
		return 0;
	return 1;
}
template <class Ttype> int tree<Ttype>:: count(node<Ttype>* const r, int *i) const// ��������� ���-�� ���������
{
	if (r->left)
		count(r->left, i);
	if (r->right)
		count(r->right, i);
	return ++i[0];
}
template <class Ttype> int tree<Ttype>:: equivalence(node<Ttype>* const r1, node<Ttype>* const r2) const
{
	int c1, c2;
	int i[1];
	i[0] = 0;
	c1 = subtree(r1,r2,i);
	c2 = count(r2,i);
	return c1 == c2;
}
template <class Ttype> tree<Ttype>& tree<Ttype>:: operator -= (const tree<Ttype> &t) // ��������
{
	if (root == NULL) 
		return *this;
	if (t.root == NULL)
		return *this;
	root = res(root,t.root);
}
template <class Ttype> tree<Ttype>& tree<Ttype>:: operator += (const tree<Ttype> &t) // �����������
{
	if (root == NULL) {
		copytree(&root,t.root);
		return *this;
	}
	if (t.root == NULL)
		return *this;
    root = add (root, t.root);
    return *this;
}
template <class Ttype> tree<Ttype>& tree<Ttype>:: operator ^= (const tree<Ttype> &t)
{
	if (root == NULL){
		return *this;
	}
	if (t.root == NULL){
		root = NULL;
		return *this;
	}
    root = x (root, t.root);
    return *this;
}
template <class Ttype> tree<Ttype>& tree<Ttype>:: operator &= (const tree<Ttype> &t)
{
	if (root == 0){
		copytree(&root,t.root);
		return *this;
	}
	if (t.root == 0)
		return *this;
    root = symmres (root, t.root);
    return *this;
}
template <class Ttype> tree<Ttype> tree<Ttype>:: operator + (const Ttype i)
{ //�������� ������� 
//	if (!search(root,i)){ // � ��������� �������� �� �����������
		root = insert(root, i);
		return *this;
//	}
}
template <class Ttype> tree<Ttype> tree<Ttype>:: operator - (const Ttype i) // �������� �� ��������
{
	if (search(root,i))
		root = dlt(root,i);
	return *this;
}
template <class Ttype> tree<Ttype>&  tree<Ttype>:: operator -- () //  ����������
{
	root = dlt(root,max(root));
	return *this;
}
template <class Ttype> tree<Ttype>&  tree<Ttype>:: operator -- (int) // �����������
{
	root = dlt(root,min(root));
	return *this;
}
template <class Ttype> int tree<Ttype>:: operator < (const  tree<Ttype> &t)const
// ���������� ���-�� ���������, 
{
	if (root == 0) 	//������ ��������� 
		return 0;								
	if (t.root == 0) 	// ������ ��������� 
		return 0;
	int i[1];
	i[0] = 0;
	return subtree(root,t.root,i); 
}
template <class Ttype> int tree<Ttype>:: operator == (const tree<Ttype> &t)  const
{
	return equivalence(root,t.root);
}
template <class Ttype> tree<Ttype>:: operator int() const
{
	int i[1];
	i[0] = 0;
	if (root == 0) //������ ������
		return 0;
	return count(root,i);
}
template <class Ttype> void tree<Ttype>:: printtree(node<Ttype>* const r, ostream& out) const
{
	if (r == 0) 
		out<<"Empty list!"<<endl;
	else
		lrprn(r);
}
// ����� ������
// ���������
/*template <class Stype> class set
{
	public:
		
	private:
		node <Ttype> *root;
		
		
};*/
int main()
{
	tree <int> t1(2) ;
//	t1+=6;
//	t1--;
	cout<<"t1: "<<t1<<endl;
	tree<int> t2(2);
	t2+=4;
	//t2--;
	cout<<"t2: "<<t2<<endl;
	
	cout<< "t2<4: "<<( t2<4 )<<endl;
	
	
}
