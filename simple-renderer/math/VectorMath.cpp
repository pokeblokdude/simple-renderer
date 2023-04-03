#include "VectorMath.h"
#include <cmath>

// cross product of two vectors
vec3 cross(vec3 a, vec3 b) {
  return vec3{
    a.y*b.z - a.z*b.y,
    a.z*b.x - a.x*b.z,
    a.x*b.y - a.y*b.x
  };
}

// convert from radians to degrees
float degrees(float r) {
  return r * M_RAD_TO_DEG;
}

// CREDIT: https://developer.download.nvidia.com/cg/determinant.html
// return determinant of square matrix
float determinant(mat2x2 m) {
  return m.m00*m.m11 - m.m01*m.m10;
}
float determinant(mat3x3 m) {
  return dot(
    vec3{m.m00, m.m01, m.m02},
      vec3{m.m11, m.m12, m.m10} * vec3{m.m22, m.m20, m.m21}
      - vec3{m.m12, m.m10, m.m11} * vec3{m.m21, m.m22, m.m20}
  );
}
float determinant(mat4x4 m) {
  return dot(
    vec4{1, -1, 1, -1} * vec4{m.m00, m.m01, m.m02, m.m03},
      vec4{m.m11, m.m12, m.m13, m.m10} *
        (vec4{m.m22, m.m23, m.m20, m.m21} * vec4{m.m33, m.m30, m.m31, m.m32}
        - vec4{m.m23, m.m20, m.m21, m.m22} * vec4{m.m32, m.m33, m.m30, m.m31})
      + vec4{m.m12, m.m13, m.m10, m.m11} *
        (vec4{m.m23, m.m20, m.m21, m.m22} * vec4{m.m31, m.m32, m.m33, m.m30}
        - vec4{m.m21, m.m22, m.m23, m.m20} * vec4{m.m33, m.m30, m.m31, m.m32})
      + vec4{m.m13, m.m10, m.m11, m.m12} *
        (vec4{m.m21, m.m22, m.m23, m.m20} * vec4{m.m32, m.m33, m.m30, m.m31}
        - vec4{m.m22, m.m23, m.m20, m.m21} * vec4{m.m31, m.m32, m.m33, m.m30})
  );
}

