#define mass_cxx
#include "mass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF1.h>
#include <stdio.h>
#include <TTree.h>

const double massK = 493.667;
const double massPi = 105.65836;



void mass::Loop()
{

// In a ROOT session, you can do:
//      root> .L mass.C
//      root> mass t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//
	TFile *file = new TFile("known3body.root", "RECREATE");
	TTree *tree = new TTree("histTree", "histogramas das combinacoes possiveis");
	
	TH1F *KKK = new TH1F("KKK","histKKK",  500, 0, 3000);
	TH1F *KKP = new TH1F("KKP","histKKP",  500, 0, 3000);
	TH1F *KPK = new TH1F("KPK","histKPK",  500, 0, 3000);
	TH1F *KPP = new TH1F("KPP","hsitKPP",  500, 0, 3000);
	TH1F *PKK = new TH1F("PKK","histPKK",  500, 0, 3000);
	TH1F *PKP = new TH1F("PKP","histPKP",  500, 0, 3000);
	TH1F *PPK = new TH1F("PPK","histPPK",  500, 0, 3000);
	TH1F *PPP = new TH1F("PPP","histPPP",  500, 0, 3000);
	
	double mmae, p1sq, p2sq, p3sq, ptsq, m1, m2, m3, emae;
	
	//------------------ALTERAR AQUI PARA MUDAR A MASSA
	m1=massPi;
	m2=massK;
	m3=massPi;
	
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
   
   
//--------------------A PARTIR DAQUI COMECAM OS CALCULOS 
//---------------CALCULOS GERAIS
 	mmae =0;
 	p1sq = p1_PX*p1_PX + p1_PY*p1_PY + p1_PZ*p1_PZ;
 	p2sq = p2_PX*p2_PX + p2_PY*p2_PY + p2_PZ*p2_PZ;
 	p3sq = p3_PX*p3_PX + p3_PY*p3_PY + p3_PZ*p3_PZ;
 	ptsq = (p1_PX+p2_PX+p3_PX)*(p1_PX+p2_PX+p3_PX) + (p1_PY+p2_PY+p3_PY)*(p1_PY+p2_PY+p3_PY) + (p1_PZ+p2_PZ+p3_PZ)*(p1_PZ+p2_PZ+p3_PZ);
 	
//---------------CALCULOS ESPECIFICOS
//-------KKK--------

	m1 = massK;	m2 = massK;	m3 = massK;
	emae = sqrt(m1*m1+p1sq)+sqrt(m2*m2+p2sq)+sqrt(m3*m3+p3sq);
	mmae = sqrt(emae*emae-ptsq);
	KKK->Fill(mmae);
	
//-------KKP--------

	m1 = massK;	m2 = massK;	m3 = massPi;
	emae = sqrt(m1*m1+p1sq)+sqrt(m2*m2+p2sq)+sqrt(m3*m3+p3sq);
	mmae = sqrt(emae*emae-ptsq);
	KKP->Fill(mmae);

//-------KPK--------

	m1 = massK;	m2 = massPi;	m3 = massK;
	emae = sqrt(m1*m1+p1sq)+sqrt(m2*m2+p2sq)+sqrt(m3*m3+p3sq);
	mmae = sqrt(emae*emae-ptsq);
	KPK->Fill(mmae);

//-------KPP--------

	m1 = massK;	m2 = massPi;	m3 = massPi;
	emae = sqrt(m1*m1+p1sq)+sqrt(m2*m2+p2sq)+sqrt(m3*m3+p3sq);
	mmae = sqrt(emae*emae-ptsq);
	KPP->Fill(mmae);

//-------PKK---------

	m1 = massPi;	m2 = massK;	m3 = massK;
	emae = sqrt(m1*m1+p1sq)+sqrt(m2*m2+p2sq)+sqrt(m3*m3+p3sq);
	mmae = sqrt(emae*emae-ptsq);
	PKK->Fill(mmae);

//-------PKP---------

	m1 = massPi;	m2 = massK;	m3 = massPi;
	emae = sqrt(m1*m1+p1sq)+sqrt(m2*m2+p2sq)+sqrt(m3*m3+p3sq);
	mmae = sqrt(emae*emae-ptsq);
	PKP->Fill(mmae);

//-------PPK---------

	m1 = massPi;	m2 = massPi;	m3 = massK;
	emae = sqrt(m1*m1+p1sq)+sqrt(m2*m2+p2sq)+sqrt(m3*m3+p3sq);
	mmae = sqrt(emae*emae-ptsq);
	PPK->Fill(mmae);

//-------PPP---------

	m1 = massPi;	m2 = massPi;	m3 = massPi;
	emae = sqrt(m1*m1+p1sq)+sqrt(m2*m2+p2sq)+sqrt(m3*m3+p3sq);
	mmae = sqrt(emae*emae-ptsq);
	PPP->Fill(mmae);
	
//--------FIM DOS CALCULOS

   } //--------------FIM DO FOR DAS ENTRADAS
   
   //---------------SALVANDO NA NOVA TREE
   
   tree->Fill();
   file->Write();
   file->Close();

}
