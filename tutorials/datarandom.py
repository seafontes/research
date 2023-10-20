import numpy as np
import random

f = open("data.txt", "w")

for i in range(100):
	f.write("{} {} \n".format(i, random.randint(1,10)))
