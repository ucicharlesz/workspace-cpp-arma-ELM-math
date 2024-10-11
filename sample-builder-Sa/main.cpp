/**
 * sample-builder-Sa
 * main.cpp
 *
 * Created on: 3/29/2013
 *     Author: ZHU Qiuxi
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <limits>
#include <math.h>

using namespace std;

static const int CAPACITY=5000;
static const double X_SYM_RANGE=10.;
static const double D_SYM_RANGE=0.2;

static double f_Sa(double x);
static double rand_double(double value1,double value2);

int main(int argc,char *argv[]){
	if(argc<2) return -1;
	if(argc>2) return -2;
	
	ofstream fout(argv[1]);
	
	if(!fout.is_open()) return -4; //failure opening file
	fout.precision(numeric_limits<double>::digits10);
	srand((int)time(NULL));
	for(int i=0;i<=CAPACITY;++i){
		double ox=rand_double(-X_SYM_RANGE,X_SYM_RANGE);
		double od=rand_double(-D_SYM_RANGE,D_SYM_RANGE);
	//	double od=0.;
		double ty=f_Sa(ox);
		
		fout<<ox<<","<<(ty+od)<<endl;
	}
	fout.close();
	return 0;
}

static double f_Sa(double x){
	if(x==0.) return 1;
	else return sin(x)/x;
}

static double rand_double(double value1,double value2){
	return value1+(value2-value1)*rand()/(RAND_MAX+1.);
}
