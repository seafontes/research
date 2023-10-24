void tut9(){
	TH1F *hist = new TH1F("hist", "TITULO PODE SER NADA", 100, 0, 10);

	TRandom2 *rand = new TRandom2(3);

	fstream file;
	file.open("data6.txt", ios::out);
	
	for(int i=0; i<1000;i++){
		double r = rand->Gaus(5,1);
		file << r << endl;
	}

	file.close();
	
	file.open("data6.txt", ios::in);
	
	double value;

	while(1){
	file  >> value;
	hist->Fill(value);
	if(file.eof()) break;
	}
	
	file.close();
	
	hist->SetFillColor(kGreen-9);

	TF1 *fit = new TF1("fit", "gaus",0, 10);
	
	fit->SetParameter(0, 50);
	fit->SetParameter(1, 5);
	fit->SetParameter(2, 1);

	hist->GetXaxis()->SetTitle("qqr coisa");
	hist->GetYaxis()->SetTitle("student");

	TCanvas *c1 = new TCanvas();
	hist->SetStats(0);
	c1->SetTickx();
	c1->SetTicky();
	hist->Draw();
	hist->Fit("fit", "RQ");
	
	TLegend *leg = new TLegend(0.7,0.7, 0.8,0.9); 
	
	leg->SetBorderSize(0);
	leg->AddEntry(hist, "NOME", "l");
	leg->AddEntry(fit, "fit", "p");
	leg->Draw();
	
	
	
	double mean = fit->GetParameter(1);
	double sigma = fit->GetParameter(2);
	
	cout << mean/sigma << endl;
	
}
