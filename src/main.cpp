#include "matrix2d.h"

int main()
{
    // create a few matrices with initialization list
    Matrix2D a {{1.5, 2.3, 3.1}, {5.8, 6.4, 4.2}, {4.3, 8.5, 4.7}};
    // missing values ​​are filled with zeros
    Matrix2D b {{0.2, 1.0, 3.1}, {6.6, 7.3, 4.4}, {8.8, 2.1}};
    Matrix2D c {{1.0, 3.3}, {6.8, 1.4}, {1.8, 9.2}, {6.4, 7.4}};
    
    std::cout << "Matrix a: " << std::endl;
    a.print();
    std::cout << "Matrix b: " << std::endl;
    b.print();
    std::cout << "Matrix c: " << std::endl;
    c.print();
 
    auto sum = a + b;
    std::cout << "Sum matrices a + b result: " << std::endl;
    sum.print();
    
    try
    {
        std::cout << "Sum matrices a + c result: " << std::endl;
        a + c;
    }
    catch( const exception& e )
    {
        cerr << e.what() << std::endl;
    }
    
    auto conc = a | b;
    std::cout << std::endl << "Сoncatenate matrices a | b result: " << std::endl;
    conc.print();

    try
    {
        std::cout << "Сoncatenate matrices a | c result: " << std::endl;
        a | c;
    }
    catch( const exception& e )
    {
        cerr << e.what() << std::endl;
    }
    
    std::cout << std::endl << "Iteration a: " << std::endl;
    for( auto elem : a )
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl << std::endl;
    
    std::cout << "Old-style iteration b: " << std::endl;
    for( auto iter = b.begin(); iter != b.end(); ++iter  )
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
    
    std::cout << std::endl << "Copy construcor a -> a1:" << std::endl;
    Matrix2D a1 = a;
    a1.print();
    if( !a.empty() )
    {
        std::cout << "Origin a is not empty" << std::endl;
    }
    
    std::cout << std::endl << "Copy operator b -> b1:" << std::endl;
    
    Matrix2D b1;
    b1 = b;
    b1.print();
    
    if( !b.empty() )
    {
        std::cout << "Origin b is not empty" << std::endl;
    }
    
    std::cout << std::endl << "Move construcor a1 -> a2:" << std::endl;
    Matrix2D a2 = std::move( a1 );
    a2.print();
    
    if( a1.empty() )
    {
        std::cout << "Origin a1 is empty" << std::endl;
    }
    
    std::cout << std::endl << "Move operator b -> b1:" << std::endl;
    
    Matrix2D b2;
    b2 = std::move( b1 );
    b2.print();
    
    if( b1.empty() )
    {
        std::cout << "Origin b1 is empty" << std::endl;
    }
    
    // Indexing in style a[i, j] will appear in C++23
    std::cout << std::endl << "Indexing in style a[{1, 1}] = " << a[{1, 1}] << std::endl;
    a[{1, 1}] = 33.8;
    std::cout << "Set a[{1, 1}] = 33.8" << std::endl;
    std::cout << "Updated matrix a:" << std::endl;
    a.print();
    
    try
    {
        std::cout << "Set a[{1, 5}] = 70.0" << std::endl;
        a[{1, 5}] = 70.0;
    }
    catch( const exception& e )
    {
        cerr << std::endl << e.what() << std::endl;
    }
    
    try
    {
        std::cout << "Set a[{5, 1}] = 10.0" << std::endl;
        a[{5, 1}] = 10.0;
    }
    catch( const exception& e )
    {
        cerr << std::endl << e.what() << std::endl;
    }
    
    std::cout << std::endl << "Indexing in style a[1][1] = " << a[1][1] << std::endl;
    a[1][1] = 14.1;
    std::cout << "Set a[1][1] = 14.1" << std::endl;
    std::cout << "Updated matrix a:" << std::endl;
    a.print();
    
    try
    {
        std::cout << "Set a[5][1] = 11.0" << std::endl;
        a[5][1] = 11.0;
    }
    catch( const exception& e )
    {
        cerr << std::endl << e.what() << std::endl;
    }
    
    return 0;
}
