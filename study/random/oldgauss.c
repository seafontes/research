#include <TH1F.h>
#include <TCanvas.h>
#include <TRandom3.h>

void gauss() {

	TRandom3 randomGenerator(0);

    	TH1F *hist = new TH1F("hsit", "Gaussian", 100, 1820, 1920);

    	double mean = 1869;
    	double stdDev = 10;
	double slope = 1/0.003;

    	for (int i = 0; i < 10000; ++i) {
        	double value1 = randomGenerator.Gaus(mean, stdDev);
        	double value2 = 1820 + randomGenerator.Exp(slope);
		if(i<10){
			cout<<value2<<endl;}

		hist->Fill(value2);
		hist->Fill(value1);
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

