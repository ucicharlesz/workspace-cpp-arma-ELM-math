/**
 * SLFNMat.cpp
 *
 * Created on: 4/18/2013
 *     Author: ZHU Qiuxi
 */

#include <iostream>
#include <iomanip>
#include <limits>
#include "armadillo"
#include "SLFNMat.hpp"
#include "ActivationFunction.h"

using namespace std;
using namespace arma;
using namespace model;

SLFNMat::SLFNMat()
	:wIn(),b(),wOut(),g(NULL){
	;
}

SLFNMat::~SLFNMat(){;}

/*These member functions will throw -1 for NullPointerException (in Java),
                                and -2 for IllegaL_ARGumentException*/
//                  they will throw -3 for unexpected internal mismatches

Mat<double>& SLFNMat::getWIn(){
	if(wIn.empty()) throw -1;
	return wIn;
}

Col<double>& SLFNMat::getB(){
	if(b.empty()) throw -1;
	return b;
}

Mat<double>& SLFNMat::getWOut(){
	if(wOut.empty()) throw -1;
	return wOut;
}

ActivationFunction* SLFNMat::getG(){
	if(g==NULL) throw -1;
	return g;
}

int SLFNMat::getN(){
	return getWIn().n_cols;
}

int SLFNMat::getNH(){
	return getB().n_rows;
}

int SLFNMat::getM(){
	return getWOut().n_cols;
}

void SLFNMat::setWIn(const Mat<double>& arg){
	if(arg.empty()) throw -1;
	if(arg.n_rows<1 || arg.n_cols<1)
		throw -2;
	if(!b.empty()) if(arg.n_rows!=b.n_rows) throw -2;
	if(!wOut.empty()) if(arg.n_rows!=wOut.n_rows) throw -2;
	wIn=arg;
}

void SLFNMat::setB(const Col<double>& arg){
	if(arg.empty()) throw -1;
	if(arg.n_rows<1 || arg.n_cols!=1)
		throw -2;
	if(!wIn.empty()) if(arg.n_rows!=wIn.n_rows) throw -2;
	if(!wOut.empty()) if(arg.n_rows!=wOut.n_rows) throw -2;
	b=arg;
}

void SLFNMat::setWOut(const Mat<double>& arg){
	if(arg.empty()) throw -1;
	if(arg.n_rows<1 || arg.n_cols<1)
		throw -2;
	if(!wIn.empty()) if(arg.n_rows!=wIn.n_rows) throw -2;
	if(!b.empty()) if(arg.n_rows!=b.n_rows) throw -2;
	wOut=arg;
}

void SLFNMat::setG(ActivationFunction* arg){
	if(arg==NULL) throw -1;
	g=arg;
}

Col<double> SLFNMat::f(const Col<double>& in){
	if(wIn.empty() || b.empty() || wOut.empty() || g==NULL) throw -1;
	if(in.empty()) throw -1;
	if(in.n_rows<1 || in.n_cols!=1)
		throw -2;
	
	Col<double> r=zeros<Col<double> >(getM(),1);
	
	for(int i=0;i<getNH();++i)
		r+=wOut.row(i).t()*g->f(dot(in,wIn.row(i).t())+b.at(i));
	return r;
}
