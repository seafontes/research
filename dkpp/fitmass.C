#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooGaussian.h>
#include <RooPlot.h>
#include <TCanvas.h>
#include <RooFit.h>

void fitmass(){

	TFile *kpipi = new TFile("DKPP_1M_2016.root");
        TTree *tree = (TTree*)kpipi->Get("DecayTree");
	RooRealVar D_M("D_M", "D_M",1800,1950);
	RooDataSet data("data", "dataset from tree", RooArgSet(D_M), RooFit::Import(*tree));
	
	RooRealVar mean("mean", "Mean of Gaussian", 1870, 1850, 1900);
    	RooRealVar sigma("sigma", "Width of Gaussian", 3, 1, 15);
    	RooGaussian gauss("gauss", "Gaussian Model", D_M, mean, sigma);


	RooRealVar bgpar("bgpar", "exp parameter", 0.0, -0.01, 0.01);
   	RooExponential background("background", "BG PDF", D_M, bgpar);

	RooRealVar nsig("nsig", "#signal events", 800000, 0., 1000000);
  	RooRealVar nbkg("nbkg", "#background events", 200000, 0., 1000000);

  	RooAddPdf model("model", "g+a", {gauss, background}, {nsig, nbkg});
  	
  	model.fitTo(data);
  	RooPlot *mesframe = D_M.frame();
  	
  	data.plotOn(mesframe);
   	model.plotOn(mesframe);
   	model.plotOn(mesframe, RooFit::Components(background), RooFit::LineStyle(ELineStyle::kDashed));

   	mesframe->Draw();
}
