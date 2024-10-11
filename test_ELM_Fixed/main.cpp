#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <limits>
#include <iomanip>
#include "armadillo"
#include "SLFN.h"
#include "SLFNMat.hpp"
#include "SigmoidFunction.h"
#include "SLFNTrainer.hpp"
#include "SLFNELM.hpp"

using namespace std;
using namespace arma;
using namespace model;

void out_exception(int arg);
void printMat(const Mat<double>& arg);

int main(int argc,char *argv[]){
	if(argc<4) return -1;
	if(argc>4) return -2;
	
	int ch=std::atoi(argv[3]);
	ifstream fin(argv[1]);
	vector<string> lines;
	
	if(!fin.is_open()) return -4; //failure opening file
	while(1){
		string line;
		
		if(!getline(fin,line)) break;
		lines.push_back(line);
	}
	fin.close();
	
	int size=lines.size();
	double* dxa=new double[size]; //ATTENTION: new
	double* dya=new double[size]; //ATTENTION: new
	
	for(int i=0;i<size;++i){
		const char* line=lines.at(i).c_str();
		
		sscanf(line,"%lf,%lf",&dxa[i],&dya[i]);
	}
	
	SLFN* net=new SLFNMat();
	Mat<double> b(ch,1);
	Mat<double> wIn(ch,1);
	
	net->setG(SigmoidFunction::getInstance());
	for(int i=0;i<ch;++i){
		b.at(i)=i/(double)ch;
		wIn.at(i)=b.at(i);
	}
	net->setWIn(wIn);
	net->setB(b);
	
	Mat<double> tIn(size,1);
	Mat<double> tOut(size,1);
	
	for(int i=0;i<size;++i){
		tIn.at(i)=dxa[i];
		tOut.at(i)=dya[i];
	}
	
	SLFNTrainer* trainer=SLFNELM::getInstance();

	try{
		trainer->run(net,tIn,tOut);
	} catch(int e){
		out_exception(e);
		return e;
	}

	//clean up
	delete[] dxa;
	delete[] dya;
	
	cout<<"Input weights:"<<endl;
	printMat(net->getWIn());
	cout<<endl;
	cout<<"Hidden layers biases:"<<endl;
	printMat(net->getB());
	cout<<endl;
	cout<<"Output weights:"<<endl;
	printMat(net->getWOut());
	cout<<endl;
	
	ofstream fout(argv[2]);
	
	if(!fout.is_open()) return -4; //failure opening file
	fout.precision(numeric_limits<double>::digits10);
	for(int txint=-20;txint<20;txint+=1){
		double tx=txint/2.;
		Col<double> txa(&tx,1);
		Col<double> tya=net->f(txa);
		
		fout<<tx<<","<<tya.at(0)<<endl;
	}
	
	fout.close();
	delete net;
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
	cout<<" ("<<arg<<")"<<endl;
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
