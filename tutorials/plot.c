void plot(){
	TFile *file = new TFile("output.root", "READ");
	
	TH1F *hist = (TH1F*)file->Get("hist");
	hist->Draw();
	// file->close();
	
}
