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

	TCanvas *c1 = new TCanvas();
	hist->Draw();
}

