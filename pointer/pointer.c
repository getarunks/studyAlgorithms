From : https://stackoverflow.com/questions/917783/how-do-i-work-with-dynamic-multi-dimensional-arrays-in-c

Basics
Arrays in c are declared and accessed using the [] operator. So that

int ary1[5];
declares an array of 5 integers. Elements are numbered from zero so ary1[0] is the first element, and ary1[4] is the last element. Note1: There is no default initialization, so the memory occupied by the array may initially contain anything. Note2: ary1[5] accesses memory in an undefined state (which may not even be accessible to you), so don't do it!

Multi-dimensional arrays are implemented as an array of arrays (of arrays (of ... ) ). So

float ary2[3][5];
declares an array of 3 one-dimensional arrays of 5 floating point numbers each. Now ary2[0][0] is the first element of the first array, ary2[0][4] is the last element of the first array, and ary2[2][4] is the last element of the last array. The '89 standard requires this data to be contiguous (sec. A8.6.2 on page 216 of my K&R 2nd. ed.) but seems to be agnostic on padding.

Trying to go dynamic in more than one dimension
If you don't know the size of the array at compile time, you'll want to dynamically allocate the array. It is tempting to try

double *buf3;
buf3 = malloc(3*5*sizeof(double));
/* error checking goes here */
which should work if the compiler does not pad the allocation (stick extra space between the one-dimensional arrays). It might be safer to go with:

double *buf4;
buf4 = malloc(sizeof(double[3][5]));
/* error checking */
but either way the trick comes at dereferencing time. You can't write buf[i][j] because buf has the wrong type. Nor can you use

double **hdl4 = (double**)buf;
hdl4[2][3] = 0; /* Wrong! */
because the compiler expects hdl4 to be the address of an address of a double. Nor can you use double incomplete_ary4[][]; because this is an error;

So what can you do?

Do the row and column arithmetic yourself
Allocate and do the work in a function
Use an array of pointers (the mechanism qrdl is talking about)
Do the math yourself
Simply compute memory offset to each element like this:

  for (i=0; i<3; ++i){
     for(j=0; j<3; ++j){
        buf3[i * 5 + j] = someValue(i,j); /* Don't need to worry about 
                                             padding in this case */
     }
  }
Allocate and do the work in a function
Define a function that takes the needed size as an argument and proceed as normal

void dary(int x, int y){
  double ary4[x][y];
  ary4[2][3] = 5;
}
Of course, in this case ary4 is a local variable and you can not return it: all the work with the array must be done in the function you call of in functions that it calls.

An array of pointers
Consider this:

double **hdl5 = malloc(3*sizeof(double*));
/* Error checking */
for (i=0; i<3; ++i){
   hdl5[i] = malloc(5*sizeof(double))
   /* Error checking */
}
Now hdl5 points to an array of pointers each of which points to an array of doubles. The cool bit is that you can use the two-dimensional array notation to access this structure---hdl5[0][2] gets the middle element of the first row---but this is none-the-less a different kind of object than a two-dimensional array declared by double ary[3][5];.

This structure is more flexible then a two dimensional array (because the rows need not be the same length), but accessing it will generally be slower and it requires more memory (you need a place to hold the intermediate pointers).

Note that since I haven't setup any guards you'll have to keep track of the size of all the arrays yourself.

Arithmetic
c provides no support for vector, matrix or tensor math, you'll have to implement it yourself, or bring in a library.

Multiplication by a scaler and addition and subtraction of arrays of the same rank are easy: just loop over the elements and perform the operation as you go. Inner products are similarly straight forward.

Outer products mean more loops.

