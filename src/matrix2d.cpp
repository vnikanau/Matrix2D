#include "matrix2d.h"
#include "exception.h"

template <Numeric T>
Matrix2D<T>::Matrix2D( const size_t numRows, const size_t numCols ) : _matrix( numRows * numCols ), _rows{ numRows }, _cols{ numCols }
{
}

template <Numeric T>
Matrix2D<T>::Matrix2D( const initializer_list<initializer_list<T> > &inputList )
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

template <Numeric T>
Matrix2D<T>::Matrix2D( Matrix2D<T> &&rmatrix ) : _matrix( std::move( rmatrix._matrix ) ),
                                                 _rows( std::move( rmatrix._rows ) ),
                                                 _cols( std::move( rmatrix._cols ) )
{
    rmatrix._rows = 0;
    rmatrix._cols = 0;
}

template <Numeric T>
void Matrix2D<T>::print() const
{
    cout << "matrix " << numRows() << " x " << numColumns() << endl;
    for ( size_t row = 0; row < numRows(); row++ )
    {
        cout << "[ ";
        for ( size_t col = 0; col < numColumns(); col++ )
        {
            auto val = _matrix[row * numColumns() + col];
            cout << val << " ";
        }
        cout << "]" << endl;
    }
    cout << endl;
}

template <Numeric T>
Matrix2D<T> & Matrix2D<T>::operator = ( Matrix2D<T> && rmatrix )
{
    _matrix = std::move( rmatrix._matrix );
    _rows = std::move( rmatrix._rows );
    _cols = std::move( rmatrix._cols );
    rmatrix._rows = 0;
    rmatrix._cols = 0;
    return *this;
}

// Horizontally concatenate matrix with another matrix, rmatrix
template <Numeric T>
Matrix2D<T> Matrix2D<T>::operator | ( const Matrix2D<T> & rmatrix )
{
    Matrix2D<T> result( _rows, ( _cols + rmatrix._cols ) ); // copy matrix intro result
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

template <Numeric T>
T & Matrix2D<T>::operator [] ( const pair<size_t, size_t> ind )
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

template <Numeric T>
typename std::span<T> Matrix2D<T>::operator [] ( const size_t row )
{
    if ( numRows() <= row )
    {
        throw Exception( "Row index out of range!" );
    }
    
    return std::span( _matrix.data() + row * _cols, _cols );
}

template <Numeric T>
Matrix2D<T> Matrix2D<T>::operator + ( const Matrix2D<T> & rhs )
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

template <Numeric T>
Matrix2D<T>::iterator::iterator( typename vector<T>::iterator initLoc )
{
    _current = initLoc;
}

template <Numeric T>
typename Matrix2D<T>::iterator Matrix2D<T>::begin()
{
    return Matrix2D::iterator( _matrix.begin() );
}

template <Numeric T>
typename Matrix2D<T>::iterator Matrix2D<T>::end()
{
    return Matrix2D<T>::iterator( _matrix.end() );
}
   
template <Numeric T>
typename Matrix2D<T>::iterator& Matrix2D<T>::iterator::operator++()
{
    ++_current;
    return *this;
}

template <Numeric T>
typename Matrix2D<T>::iterator Matrix2D<T>::iterator::operator++( int )
{
    return iterator( _current++ );
}

template <Numeric T>
typename Matrix2D<T>::iterator& Matrix2D<T>::iterator::operator--()
{
    --_current;
    return *this;
}

template <Numeric T>
typename Matrix2D<T>::iterator Matrix2D<T>::iterator::operator--( int )
{
    return iterator( _current-- );
}

template <Numeric T>
bool Matrix2D<T>::iterator::operator!=( const iterator& rhs ) const
{
    return _current != rhs._current;
}

template <Numeric T>
T& Matrix2D<T>::iterator::operator*()
{
    return *_current;
}

template class Matrix2D<float>;
template class Matrix2D<double>;
template class Matrix2D<int>;
template class Matrix2D<long>;
template class Matrix2D<long long>;
template class Matrix2D<unsigned int>;
template class Matrix2D<unsigned long>;
template class Matrix2D<unsigned long long>;

