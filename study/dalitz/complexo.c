#include<stdio.h>
#include<TH1F.h>
#include<TCanvas.h>
#include<TRandom3.h>
#include<math.h>
#include<stdbool.h>
#include<TComplex.h>


void complexo(){
	TComplex *A = new TComplex(-1,1);
	TComplex *B = new TComplex(-1,1);
	TComplex *C = new TComplex(-1,1);
	*A = TComplex(0,0);
	*C = *A-*B;
	Double_t mod = 	C->Rho();
	cout<<mod;
}
