#include<stdio.h>
#include<TH1F.h>
#include<TCanvas.h>
#include<TRandom3.h>
#include<math.h>

const double massK = 493.667;
const double massPi = 105.65836;
const double massD = 1869.62;

double lambdasqrt(double x, double y, double z){
	double value;
	value = (x-y-z)*(x-y-z)-4*y*z;
	return sqrt(value);
}
double s13_boundlow(double m1, double m2, double m3, double m0, double )
double s13_boundup(double )
void ex5(){
	TRandom3 randomGenerator(0);
	
	double s12_min, s12_max, s13_min, s13_max;
	double m1, m2, m3, s;
	
	
	//----ATRIBUIÇÃO DAS MASSAS 
	m0=massD;	m1=massK;	m2=massK;	m3=massPi;
	
	s12_min=(m1+m2)*(m1+m2);
	s12_max=(m0-m3)*(m0-m3);
	s13_min=(m1+m3)*(m1+m3);
	s13_max=(m0-m2)*(m0-m2);
	
	
	
	
		s12_min+(s12_max-s12_min)*randomGenerator.Rndm();
		s13_min+(s13_max-s13_min)*randomGenerator.Rndm();
	
	
}
