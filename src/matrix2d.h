#ifndef _MATRIX2D_H
#define _MATRIX2D_H

#include <iostream>
#include <vector>
#include <span>

using namespace std;

template<typename NumericType>
concept Numeric = std::is_arithmetic<NumericType>::value;

template<Numeric T>
class Matrix2D
{
private:
    size_t _rows;
    size_t _cols;
    vector<T> _matrix;
    
public:
    
    Matrix2D( const size_t numRows = 0, const size_t numCols = 0 );
    explicit Matrix2D( const initializer_list<initializer_list<T> > & );
    Matrix2D( const Matrix2D & ) = default;
    Matrix2D( Matrix2D && );
     
    inline bool empty() const { return _matrix.empty(); }
    inline size_t numRows() const { return _rows; }
    inline size_t numColumns() const { return _cols; }
    void print() const;

    /* Operator overloads */
    T & operator [] ( const pair<size_t, size_t> );
    span<T> operator [] ( const size_t res );
    Matrix2D & operator = ( const Matrix2D & ) = default;
    Matrix2D & operator = ( Matrix2D && );
    Matrix2D operator + ( const Matrix2D & );
    Matrix2D operator | ( const Matrix2D & );

    class iterator
    {
    private:
        typename vector<T>::iterator _current;

    public:
        iterator( typename vector<T>::iterator initLoc );
        iterator& operator++();
        iterator operator++( int );
        iterator& operator--();
        iterator operator--( int );
        bool operator!=( const iterator& rhs ) const;
        T& operator*();
    };

    iterator begin();
    iterator end();
};

#endif // _MATRIX2D_H
