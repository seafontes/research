#include<stdio.h>
#include<TH1F.h>
#include<TCanvas.h>
#include<TRandom3.h>
#include<math.h>
#include "fitDmass.C"

double f(double a){
	double mean= 1869;
	double stdDev = 10;
	return (1.0/stdDev*sqrt(M_PI*2))*exp(-0.5*(a-mean)*(a-mean)/(stdDev*stdDev));
}

double g(double a){
	double slope = -0.003;
	double norm = slope/(exp(slope*100)-1);
	return norm*exp(slope*(a-1820));
}

void gauss(){

	TH1F *hist =new TH1F("hist", "Guassian", 100, 1820, 1920);
	TRandom3 randomGenerator(0);
	double a, b;
	int i=0;
	int entriesSignal = 10000;
	
	while(i<entriesSignal){

		a  = 1820+100*randomGenerator.Rndm();
		b  = randomGenerator.Rndm();

		if((f(a)/f(1869))>b){
			hist->Fill(a);
			i++;
		}
	}
	i=0;
	//CHECAR ESSE CODIGO COM A CARLA
	
	int entriesBack = 10000;
	while(i<entriesBack){
	
		a = 1820+100*randomGenerator.Rndm();
		b = randomGenerator.Rndm();
		
		if((g(a)/g(1820))>b){
			hist->Fill(a);
			i++;	
		}
	}


	TF1 *fit = new TF1("fit", fitDmass, 1820, 1920, 5);
	fit->SetParNames("NSignal", "Mean Mass", "Width","bg slope","NBack");
	fit->SetParameters(entriesSignal, 1869, 10, -0.003, entriesBack);
    	TCanvas *canvas = new TCanvas("", "Ex", 800, 600);
    	hist->Draw();
	hist->Fit("fit", "fit");
    	canvas->Draw();
}

