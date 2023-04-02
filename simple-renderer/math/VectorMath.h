#pragma once

struct vec2 {
  float x;
  float y;

  // override addition
  vec2& operator+=(const vec2& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }
  friend vec2 operator+(vec2 lhs, const vec2& rhs) {
    lhs += rhs;
    return lhs;
  }
  // override subtraction
  vec2& operator-=(const vec2& rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
  }
  friend vec2 operator-(vec2 lhs, const vec2& rhs) {
    lhs -= rhs;
    return lhs;
  }
  // override v/v multiplication
  vec2& operator*=(const vec2& rhs) {
    this->x *= rhs.x;
    this->y *= rhs.y;
    return *this;
  }
  friend vec2 operator*(vec2 lhs, const vec2& rhs) {
    lhs *= rhs;
    return lhs;
  }
  // override v/f multiplication
  vec2& operator*=(const float& rhs) {
    this->x *= rhs;
    this->y *= rhs;
    return *this;
  }
  friend vec2 operator*(vec2 lhs, const float& rhs) {
    lhs *= rhs;
    return lhs;
  }
  // f/v mult
  friend vec2 operator*(const float& lhs, vec2 rhs) {
    rhs *= lhs;
    return rhs;
  }
  // override negation
  vec2& operator-() const {
    vec2 v;
    v.x = -this->x;
    v.y = -this->y;
    return v;
  }
};
struct vec2i {
  int x;
  int y;

  // override addition
  vec2i& operator+=(const vec2i& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }
  friend vec2i operator+(vec2i lhs, const vec2i& rhs) {
    lhs += rhs;
    return lhs;
  }
  // override subtraction
  vec2i& operator-=(const vec2i& rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
  }
  friend vec2i operator-(vec2i lhs, const vec2i& rhs) {
    lhs -= rhs;
    return lhs;
  }
  // override v/v multiplication
  vec2i& operator*=(const vec2i& rhs) {
    this->x *= rhs.x;
    this->y *= rhs.y;
    return *this;
  }
  friend vec2i operator*(vec2i lhs, const vec2i& rhs) {
    lhs *= rhs;
    return lhs;
  }
  // override v/f multiplication
  vec2i& operator*=(const float& rhs) {
    this->x *= rhs;
    this->y *= rhs;
    return *this;
  }
  friend vec2i operator*(vec2i lhs, const int& rhs) {
    lhs *= rhs;
    return lhs;
  }
  // f/v mult
  friend vec2i operator*(const int& lhs, vec2i rhs) {
    rhs *= lhs;
    return rhs;
  }
  // override negation
  vec2i& operator-() const {
    vec2i v;
    v.x = -this->x;
    v.y = -this->y;
    return v;
  }
};
struct vec3 {
  float x;
  float y;
  float z;

  vec3& operator+=(const vec3& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
  }
  friend vec3 operator+(vec3 lhs, const vec3& rhs) {
    lhs += rhs;
    return lhs;
  }
  vec3& operator-=(const vec3& rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
  }
  friend vec3 operator-(vec3 lhs, const vec3& rhs) {
    lhs -= rhs;
    return lhs;
  }
  vec3& operator*=(const vec3& rhs) {
    this->x *= rhs.x;
    this->y *= rhs.y;
    this->z *= rhs.z;
    return *this;
  }
  friend vec3 operator*(vec3 lhs, const vec3& rhs) {
    lhs *= rhs;
    return lhs;
  }
  vec3& operator*=(const float& rhs) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this;
  }
  friend vec3 operator*(vec3 lhs, const float& rhs) {
    lhs *= rhs;
    return lhs;
  }
  friend vec3 operator*(const float& lhs, vec3 rhs) {
    rhs *= lhs;
    return rhs;
  }
  vec3& operator-() const {
    vec3 v;
    v.x = -this->x;
    v.y = -this->y;
    v.z = -this->z;
    return v;
  }
};
struct vec3i {
  int x;
  int y;
  int z;

  vec3i& operator+=(const vec3i& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
  }
  friend vec3i operator+(vec3i lhs, const vec3i& rhs) {
    lhs += rhs;
    return lhs;
  }
  vec3i& operator-=(const vec3i& rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
  }
  friend vec3i operator-(vec3i lhs, const vec3i& rhs) {
    lhs -= rhs;
    return lhs;
  }
  vec3i& operator*=(const vec3i& rhs) {
    this->x *= rhs.x;
    this->y *= rhs.y;
    this->z *= rhs.z;
    return *this;
  }
  friend vec3i operator*(vec3i lhs, const vec3i& rhs) {
    lhs *= rhs;
    return lhs;
  }
  vec3i& operator*=(const int& rhs) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this;
  }
  friend vec3i operator*(vec3i lhs, const int& rhs) {
    lhs *= rhs;
    return lhs;
  }
  friend vec3i operator*(const int& lhs, vec3i rhs) {
    rhs *= lhs;
    return rhs;
  }
  vec3i& operator-() const {
    vec3i v;
    v.x = -this->x;
    v.y = -this->y;
    v.z = -this->z;
    return v;
  }
};
struct vec4i {
  int x;
  int y;
  int z;
  int w;

