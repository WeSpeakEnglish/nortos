#ifndef _NORTOS_H
#define _NORTOS_H

typedef void(*fP)(void);

class fQ {
private:
    int first;
    int last;
    fP * fQueue;
    int lengthQ;
public:
    fQ(int sizeQ);
    ~fQ();
    int push(fP);
    int pull(void);
};

#endif