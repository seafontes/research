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
	return m1*m1 + m3*m3 -(1./(2.*s12))*brkt;

}

double g(double a, double b){
	double mean1= 1200000;
	double mean2= 1400000;
	double stdDev = 200000;
	return exp(-0.5*((a-mean1)*(a-mean1)+(b-mean2)*(b-mean2))/(stdDev*stdDev));
}

void ex6(){

	TRandom3 randomGenerator(0);
	
	double s12_min, s12_max, s13_min, s13_max;
	double m1, m2, m3, m0;
	int i=0;
	double s12, s13;
	
	
	
	//----ATRIBUIÇÃO DAS MASSAS 
	m0=massD;	m1=massK;	m2=massK;	m3=massPi;
	
	//----DEFINICAO DOS LIMITES BRUTOS
	s12_min=(m1+m2)*(m1+m2);	s12_max=(m0-m3)*(m0-m3);
	
	s13_min=(m1+m3)*(m1+m3);	s13_max=(m0-m2)*(m0-m2);
	
	
	TH2F *hist = new TH2F("hist", "hist", 1000, s12_min, s12_max, 1000, s13_min, s13_max);

	
	while(i<100000){
		
		s12 = s12_min+(s12_max-s12_min)*randomGenerator.Rndm();
		s13 = s13_min+(s13_max-s13_min)*randomGenerator.Rndm();
		
		double boundup 	= s13_bound(m1,m2,m3,m0,s12,1.0);
		double boundlow = s13_bound(m1,m2,m3,m0,s12,-1.0);
		
		if((s13>boundlow)&&(s13<boundup)){
			
			double test = randomGenerator.Rndm();
			
			double point = g(s12, s13);
			
			if(point>test){
				hist->Fill(s12,s13);
				i++;
				cout<< "PONTO ADICIONADO"<<endl;
			}
		}
	}	
	
	TCanvas *c1 = new TCanvas();
	hist->Draw();
}
