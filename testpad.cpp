#include <iostream>

using namespace std;

int main()
{
   int x = 42;
   int *y = &x;
   *y = x * 2;
   cout << x << " " << *y << endl
        << endl;

   int *pointer;
   cout << "int *pointer; " << endl
        << "          // It is currently just an \"empty\" variable for an address located in the address labeled *pointer" << endl;
   int integer = 10;
   cout << "int integer = 10;" << endl;
   pointer = &integer;
   cout << "pointer = &integer" << endl
        << "          // This makes it so the address labeled *pointer now has the contents of &integer." << endl
        << "          // This means that now the \"empty\" part of pointer is now filled with the address of integer" << endl
        << endl;
   cout << "cout << pointer (The contents of pointer) is " << pointer << endl
        << "cout << &pointer (The memory address of pointer) is " << &pointer << endl
        << "cout << *pointer (The value of the memory address stored in pointer) is " << *pointer << endl;
}