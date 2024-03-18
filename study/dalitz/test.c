#include<stdio.h>
#include<TH1F.h>
#include<TCanvas.h>
#include<TRandom3.h>
#include<math.h>
#include<stdbool.h>
#include<TComplex.h>


void test(){

	TComplex *b = new TComplex(1,0,false);
	TComplex *a = new TComplex(1,M_PI/2.,true);
	cout << (*b+*a).Rho2();

}
