#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooGaussian.h>
#include <RooPlot.h>
#include <TCanvas.h>
#include <RooFit.h>

void fit2G(){

	TFile *kpipi = new TFile("DKPP_1M_2016.root");
        TTree *tree = (TTree*)kpipi->Get("DecayTree");
	RooRealVar D_M("D_M", "D_M",1800,1950);
	RooDataSet data("data", "dataset from tree", RooArgSet(D_M), RooFit::Import(*tree));
	
	RooRealVar mean("mean", "Mean of Gaussian", 1870., 1850., 1900.);
    	RooRealVar sigma1("sigma", "Width of Gaussian", 3., 1., 15.);
    	RooRealVar sigma2("sigma2", "Widith of Sigma 2", 7., 1., 15.);
    	RooGaussian gauss1("gauss1", "Gaussian Model 1", D_M, mean, sigma1);
	RooGaussian gauss2("gauss2", "Gaussian Model 2", D_M, mean, sigma2);

	RooRealVar bgpar("bgpar", "exp parameter", 0.0, -0.01, 0.01);
   	RooExponential background("background", "BG PDF", D_M, bgpar);

	RooRealVar nsig("nsig", "#signal events", 800000, 0., 1000000);
  	RooRealVar nbkg("nbkg", "#background events", 200000, 0., 1000000);
  	
  	//soma dos sinais
  	RooRealVar sig1frac("sig1frac","fraction",0.5,0.,1.);
	RooAddPdf sig("sig", "Signal", RooArgList(gauss1, gauss2), sig1frac);


  	RooAddPdf model("model", "s1+S2+bg", RooArgList(sig, background),{nsig, nbkg});
  	
  	model.fitTo(data);
  	RooPlot *mesframe = D_M.frame();
  	
  	data.plotOn(mesframe);
   	model.plotOn(mesframe);
   	model.plotOn(mesframe, RooFit::Components(background), RooFit::LineStyle(ELineStyle::kDashed));

   	mesframe->Draw();
}
