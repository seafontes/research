import ROOT

# Set seed for reproducibility
ROOT.gRandom.SetSeed(0)

# Create a histogram
hist = ROOT.TH1F("myhist", "Gaussian Distribution", 100, 1820, 1920)

# Set the mean and standard deviation of the Gaussian distribution
mean = 1869
std_dev = 10

# Fill the histogram with Gaussian-distributed data
for i in range(10000):
    value = ROOT.gRandom.Gaus(mean, std_dev)
    hist.Fill(value)

# Create a canvas and draw the histogram
canvas = ROOT.TCanvas("mycanvas", "Gaussian Distribution Canvas", 800, 600)
hist.Draw()

# Show the canvas
canvas.Draw()
