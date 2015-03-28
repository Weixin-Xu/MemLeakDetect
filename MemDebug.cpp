#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <new>

#include <vector>
#include <algorithm>
using namespace std;



#define PATH_LEN 128
class ptr_info {
    public:
    void * ptr;
    char fileName[PATH_LEN];
    int line;
};

class Track {
    vector<ptr_info> info;
    public:
    ~Track() {
#ifdef MEMDEBUG
        vector<ptr_info>::iterator iter;
        cout << "Memory Leak: " << endl;
        for (iter = info.begin(); iter != info.end(); iter++) {
            cout << iter->ptr 
                << " " << iter->fileName 
                << " " << iter->line
                << endl;
        }
#endif
    }
    void add(void *p, const char * fileName, int line) {
        ptr_info item;
        item.ptr = p;
        strcpy(item.fileName, fileName);
        item.line = line;
        info.push_back(item);
    }

    void del(void * pointer) {
        vector<ptr_info>::iterator iter;
        for (iter = info.begin(); iter != info.end();) {
            if (iter->ptr == pointer) {
                iter = info.erase(iter);
            }
            else {
                iter++;
            }
        }
    }

    void print(void) {
        
    }

};

Track t;

void * operator new(size_t size, const char* file, int line) 
{
    void *p =  malloc(size);
    t.add(p, file, line);
    return p;
}

void * operator new ( size_t size, const std::nothrow_t & nothrow_value, const char * file, int line) throw() 
{
    void * p = malloc(size);
    t.add(p, file, line);
    return p;
}

void * operator new[] (size_t size, const char * file, int line)
{
    return operator new (size, file, line);
}

void operator delete(void * pointer) throw (){
    t.del(pointer);
    return free(pointer);
}

void operator delete[] (void * pointer) throw (){
    return operator delete ( pointer );
}

void * malloc( size_t size, const char * file, int line)
{
    void * p = malloc(size);
    t.add(p, file, line);
    return p;
}

void debug_free( void * p)
{
    t.del(p);
    return free(p);
}
