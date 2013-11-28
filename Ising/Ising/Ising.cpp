#include "stdafx.h"

using namespace std;

ifstream in("input.txt");

int N=10;		// ������ �������
int I=5000;	    // ���������� ��������. I for Iterations
double J=1;		// ����������� ����� ����� ��������� �������
double H=-1;		// ������� ��������� ����
long double K=0.0000000001;	// ����� ����������� ���������
int TMin=1;		// ������������� �������� �� �������� 10
int TMax=20;
int Av=1000;			// �� ������ ����� ������� ���������
//long double K=exp(log(10.0))*exp(-23.0);	// ����������� ��������� � ������� ��
vector<vector<short>> lattice(N);	// ��������� ������� �������
vector<vector<short>> extra(N);		// ��������� �������� ����������� �������

int Spin(int i, int j, long t);		// ��������� ����� �������� �������
void Fill();				// ���������� �������
int Magnetization();		// ���������� ��������������� ��� ������ ������������
void Print(int a, int b);	// ��� �������
void Back();				// �������������� �������
double Average(int X) ;
void MFill(int M[]);				// ���������� �������� �� �����

int _tmain(int argc, _TCHAR* argv[])
{    
	int a,b; //
	int *M=new int[TMax-TMin+1];	// ������ ���������������� 
	long t;						// �������� �����������
	srand(time(NULL));

	MFill(M);			// ���������� ������� ���������������� 0��

	cout << "J: ";
	for(int i=0;i<Av; i++)		// ������� �� ������� 
	{
		Fill();
		for(int T=TMin; T<TMax; T++)
		{	
			t=1;
			for(int j=0; j<T-TMin; j++)
			{
				t*=10;
			}
			for(int i=0; i<I; i++)
			{
				a=rand()%N;
				b=rand()%N;
				lattice[a][b]=Spin(a, b, t);
			}
			M[T-TMin]+=Magnetization();
			Back();
		}
	}
	for(int T=TMin; T<TMax; T++)
	{		
		cout << Average(M[T-TMin]) << " ";
	}
	return 0;
}

double Average(int X)
{
	double rat1, rat2, result;
    for(int T=TMin; T<TMax; T++)	// ����������
	{		
		rat1=X;
		rat2=Av;
		result=rat1/rat2;
		Back();
	}
	return result;
}

void Print(int a, int b)	// ��� �������
{
	cout << "a:" << a << " " << "b:" << b << "\n";
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			cout << lattice[i][j] << " ";
		}
		cout << "\n";
	}
}

int Spin(int i, int j, long t)
{
 long double beta=1/K;		// ����� k=1
 long double x=t;
 beta/=x;
 long double b=H;			// ������� ��������������
 long double pos;		// ����������� ��������������� � ��������������� �����
 // �������� ���� ������� 

 if(i-1>=0) b+=J*lattice[i-1][j];
 if(i+1<N) b+=J*lattice[i+1][j];
 if(j-1>=0) b+=J*lattice[i][j-1];
 if(j+1<N) b+=J*lattice[i][j+1];

 long double e=exp(-1*b*beta); 
 pos=1/(1+e);

 int ratio=rand()%1000;
 long double result=ratio;		// ���������� ������������ 
 result/=1000;

 if(result>pos) return -1;
 else return 1;
}

int Magnetization()
{
	int s=0;
	for(int i=0; i<N; i++)
	{ 
		for(int j=0; j<N; j++)
		{
			s+=lattice[i][j];
		}
	}
	return s;
}

void Fill()
{
	for(int i=0; i<N; i++)
	{
		lattice[i].resize(N);
		extra[i].resize(N);
		for(int j=0; j<N; j++)						// ������� ������� � �������� ��������� �������
		{
			if((rand()%1000)>499) lattice[i][j]=-1;
			else lattice[i][j]=1;
			extra[i][j]=lattice[i][j];	// �������� ������
		}
	}
}

void Back()
{
	// ���������� ������� � ���������� ���������
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)						
		{
			lattice[i][j]=extra[i][j];	
		}
	}	
}

void MFill(int M[])
{
	for(int T=TMin; T<TMax; T++)
	{
		M[T-TMin]=0;
	}
}