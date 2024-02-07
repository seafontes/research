//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Dec 27 16:08:34 2023 by ROOT version 6.30/02
// from TTree DecayTree/signal
// found on file: Unknown3body.root
//////////////////////////////////////////////////////////

#ifndef mass_h
#define mass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class mass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        p3_PX;
   Double_t        p3_PY;
   Double_t        p3_PZ;
   Double_t        p2_PX;
   Double_t        p2_PY;
   Double_t        p2_PZ;
   Double_t        p1_PX;
   Double_t        p1_PY;
   Double_t        p1_PZ;

   // List of branches
   TBranch        *b_p3_PX;   //!
   TBranch        *b_p3_PY;   //!
   TBranch        *b_p3_PZ;   //!
   TBranch        *b_p2_PX;   //!
   TBranch        *b_p2_PY;   //!
   TBranch        *b_p2_PZ;   //!
   TBranch        *b_p1_PX;   //!
   TBranch        *b_p1_PY;   //!
   TBranch        *b_p1_PZ;   //!

   mass(TTree *tree=0);
   virtual ~mass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef mass_cxx
mass::mass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Unknown3body.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Unknown3body.root");
      }
      f->GetObject("DecayTree",tree);

   }
   Init(tree);
}

mass::~mass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t mass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t mass::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void mass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("p3_PX", &p3_PX, &b_p3_PX);
   fChain->SetBranchAddress("p3_PY", &p3_PY, &b_p3_PY);
   fChain->SetBranchAddress("p3_PZ", &p3_PZ, &b_p3_PZ);
   fChain->SetBranchAddress("p2_PX", &p2_PX, &b_p2_PX);
   fChain->SetBranchAddress("p2_PY", &p2_PY, &b_p2_PY);
   fChain->SetBranchAddress("p2_PZ", &p2_PZ, &b_p2_PZ);
   fChain->SetBranchAddress("p1_PX", &p1_PX, &b_p1_PX);
   fChain->SetBranchAddress("p1_PY", &p1_PY, &b_p1_PY);
   fChain->SetBranchAddress("p1_PZ", &p1_PZ, &b_p1_PZ);
   Notify();
}

Bool_t mass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void mass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t mass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef mass_cxx
