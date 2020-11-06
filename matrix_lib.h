#ifndef MATRIX_LIB_H
#define MATRIX_LIB_H
//Simple Matrix library intended for Neural Network basics
#include <stdlib.h>
#include <stdio.h>

typedef float matType; //one place to change type of matrix

typedef struct Matrix{
    int columns;
    int rows;
    matType *data;
}Matrix;

Matrix MatrixCreate(int columns, int rows);
void    MatrixDestroy(Matrix mat);

void    MatrixAdd(Matrix mat, matType i);
void    MatrixScaler(Matrix mat, matType i);
void    MatrixSum(Matrix mat, Matrix mat2);
void    MatrixSubtract(Matrix mat, Matrix mat2);
void    MatrixMultiplyElements(Matrix mat, Matrix mat2);
Matrix MatrixMultiply(Matrix mat1, Matrix mat2);
Matrix MatrixProduct(Matrix mat1, Matrix mat2);
Matrix MatrixTransposed(Matrix mat);
Matrix MatrixCreateColumnFromArray(matType* _data, int size);
Matrix MatrixCopy(Matrix mat);
void    MatrixPrint(Matrix mat);
#endif //MATRIX_LIB_H



#if defined MATRIX_LIB_IMPLEMENTATION
//Float matrix
Matrix MatrixCreate(int columns, int rows){
    matType *data = (matType*)calloc( columns * rows, sizeof(matType));
    Matrix mat = {columns, rows, data};
    return mat;
}

void MatrixDestroy(Matrix mat){
    free(mat.data);
}

Matrix MatrixTransposed(Matrix mat){
    Matrix newMat = MatrixCreate(mat.rows, mat.columns);
    for(int y = 0; y < mat.rows; y++){
        for(int x = 0; x < mat.columns; x++){
            newMat.data[x*newMat.columns+y] = mat.data[x+y*mat.columns];
        }
    }
    return newMat;
}

void    MatrixAdd(Matrix mat, matType i){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.columns; x++){
            mat.data[x+y*mat.columns] += i;
        }
    }
}

void    MatrixScaler(Matrix mat, matType i){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.columns; x++){
            mat.data[x+y*mat.columns] *= i;
        }
    }
}

void    MatrixSum(Matrix mat, Matrix mat2){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.columns; x++){
            mat.data[x+y*mat.columns] += mat2.data[x+y*mat.columns];
        }
    }
}

void    MatrixSubtract(Matrix mat, Matrix mat2){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.columns; x++){
            mat.data[x+y*mat.columns] -= mat2.data[x+y*mat.columns];
        }
    }
}

void    MatrixMultiplyElements(Matrix mat, Matrix mat2){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.columns; x++){
            mat.data[x+y*mat.columns] -= mat2.data[x+y*mat.columns];
        }
    }
}

Matrix MatrixMultiply(Matrix mat1, Matrix mat2){
    Matrix mat3 = MatrixCreate(mat2.columns, mat1.rows);
    for(int i = 0; i < mat3.rows; ++i)
        for(int j = 0; j < mat3.columns; ++j)
            for(int k = 0; k < mat1.columns; ++k)
            {
                mat3.data[j + i * mat3.columns] += mat1.data[k + i * mat1.columns] * mat2.data[k * mat2.columns + j];
            }
    return mat3;
}

Matrix MatrixProduct(Matrix mat1, Matrix mat2){
    Matrix mat3 = MatrixCreate(mat2.columns, mat1.rows);
    for(int i = 0; i < mat3.rows; ++i)
        for(int j = 0; j < mat3.columns; ++j){
            matType summ = (matType)0;
            for(int k = 0; k < mat1.columns; ++k)
            {
                summ += mat1.data[k + i * mat1.columns] * mat2.data[k * mat2.columns + j];
            }
            mat3.data[j + i * mat3.columns] = summ;
        }
    return mat3;
}

Matrix MatrixCreateColumnFromArray(matType* _data, int size){
    matType* data = (matType*)calloc( size, sizeof(matType));
    Matrix mat = {1, size, data};
    for(int i=0; i < size; i++){
        mat.data[i] = _data[i];
    }
    return mat;
}

Matrix MatrixCopy(Matrix mat){
    matType* data = (matType*)calloc(mat.columns * mat.rows, sizeof(matType));
    Matrix newMat = {mat.columns, mat.rows, data};
    return newMat;
}

void MatrixPrint(Matrix mat){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.columns; x++){
            printf("%f ", mat.data[x+y*mat.columns]);
        }
        printf("\n");
    }
}

#endif //MATRIX_LIB_IMPLEMENTATION
