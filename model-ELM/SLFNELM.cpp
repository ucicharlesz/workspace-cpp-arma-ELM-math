/**
 * SLFNELM.cpp
 *
 * Created on: 3/29/2013
 *     Author: ZHU Qiuxi
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "armadillo"
#include "SLFNELM.hpp"
#include "ActivationFunction.h"

using namespace arma;
using namespace model;

SLFNELM::SLFNELM(){;}
SLFNELM::~SLFNELM(){;}

SLFNELM* SLFNELM::getInstance(){
	static SLFNELM* instance=new SLFNELM();
	
	return instance;
}

void SLFNELM::run(SLFN* net,const Mat<double>& tIn,const Mat<double>& tOut){
	if(net==NULL) throw -1;
	if(tIn.empty() || tOut.empty()) throw -1;
	if(tIn.n_rows<1 || tIn.n_cols<1)
		throw -2;
	if(tOut.n_rows<1 || tOut.n_cols<1)
			throw -2;
	if(tIn.n_rows!=tOut.n_rows) throw -2;
	
	int netN=net->getN();
//	int netNH=net->getNH(); //unused
//	int netM=net->getM(); //M is unknown

	try{
		net->getWOut();
		throw -2; //wOut is already set
	} catch(int e){
		if(e!=-1) throw -2;//wOut is absent, which is expected
	}
	if(tIn.n_cols!=(unsigned int)netN) throw -2;

	Mat<double> tH=getH(net,tIn);
	Mat<double> tInvH=pinv(tH);
	Mat<double> netWOut=tInvH*tOut;
	
	net->setWOut(netWOut);
}

static double rand_double(double value1,double value2);
static double rand_double();

void SLFNELM::init(SLFN* net,int netN,int netNH){
	if(net==NULL) throw -1;
	try{
		net->getWIn();
		throw -2;
	} catch(int e){
		if(e!=-1) throw -2;//defined as NullPointerException in Java
	}
	try{
		net->getB();
		throw -2;
	} catch(int e){
		if(e!=-1) throw -2;//defined as NullPointerException in Java
	}
	if(netN<1) throw -2;
	if(netNH<1) throw -2;

	Mat<double> netWIn(netNH,netN);
	Col<double> netB(netNH,1);

	srand((int)time(NULL));
	for(int i=0;i<netNH*netN;++i)
		netWIn.at(i)=rand_double();
	for(int i=0;i<netNH;++i)
		netB.at(i)=rand_double();
	net->setWIn(netWIn);
	net->setB(netB);
}

Mat<double> SLFNELM::getH(SLFN* net,const Mat<double>& tIn){
	Mat<double> netWIn=net->getWIn();
	Col<double> netB=net->getB();
	int netN=net->getN();
	int netNH=net->getNH();
	
	if(netN<1 || netNH<1) throw -2;
	
	ActivationFunction* netG=net->getG();
	int tN=tIn.n_rows;
	Mat<double> tH(tN,netNH);
	
	for(int i=0;i<tN;++i)
		for(int j=0;j<netNH;++j)
			tH.at(i,j)=netG->f(dot(netWIn.row(j),tIn.row(i))+netB.at(j));
	return tH;
}

static double rand_double(double value1,double value2){
	return value1+(value2-value1)*rand()/(RAND_MAX+1.);
}
static double rand_double(){
	return rand_double(0,1);
}
