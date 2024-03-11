#include<stdio.h>
#include<TH1F.h>
#include<TCanvas.h>
#include<TRandom3.h>
#include<math.h>
#include <stdbool.h>

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

double breitwigner(double x, double x0, double Gamma){
	double aux1 = (1./M_PI)*(Gamma/2.);
	double aux2 = Gamma*Gamma/4.;
	double bw = aux1*(1./(aux2+(x-x0)*(x-x0)));
	return bw;
}

void ex7(){

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
		bool mcs12, mcs13;
		mcs12 = false;		
		mcs13 = false;

		if((s13>boundlow)&&(s13<boundup)){
			
			// --- PARAMETROS PARA BREITWIGNER DE K*(892) DE S13
			double x0 = 891760;
			double Gamma = 50300;
			//-------------------------------------------
			double test = randomGenerator.Rndm();
			double point = breitwigner(s13,x0,Gamma)/breitwigner(x0,x0,Gamma);

			if(point>test)
				mcs13 = true;
				
			// --- PARAMETROS PARA BREITWIGNER PHI DE S12
			x0 = 1019461;
			Gamma = 4249;
			//-------------------------------------------
			test = randomGenerator.Rndm();
			point = breitwigner(s12,x0,Gamma)/breitwigner(x0,x0,Gamma);

			if(point>test)
				mcs12 = true;
				
			
			
			if(mcs12 && mcs13){
				hist->Fill(s12,s13);
				i++;
				cout<< "PONTO ADICIONADO: "<< i <<endl;
			
			}
		}
	}	
	
	TCanvas *c1 = new TCanvas();
	hist->Draw();
}