// CREDIT: https://developer.download.nvidia.com/cg/dot.html
// dot product of two vectors
float dot(vec2 a, vec2 b) {
  return a.x*b.x + a.y*b.y;
}
float dot(vec3 a, vec3 b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}
float dot(vec4 a, vec4 b) {
  return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

// CREDIT: https://developer.download.nvidia.com/cg/inverse.html
// returns the matrix inverse of A
mat2x2 inverse(mat2x2 A) {
  mat2x2 C;

  float det = determinant(A);
  C.m00 = A.m11 / det;
  C.m01 = -A.m01 / det;
  C.m10 = -A.m10 / det;
  C.m11 = A.m00 / det;

  return C;
}
mat3x3 inverse(mat3x3 A) {
  mat3x3 C;

  float det = determinant(A);
  C.m00 = (A.m11*A.m22 - A.m12*A.m21) / det;  // A
  C.m01 = -(A.m01*A.m22 - A.m02*A.m21) / det; // D
  C.m02 = (A.m01*A.m12 - A.m02*A.m11) / det;  // G
  C.m10 = -(A.m10*A.m22 - A.m12*A.m20) / det; // B
  C.m11 = (A.m00*A.m22 - A.m02*A.m20) / det;  // E
  C.m12 = -(A.m00*A.m12 - A.m02*A.m10) / det; // H
  C.m20 = (A.m10*A.m21 - A.m11*A.m20) / det;  // C
  C.m21 = -(A.m00*A.m21 - A.m01*A.m20) / det; // F
  C.m22 = (A.m00*A.m11 - A.m01*A.m10) / det;  // I

  return C;
}
// CREDIT: https://stackoverflow.com/a/44446912
mat4x4 inverse(mat4x4 A) {
  float A2323 = A.m22 * A.m33 - A.m23 * A.m32 ;
  float A1323 = A.m21 * A.m33 - A.m23 * A.m31 ;
  float A1223 = A.m21 * A.m32 - A.m22 * A.m31 ;
  float A0323 = A.m20 * A.m33 - A.m23 * A.m30 ;
  float A0223 = A.m20 * A.m32 - A.m22 * A.m30 ;
  float A0123 = A.m20 * A.m31 - A.m21 * A.m30 ;
  float A2313 = A.m12 * A.m33 - A.m13 * A.m32 ;
  float A1313 = A.m11 * A.m33 - A.m13 * A.m31 ;
  float A1213 = A.m11 * A.m32 - A.m12 * A.m31 ;
  float A2312 = A.m12 * A.m23 - A.m13 * A.m22 ;
  float A1312 = A.m11 * A.m23 - A.m13 * A.m21 ;
  float A1212 = A.m11 * A.m22 - A.m12 * A.m21 ;
  float A0313 = A.m10 * A.m33 - A.m13 * A.m30 ;
  float A0213 = A.m10 * A.m32 - A.m12 * A.m30 ;
  float A0312 = A.m10 * A.m23 - A.m13 * A.m20 ;
  float A0212 = A.m10 * A.m22 - A.m12 * A.m20 ;
  float A0113 = A.m10 * A.m31 - A.m11 * A.m30 ;
  float A0112 = A.m10 * A.m21 - A.m11 * A.m20 ;

  float det = determinant(A);
  det = 1 / det;

  return mat4x4 {
     det *  (A.m11 * A2323 - A.m12 * A1323 + A.m13 * A1223),
     det * -(A.m01 * A2323 - A.m02 * A1323 + A.m03 * A1223),
     det *  (A.m01 * A2313 - A.m02 * A1313 + A.m03 * A1213),
     det * -(A.m01 * A2312 - A.m02 * A1312 + A.m03 * A1212),
     det * -(A.m10 * A2323 - A.m12 * A0323 + A.m13 * A0223),
     det *  (A.m00 * A2323 - A.m02 * A0323 + A.m03 * A0223),
     det * -(A.m00 * A2313 - A.m02 * A0313 + A.m03 * A0213),
     det *  (A.m00 * A2312 - A.m02 * A0312 + A.m03 * A0212),
     det *  (A.m10 * A1323 - A.m11 * A0323 + A.m13 * A0123),
     det * -(A.m00 * A1323 - A.m01 * A0323 + A.m03 * A0123),
     det *  (A.m00 * A1313 - A.m01 * A0313 + A.m03 * A0113),
     det * -(A.m00 * A1312 - A.m01 * A0312 + A.m03 * A0112),
     det * -(A.m10 * A1223 - A.m11 * A0223 + A.m12 * A0123),
     det *  (A.m00 * A1223 - A.m01 * A0223 + A.m02 * A0123),
     det * -(A.m00 * A1213 - A.m01 * A0213 + A.m02 * A0113),
     det *  (A.m00 * A1212 - A.m01 * A0212 + A.m02 * A0112)
  };
}

// multiplication of different types
// scale vector by float
vec2 mul(float f, vec2 v) {
  return f*v;
}
vec3 mul(float f, vec3 v) {
  return f*v;
}
vec4 mul(float f, vec4 v) {
  return f*v;
}
vec2 mul(vec2 v, float f) {
  return f*v;
}
vec3 mul(vec3 v, float f) {
  return f*v;
}
vec4 mul(vec4 v, float f) {
  return f*v;
}
// component-wise vector multiplication
vec2 mul(vec2 v0, vec2 v1) {
  return v0*v1;
}
vec3 mul(vec3 v0, vec3 v1) {
  return v0*v1;
}
vec4 mul(vec4 v0, vec4 v1) {
  return v0*v1;
}
// scale matrix by float
mat2x2 mul(float f, mat2x2 m) {
  return mat2x2 {
    f*m.m00, f*m.m01,
    f*m.m10, f*m.m11
  };
}
mat3x3 mul(float f, mat3x3 m) {
  return mat3x3 {
    f*m.m00, f*m.m01, f*m.m02,
    f*m.m10, f*m.m11, f*m.m12,
    f*m.m20, f*m.m21, f*m.m22
  };
}
mat4x4 mul(float f, mat4x4 m) {
  return mat4x4 {
    f*m.m00, f*m.m01, f*m.m02, f*m.m03,
    f*m.m10, f*m.m11, f*m.m12, f*m.m13,
    f*m.m20, f*m.m21, f*m.m22, f*m.m23,
    f*m.m30, f*m.m31, f*m.m32, f*m.m33
  };
}
mat2x2 mul(mat2x2 m, float f) {
  return mat2x2 {
    f*m.m00, f*m.m01,
    f*m.m10, f*m.m11
  };
}
mat3x3 mul(mat3x3 m, float f) {
  return mat3x3 {
    f*m.m00, f*m.m01, f*m.m02,
    f*m.m10, f*m.m11, f*m.m12,
    f*m.m20, f*m.m21, f*m.m22
  };
}
mat4x4 mul(mat4x4 m, float f) {
  return mat4x4 {
    f*m.m00, f*m.m01, f*m.m02, f*m.m03,
    f*m.m10, f*m.m11, f*m.m12, f*m.m13,
    f*m.m20, f*m.m21, f*m.m22, f*m.m23,
    f*m.m30, f*m.m31, f*m.m32, f*m.m33
  };
}
// matrix-matrix multiplication
mat2x2 mul(mat2x2 A, mat2x2 B) {
  return mat2x2 {
    A.m00*B.m00 + A.m01*B.m10, A.m00*B.m01 + A.m01*B.m11,   // 00, 01
    A.m10*B.m00 + A.m11*B.m10, A.m10*B.m01 + A.m11*B.m11    // 10, 11
  };
}
mat3x3 mul(mat3x3 A, mat3x3 B) {
  return mat3x3 {
    A.m00*B.m00 + A.m01*B.m10 + A.m02*B.m20,          // 00
    A.m00*B.m01 + A.m01*B.m11 + A.m02*B.m21,          // 01
    A.m00*B.m02 + A.m01*B.m12 + A.m02*B.m22,          // 02
  
    A.m10*B.m00 + A.m11*B.m10 + A.m12*B.m20,          // 10
    A.m10*B.m01 + A.m11*B.m11 + A.m12*B.m21,          // 11
    A.m10*B.m02 + A.m11*B.m12 + A.m12*B.m22,          // 12

    A.m20*B.m00 + A.m21*B.m10 + A.m22*B.m20,          // 20
    A.m20*B.m01 + A.m21*B.m11 + A.m22*B.m21,          // 21
    A.m20*B.m02 + A.m21*B.m12 + A.m22*B.m22           // 22
  };
}
mat4x4 mul(mat4x4 A, mat4x4 B) {
  return mat4x4 {
    A.m00*B.m00 + A.m01*B.m10 + A.m02*B.m20 + A.m03*B.m30,  // 00
    A.m00*B.m01 + A.m01*B.m11 + A.m02*B.m21 + A.m03*B.m31,  // 01
    A.m00*B.m02 + A.m01*B.m12 + A.m02*B.m22 + A.m03*B.m32,  // 02
    A.m00*B.m03 + A.m01*B.m13 + A.m02*B.m23 + A.m03*B.m33,  // 03
    
    A.m10*B.m00 + A.m11*B.m10 + A.m12*B.m20 + A.m13*B.m30,  // 10
    A.m10*B.m01 + A.m11*B.m11 + A.m12*B.m21 + A.m13*B.m31,  // 11
    A.m10*B.m02 + A.m11*B.m12 + A.m12*B.m22 + A.m13*B.m32,  // 12
    A.m10*B.m03 + A.m11*B.m13 + A.m12*B.m23 + A.m13*B.m33,  // 13
    
    A.m20*B.m00 + A.m21*B.m10 + A.m22*B.m20 + A.m23*B.m30,  // 20
    A.m20*B.m01 + A.m21*B.m11 + A.m22*B.m21 + A.m23*B.m31,  // 21
    A.m20*B.m02 + A.m21*B.m12 + A.m22*B.m22 + A.m23*B.m32,  // 22
    A.m20*B.m03 + A.m21*B.m13 + A.m22*B.m23 + A.m23*B.m33,  // 23
    
    A.m30*B.m00 + A.m31*B.m10 + A.m32*B.m20 + A.m33*B.m30,  // 30
    A.m30*B.m01 + A.m31*B.m11 + A.m32*B.m21 + A.m33*B.m31,  // 31
    A.m30*B.m02 + A.m31*B.m12 + A.m32*B.m22 + A.m33*B.m32,  // 32
    A.m30*B.m03 + A.m31*B.m13 + A.m32*B.m23 + A.m33*B.m33   // 33
  };
}
// matrix-vector multiplication (linear mapping)
vec2 mul(vec2 v, mat2x2 m) {
  vec2 y;
  y.x = m.m00*v.x + m.m01*v.y;
  y.y = m.m10*v.x + m.m11*v.y;
  return y;
}
vec3 mul(vec3 v, mat3x3 m) {
  vec3 y;
  y.x = m.m00*v.x + m.m01*v.y + m.m02*v.z;
  y.y = m.m10*v.x + m.m11*v.y + m.m12*v.z;
  y.z = m.m20*v.x + m.m21*v.y + m.m22*v.z;
  return y;
}
vec4 mul(vec4 v, mat4x4 m) {
  vec4 y;
  y.x = m.m00*v.x + m.m01*v.y + m.m02*v.z + m.m03*v.w;
  y.y = m.m10*v.x + m.m11*v.y + m.m12*v.z + m.m13*v.w;
  y.z = m.m20*v.x + m.m21*v.y + m.m22*v.z + m.m23*v.w;
  y.w = m.m30*v.x + m.m31*v.y + m.m32*v.z + m.m33*v.w;
  return y;
}
vec2 mul(mat2x2 m, vec2 v) {
  vec2 y;
  y.x = m.m00*v.x + m.m01*v.y;
  y.y = m.m10*v.x + m.m11*v.y;
  return y;
}
vec3 mul(mat3x3 m, vec3 v) {
  vec3 y;
  y.x = m.m00*v.x + m.m01*v.y + m.m02*v.z;
  y.y = m.m10*v.x + m.m11*v.y + m.m12*v.z;
  y.z = m.m20*v.x + m.m21*v.y + m.m22*v.z;
  return y;
}
vec4 mul(mat4x4 m, vec4 v) {
  vec4 y;
  y.x = m.m00*v.x + m.m01*v.y + m.m02*v.z + m.m03*v.w;
  y.y = m.m10*v.x + m.m11*v.y + m.m12*v.z + m.m13*v.w;
  y.z = m.m20*v.x + m.m21*v.y + m.m22*v.z + m.m23*v.w;
  y.w = m.m30*v.x + m.m31*v.y + m.m32*v.z + m.m33*v.w;
  return y;
}

// CREDIT: https://developer.download.nvidia.com/cg/normalize.html
// return normalized vector (length of 1)
vec2 normalize(vec2 v) {
  return rsqrt(dot(v, v)) * v;
}
vec3 normalize(vec3 v) {
  return rsqrt(dot(v, v)) * v;
}
vec4 normalize(vec4 v) {
  return rsqrt(dot(v, v)) * v;
}

// convert degrees to radians
float radians(float d) {
  return d * M_DEG_TO_RAD;
}

// CREDIT: Quake III - https://en.wikipedia.org/wiki/Fast_inverse_square_root
// returns 1/sqrt(x)
float rsqrt(float number) {
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y  = number;
  i  = * ( long * ) &y;                       // evil floating point bit level hacking
  i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
  y  = * ( float * ) &i;
  y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
  //	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

  return y;
}

mat2x2 transpose(mat2x2 m) {
  mat2x2 C;

  C.m00 = m.m00;
  C.m01 = m.m10;
  C.m10 = m.m01;
  C.m11 = m.m11;
  
  return C;
}
mat3x3 transpose(mat3x3 m) {
  mat3x3 C;

  C.m00 = m.m00;
  C.m01 = m.m10;
  C.m02 = m.m20;
  C.m10 = m.m01;
  C.m11 = m.m11;
  C.m12 = m.m21;
  C.m20 = m.m02;
  C.m21 = m.m12;
  C.m22 = m.m22;

  return C;
}
mat4x4 transpose(mat4x4 m) {
  mat4x4 C;

  C.m00 = m.m00;
  C.m01 = m.m10;
  C.m02 = m.m20;
  C.m03 = m.m30;
  C.m10 = m.m01;
  C.m11 = m.m11;
  C.m12 = m.m21;
  C.m13 = m.m31;
  C.m20 = m.m02;
  C.m21 = m.m12;
  C.m22 = m.m22;
  C.m23 = m.m32;
  C.m30 = m.m03;
  C.m31 = m.m13;
  C.m32 = m.m23;
  C.m33 = m.m33;

  return C;
}