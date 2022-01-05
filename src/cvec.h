/*
 * Copyright (c) 2022 Dmytro Zykov
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS 
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

#ifndef CVEC_H_
#define CVEC_H_

#define CVEC_INITIAL_CAPACITY 2
#define CVEC_RESIZE_FACTOR 1.6

typedef struct _cvec *cvec;

cvec _cvec_create(int capacity, int stride);
void _cvec_push_back(cvec vec, void *value_ptr);
void _cvec_insert(cvec vec, int index, void *value_ptr);
void _cvec_set_at(cvec vec, int index, void *value_ptr);
void *_cvec_at(cvec vec, int index);
void cvec_destroy(cvec vec);
int cvec_size(cvec vec);
void cvec_pop_back(cvec vec);
void cvec_erase(cvec vec, int index);

#define cvec_create(type) _cvec_create(CVEC_INITIAL_CAPACITY, sizeof(type))
#define cvec_push_back(vec, value) { typeof(value) e = value;_cvec_push_back(vec, &e); }
#define cvec_insert(vec, index, value) { typeof(value) e = value;_cvec_insert(vec, index, &e); }
#define cvec_set_at(vec, index, value) { typeof(value) e = value;_cvec_set_at(vec, index, &e); }
#define cvec_at(vec, index, type) (*((type *)(_cvec_at(vec, index))))

#endif // !CVEC_H_
