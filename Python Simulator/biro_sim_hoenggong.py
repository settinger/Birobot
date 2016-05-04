from __future__ import print_function
import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib
matplotlib.use('TkAgg')

import birobot
from biro_constants_bad import *

# Get list of actions to simulate
up = -130
dn = -150

waypts = [
(0, 0, up),
(-20, 41, up), (-20, 41, dn), (-85, 38, dn), (-85, 38, up),
(-95, 22, up), (-95, 22, dn), (-10, 22, dn), (-10, 22, up),
(-51, 39, up), (-51, 39, dn), (-51, 2, dn), (-51, 2, up),
(-57, 20, up), (-57, 20, dn), (-70, 8, dn), (-94, -3, dn), (-94, -3, up),
(-45, 20, up), (-45, 20, dn), (-30, 8, dn), (-10, -3, dn), (-10, -3, up),
(-80, -3, up), (-80, -3, dn), (-80, -43, dn), (-80, -43, up),
(-80, -3, up), (-80, -3, dn), (-24, -3, dn), (-24, -43, dn), (-24, -43, up),
(-80, -20, up), (-80, -20, dn), (-24, -20, dn), (-24, -20, up),
(-80, -38, up), (-80, -38, dn), (-24, -38, dn), (-24, -38, up),

(5, 41, up), (5, 41, dn), (15, 33, dn), (15, 33, up),
(1, 18, up), (1, 18, dn), (12, 9, dn), (12, 9, up),
(3, -41, up), (3, -41, dn), (10, -8, dn), (10, -8, up),
(25, 33, up), (25, 33, dn), (82, 33, dn), (82, 33, up),
(40, 45, up), (40, 45, dn), (40, 14, dn), (40, 14, up),
(66, 45, up), (66, 45, dn), (66, 14, dn), (66, 14, up),
(20, 13, up), (20, 13, dn), (85, 13, dn), (85, 13, up),
(40, 11, up), (40, 11, dn), (32, 0, dn), (19, -11, dn), (19, -11, up),
(66, 11, up), (66, 11, dn), (85, -12, dn), (85, -12, up),
(34, -3, up), (34, -3, dn), (68, -3, dn), (68, -22, dn), (68, -22, up),
(34, -20, up), (34, -20, dn), (68, -20, dn), (68, -20, up),
(34, -3, up), (34, -3, dn), (34, -31, dn), (40, -40, dn), (72, -40, dn), (80, -30, dn), (81, -25, dn), (81, -25, up),
(0, 0, up)
]

# Initialize frame
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

oldpt = (0,0,-100)
pathx = [oldpt[0]]
pathy = [oldpt[1]]
pathz = [oldpt[2]]

# Initialize qA, qB, qC
qA = 45; qB = 45; qC = 45

# Number of actions to animate
for waypt in waypts:
    # Draw travel between waypoints faithfully to actual robut
    # Let's say (for now) we animate five frames in between each waypoint
    (x0, y0, z0) = oldpt
    (x1, y1, z1) = waypt
    dist = np.sqrt((x1-x0)**2+(y1-y0)**2+(z1-z0)**2)
    for dt in np.linspace(0,1,np.ceil(dist*30/80)):
        plt.cla()
        
        # Compute angles, locations of points
        dest = (x0 + dt*(x1-x0), y0 + dt*(y1-y0), z0 + dt*(z1-z0))
        (xd, yd, zd) = dest
        if zd < (dn+1):
            pathx += [xd]
            pathy += [yd]
            pathz += [zd]
        
        (qA, qB, qC) = birobot.xyz2servo(xd, yd, zd, qA, qB, qC)
        # TEMPHACK:
        # qA += 180; qB += 180; qC += 180;
        # Rotation matrix from frame N to frames of upper links:
        R_A_N = birobot.rotationMatrix([1,0,0], qA*np.pi/180)
        R_B_N = birobot.rotationMatrix([1,0,0], qB*np.pi/180) * birobot.rotationMatrix([0,0,1], 2*np.pi/3)
        R_C_N = birobot.rotationMatrix([1,0,0], qC*np.pi/180) * birobot.rotationMatrix([0,0,1], 4*np.pi/3)
