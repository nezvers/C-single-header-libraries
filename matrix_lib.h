#ifndef MATRIX_LIB_H
#define MATRIX_LIB_H
//Simple Matrix library intended for Neural Network basics
#include <stdlib.h>
#include <stdio.h>

typedef struct MatrixF{
    int columns;
    int rows;
    float *data;
}MatrixF;

MatrixF MatrixFCreate(int columns, int rows);
void    MatrixFDestroy(MatrixF mat);

MatrixF MatrixFTransposed(MatrixF mat);
void    MatrixFAdd(MatrixF mat, float i);
void    MatrixFScaler(MatrixF mat, float i);
void    MatrixFSum(MatrixF mat, MatrixF mat2);
void    MatrixFSubtract(MatrixF mat, MatrixF mat2);
void    MatrixFMultiplyElements(MatrixF mat, MatrixF mat2);
MatrixF MatrixFMultiply(MatrixF mat1, MatrixF mat2);
MatrixF MatrixFProduct(MatrixF mat1, MatrixF mat2);
MatrixF MatrixFCreateColumnFromArray(float* _data, int size);
MatrixF MatrixFCopy(MatrixF mat);
void    MatrixFPrint(MatrixF mat);
#endif //MATRIX_LIB_H



#if defined MATRIX_LIB_IMPLEMENTATION
//Float matrix
MatrixF MatrixFCreate(int columns, int rows){
    float *data = (float*)calloc( columns * rows, sizeof(float));
    MatrixF mat = {columns, rows, data};
    return mat;
}

void MatrixFDestroy(MatrixF mat){
    free(mat.data);
}

MatrixF MatrixFTransposed(MatrixF mat){
    MatrixF newMat = MatrixFCreate(mat.rows, mat.columns);
    for(int y = 0; y < mat.rows; y++){
        for(int x = 0; x < mat.columns; x++){
            newMat.data[x*newMat.columns+y] = mat.data[x+y*mat.columns];
        }
    }
    return newMat;
}

void    MatrixFAdd(MatrixF mat, float i){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.columns; x++){
            mat.data[x+y*mat.columns] += i;
        }
    }
}

void    MatrixFScaler(MatrixF mat, float i){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.columns; x++){
            mat.data[x+y*mat.columns] *= i;
        }
    }
}

void    MatrixFSum(MatrixF mat, MatrixF mat2){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.columns; x++){
            mat.data[x+y*mat.columns] += mat2.data[x+y*mat.columns];
        }
    }
}

void    MatrixFSubtract(MatrixF mat, MatrixF mat2){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.columns; x++){
            mat.data[x+y*mat.columns] -= mat2.data[x+y*mat.columns];
        }
    }
}

void    MatrixFMultiplyElements(MatrixF mat, MatrixF mat2){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.columns; x++){
            mat.data[x+y*mat.columns] -= mat2.data[x+y*mat.columns];
        }
    }
}

MatrixF MatrixFMultiply(MatrixF mat1, MatrixF mat2){
    MatrixF mat3 = MatrixFCreate(mat2.columns, mat1.rows);
    for(int i = 0; i < mat3.rows; ++i)
        for(int j = 0; j < mat3.columns; ++j)
            for(int k = 0; k < mat1.columns; ++k)
            {
                mat3.data[j + i * mat3.columns] += mat1.data[k + i * mat1.columns] * mat2.data[k * mat2.columns + j];
            }
    return mat3;
}

MatrixF MatrixFProduct(MatrixF mat1, MatrixF mat2){
    MatrixF mat3 = MatrixFCreate(mat2.columns, mat1.rows);
    for(int i = 0; i < mat3.rows; ++i)
        for(int j = 0; j < mat3.columns; ++j){
            float summ = 0.0f;
            for(int k = 0; k < mat1.columns; ++k)
            {
                summ += mat1.data[k + i * mat1.columns] * mat2.data[k * mat2.columns + j];
            }
            mat3.data[j + i * mat3.columns] = summ;
        }
    return mat3;
}

MatrixF MatrixFCreateColumnFromArray(float* _data, int size){
    float* data = (float*)calloc( size, sizeof(float));
    MatrixF mat = {1, size, data};
    for(int i=0; i < size; i++){
        mat.data[i] = _data[i];
    }
    return mat;
}

MatrixF MatrixFCopy(MatrixF mat){
    float* data = (float*)calloc(mat.columns * mat.rows, sizeof(float));
    MatrixF newMat = {mat.columns, mat.rows, data};
    return newMat;
}

void MatrixFPrint(MatrixF mat){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.columns; x++){
            printf("%f ", mat.data[x+y*mat.columns]);
        }
        printf("\n");
    }
}

#endif //MATRIX_LIB_IMPLEMENTATION
