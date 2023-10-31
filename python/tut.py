from ROOT import *

h1 = TH1F("h1", "Random", 200,-5,5)
h1.FillRandom("gaus")

c1= TCanvas()
h1.Draw()

c1.Print("c1.pdf")
