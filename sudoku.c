/*
 * sudoku.c
 * Andrea Foo (afoo01) and Erena Inoue (einoue01)
 * Comp40, HW2 iii
 * Due: February 10, 2020
 * Purpose: Implmentation file for the sudoku using uarray2
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <uarray2.h>
#include <uarray.h>
#include <pnmrdr.h>

/* CONSTANTS width and height for sudoku board */
const int WIDTH = 9;
const int HEIGHT = 9;

/*FUNCTION PROTOTYPES */
void make_sudoku(Pnmrdr_T rdr, UArray2_T test_array);
void read_pgm(FILE *fp);
void check_for_solution(UArray2_T test_array);
void check_line(int x, int y, UArray2_T array2D, void* curr_position, void *cl);
void sudoku_map_box(UArray2_T array2D, void apply(int x, int y,
                    UArray2_T array2D, void* curr_position));
void check_for_solution(UArray2_T test_array);
void check_box(int x, int y, UArray2_T array2D, void* curr_position);


/* int main(int argc, char *argv[])
 * Function: Gets a pgm file from the arguments and opens the pgm file.
 *           will exit with code of 1 if incorrect file format is given or
 *           the sudoku is not a solution. If it is, then it will exit with
 *           an exit code of 0.
 * Input: int argc, char *argv[]
 * Output: None
 */
int main(int argc, char *argv[])
{
  assert(argc <= 2);
  if (argc == 1) {
      read_pgm(stdin);
  }
  else if (argc == 2) {
      FILE *fp = fopen(argv[1], "r");
      assert(fp != NULL);
      read_pgm(fp);
  }
  /* will exit with 0 if it is a sudoku solution. Success */
  exit(0);
}



/* void read_pgm(FILE *fp)
 * Function: Reads in the given file, checks its format, convert it to
 *           2D UArray and checks for sudoku solution. If rdr is a bad format,
 *           it will exit with a code of 1. Will raise a CRE if input file is
 *           null.
 * Input: FILE *fp
 * Output: None
 */
void read_pgm(FILE *fp)
{
    assert(fp != NULL);
    Pnmrdr_T rdr = Pnmrdr_new(fp);

    /*check to make sure that the file given is in good format */
    assert(rdr != NULL);
    int number;
    /*create a new 2D Uarray to store the pixel data of the pgm file. */
    UArray2_T array_2D = UArray2_new(WIDTH, HEIGHT, sizeof(number));

    /*stores the pixel data of the pgm file. in the 2D array */
    /*checks the array to make see if it is a valid sudoku solution */
    make_sudoku(rdr, array_2D);
    check_for_solution(array_2D);

    /* Checking to see if the pointer to be freed is NULL or not */
    assert(array_2D != NULL);
    /* frees the rdr and 2D array pointer and close the file to prevent memory
     * leaks
     */
    UArray2_free(&array_2D);
    Pnmrdr_free(&rdr);
    fclose(fp);
}

/* void make_sudoku(Pnmrdr_T rdr, UArray2_T test_array)
 * Function: By reading the image file, create a 2D UArray
 *           that represents sudoku. If rdr is null or file is not pgm, or
 *           pixel count is 0, the function will exit with a code of 1. Will
 *           raise a CRE if the width and height are not equal to 9.
 * Input: Pnmrdr_T rdr, UArray2_T test_array
 * Output: None
 */
void make_sudoku(Pnmrdr_T rdr, UArray2_T array_2D)
{
  /*checks to make sure rdr is not null */
  assert(rdr != NULL);
  Pnmrdr_mapdata data = Pnmrdr_data(rdr);
  int width = (int)data.width;
  int height = (int)data.height;
  assert((width == 9) && (height == 9));
  /* make sure that the file type is pgm. */
  assert(data.type == Pnmrdr_gray);
  /* make sure that size is not 0 */
  assert((width * height) != 0);
  /*loop through pgm image to get intensity and put it in 2D array while
   * checking to make sure that the pixel intensities are not 0 and smaller
   * than 9
   */
   for(int y = 0; y < (int)height; y++){
     for(int x = 0; x < (int)width; x++){
        int curr_intensity = (int)Pnmrdr_get(rdr);
        assert((curr_intensity > 0) && (curr_intensity <= 9));
        *((int *) UArray2_at(array_2D, x, y)) = curr_intensity;
     }
   }
}


