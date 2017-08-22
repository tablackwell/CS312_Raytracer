// Thomas Blackwell
// tablackwell@email.wm.edu
// CSCI 312 Assignment 4 - Raycaster implemented in C

#include <math.h>
#include "vec.h"

// VEC_T normalize (VEC_T v)
// Computes and returns normalized vector v
VEC_T normalize(VEC_T v){
    double len;
    len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    
    VEC_T ret;
    ret.x = (v.x / len);
    ret.y = (v.y / len);
    ret.z = (v.z / len);
    
    return ret;
}

// double dot (VEC_T v1, VEC_T v2)
// computes and returns dot product of v1 and v2
// Being used yet? No current calls to it
double dot(VEC_T v1, VEC_T v2){
    double dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return dotProduct;
}
