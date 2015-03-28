#ifndef __MEMDEBUG_H__
#define __MEMDEBUG_H__
#include <cstdio>

#ifdef MEMDEBUG

void * operator new(size_t size, const char * file, int line);
void * operator new [] (size_t size, const char * file, int line);
void * operator new( size_t size, const std::nothrow_t& nothrow_value, const char * file, int line) throw(); 
#define DEBUG_NEW new(__FILE__, __LINE__)
#define new DEBUG_NEW

void operator delete(void * pointer) throw ();
void operator delete [] (void * pointer) throw ();

void * malloc (size_t size, const char * file, int line);
//#define DEBUG_MALLOC malloc(__FILE__, __LINE__)
//#define malloc DEBUG_MALLOC
#define malloc(x) malloc((x), __FILE__, __LINE__)

void debug_free(void *p);
#define free(p) debug_free((p))

#endif
#endif
