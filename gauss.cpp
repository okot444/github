// ����� ������
#include <stdio.h>
#include <stdlib.h>
#define EPS 0.00001
#include <math.h>
int read_size(FILE*f);
double* gauss();
double read_number_d(FILE *f);
int find_a(double**m, int sz1, int sz2,int j);
void up (double **m, int sz1, int sz2, int i, int j);
void delfirst (double**m, int sz1, int sz2, int i, int j, double mr);
void check( double**m, double* x, int sz1, int sz2);
double** create2 (int sz1, int sz2);// ��������� ������ ��� ��������� ������,
double* create1 (int sz1); // ��������� ������ ��� ���������� ������
double ** copy (double**m, int sz1, int sz2); // ����������� �������
void print2 (double** m, int sz1, int sz2);
void print1 (double* m, int sz1);
void print2 (double** m, int sz1, int sz2)// ������ ���������� �������
{
    int i, j;
    for(i=0; i<sz1; i++)
    {
        for(j=0; j<sz2; j++)
            printf(" %.3e  ",m[i][j]); //
        printf("\n");
    }
    printf("\n");
}
void print1 (double* m, int sz1)// ������ ����������� �������
{
	printf ("x: ");
	if (m==0){
		printf (" no  ");
		return;
	}

	for (int i=0; i<sz1; i++)
		printf (" %.3e  ", m[i]);
	printf("\n");
}
double** create2 (int sz1, int sz2)// ��������� ������ ��� ��������� ������, �-� ���������� ��������� �� ������ �������
{
    double**t=(double**)malloc(sizeof(double*)*sz1); //������� ��������� �� ������ sz1-���-�� ��������� ������� ��������� ������
    int i;
    for(i=0; i<sz1; i++) //�������� �����
        t[i]=(double*)malloc(sizeof(double)*sz2);//*(t+i)
    return t;
}
double* create1 (int sz1) // ��������� ������ ��� ���������� ������, �-� ���������� ��������� �� ������ �������
{
	double* x = (double*)malloc(sizeof(double)*sz1);
	return x;
}
void erase2 (double **m, int sz1, int sz2)// �������� ������ (��������� ������)
{
    int i;
    for(i=0; i<sz1; i++) //�������� �����
        free(m[i]);
    free(m);
}
void erase1 (double *m, int sz1)// �������� ������ (���������� ������)
{
    free(m);
}
double** read_file (FILE *f, int n1, int m1){
    
    if (n1>0 && m1>0){
		double** m = create2(n1, m1);
		
		int i;
		int j;
		printf("\nstr (n) - %i, stl (m) - %i\n\n",n1 , m1);
		for (i=0; i<n1; i++)
		    for ( j=0; j<m1; j++)
		        m[i][j] = read_number_d(f);
		fclose(f);
		return m;
	}
	return 0;
}

int read_size(FILE*f) // ���������� ����������� ������� � �����
{
    int i;
    fscanf(f, "%i", &i);
    return i;
}
double read_number_d(FILE*f)
{
    double fl;
    fscanf(f, "%lf", &fl);
    return fl;
}

int delta(double**m, int sz1, int sz2)// �������� ������� � ������������ ����
{
	int a;
    for (int j=0; j<sz1-1; j++){ // �������� �� �������  ( ��������� sz1-1?)
        if (fabs(m[j][j])< EPS){
        	m[j][j] = 0.;
			a = find_a(m,sz1,sz2,j); //
		    if ( !a ) // ������� ���������
		        return 0; // � ������������ ���� �� ����������
		    else
            	up (m, sz1, sz2, a, j); // �������� ������� ������ a � j 
		}
		for ( int i = j+1; i<sz1; i++) { // ��� ������ ������
        	double mr = m[i][j] / m[j][j];
        	delfirst(m,sz1,sz2,i,j,mr); 
        }
    }
    return 1; // � ������������ ���� ���������
}
void delfirst (double**m, int sz1, int sz2, int i, int j, double mr) 
// �������� i-�� ������ �� �����������  mr � �������� , sz1 sz2 ��������� �������,
{
	m[i][j] = 0. ;
    for (int ii = j+1; ii<sz2; ii++){
    	if (fabs(m[i][ii]) < EPS)
        	m[i][ii] = 0.;
        m[i][ii] -= m[j][ii] * mr;
    }
}
void up (double **m, int sz1, int sz2, int a, int j) // �������� ������� ������ a � j  
{
    double* temp = m[a];
    m[a] = m[j];
    m[j] = temp;
}
int find_a(double**m, int sz1, int sz2, int j) // ���������� ���������� ������������ � ������ ������� (����� ������� ���������)
{
    int i;
    for (i=j+1; i<sz1; i++) // �������� �� ������� (� �������� �� ��������� ����)
        if (m[i][j])
            return i;
    return 0; // i == sz1 -> ���������, ����� ��������� ������ ������
    // ���������� ������, � ������� ������ ������ ��������� ����-�, ���� i>sz1 => ������� ���������
}
int mnn(double**m, int sz1, int sz2)// c������ ���������
{
	if (m[sz1-1][sz1-1] == 0. ){
		printf ("v ");
		if (m[sz1-1][sz2-1] == 0.)
			printf ("mnogo resh");
		else 
			printf ("no resh\n");
		return 0;
	} 
	return 1;
}
double* replace( double**m, double*x, int sz1, int sz2) // �������� �����������
{
	for (int i = sz1-1; i >= 0; i--){
		x[i] = m[i][sz2-1]; // b (��������� ����)
		for ( int k = sz2-1; k > i+1; k--)
			x[i] -= m[i][k-1]*x[k-1];
		x[i] /= m[i][i];
	}
	return x;
}

double* gauss ( double**m,int sz1, int sz2) // ���������� ��-�� �� ����������� ������� (��� 0 )
{ 
	if (delta(m,sz1,sz2)){ //  ����������� ���
		printf("delta:\n");
    	if (mnn(m,sz1,sz2)){
    		double*x = create1(sz1);
			x = replace(m,x,sz1,sz2);
			return x;
		}
	}
	else 
		if (m[sz1-1][sz2-1] == 0)
			printf("besk resh\n");
		else
			printf("no resh\n");
	return 0;
}
int main() {
    
    FILE*f = fopen("f.txt", "r");
    if (f){
    	double**mx;
		int n,m;
		double*x;
		
        n = read_size(f); // ������ �����
        m = read_size(f);
        mx = read_file(f,n,m);
        
        print2(mx,n,m); // �����
        fclose(f);
        
      	x = gauss(mx,n,m); // �������
        
		print2(mx, n, m); // �����
		print1(x,n);
		erase2(mx,n,m);
		erase1(x,n);
    }
    else
        printf("error open file");
    
}
/*void check( double**m, double* x, int sz1, int sz2) // �������� 
{
	for (int i=0; i<sz1; i++)
		printf ("!x[%i] : %f\n",i, x[i]); 
	for (int i=0; i<sz1; i++)
	printf ("!b[%i] : %.3e  \n",i, m[i][sz2-1]); 
	printf ("\n"); 
	for (int i=0; i<sz1; i++)
		for (int j=0; j<sz2-1; j++)
			m[i][sz2-1] -= m[i][j] * x[j];  // b (��������� ����)
}*/
