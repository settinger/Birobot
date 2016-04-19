import numpy as np
from numpy import sqrt
from scipy.optimize import fsolve

from biro_constants_bad import *


# Rotation matrix from a Scipy mailing list, March 2009
def rotationMatrix(direction, angle):
    """
    Create a rotation matrix corresponding to the rotation around a general
    axis by a specified angle.
    
    R = dd^T + cos(a) (I - dd^T) + sin(a) skew(d)
    
    Parameters:
    
    angle : float a
    direction : array d
    """
    d = np.array(direction, dtype=np.float64)
    d /= np.linalg.norm(d)
    
    eye = np.eye(3, dtype=np.float64)
    ddt = np.outer(d, d)
    skew = np.matrix([[    0,  d[2],  -d[1]],
                  [-d[2],     0,   d[0]],
                   [d[1], -d[0],     0]], dtype=np.float64)
    
    mtx = ddt + np.cos(angle) * (eye - ddt) + np.sin(angle) * skew
    return mtx

def quadraticSolve(E, F, G):
    t1 = (-F + sqrt(E*E + F*F - G*G))/(G-E)
    t2 = (-F - sqrt(E*E + F*F - G*G))/(G-E)
    q1 = 2*np.arctan(t1)*180/np.pi
    q2 = 2*np.arctan(t2)*180/np.pi
    if q1 < -90:
        q1 += 180
    if q2 < -90:
        q2 += 180
    if q1 < 90: return q1
    else: return q2

def xyz2servo(x, y, z):
    EA = 2*L*(y+a)
    EB = -L*((sqrt(3)*(x+b)) + y + c)
    EC = L*((sqrt(3)*(x-b)) - y - c)

    F = 2*L*z

    GA = x*x + y*y + z*z + a*a + L*L + 2*y*a - l*l
    GB = x*x + y*y + z*z + b*b + c*c + L*L + 2*(b*x + c*y) - l*l
    GC = x*x + y*y + z*z + b*b + c*c + L*L + 2*(c*y - b*x) - l*l

    qA = quadraticSolve(EA, F, GA)
    qB = quadraticSolve(EB, F, GB)
    qC = quadraticSolve(EC, F, GC)
    return (qA, qB, qC)
    

def servo2xyz(qA, qB, qC):
    # Rotation matrix from frame N to frames of upper links:
    R_A_N = rotationMatrix([1,0,0], qA*np.pi/180)
    R_B_N = rotationMatrix([1,0,0], qB*np.pi/180) * rotationMatrix([0,0,1], 2*np.pi/3)
    R_C_N = rotationMatrix([1,0,0], qC*np.pi/180) * rotationMatrix([0,0,1], 4*np.pi/3)

    # Define frame indexes
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
    B0 = birobot.rotationMatrix([0,0,1], 2*np.pi/3)*A0
    C0 = birobot.rotationMatrix([0,0,1], 2*np.pi/3)*B0
    A1 = A0 - L*a_y
    B1 = B0 - L*b_y
    C1 = C0 - L*c_y

    # Position vectors
    #r_Pa_N0 = 

    return 0

def equations(p):
    x, y, z = p
    eq1 = (x - sP/(2*np.sqrt(3)))
