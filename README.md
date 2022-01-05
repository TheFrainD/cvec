# cvec

A simple vector library for C. It has simillar interface to C++ stl vector.
```c
#include  <stdio.h>

#include  <cvec.h>

int  main(void)  {
	cvec  vec  =  cvec_create(int);

	cvec_push_back(vec, 10);
	cvec_push_back(vec, 57);
	cvec_push_back(vec, -75);
	cvec_push_back(vec, 11);
	cvec_push_back(vec, 5);
	cvec_pop_back(vec);
	cvec_insert(vec, 4, 42);

	cvec_destroy(vec);
	return  0;
}
```
  

## Usage

### Initializing
You can create vector like this:

```c
cvec vec =  cvec_create(int);
```
You can create vectors of different type by specifing it as an argument in `cvec_create` :
```c
// int vector
cvec ivec = cvec_create(int);

// float vector
cvec fvec = cvec_create(float);

// char vector
cvec chvec = cvec_create(char);
```
### Destroying
Every vector must be destroy after using with `cvec_destoy` :
```c
cvec_destroy(vec);
```
### Adding and accessing elements
To add element to a vector you need to use  `cvec_push_back` or `cvec_insert` and to access element by its index you need to use `cvec_at` :
```c
cvec  vec  =  cvec_create(int);

// simply adds an element to vector's end
cvec_push_back(vec, 42);
cvec_push_back(vec, 3);

// inserts an element at specified index
cvec_insert(vec, 1, 11);

// you also need to specify type of an element you want to access
printf("%d\n", cvec_at(vec, 1, int));

// not a part of a library
vec_print(vec);

cvec_destroy(vec);
```
Output:
```
42 11 3
11
```
### Removing elements
To remove an element you can use `cvec_pop_back` or `cvec_erase`:
```c
cvec  vec  =  cvec_create(int);

cvec_push_back(vec,  42);
cvec_push_back(vec,  3);
cvec_insert(vec,  1,  11);
vec_print(vec);

// removes last element
cvec_pop_back(vec);
vec_print(vec);

// removes element at specified index
cvec_erase(vec,  0);
vec_print(vec);

cvec_destroy(vec);
```
Output:
```
42 11 3 
42 11 
11 
```

### Other
```c
// returns vector's size
cvec_size(vec);

// sets elements value
// works as "type[index] = value"
cvec_set_at(vec, index, value);
```