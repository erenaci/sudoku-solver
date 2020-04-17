/*
 * uarray2.h
 * Andrea Foo (afoo01) Erena Inoue(einoue01)
 * Comp40, HW2 iii
 * Due: February 10, 2020
 * Purpose: Interface file for the uarray2 class
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <uarray.h>
#include <assert.h>

#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

struct UArray2_T;
typedef struct UArray2_T *UArray2_T;

/* UArray2_T UArray2_new(int height, int width, int size)
 * Function: Creates a new 2D Unboxed array with height and width,
 *           holding elements of the given size, there will be a checked
 *           runtime error. The 2D unboxed array is really a 1D unboxed array1D
 *           in the actual implmentation 
 * Input: int dim1, int dim2, int size. If any of these inputs are invalid,
 *        which is when any of them are less than or equal to zero, there will
 *        be a checked run time error.
 * Output: A pointer to the newly created unboxed 2D array
 */
UArray2_T UArray2_new(int width, int height, int size);


/* int UArray2_width(UArray2_T array)
 * Function: Returns the width of the specified 2D Unboxed Array
 * Input: UArray2_T array. If array or pointer to the array is null, then there
 *        will be a CRE.
 * Output: An integer, for width of the array
 */
int UArray2_width(UArray2_T array);

/* UArray2_height(UArray2_T array)
 * Function: Computes and finds the height of the 2D unboxed array. If pointer
 *           to the array is null, then the function will raise a CRE.
 * Parameters: UArray2_T array
 * Returns: Height of the 2D unboxed array
 */
int UArray2_height(UArray2_T array);

/* UArray2_size(UArray2_T array)
 * Function: Computes and finds the size of the 2D unboxed array. If pointer
 *           to the array is null, then the function will raise a CRE.
 * Parameters: UArray2_T array
 * Returns: Size of the 2D unboxed array
 */
int UArray2_size(UArray2_T array);

/* void * UArray2_at(UArray2_T array, int height, int width)
 * Function: Returns the pointer to an element at [height, width]. If pointer
 * to the array is null and/or x and y are out of bounds, there will be
 * a CRE.
 * Parameters: UArray2_T array, int height, int width
 * Returns: the pointer to an element at [height, width
 */
void * UArray2_at(UArray2_T array, int x, int y);

/* UArray2_map_col_major(UArray2_T array, void apply(int i, int j,
 *                      UArray2_T a, void *p1, void *p2), void *cl)
 * Function: Uses the apply function to manipulate the elements in 2D array
 *           based on the column. Will raise CRE if pointer to array is null
 * Parameters: UArray2_T array, void apply(int i, int j,
 *            UArray2_T a, void *p1, void *p2), void *cl)
 * Returns: No returns
 */
void UArray2_map_col_major(UArray2_T array2D, void apply(int x, int y,
                  UArray2_T array2D, void* curr_position, void*cl), void *cl);

/* UArray2_map_row_major(UArray2_T array, void apply(int i, int j,
*                           UArray2_T a, void *p1, void *p2), void *cl)
* Function: Uses the apply function to manipulate the elements in 2D array
*           based on the row. Will raise CRE if pointer to array is null.
* Parameters: UArray2_T array, void apply(int i, int j,
*             UArray2_T a, void *p1, void *p2), void *cl)
* Returns: No returns
*/
 void UArray2_map_row_major(UArray2_T array2D, void apply(int x, int y,
                    UArray2_T array2D, void* curr_position, void*cl), void *cl);

/* UArray2_free(T *array)
 * Function: frees the memory of 2D unboxed array and the pointer to the array
 * Parameters: UArray2_T *array
 * Returns: No returns
 */
void UArray2_free(UArray2_T *array);

#endif
