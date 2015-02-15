/*------------------------------------------------------------------------------

  Copyright (c) 2012-2014 viorica patraucean (vpatrauc@gmail.com)
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Affero General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Affero General Public License for more details.

  You should have received a copy of the GNU Affero General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.


  test_ellipse_fit_with_gradients.c - example of call to the function 
    ellipse_fit_with_gradientsfunctions.c, which fits algebraically an ellipse 
    to a given set of points endowed with Cartesian coordinates and gradient 
    directions. 
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "ellipse_fit_with_gradients.h"

int main( int argc, char **argv )
{
  /* Read test data from file sample_data.txt. The first line contains the number 
     of points pts_size, and the pts_size subsequent lines have the form 
     x, y, gradx, grady */
  int i;
  double *pts;
  double *grad;
  double param[5];
  char *fname = argv[1];

  FILE* f = fopen(fname,"r");
  if( f == NULL ) error("invalid input file");
  
  int pts_size;
  fscanf( f, "%d\n", &pts_size );
  if( pts_size <= 0 ) error("invalid points size");

  /* Allocate memory for point coordinates and gradients */
  pts = (double *) malloc ( 2 * pts_size * sizeof(double) ); 
  if( pts == NULL )  error("not enough memory for pts");
  grad = (double *) malloc ( 2 * pts_size * sizeof(double) );  
  if( grad == NULL )  error("not enough memory for grad");
  
  for( i=0; i<pts_size, !feof(f); ++i )
    {
      fscanf(f, "%lf %lf %lf %lf\n", &(pts[2*i]), &(pts[2*i+1]), 
                                     &(grad[2*i]), &(grad[2*i+1]) ); 
    }
  /* For repeated calls to ellipse fitting function, it is recommended to use 
     a buffer needed internally to compute the coefficients of a linear system; 
     this buffer has one element at the first call, and the function allocates 
     internally the additional memory needed */
  double *buff = (double *) malloc ( sizeof(double) );
  int size_buff_max = 1;

  ellipse_fit_with_gradients( pts, grad, pts_size, &buff, &size_buff_max, 
                              param );
  free(buff);

  /* Print result to console */
  printf("Ellipse parameters: ");
  for( i=0; i<5; ++i )
    printf("%lf ", param[i]);
  printf("\n");
  return 0;
}
