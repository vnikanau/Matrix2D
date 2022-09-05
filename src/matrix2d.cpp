#include "matrix2d.h"
#include "exception.h"

Matrix2D::Matrix2D( const size_t numRows, const size_t numCols ) : _matrix( numRows * numCols ),
_rows{ numRows }, _cols{ numCols }
{
}

Matrix2D::Matrix2D( const initializer_list<initializer_list<type> > &inputList )
{
    _rows = inputList.size();
    
    auto maxCol = max_element( inputList.begin(),
                               inputList.end(),
                               [](auto const &lhs, auto const &rhs)
                               {
                                  return lhs.size() < rhs.size();
                               });
    _cols = maxCol->size();
    _matrix.resize( _rows * _cols );
    
    size_t row{0};
    for( const auto &subList : inputList )
    {
        size_t col{0};
        for( const auto &element : subList )
        {
            _matrix[_cols * row + (col++)] = element;
        }
        ++row;
    }
}

Matrix2D::Matrix2D( Matrix2D &&rmatrix ) : _matrix( std::move( rmatrix._matrix ) ),
                                           _rows( std::move( rmatrix._rows ) ),
                                           _cols( std::move( rmatrix._cols ) )
{
    rmatrix._rows = 0;
    rmatrix._cols = 0;
}

void Matrix2D::print() const
{
    printf( "matrix %zu x %zu\n", numRows(), numColumns() );
    for ( size_t row = 0; row < numRows(); row++ )
    {
        printf( "[ " );
        for ( size_t col = 0; col < numColumns(); col++ )
        {
            printf( "%.5f ", _matrix[row * numColumns() + col] );
        }
        printf( "]\n" );
    }
    printf( "\n" );
}

Matrix2D & Matrix2D::operator = ( Matrix2D && rmatrix )
{
    _matrix = std::move( rmatrix._matrix );
    _rows = std::move( rmatrix._rows );
    _cols = std::move( rmatrix._cols );
    rmatrix._rows = 0;
    rmatrix._cols = 0;
    return *this;
}

// Horizontally concatenate matrix with another matrix, rmatrix
Matrix2D Matrix2D::operator | ( const Matrix2D & rmatrix )
{
    Matrix2D result( _rows, ( _cols + rmatrix._cols ) ); // copy matrix intro result
    if ( numRows() != rmatrix.numRows() )
    {
        throw Exception( "Row sizes do not correspond, cannot concatenate matrices!" );
    }
    else
    {
        for( size_t row = 0; row < _rows; ++row )
        {
            size_t indRes = row * (_cols + rmatrix._cols);
            size_t indLeft = row * _cols;
            size_t indRigth = row * rmatrix._cols;
            
            for( size_t col = 0; col < _cols; ++col )
            {
                result._matrix[indRes + col] = _matrix[indLeft + col];
            }
            for( size_t col = 0; col < rmatrix._cols; ++col )
            {
                result._matrix[indRes + _cols + col] = rmatrix._matrix[indLeft + col];
            }
        }
    }
    
    return result;
}

type & Matrix2D::operator [] ( const pair<size_t, size_t> ind )
{
    if ( numRows() <= ind.first )
    {
        throw Exception( "Row index out of range!" );
    }

    if ( numColumns() <= ind.second )
    {
        throw Exception( "Column index out of range!" );
    }
    
    return _matrix.at( ind.first * numColumns() + ind.second );
}

std::span<type> Matrix2D::operator [] ( const size_t row )
{
    if ( numRows() <= row )
    {
        throw Exception( "Row index out of range!" );
    }
    
    return std::span( _matrix.data() + row * _cols, _cols );
}

Matrix2D Matrix2D::operator + ( const Matrix2D & rhs )
{
    auto result = *this; // copy matrix intro result
    if ( rhs.numRows() != numRows() || rhs.numColumns() != numColumns() )
    {
        // throw error if rhs column or row size does not match matrix
        throw Exception( "Row of column size mismatch, won't add matrix" );
    }
    // perform matrix addition
    for ( size_t i = 0; i < _matrix.size(); i++ )
    {
        result._matrix[i] += rhs._matrix[i];
    }

    return result;
}

Matrix2D::iterator Matrix2D::begin()
{
    return Matrix2D::iterator( _matrix.begin() );
}

Matrix2D::iterator Matrix2D::end()
{
    return Matrix2D::iterator( _matrix.end() );
}

Matrix2D::iterator::iterator( vector<type>::iterator initLoc )
{
    _current = initLoc;
}
    
Matrix2D::iterator& Matrix2D::iterator::operator++()
{
    ++_current;
    return *this;
}

Matrix2D::iterator Matrix2D::iterator::operator++( int )
{
    return iterator( _current++ );
}

Matrix2D::iterator& Matrix2D::iterator::operator--()
{
    --_current;
    return *this;
}

Matrix2D::iterator Matrix2D::iterator::operator--( int )
{
    return iterator( _current-- );
}

bool Matrix2D::iterator::operator!=( const iterator& rhs ) const
{
    return _current != rhs._current;
}

type& Matrix2D::iterator::operator*()
{
    return *_current;
}