  vec4i& operator+=(const vec4i& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    this->w += rhs.w;
    return *this;
  }
  friend vec4i operator+(vec4i lhs, const vec4i& rhs) {
    lhs += rhs;
    return lhs;
  }
  vec4i& operator-=(const vec4i& rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    this->w -= rhs.w;
    return *this;
  }
  friend vec4i operator-(vec4i lhs, const vec4i& rhs) {
    lhs -= rhs;
    return lhs;
  }
  vec4i& operator*=(const vec4i& rhs) {
    this->x *= rhs.x;
    this->y *= rhs.y;
    this->z *= rhs.z;
    this->w *= rhs.w;
    return *this;
  }
  friend vec4i operator*(vec4i lhs, const vec4i& rhs) {
    lhs *= rhs;
    return lhs;
  }
  vec4i& operator*=(const int& rhs) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    this->w *= rhs;
    return *this;
  }
  friend vec4i operator*(vec4i lhs, const int& rhs) {
    lhs *= rhs;
    return lhs;
  }
  friend vec4i operator*(const int& lhs, vec4i rhs) {
    rhs *= lhs;
    return rhs;
  }
  vec4i& operator-() const {
    vec4i v;
    v.x = -this->x;
    v.y = -this->y;
    v.z = -this->z;
    v.w = -this->w;
    return v;
  }
};
struct vec4 {
  float x;
  float y;
  float z;
  float w;

  vec4& operator+=(const vec4& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    this->w += rhs.w;
    return *this;
  }
  friend vec4 operator+(vec4 lhs, const vec4& rhs) {
    lhs += rhs;
    return lhs;
  }
  vec4& operator-=(const vec4& rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    this->w -= rhs.w;
    return *this;
  }
  friend vec4 operator-(vec4 lhs, const vec4& rhs) {
    lhs -= rhs;
    return lhs;
  }
  vec4& operator*=(const vec4& rhs) {
    this->x *= rhs.x;
    this->y *= rhs.y;
    this->z *= rhs.z;
    this->w *= rhs.w;
    return *this;
  }
  friend vec4 operator*(vec4 lhs, const vec4& rhs) {
    lhs *= rhs;
    return lhs;
  }
  vec4& operator*=(const float& rhs) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    this->w *= rhs;
    return *this;
  }
  friend vec4 operator*(vec4 lhs, const float& rhs) {
    lhs *= rhs;
    return lhs;
  }
  friend vec4 operator*(const float& lhs, vec4 rhs) {
    rhs *= lhs;
    return rhs;
  }
  vec4& operator-() const {
    vec4 v;
    v.x = -this->x;
    v.y = -this->y;
    v.z = -this->z;
    v.w = -this->w;
    return v;
  }
};

struct mat2x2 {
  float m00, m01;
  float m10, m11;
};
struct mat3x3 {
  float m00, m01, m02;
  float m10, m11, m12;
  float m20, m21, m22;
};
struct mat4x4 {
  float m00, m01, m02, m03;
  float m10, m11, m12, m13;
  float m20, m21, m22, m23;
  float m30, m31, m32, m33;
};

// return determinant of square matrix
float determinant(mat2x2 m);
float determinant(mat3x3 m);
float determinant(mat4x4 m);

// dot product of two vectors
float dot(vec2 a, vec2 b);
float dot(vec3 a, vec3 b);
float dot(vec4 a, vec4 b);

mat2x2 inverse(mat2x2 A);
mat3x3 inverse(mat3x3 A);
mat4x4 inverse(mat4x4 A);

// multiplication of different types
//float mul(float x, float y); // 1
vec2 mul(float f, vec2 v); // 2
vec3 mul(float f, vec3 v);
vec4 mul(float f, vec4 v);
vec2 mul(vec2 v, float f); // 3
vec3 mul(vec3 v, float f);
vec4 mul(vec4 v, float f);
vec2 mul(vec2 v0, vec2 v1); // 4
vec3 mul(vec3 v0, vec3 v1);
vec4 mul(vec4 v0, vec4 v1);
mat2x2 mul(float f, mat2x2 m); // 5
mat3x3 mul(float f, mat3x3 m);
mat4x4 mul(float f, mat4x4 m);
mat2x2 mul(mat2x2 m, float f); // 6
mat3x3 mul(mat3x3 m, float f);
mat4x4 mul(mat4x4 m, float f);
mat2x2 mul(mat2x2 A, mat2x2 B); // 7
mat3x3 mul(mat3x3 A, mat3x3 B);
mat4x4 mul(mat4x4 A, mat4x4 B);
vec2 mul(vec2 v, mat2x2 m); // 8
vec3 mul(vec3 v, mat3x3 m);
vec4 mul(vec4 v, mat4x4 m);
vec2 mul(mat2x2 m, vec2 v); // 9
vec3 mul(mat3x3 m, vec3 v);
vec4 mul(mat4x4 m, vec4 v);

// return normalized vector (length of 1)
vec2 normalize(vec2 v);
vec3 normalize(vec3 v);
vec4 normalize(vec4 v);

// returns 1/sqrt(x)
float rsqrt(float x);

mat2x2 transpose(mat2x2 m);
mat3x3 transpose(mat3x3 m);
mat4x4 transpose(mat4x4 m);