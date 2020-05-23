//
//  Test.cpp
//  DS_C++ Project
//
//  Created by Debbie on 2020/3/16.
//  Copyright © 2020 Debbie. All rights reserved.
//


#include <iostream>

using namespace std;

int foo = 0;
int fuck = 5;

class Base {
public:
    Base() {cout << fuck;}
};

class A: public Base {
private:
    int foo;
public:
    A() {foo = 1; cout << foo;}
friend class B;

};

class B: public Base{
public:
    void show(A& a) {cout << a.foo << foo;}
};



int main()
{
    A a;
    B b;
    b.show(a);
    return 0;
}
