#ifndef NN_ACTIVATION_FUNCTIONS_H
#define NN_ACTIVATION_FUNCTIONS_H

#include <math.h>

#if defined(__TINYC__)
    #define NNACTDEF static inline // plain inline not supported by tinycc
#else
    #define NNACTDEF inline        // Functions may be inlined or external definition used
#endif

#ifdef __cplusplus
    extern "C" {            // Prevents name mangling of functions
#endif

// Hyperbolic Tanjant Function
NNACTDEF float _tanh(float x, int derivative);
//ReLU Function
NNACTDEF float re(float x);
//Leaky ReLy
NNACTDEF float lr(float x);
//ReLu6
NNACTDEF float re6(float x);
// half swish
NNACTDEF float h_swish(float x);
//Fast Sigmoid function
NNACTDEF float fast_sigmoid(float x);
//Sigmoid function
NNACTDEF float sigmoid(float x);
//swish
NNACTDEF float swish(float x);
//Gradient value
NNACTDEF float dsigmoid(float x);
#ifdef __cplusplus
    }
#endif

#endif // NN_ACTIVATION_FUNCTIONS_H

#ifdef NN_ACTIVATION_IMPLEMENTATION
// Hyperbolic Tanjant Function
float _tanh(float x, int derivative){
    if(derivative){
        return (1 - (x*x));
    }
    return tanhf(x);
}

//ReLU Function
float re(float x){
    return fmax(0.0, x);
}

//Leaky ReLy
float lr(float x){
    return fmax(x*0.01f, x);
}

//ReLu6
float re6(float x){
    return fmin(fmax(0.0f, x), 6.0f);
}

// half swish
float h_swish(float x){
    return x * (re6(x+3)/ 6.0f);
}

//Fast Sigmoid function
float fast_sigmoid(float x){
    return x / (1+fabsf(x));
}

//Sigmoid function
float sigmoid(float x){
    return (1/(1+expf(-x)));
}

//swish
float swish(float x){
    return sigmoid(x) *x;
}

//For gradient
float dsigmoid(float x) {
  return x * (1-x);
}
#endif
