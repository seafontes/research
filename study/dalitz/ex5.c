#include<stdio.h>
#include<TH1F.h>
#include<TCanvas.h>
#include<TRandom3.h>
#include<math.h>

const double massK = 493.667;
const double massPi = 105.65836;
const double massD = 1869.62;

double lambdasqrt(double x, double y, double z){ //-----RAIZ DA FUNCAO LAMBDA
	double value;
	value = (x-y-z)*(x-y-z)-4*y*z;
	return sqrt(value);
}
double s13_bound(double m1, double m2, double m3, double m0, double s12, double uplow){//-------------FUNCAO LIMITE, UPLOW DEFINE QUAL
	
	double s = m0*m0;
	double lbds = -1.0*(uplow)*lambdasqrt(s12, m2*m2, m1*m1)*lambdasqrt(s,s12,m3*m3);
	double brkt = (s12-s+m3*m3)*(s12+m1*m1-m2*m2)+lbds;
	return m1*m1 + m3*m3 -(1./2*s12)*brkt;

}



void ex5(){
	TRandom3 randomGenerator(0);
	
	double s12_min, s12_max, s13_min, s13_max;
	double m1, m2, m3, m0;
	int i;
	double randoms12, randoms13;
	
	
	
	//----ATRIBUIÇÃO DAS MASSAS 
	m0=massD;	m1=massK;	m2=massK;	m3=massPi;
	
	//----DEFINICAO DOS LIMITES BRUTOS
	s12_min=(m1+m2)*(m1+m2);
	s12_max=(m0-m3)*(m0-m3);
	s13_min=(m1+m3)*(m1+m3);
	s13_max=(m0-m2)*(m0-m2);
	
	TH2F *hist = new TH2F("hist", "hist", 1000, s12_min, s12_max, 1000, s13_min, s13_max);
	
	
	i=0;
	while(i<10000){
		
		cout << i <<endl;
		
		randoms12 = s12_min+(s12_max-s12_min)*randomGenerator.Rndm();
		randoms13 = s13_min+(s13_max-s13_min)*randomGenerator.Rndm();
		
		if((randoms13>=s13_bound(m1,m2,m3,m0,randoms12,-1.))&&(randoms13<=s13_bound(m1,m2,m3,m0,randoms12,1.0))){
			
			hist->Fill(randoms12,randoms13);
			i++;
			
		}	
	
	}	
	
	TCanvas *c1 = new TCanvas();
	hist->Draw();
}
