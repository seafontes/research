#define mass_cxx
#include "mass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF1.h>
#include <stdio.h>

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

	TCanvas *cv1 = new TCanvas();
	TH1F *massmae = new TH1F("TESTE", "teste", 300, 0, 4000);
	double mmae, e2, dotprod, m1, m2, m3;
	
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
 	mmae =0;
 	dotprod=2*(0                                                                                   +sqrt((m1*m1+p1_PX*p1_PX+p1_PY*p1_PY+p1_PZ*p1_PZ)*(m2*m2+p2_PX*p2_PX+p2_PY*p2_PY+p2_PZ*p2_PZ)) +sqrt((m3*m3+p3_PX*p3_PX+p1_PY*p3_PY+p3_PZ*p3_PZ)*(m2*m2+p2_PX*p2_PX+p2_PY*p2_PY+p2_PZ*p2_PZ))+sqrt((m1*m1+p1_PX*p1_PX+p1_PY*p1_PY+p1_PZ*p1_PZ)*(m3*m3+p3_PX*p3_PX+p3_PY*p3_PY+p3_PZ*p3_PZ))                                                                                                            -((p1_PX*p2_PX+p1_PY*p2_PY+p1_PZ*p2_PZ)+(p1_PX*p3_PX+p1_PY*p3_PY+p1_PZ*p3_PZ)+(p3_PX*p2_PX+p3_PY*p2_PY+p3_PZ*p2_PZ))); // 4-MOMENTO CRUZADO
 	mmae = sqrt(m1*m1+m2*m2+m3*m3+dotprod);
 	
 	
 	massmae->Fill(mmae);
   
   
   }
   
   TF1 *fit = new TF1("fit", "gaus", 0, 4000);
   fit->SetParameter(1, 1869);
   massmae->Draw();
   massmae->Fit("fit", "fit");
   cv1->Draw();
}


//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname

// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
