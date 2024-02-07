void tut4(){

	TGraph *gr =  new TGraph();
	gr->SetMarkerStyle(kFullCircle);

	fstream file;
	file.open("data.txt", ios::in);

	while(1){
		double x,y;
		file >> x >> y;
		gr->SetPoint(gr->GetN(),x,y);
		if(file.eof())	break;
	}

	file.close();
	TCanvas *c1 = new TCanvas();
	gr->Draw("AL*");

}