/* void check_line(int x, int y, UArray2_T array2D,
 *                    void* curr_position, void*cl)
 * Function: Checks whether there are repeating numbers in a line
 *          of sudoku array. This function is to be applied on row major and col
 *          major functions to check. Will raise a CRE if pointer to the arrayis
 *          null.
 * Input: int x, int y, UArray2_T array2D, void* curr_position, void *cl
 * Output: None
 */
void check_line(int x, int y, UArray2_T array2D, void* curr_position, void *cl)
{
  (void) cl;
  /* Makes sure that the pointer to the array is not NULL, if it is, CRE */
  assert((array2D != NULL) && (x >= 0) && (x < UArray2_width(array2D)) &&
          (y >= 0) && (y < UArray2_height(array2D)));
  /* loops through the line and checks to make sure that every pixel after the
   * current pixel will not have the same intensity as the current pixel
   * If it does, then it will exit with a code of 1 */
  for (int i = y+1; i < 9; i++) {
    if ((*((int *)curr_position) == *((int *)UArray2_at(array2D, x, i)))) {
      exit(1);
    }
  }
}

/* void check_box(int x, int y, UArray2_T array2D, void* curr_position)
 * Function: Checks whether there are repeating numbers in a box
 *           of sudoku array. If there is, then the program will exit with an
 *           exit code code of 1. If it is a solution, then nothing happens.
 * Input: int x, int y, UArray2_T array2D, void* curr_position
 * Output: None
 */
void check_box(int x, int y, UArray2_T array2D, void* curr_position)
{
  /* Makes sure that the pointer to the array is not NULL, if it is, CRE */
  assert(array2D != NULL);
  int i = x + 1;
  int j = y + 1;
  /*loop will continue for two indices after the current index to check a 3 by 3
   * box in the 2D array */
  while (i < (x + 2)) {
    while (j < (y + 2)) {
      /* will exit if the value at current position is equal to any of the
       * values in the next two indices, indicating that it is not a
       * sudoku solution
       */
      if (*((int *)curr_position) == *((int *)UArray2_at(array2D, i, j))) {
        exit(1);
      }
      j++;
    }
    i++;
  }
}

/* void sudoku_map_box(UArray2_T array2D, void apply(int x, int y,
                    UArray2_T array2D, void* curr_position))
 * Function: Checks to see if the pgm file is a sudoku solution by the 3 by 3
 *           box framework by calling the apply function, which is check_box,
 *           on each 3 by 3 box in the pgm file. Will raise a CRE if pointer
 *           to array is null or the array size is not 9x9.
 * Input: int x, int y, UArray2_T array2D, void* curr_position
 * Output: None
 */
void sudoku_map_box(UArray2_T array2D, void apply(int x, int y,
                    UArray2_T array2D, void* curr_position))
{
  /* Makes sure that the pointer to the array is not NULL, if it is, CRE */
  assert(array2D != NULL);
  int height = UArray2_height(array2D);
  int width = UArray2_width(array2D);
  /* Makes sure that the array is 9x9, if it is, CRE */
  assert((height == 9) && (width == 9));
  int x = 0;
  int y = 0;
  /* will keep looping until it has called the apply function on all the 3 by 3
   * boxes in the sudoku arrray
   */
  while(x < height){
    while(y < width){
      apply(x, y, array2D, UArray2_at(array2D, x, y));
      y += 3;
    }
    x += 3;
  }
}

/* void check_for_solution(UArray2_T test_array)
 * Function: calls other helper check functions to check the entire
 * sudoku. If the input array is NULL, the function will raise a
 * checked runtime error
 * Input: UArray2_T test_array
 * Output: None
 */
void check_for_solution(UArray2_T test_array)
{
  /* Makes sure that the pointer to the array is not NULL, if it is, CRE */
  assert(test_array != NULL);

  /*dummy to pass into the closure argument for the map functions */
  bool OK = true;
  /*checks to make sure that every column does not have repeating numbers*/
  UArray2_map_col_major(test_array, check_line, &OK);

  /*checks to make sure that every row does not have repeating numbers*/
  UArray2_map_row_major(test_array, check_line, &OK);

  /*checks to make sure that every 3 by 3 box does not have repeating numbers*/
  sudoku_map_box(test_array, check_box);
}