##        R_B_N = birobot.rotationMatrix([0,0,1], 2*np.pi/3) * birobot.rotationMatrix([1,0,0], qB*np.pi/180)
##        R_C_N = birobot.rotationMatrix([0,0,1], 4*np.pi/3) * birobot.rotationMatrix([1,0,0], qC*np.pi/180)

        # Define frame indexes (relative to inertial frame)
        n_x = np.matrix([1,0,0]).T
        n_y = np.matrix([0,1,0]).T
        n_z = np.matrix([0,0,1]).T
        a_x = R_A_N.I*n_x
        a_y = R_A_N.I*n_y
        a_z = R_A_N.I*n_z
        b_x = R_B_N.I*n_x
        b_y = R_B_N.I*n_y
        b_z = R_B_N.I*n_z
        c_x = R_C_N.I*n_x
        c_y = R_C_N.I*n_y
        c_z = R_C_N.I*n_z
        
        A0 = -sB/2*n_y
        B0 = birobot.rotationMatrix([0,0,1], -2*np.pi/3)*A0
        C0 = birobot.rotationMatrix([0,0,1], -2*np.pi/3)*B0
        A1 = A0 - L*a_y
        B1 = B0 - L*b_y
        C1 = C0 - L*c_y

        P0 = np.matrix([xd, yd, zd]).T
        PA = P0 + A0*sP/sB
        PB = P0 + B0*sP/sB
        PC = P0 + C0*sP/sB
                
        # Draw the hexagon that is the top of the machine
        xlist = [sB/2*np.cos(q) for q in np.linspace(0, 2*np.pi, 7)]
        ylist = [sB/2*np.sin(q) for q in np.linspace(0, 2*np.pi, 7)]
        zlist = [0 for q in np.linspace(0, 2*np.pi, 7)]
        ax.plot(xlist, ylist, zlist, 'g-')
        
        # Draw the triangle that is the end effector
        xlist = [xd + sP/2*np.cos(q) for q in np.linspace(0, 2*np.pi, 7)]
        ylist = [yd + sP/2*np.sin(q) for q in np.linspace(0, 2*np.pi, 7)]
        zlist = [zd for q in np.linspace(0, 2*np.pi, 7)]
        ax.plot(xlist, ylist, zlist, 'g-')
        
        # Draw the upper links
        Alink = [(A0[n].sum(), A1[n].sum()) for n in [0, 1, 2]]
        Blink = [(B0[n].sum(), B1[n].sum()) for n in [0, 1, 2]]
        Clink = [(C0[n].sum(), C1[n].sum()) for n in [0, 1, 2]]
        ax.plot(Alink[0], Alink[1], Alink[2], 'r--', lw=3)
        ax.plot(Blink[0], Blink[1], Blink[2], 'r--', lw=3)
        ax.plot(Clink[0], Clink[1], Clink[2], 'r--', lw=3)
        
        # Draw the parallelograms
        Alink = [(PA[n].sum(), A1[n].sum()) for n in [0, 1, 2]]
        Blink = [(PB[n].sum(), B1[n].sum()) for n in [0, 1, 2]]
        Clink = [(PC[n].sum(), C1[n].sum()) for n in [0, 1, 2]]
        ax.plot(Alink[0], Alink[1], Alink[2], 'b--', lw=3)
        ax.plot(Blink[0], Blink[1], Blink[2], 'b--', lw=3)
        ax.plot(Clink[0], Clink[1], Clink[2], 'b--', lw=3)
        
        ax.scatter(pathx, pathy, pathz, 'm:')

        ax.set_xlim3d((-150,150))
        ax.set_ylim3d((-150,150))
        ax.set_zlim3d((-300,0))

        vec = PA - A1
        vec = vec.T*vec
#        print(str(qA) + ', ' + str(qB) + ', ' + str(qC))
        #plt.show()
        plt.pause(0.001)
    oldpt = waypt
