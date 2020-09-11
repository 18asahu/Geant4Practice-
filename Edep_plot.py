# -*- coding: utf-8 -*-
"""
Created on Fri Sep 11 17:57:24 2020

@author: neham
"""

import matplotlib.pyplot as plt
import numpy as np

f = open('output.txt')
lines = f.readlines()

values = lines[737: ]

energy_s1 = []
edep_s1 = []
energy_s0 = []
edep_s0 = []

#Separate the parallel runs
for i in values:
    k = (i[8:15])
    stream = i[4]
    
    if stream == '1':
        if k == 'Energy:':
            p = i[15::]
            d = float(p[:-2])
            energy_s1.append(d)        
        if k == 'Edep_Si':
            q = i[17::]
            e = float(q[:-2])
            edep_s1.append(e)
            
    if stream == '0':
        if k == 'Energy:':
            p = i[15::]
            d = float(p[:-2])
            energy_s0.append(d)        
        if k == 'Edep_Si':
            q = i[17::]
            e = float(q[:-2])
            edep_s0.append(e)

#Plotting histogram            
np_hist = edep_s1   #change to edep_s2 for stream2
hist,bin_edges = np.histogram(np_hist)

plt.figure(figsize=[10,8])
plt.bar(bin_edges[:-1], hist, width = 0.5, color='#0504aa',alpha=0.7)
plt.xlim(min(bin_edges), 8) # set 8 to max(bin_edges) for full coverage
plt.grid(axis='y', alpha=0.75)
plt.xlabel('Edep/MeV',fontsize=15)
plt.ylabel('Frequency',fontsize=15)
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)
plt.ylabel('Frequency',fontsize=15)
plt.title('Energy Deposited in Si',fontsize=15)
plt.show()
   
#print(energy_s1)
#print(energy_s0)



