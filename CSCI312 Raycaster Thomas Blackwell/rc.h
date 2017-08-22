// Thomas Blackwell
// tablackwell@email.wm.edu
// CSCI 312 Assignment 4 - Raycaster implemented in C

#include "vec.h"
#ifndef OBJ_H
#define OBJ_H


// RAY_T - origin and direction fields  
typedef struct{
    VEC_T origin;
    VEC_T direction;
} RAY_T;

// COLOR_T - with R,G,B fields
typedef struct{
    double r;
    double g;
    double b;
} COLOR_T;

// SPHERE_T - with Center and Radius
typedef struct{
    VEC_T center;
    double radius;
} SPHERE_T;

// OBJ_T - with sphere, color, and next fields
typedef struct OBJ {
    SPHERE_T sphere;
    COLOR_T color;
    struct OBJ *next;
} OBJ_T;

COLOR_T cast(RAY_T ray, OBJ_T *list);

#endif
