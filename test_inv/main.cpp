#include <iostream>
#include <iomanip>
#include <string>
#include "armadillo"

using namespace std;
using namespace arma;

void printMat(const Mat<double>& arg);
void runTestOnce(const Mat<double>& arg,string s);

int main(int argc,char *argv[]){
	const int L_A_1=4;
	const int L_A_2=4;
	const int L_B_1=4;
	const int L_B_2=4;
	const int L_X_1=3;
	const int L_X_2=5;
	double _a[L_A_1*L_A_2]={1.,0.,0.,0.,
	                        0.,1.,0.,0.,
	                        0.,0.,1.,0.,
	                        0.,0.,0.,1.};
	double _b[L_B_1*L_B_2]={1.,0.,0.,0.,
	                        0.,2.,0.,0.,
	                        0.,0.,3.,0.,
	                        0.,0.,0.,4.};
	double _x[L_X_1*L_X_2]={1.,1.,0.,1.,0.,
	                        0.,1.,1.,1.,1.,
	                        1.,0.,1.,1.,0.};
	Mat<double> a=Mat<double>(_a,L_A_2,L_A_1).t();
	Mat<double> b=Mat<double>(_b,L_B_2,L_B_1).t();
	Mat<double> x=Mat<double>(_x,L_X_2,L_X_1).t();
	Mat<double> y=x.t();
	
	runTestOnce(a,"A");
	runTestOnce(b,"B");
	runTestOnce(x,"X");
	runTestOnce(y,"Y");
	return 0;
}

void printMat(const Mat<double>& arg){
	if(arg.empty()) return;
	if(arg.n_rows<1 || arg.n_cols<1) return;
	for(unsigned int i=0;i<arg.n_rows;++i){
		cout<<"\t";
		for(unsigned int j=0;j<arg.n_cols;++j)
			cout<<fixed<<setprecision(4)<<arg.at(i,j)<<" ";
		cout<<endl;
	}
}

void runTestOnce(const Mat<double>& arg,string s){
	Mat<double> inv=pinv(arg);
	
	cout<<"Matrix "<<s<<":"<<endl;
	printMat(arg);
	cout<<endl;
	cout<<"Matrix "<<s<<", "<<s<<"^+:"<<endl;
	printMat(inv);
	cout<<endl;
}
