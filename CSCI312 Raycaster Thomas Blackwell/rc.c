// Thomas Blackwell
// tablackwell@email.wm.edu
// CSCI 312 Assignment 4 - Raycaster implemented in C
#include <stdlib.h>
#include <stdio.h>
#include "rc.h"
#include <math.h>



// void read_objs (OBJ_T **list)
// Reads spheres from stdin; creates linked list
void read_objs(OBJ_T **list){
    OBJ_T *node; // The node for the linked list
    double cx,cy,cz,rad,r,g,b; // The values to be taken from the file
    
    while(scanf("%lf %lf %lf %lf %lf %lf %lf", &cx, &cy, &cz, &rad, &r, &g, &b) == 7){
        //Allocate memory for each node, then set the values for the sphere's dimensions
        node = (OBJ_T *)malloc(sizeof(OBJ_T)); 
        node->sphere.center.x = cx;
        node->sphere.center.y = cy;
        node->sphere.center.z = cz;
        node->sphere.radius = rad;
        
        // Set colors according to values in the file
        node->color.r = r;
        node->color.g = g;
        node->color.b = b;
        
        // Go to the next node
        node->next = *list;
        *list = node;
    }
}

// int intersect_sphere (RAY_T ray, SPHERE_T sphere, double *t)
// computes intersection of ray and sphere; returns 1 if intersection, 0 otherwise
// t is set to distance from camera to sphere intersection
int intersect_sphere(RAY_T ray, SPHERE_T sphere, double *t){
    double A,B,C;
    A = 1.0;
    
    // Assign values according to the quadratic formula
    B = 2*((ray.direction.x * (ray.origin.x - sphere.center.x)) 
        + (ray.direction.y * (ray.origin.y - sphere.center.y)) 
        + (ray.direction.z * (ray.origin.z - sphere.center.z)));
    
    // Same thing here... according to code given in class
    C = ((ray.origin.x - sphere.center.x)*(ray.origin.x - sphere.center.x) 
        + (ray.origin.y - sphere.center.y)*(ray.origin.y - sphere.center.y) 
        + (ray.origin.z - sphere.center.z)*(ray.origin.z - sphere.center.z)
        - sphere.radius * sphere.radius);
        
    double discriminant = B*B - 4*A*C; // The part that goes inside the sqrt
    if(discriminant < 0){return 0;} // Dont want to divide by zero, so return 0 to prevent that
    
    // Calculate our t0 and t1....
    double t0 = ((-B + sqrt(discriminant)) / 2*A);
    double t1 = ((-B + sqrt(discriminant)) / 2*A);
    if(t0 < 0 && t1 <0){return 0;} // If both of the T's are negative, then just return 0 - no intersection!
    
    // Choose the smaller of the two values
    if(t0 < t1){*t = t0;}
    else{*t = t1;}
    
    return 1; // If we get here, an intersection has been found. 
}

// COLOR_T cast (RAY_T ray, OBJ_T * list)
// iterates through linked list; finds closest intersection; returns color of closest sphere
COLOR_T cast(RAY_T ray, OBJ_T *list){
    OBJ_T *curr;
    double t;
    double min_t = 1000.0;
    
    // Initialize our color values. Set to one to ensure white backgrounds when no intersection is found. 
    // Fun thing to do: if you remove these assignments to one, we get some cool gradients in the output. We set these to 1.0, so it stays white in the absence of a sphere. 
    COLOR_T color;
    color.r = 1.0;
    color.g = 1.0;
    color.b = 1.0;
    
    // Iterate through the list set the current color to the color there
    for(curr = list; curr != NULL; curr = curr->next){
        if(intersect_sphere(ray, (*curr).sphere, &t)){ //check if we have an intersection,
            if(t < min_t){
                min_t = t;
                color = curr->color;
            }
        }
    }
    return color;
}

// main
// initializes image file; loops through pixels; sets ray; prints pixels; frees linked list
main(){
    
    OBJ_T *list = NULL;
    OBJ_T *curr;
    RAY_T ray;
    int x,y;
    
    read_objs(&list); //Read in the objects, passing an address of our list to the method
    
    printf("P6\n1000 1000\n255\n"); // Initializes the image by creating the ppm header
    
    // Loop through the pixels, 
    for (x = 0; x < 1000; x++){
        for (y = 0; y < 1000; y++){
            
            // Set up the ray
            ray.origin.x = 0;
            ray.origin.y = 0;
            ray.origin.z = 0;
            
            // Set the direction adjusted for the resolution of our image (1000x100)
            ray.direction.z = 1;
            ray.direction.x = -0.5 + y / 1000.0;
            ray.direction.y = 0.5 - x / 1000.0;
            
            // Normalize the ray's direction
            ray.direction = normalize(ray.direction);
            
            //Pass our list of pixels to Cast to get the proper pixel
            COLOR_T pix = cast(ray,list);

            //Now print the color at that pixel. 
            printf("%c%c%c", (unsigned char)(pix.r*255), (unsigned char)(pix.g*255),(unsigned char)(pix.b*255));
        }
    }
    
    // Free each individual item from the linked list
    while(list != NULL){
        curr = list;
        list = list->next;
        free(curr);
    }
}
