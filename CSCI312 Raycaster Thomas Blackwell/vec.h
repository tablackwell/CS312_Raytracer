// Thomas Blackwell
// tablackwell@email.wm.edu
// CSCI 312 Assignment 4 - Raycaster implemented in C

#ifndef VEC_H
#define VEC_H

// VEC_T - with x, y, and z fields. They correspond to coordinate locations of spheres in our txt files. 
typedef struct {
    double x;
    double y; 
    double z;
} VEC_T;

// Provides information to vec.c - informs the compiler of which types to expect from function returns. 
VEC_T normalize(VEC_T); 
double dot(VEC_T, VEC_T);

#endif

