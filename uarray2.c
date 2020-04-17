/*
 * uarray2.c
 * Andrea Foo (afoo01) and Erena Inoue(einoue01)
 * Comp40, HW2 iii
 * Due: February 10, 2020
 * Purpose: Implmentation file for the uarray2 class
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "uarray2.h"
#include <uarray.h>

/*
 * struct of UArray2_T that will hold the width, and height of the array, a
 * a pointer to the one dimensional array, and the size of each element in the
 * array. Hence, the 2D unboxed array is really implemented as a 1D unboxed
 * array
 */
struct UArray2_T {
  int width;
  int height;
  int size;
  UArray_T array_elems;
};


UArray2_T UArray2_new(int width, int height, int size)
{
  /*Make sure that the size, height, and width is larger than 0, if not, CRE */
  assert(height > 0 && width > 0);
  assert(size != 0);
  /*computing the size of 1D array */
  int array_size = height * width;
  UArray2_T newArray = malloc(sizeof(*newArray));
  /*check to make sure the newly allocated pointer is not null */
  assert(newArray != NULL);
  /* assigning to the elements in the struct */
  UArray_T array1D = UArray_new(array_size, size);
  newArray -> width = width;
  newArray -> height = height;
  newArray -> size = size;
  newArray -> array_elems = array1D;
  return newArray;
}

int UArray2_width(UArray2_T array2D)
{
  /* Makes sure that the pointer to the array is not NULL, if it is, CRE */
  assert(array2D != NULL);
  return array2D -> width;
}

int UArray2_height(UArray2_T array2D)
{
  /* Makes sure that the pointer to the array is not NULL, if it is, CRE */
  assert(array2D != NULL);
  return array2D -> height;
}

int UArray2_size(UArray2_T array2D)
{
  /* Makes sure that the pointer to the array is not NULL, if it is, CRE */
  assert(array2D != NULL);
  return array2D -> size;
}

void *UArray2_at(UArray2_T array2D, int x, int y)
{
  /* Makes sure that the pointer to the array is not NULL and x and y are within
   bounds otherwise, CRE */
  assert(array2D != NULL);
  assert((x >= 0) && (x < array2D -> width) && (y < array2D -> height) &&
          (y >= 0));
  int array_width = array2D -> width;
  int index = array_width * y + x; /* index calculation */
  return UArray_at(array2D -> array_elems, index);
}

void UArray2_map_col_major(UArray2_T array2D, void apply(int x, int y,
                           UArray2_T array2D, void* curr_position, void*cl),
                           void *cl)
{
  /* Makes sure that the array is not NULL, if it is, CRE */
  assert(array2D != NULL);
  int height = array2D -> height;
  int width = array2D -> width;
  /*loops through the entire 2D array column by column and calls function on
  * each element in the 2D array */
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
        apply(x, y, array2D, UArray2_at(array2D, x, y), &cl);
    }
  }
}

void UArray2_map_row_major(UArray2_T array2D, void apply(int y, int x,
                           UArray2_T array2D, void* curr_position, void*cl),
                          void *cl)
{
  /* Makes sure that the array is not NULL, if it is, CRE */
  assert(array2D != NULL);
  int height = array2D -> height;
  int width = array2D -> width;
  /*loops through the entire 2D array row by row and calls function on
  * each element in the 2D array */
  for (int x = 0; x < height; x++) {
    for (int y = 0; y < width; y++) {
        apply(y, x, array2D, UArray2_at(array2D, y, x), &cl);
    }
  }
}

void UArray2_free(UArray2_T *array2D)
{
  /* Makes sure that the pointer array and its pointer are not NULL,
   if it is, CRE */
  assert(array2D != NULL && *array2D != NULL);
  /*frees the Uarray to prevent memory leaks */
  UArray_free(&(*array2D)->array_elems);
  /*frees the pointer to the Uarray */
  free(*array2D);
}
