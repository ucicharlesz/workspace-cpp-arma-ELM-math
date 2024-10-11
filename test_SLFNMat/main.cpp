#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "armadillo"
#include "ActivationFunction.h"
#include "HyperbolicTangentFunction.h"
#include "SLFN.h"
#include "SLFNMat.hpp"

using namespace std;
using namespace arma;
using namespace model;

void out_exception(int arg);
void printMat(const Mat<double>& arg);

int main(int argc,char* argv[]){
	SLFN* net=new SLFNMat();
	const int N=1;
	const int NH=3;
	const int M=1;
	double _wIn[NH*N]={-0.5,0.8,0.2};
	double _b[NH]={0.4,-0.7,0.3};
	double _wOut[NH*M]={0.6,-0.7,0.2};
	ActivationFunction* g=HyperbolicTangentFunction::getInstance();
	Mat<double> wIn=Mat<double>(_wIn,N,NH).t();
	Col<double> b(_b,NH);
	Mat<double> wOut=Mat<double>(_wOut,M,NH).t();

	try{
		net->setWIn(wIn);
		net->setB(b);
		net->setWOut(wOut);
		net->setG(g);
	} catch(int e){
		out_exception(e);
		return e;
	}

	const int L_IN=1;
	double _in[L_IN]={0.25};
	Col<double> in(_in,L_IN);
	Col<double> out=net->f(in);
	
	delete net;
	cout<<"SLFN output:"<<endl;
	printMat(out);
	return 0;
}

void out_exception(int arg){
	cout<<"Exception caught: ";
	switch(arg){
	case -1: cout<<"null pointer"; break;
	case -2: cout<<"illegal argument"; break;
	case -3: cout<<"unexpected internal mismatch"; break;
	default: cout<<"unknown";
	}
	cout<<endl;
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
