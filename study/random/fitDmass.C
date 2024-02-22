Double_t fitDmass(Double_t *v, Double_t *par)
{
   /*----------LISTA DE PARAMETROS 
   	0 - # de sinais 
   	1 - media da massa
   	2 - largura 
   	3 - slope do bg
   	4 - # de bg
   */
   
   Double_t dx = 1.;
   Double_t constant = 2.5066297; // raiz de 2pi

   Double_t fnorm = 1./ (constant * par[2]);
   
   Double_t gaussian = fnorm * TMath::Exp (-(par[1] - v[0])*(par[1] - v[0]) / (2.*par[2]*par[2]));
   
   Double_t norm_back = par[3]/(TMath::Exp(par[3]*(100))-1);
   
   Double_t back = norm_back * TMath::Exp(par[3]*(v[0]-1820));
   
   Double_t gfit = dx*  (par[0] * gaussian + par[4]* back);

   return gfit;
}

