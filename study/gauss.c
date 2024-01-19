#include<stdio.h>
#include<TH1F.h>
#include<TCanvas.h>
#include<TRandom3.h>
#include<math.h>

double f(double a){
	double mean= 1869;
	double stdDev = 10;
	return (1.0/stdDev*sqrt(M_PI*2))*exp(-0.5*(a-mean)*(a-mean)/(stdDev*stdDev));
}

double g(double a){
	double slope = -0.003;
	return (exp(slope*a));
}

void gauss(){

	TH1F *hist =new TH1F("hist", "Guassian", 100, 1820, 1920);
	TRandom3 randomGenerator(0);
	double a, b;
	int i=0;
	int entries = 10000;
	
	while(i<entries){

		a  = 1820+100*randomGenerator.Rndm();
		b  = randomGenerator.Rndm();

		if((f(a)/f(1869))>b){
			hist->Fill(a);
			i++;
		}
	}
	i=0;
	
	entries=10000;
	//CHECAR ESSE CODIGO COM A CARLA
	
	while(i<entries){
	
		a = randomGenerator.Rndm();
		b = randomGenerator.Rndm();
		
		if((g(a)/g(0))>b){
			hist->Fill(1820+100*a);
			i++;	
		}
	}


	TF1 *fit = new TF1("fit", "gaus", 1820, 1920);
	fit->SetParameter(0,100);
	fit->SetParameter(1,1869);
	fit->SetParameter(2,10);
    	TCanvas *canvas = new TCanvas("", "Ex", 800, 600);
    	hist->Draw();
	hist->Fit("fit", "fit");
    	canvas->Draw();
}

