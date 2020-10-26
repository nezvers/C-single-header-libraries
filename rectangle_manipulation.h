#ifndef RECTANGLE_MANIPULATION_H
#define RECTANGLE_MANIPULATION_H

#ifndef RECTANGLE_MANIPULATION_STANDALONE
    #include "raylib.h"
#else
    typedef struct Rectangle{
        float x;
        float y;
        float width;
        float height;
    }Rectangle;
    
    typedef struct Vector2{
        float x;
        float y;
    }Vector2;
#endif

#if defined(RECTANGLE_MANIPULATION_HEADER_ONLY)
    #define RECTMDEF static inline // Functions may be inlined, no external out-of-line definition
#else
    #if defined(__TINYC__)
        #define RECTMDEF static inline // plain inline not supported by tinycc
    #else
        #define RECTMDEF inline        // Functions may be inlined or external definition used
    #endif
#endif

#ifdef __cplusplus
    extern "C" {            // Prevents name mangling of functions
#endif
RECTMDEF void        RectRemoveTop       (Rectangle *rect, float amount);        //cut off top side and remove it
RECTMDEF void        RectRemoveBottom    (Rectangle *rect, float amount);        //cut off bottom side and remove it
RECTMDEF void        RectRemoveLeft      (Rectangle *rect, float amount);        //cut off left side and remove it
RECTMDEF void        RectRemoveRight     (Rectangle *rect, float amount);        //cut off right side and remove it
RECTMDEF Rectangle   RectCutTop          (Rectangle *rect, float amount);        //cut off top side and return it
RECTMDEF Rectangle   RectCutBottom       (Rectangle *rect, float amount);        //cut off bottom side and return it
RECTMDEF Rectangle   RectCutLeft         (Rectangle *rect, float amount);        //cut off left side and return it
RECTMDEF Rectangle   RectCutRight        (Rectangle *rect, float amount);        //cut off right side and return it
RECTMDEF Vector2     RectGetTopLeft      (Rectangle *rect);                      //get point of corner
RECTMDEF Vector2     RectGetTopRight     (Rectangle *rect);                      //get point of corner
RECTMDEF Vector2     RectGetBottomRight  (Rectangle *rect);                      //get point of corner
RECTMDEF Vector2     RectGetBottomLeft   (Rectangle *rect);                      //get point of corner
RECTMDEF void        RectSetCenter       (Rectangle *rect, float _x, float _y);  //moves rectangle to new center position
RECTMDEF void        RectExpand          (Rectangle *rect, float _x, float _y);  //expands rectangle from center & shrink with negative
RECTMDEF void        RectExpandEx        (Rectangle *rect, float l, float t, float r, float b); //expands rectangle from center & shrink with negative
RECTMDEF Rectangle   RectGetMarginArea   (Rectangle *rect, float l, float t, float r, float b); //returns rectangle with removed margins
RECTMDEF float       RectAspectRatio     (Rectangle *rect);                      //get aspect ratio of a Rectangle

#ifdef __cplusplus
    }
#endif

//------------------------------------------------------------------------------------
// Rectangle manipulation function implementation
//------------------------------------------------------------------------------------
#ifdef RECTANGLE_MANIPULATION_IMPLEMENTATION
void RectangleRemoveTop(Rectangle *rect, float amount){
    rect->y += amount;
    rect->height -= amount;
}
void RectangleRemoveBottom(Rectangle *rect, float amount){
    rect->height -= amount;
}
void RectangleRemoveLeft(Rectangle *rect, float amount){
    rect->x += amount;
    rect->width -= amount;
}
void RectangleRemoveRight(Rectangle *rect, float amount){
    rect->width -= amount;
}
Rectangle RectangleCutTop(Rectangle *rect, float amount){
    RectangleRemoveTop(rect, amount);
    return (Rectangle){rect->x, rect->y-amount, rect->width, amount};
}
Rectangle RectangleCutBottom(Rectangle *rect, float amount){
    RectangleRemoveBottom(rect, amount);
    return (Rectangle){rect->x, rect->y+rect->height, rect->width, amount};
}
Rectangle RectangleCutLeft(Rectangle *rect, float amount){
    RectangleRemoveLeft(rect, amount);
    return (Rectangle){rect->x-amount, rect->y, amount, rect->height};
}
Rectangle RectangleCutRight(Rectangle *rect, float amount){
    RectangleRemoveRight(rect, amount);
    return (Rectangle){rect->x+rect->width, rect->y, amount, rect->height};
}
Vector2 RectGetTopLeft(Rectangle *rect){
    return (Vector2){rect->x, rect->y};
}
Vector2 RectGetTopRight(Rectangle *rect){
    return (Vector2){rect->x +rect->width, rect->y};
}
Vector2 RectGetBottomLeft(Rectangle *rect){
    return (Vector2){rect->x, rect->y +rect->height};
}
Vector2 RectGetBottomRight(Rectangle *rect){
    return (Vector2){rect->x +rect->width, rect->y +rect->height};
}
void RectSetCenter(Rectangle *rect, float _x, float _y){
    rect->x = _x -rect->width *0.5;
    rect->y = _y -rect->height *0.5;
}
void RectExpand(Rectangle *rect, float _x, float _y){
    rect->x = rect->x -_x *0.5;
    rect->width = _x;
    rect->y = rect->y -_y *0.5;
    rect->height = _y;
}
void RectExpandEx(Rectangle *rect, float l, float t, float r, float b){
    rect->x = rect->x -l;
    rect->width = +l +r;
    rect->y = rect->y -t;
    rect->height = +t +b;
}
Rectangle RectGetMarginArea(Rectangle *rect, float l, float t, float r, float b){
    return (Rectangle){rect->x+l, rect->y+t, rect->width-l-r, rect->height-t-b};
}
float RectAspectRatio(Rectangle *rect){
    return rect->width / rect->height;
}
#endif // RECTANGLE_MANIPULATION_IMPLEMENTATION

#endif // RECTANGLE_MANIPULATION_H