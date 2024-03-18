#include<stdio.h>
#include<TH1F.h>
#include<TCanvas.h>
#include<TRandom3.h>
#include<math.h>
#include<stdbool.h>
#include<TComplex.h>

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
Double_t denominador(double m0, double s, double Gamma){
	Double_t aux = (m0*m0-s)*(m0*m0-s)+(m0*Gamma)*(m0*Gamma);
	return aux;

}

double coss(double m1, double m2, double m3, double m0, double s12, double s13){

	double s = m0*m0;
	double lbds = lambdasqrt(s12, m2*m2, m1*m1)*lambdasqrt(s,s12,m3*m3);
	double aux1 = (s12-s+m3*m3)*(s12+m1*m1-m2*m2);
	double aux2 = (s13-m1*m1-m3*m3)*2*s12;
	return (aux1+aux2)/(lbds);

}
void ex9(){

	TRandom3 randomGenerator(0);
	
	double s12_min, s12_max, s13_min, s13_max;
	double m1, m2, m3, m0;
	int i=0;
	double s12, s13;
	Double_t maxPDF;
	Double_t test;
	
	
	//----ATRIBUIÇÃO DAS MASSAS 
	m0=massD;	m1=massK;	m2=massK;	m3=massPi;
	
	//----DEFINICAO DOS LIMITES BRUTOS
	s12_min=(m1+m2)*(m1+m2);	s12_max=(m0-m3)*(m0-m3);
	
	s13_min=(m1+m3)*(m1+m3);	s13_max=(m0-m2)*(m0-m2);
	
	
	TH2F *hist = new TH2F("hist", "hist", 250, s12_min, s12_max, 250, s13_min, s13_max);
	
	TComplex *bwpdf = new TComplex(0,0);
	
	Double_t rePhi, imPhi, reK, imK;
	
	// --- PARAMETROS PARA BREITWIGNER DE K*(892) DE S13
	double m0K = 891.670;
	double GammaK = 51.400;
	//-------------------------------------------
				
	// --- PARAMETROS PARA BREITWIGNER PHI DE S12
	double m0Phi = 1019.461;
	double GammaPhi = 4.249;
	//-------------------------------------------
	double a_Phi =1;
	double delta_phi = M_PI*0.5;
	TComplex *phase = new TComplex(1,delta_phi,true);
	
	
	while(i<100000){
		
		s12 = s12_min+(s12_max-s12_min)*randomGenerator.Rndm();
		s13 = s13_min+(s13_max-s13_min)*randomGenerator.Rndm();
		
		double boundup 	= s13_bound(m1,m2,m3,m0,s12,1.0);
		double boundlow = s13_bound(m1,m2,m3,m0,s12,-1.0);
		
		double angulardist = coss(m1,m2,m3,m0,s12,s13);
		
		
		if((s13>boundlow)&&(s13<boundup)){
		
			rePhi	= (m0Phi*m0Phi-s12)/denominador(m0Phi, s12, GammaPhi);
			imPhi	= (m0*GammaPhi)/denominador(m0Phi, s12, GammaPhi);
			
			reK	= (m0K*m0K-s13)/denominador(m0K, s13, GammaK);
			imK	= (m0K*GammaK)/denominador(m0K, s13, GammaK);
			
			TComplex *A_Phi = new TComplex(rePhi,imPhi);
			TComplex *A_K = new TComplex(reK,imK);
			*A_Phi = a_Phi*(*phase)*(*A_Phi);
			
			
			if(i==0){	maxPDF=(*A_Phi+*A_K).Rho();}
			else if((*A_Phi+*A_K).Rho()>maxPDF){	maxPDF = (*A_Phi+*A_K).Rho();}
			i++;
		}
	}
	
	cout<<" o maximo achado foi de: "<< maxPDF << endl<<"iniciando monte carlo"<<endl;
	i=0;
	while(i<500000){
		
		s12 = s12_min+(s12_max-s12_min)*randomGenerator.Rndm();
		s13 = s13_min+(s13_max-s13_min)*randomGenerator.Rndm();
		
		double boundup 	= s13_bound(m1,m2,m3,m0,s12,1.0);
		double boundlow = s13_bound(m1,m2,m3,m0,s12,-1.0);
		
		double angulardist = coss(m1,m2,m3,m0,s12,s13);
				
		if((s13>boundlow)&&(s13<boundup)){
		
			double angulardist = coss(m1,m2,m3,m0,s12,s13);
		
			rePhi	= (m0Phi*m0Phi-s12)/denominador(m0Phi, s12, GammaPhi);
			imPhi	= (m0*GammaPhi)/denominador(m0Phi, s12, GammaPhi);
			
			reK	= (m0K*m0K-s13)/denominador(m0K, s13, GammaK);
			imK	= (m0K*GammaK)/denominador(m0K, s13, GammaK);
			
			TComplex *A_Phi = new TComplex(rePhi,imPhi);
			TComplex *A_K = new TComplex(reK,imK);
			*A_Phi = a_Phi*(*phase)*(*A_Phi);
			
			test = randomGenerator.Rndm();
			if(test < ((*A_Phi+*A_K).Rho()/maxPDF)){
			
				hist->Fill(s12,s13);
				i++;
			}
		}
	}
		
	
	TCanvas *c1 = new TCanvas();
	hist->Draw();
	
}
