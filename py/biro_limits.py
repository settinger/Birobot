# -*- coding: utf-8 -*-
"""
Created on Fri Apr 22 11:40:59 2016

@author: Sam
"""

# Visualizations to help me figure out what size bounding box to use

import numpy as np
from numpy import sqrt
from scipy.optimize import fsolve
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib

from biro_constants_bad import *


# Gotta compute the intersection of three spheres

'''
    EA = 2*L*(y+a)
    EB = -L*((sqrt(3)*(x+b)) + y + c)
    EC = L*((sqrt(3)*(x-b)) - y - c)

    F = 2*L*z

    GA = x*x + y*y + z*z + a*a + L*L + 2*y*a - l*l
    GB = x*x + y*y + z*z + b*b + c*c + L*L + 2*(b*x + c*y) - l*l
    GC = x*x + y*y + z*z + b*b + c*c + L*L + 2*(c*y - b*x) - l*l
'''

def isValid(x,y,z):
    EA = 2*L*(y+a)
    EB = -L*((sqrt(3)*(x+b)) + y + c)
    EC = L*((sqrt(3)*(x-b)) - y - c)
    F = 2*L*z
    GA = x*x + y*y + z*z + a*a + L*L + 2*y*a - l*l
    GB = x*x + y*y + z*z + b*b + c*c + L*L + 2*(b*x + c*y) - l*l
    GC = x*x + y*y + z*z + b*b + c*c + L*L + 2*(c*y - b*x) - l*l
    if ((EA*EA+F*F-GA*GA)>0) and ((EB*EB+F*F-GB*GB)>0) and ((EC*EC+F*F-GC*GC)>0):
        return True
    else:
        return False


validpts = [[] for q in range(3)]

for x in np.linspace(-300,300, 101):
    for y in np.linspace(-300,300, 101):
        for z in np.linspace(-300,0, 101):
            if isValid(x,y,z):
                if not isValid(x+6,y,z) or not isValid(x-6,y,z) or not isValid(x,y+6,z) or not isValid(x,y-6,z) or not isValid(x,y,z+6) or not isValid(x,y,z-6):
                    validpts[0] += [x]
                    validpts[1] += [y]
                    validpts[2] += [z]

# Crude filter: If you have six neighbors, gtfo


fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(*validpts)


'''
with open('pointcloud.csv', 'wb') as csvfile:
     aa = csv.writer(csvfile)
     for n in range(len(validpts[0])):
         aa.writerow([validpts[0][n], validpts[1][n], validpts[2][n]])
'''