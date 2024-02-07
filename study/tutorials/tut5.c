void tut5(){
	TRandom2 *rand = new TRandom2(1);//i can put (seed)

	TH1F *hist = new TH1F("hist", "Histogram", 100, 0, 100);

	for(int i=0;i<100000;i++){

	double r = rand->Rndm()*100;
	cout << r << endl;
	hist->Fill(r);

	}

	TCanvas *c1 = new TCanvas();
	hist->GetYaxis()->SetRangeUser(0,2000);
	hist->Draw();
}
