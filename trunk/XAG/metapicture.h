#ifndef METAPICTURE_H_INCLUDED
#define METAPICTURE_H_INCLUDED

struct metapicture {
    long int size;
    int width;
    int height;
    char name[20];

};

struct metapicture getMetaPicture(int ,int , char[20]);



#endif // METAPICTURE_H_INCLUDED
