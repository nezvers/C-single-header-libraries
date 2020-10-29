#ifndef MATRIX_LIB_H
#define MATRIX_LIB_H
//Simple Matrix library intended for Neural Network basics
#include <stdlib.h>
#include <stdio.h>

typedef struct MatrixF{
    int collumns;
    int rows;
    float *data;
}MatrixF;

MatrixF CreateMatrixF(int collumns, int rows);
void DestroyMatrixF(MatrixF mat);

MatrixF TransposeMatrixF(MatrixF mat);
MatrixF MatrixFAdd(MatrixF mat, float i);
MatrixF MatrixFScaler(MatrixF mat, float i);
MatrixF MatrixFSum(MatrixF mat, MatrixF mat2);
MatrixF MatrixFSubtract(MatrixF mat, MatrixF mat2);

#endif //MATRIX_LIB_H



#if defined MATRIX_LIB_IMPLEMENTATION
//Float matrix
MatrixF CreateMatrixF(int collumns, int rows){
    float *data = (float*)calloc( collumns * rows, sizeof(float));
    MatrixF mat = {collumns, rows, data};
    return mat;
}

void DestroyMatrixF(MatrixF mat){
    free(mat.data);
}

MatrixF TransposeMatrixF(MatrixF mat){
    MatrixF newMat = CreateMatrixF(mat.rows, mat.collumns);
    for(int y = 0; y < mat.rows; y++){
        for(int x = 0; x < mat.collumns; x++){
            newMat.data[x*newMat.collumns+y] = mat.data[x+y*mat.collumns];
        }
    }
    DestroyMatrixF(mat);
    return newMat;
}

MatrixF MatrixFAdd(MatrixF mat, float i){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.collumns; x++){
            mat.data[x+y*mat.collumns] += i;
        }
    }
    return mat;
}

MatrixF MatrixFScaler(MatrixF mat, float i){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.collumns; x++){
            mat.data[x+y*mat.collumns] *= i;
        }
    }
    return mat;
}

MatrixF MatrixFSum(MatrixF mat, MatrixF mat2){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.collumns; x++){
            mat.data[x+y*mat.collumns] += mat2.data[x+y*mat.collumns];
        }
    }
    return mat;
}

MatrixF MatrixFSubtract(MatrixF mat, MatrixF mat2){
    for( int y = 0; y < mat.rows; y++){
        for(int x =0; x < mat.collumns; x++){
            mat.data[x+y*mat.collumns] -= mat2.data[x+y*mat.collumns];
        }
    }
    return mat;
}

MatrixF MatrixFMultiply(MatrixF mat1, MatrixF mat2){
    MatrixF mat3 = CreateMatrixF(mat2.collumns, mat1.rows);
    for(int i = 0; i < mat3.rows; ++i)
        for(int j = 0; j < mat3.collumns; ++j)
            for(int k = 0; k < mat1.collumns; ++k)
            {
                mat3.data[j + i * mat3.collumns] += mat1.data[k + i * mat1.collumns] * mat2.data[k * mat2.collumns + j];
            }
    return mat3;
}



#endif //MATRIX_LIB_IMPLEMENTATION
