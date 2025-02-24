#pragma once

#define PI 3.141592653589793

static inline i32 SafeRatio0(i32 a, i32 b) {
    if (b == 0) {
        return 0;
    }
    return a/b;
}

static inline f32 SafeRatio0(f32 a, f32 b) {
    if (b < 0.0000001f) {
        return 0;
    }
    return a/b;
}

static inline f32 SafeRatio1(f32 a, f32 b) {
    if (b < 0.0000001f) {
        return 1;
    }
    return a/b;
}

//
// vec2
//

struct vec2 {
    union {
        f32 Elements[2];
        struct {
            union {
                f32 x;
                f32 r;
            };
            union {
                f32 y;
                f32 g;
            };
        };
    };

    vec2() : x(0), y(0) {}
    vec2(f32 a) : x(a), y(a) {}
    vec2(f32 x, f32 y) : x(x), y(y) {}
};

struct vec2i {
    union {
        i32 Elements[2];
        struct {
            union {
                i32 x;
                i32 r;
            };
            union {
                i32 y;
                i32 g;
            };
        };
    };

    vec2i() : x(0), y(0) {}
    vec2i(i32 a) : x(a), y(a) {}
    vec2i(i32 x, i32 y) : x(x), y(y) {}
};

static inline vec2 operator+(const vec2& a, const vec2& b) {
    return vec2(a.x + b.x, a.y + b.y);
}

static inline vec2 operator-(const vec2& a, const vec2& b) {
    return vec2(a.x - b.x, a.y - b.y);
}

static inline vec2i operator+(const vec2i& a, const vec2i& b) {
    return vec2i(a.x + b.x, a.y + b.y);
}

static inline vec2i operator-(const vec2i& a, const vec2i& b) {
    return vec2i(a.x - b.x, a.y - b.y);
}

static inline vec2 operator*(const vec2& a, f32 r) {
    return vec2(a.x*r, a.y*r);
}

static inline vec2 operator*(f32 r, const vec2& a) {
    return vec2(a.x*r, a.y*r);
}

static inline vec2 operator/(const vec2& a, f32 r) {
    return vec2(SafeRatio0(a.x, r), SafeRatio0(a.y, r));
}

static inline vec2i operator/(const vec2i& a, i32 r) {
    return vec2i(SafeRatio0(a.x, r), SafeRatio0(a.y, r));
}

static inline vec2 operator/(const vec2i& a, f32 r) {
    return vec2(SafeRatio0((f32)a.x, r), SafeRatio0((f32)a.y, r));
}

static inline f32 Dot(const vec2& a, const vec2& b) {
    return (a.x*b.x + a.y*b.y);
}

static inline f32 Dot(const vec2i& a, const vec2i& b) {
    return (a.x*b.x + a.y*b.y);
}

static inline f32 Magnitude(vec2 v) {
    return sqrtf(Dot(v, v));
}

static inline f32 Magnitude(vec2i v) {
    return sqrtf(Dot(v, v));
}

static inline vec2 Normalized(vec2 v) {
    f32 Length = Magnitude(v);
    if (Length > 0.f) {
        return v/Length;
    }
    return {};
}

static inline vec2 Normalized(vec2i v) {
    vec2 Result = { (f32)v.x, (f32)v.y };
    f32 Length = Magnitude(Result);
    if (Length > 0.f) {
        return Result/Length;
    }
    return {};
}

static inline vec2i Clamp(vec2i v, vec2i x, vec2i y) {
    vec2i Result = v;
    if (v.x > x.y) {
        Result.x = x.y;
    }
    else if (v.x < x.x) {
        Result.x = x.x;
    }
    if (v.y > y.y) {
        Result.y = y.y;
    }
    else if (v.y < y.x) {
        Result.y = y.x;
    }
    return Result;
}

//
// vec3
//

struct vec3 {
    union {
        f32 Elements[3];
        struct {
            union {
                f32 x;
                f32 r;
            };
            union {
                f32 y;
                f32 g;
            };
            union {
                f32 z;
                f32 b;
            };
        };
    };

    vec3() : x(0), y(0), z(0) {}
    vec3(f32 a) : x(a), y(a), z(a) {}
    vec3(vec2 v, f32 a) : x(v.x), y(v.y), z(a) {}
    vec3(f32 a, vec2 v) : x(a), y(v.x), z(v.y) {}
    vec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}
    vec3(u32 x, u32 y, u32 z) : x((f32)x), y((f32)y), z((f32)z) {}
    //vec3(u32 x, u32 y, u32 z) : x((f32)x), y((f32)y), z((f32)z) {}
};

static inline vec3 operator+(const vec3& a, const vec3& b) {
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

static inline vec3 operator-(const vec3& a) {
    return vec3(-a.x, -a.y, -a.z);
}

static inline vec3 operator-(const vec3& a, const vec3& b) {
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

static inline vec3 operator*(f32 r, const vec3& a) {
    return vec3(a.x*r, a.y*r, a.z*r);
}

static inline vec3 operator*(const vec3& a, f32 r) {
    return vec3(a.x*r, a.y*r, a.z*r);
}

static inline vec3 operator/(const vec3& a, f32 r) {
    return vec3(a.x/r, a.y/r, a.z/r);
}

static inline vec3 operator/(const vec3& a, const vec3& b) {
    return vec3(a.x/b.x, a.y/b.y, a.z/b.z);
}

static inline vec3 operator*(const vec3& a, const vec3& b) {
    return vec3(a.x*b.x, a.y*b.y, a.z*b.z);
}

static inline f32 Dot(const vec3& a, const vec3& b) {
    return (a.x*b.x + a.y*b.y + a.z*b.z);
}

static inline vec3 Cross(const vec3& a, const vec3& b) {
    vec3 Result = {};
    Result.x = a.y*b.z - b.y*a.z;
    Result.y = a.z*b.x - b.z*a.x;
    Result.z = a.x*b.y - b.x*a.y;
    return Result;
}

static inline f32 Magnitude(vec3 v) {
    return sqrtf(Dot(v, v));
}

static inline vec3 Normalized(vec3 v) {
    f32 Length = Magnitude(v);
    if (Length > 0.f) {
        return v/Length;
    }
    else {
        return {};
    }
}

//
// vec4
//

struct vec4 {
    union {
        f32 Elements[4];
        struct {
            union {
                f32 x;
                f32 r;
            };
            union {
                f32 y;
                f32 g;
            };
            union {
                f32 z;
                f32 b;
                f32 Width;
            };
            union {
                f32 w;
                f32 a;
                f32 Height;
            };
        };
        struct {
            vec3 xyz;
            f32 w;
        };
    };

    vec4() {}
    vec4(f32 a) : x(a), y(a), z(a), w(a) {}
    vec4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w) {}
    vec4(vec3 v, f32 w) : x(v.x), y(v.y), z(v.z), w(w) {}
    vec4(vec2 v, f32 z, f32 w) : x(v.x), y(v.y), z(z), w(w) {}
};

//
// Quaternions
//

struct quaternion {
    union {
        struct {
            f32 w;
            f32 x;
            f32 y;
            f32 z;
        };
        struct {
            f32 phi;
            vec3 v;
        };
    };

    quaternion() : phi(1.f), v(vec3(0.f, 0.f, 0.f)) {}
    quaternion(f32 theta, vec3 n) : phi(cosf(theta/2.f)), v(sinf(theta/2.f)*Normalized(n)) {}
    quaternion(f32 w0, f32 x0, f32 y0, f32 z0) : w(w0), x(x0), y(y0), z(z0) {}
};

static inline quaternion Conjugate(const quaternion& Q) {
    quaternion P = {};
    P.w = Q.w;
    P.v = -Q.v;
    return P;
}

static inline f32 Dot(const quaternion& Q, const quaternion& P) {
    return (Q.w*P.w + Q.x*P.x + Q.y*P.y + Q.z*P.z);
}

static inline f32 Magnitude(const quaternion& Q) {
    return sqrtf(Dot(Q, Q));
}

static inline quaternion operator/(const quaternion& Q, f32 r) {
    return { SafeRatio0(Q.w, r), SafeRatio0(Q.x, r), SafeRatio0(Q.y, r), SafeRatio0(Q.z, r) };
}

static inline quaternion Normalized(const quaternion& Q) {
    f32 Length = Magnitude(Q);
    if (Length > 0.00000001f) {
        return Q/Length;
    }
    return quaternion();
}

static inline quaternion operator*(const quaternion& Q, const quaternion& P) {
    f32 w = Q.phi*P.phi - Dot(Q.v, P.v);
    vec3 v = Q.phi*P.v + P.phi*Q.v + Cross(Q.v, P.v);
    return { w, v.x, v.y, v.z };
}

static inline vec3 Rotate(const vec3& v, const quaternion& Q) {
    quaternion P = quaternion(0.f, v.x, v.y, v.z);
    quaternion N = Normalized(Q);
    quaternion Result = N*P*Conjugate(N);
    return { Result.x, Result.y, Result.z };
}

//
// matrix 3x3
//
struct mat3 {
    f32 Elements[9];
};
#define Mat3Identity mat3{ 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f,}

static inline mat3 operator*(const mat3& A, const mat3& B) {
    mat3 Result;
    for (i32 j = 0; j < 3; ++j) {
        for (i32 i = 0; i < 3; ++i) {
            Result.Elements[j*3 + i] = 0.0f;
            for (i32 k = 0; k < 3; ++k) {
                Result.Elements[j*3 + i] += A.Elements[j*3 + k]*B.Elements[k*3 + i];
            }
        }
    }
    return Result;
}

static inline vec3 operator*(const mat3& A, vec3 v) {
    vec3 Result = {};
    for (i32 j = 0; j < 3; ++j) {
        for (i32 i = 0; i < 3; ++i) {
            Result.Elements[j] += A.Elements[j*3 + i]*v.Elements[i];
        }
    }
    return Result;
}

// TODO: fix this, this isn't the inverse in the general case.
// This is really just the transpose
static inline mat3 Inverse(const mat3& A) {
    mat3 Result = {};
    for (u32 j = 0; j < 3; j++) {
        for (u32 i = 0; i < 3; i++) {
            Result.Elements[j*3 + i] = A.Elements[i*3 + j];
        }
    }
    return Result;
}

//
// matrix 4x4
//

struct mat4 {
    f32 Elements[16];
};
#define MAT4_IDENTITY mat4{ 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f}

static mat4 operator*(const mat4& A, const mat4& B) {
    mat4 Result;
    for (i32 j = 0; j < 4; ++j) {
        for (i32 i = 0; i < 4; ++i) {
            Result.Elements[j*4 + i] = 0.0f;
            for (i32 k = 0; k < 4; ++k) {
                Result.Elements[j*4 + i] += A.Elements[j*4 + k]*B.Elements[k*4 + i];
            }
        }
    }
    return Result;
}

static inline mat4 Transpose(const mat4& A) {
    mat4 Result = {};
    for (u32 j = 0; j < 4; j++) {
        for (u32 i = 0; i < 4; i++) {
            Result.Elements[j*4 + i] = A.Elements[i*4 + j];
        }
    }
    return Result;
}

static inline vec4 operator*(const mat4& A, const vec4& v) {
    vec4 Result = vec4();
    for (i32 j = 0; j < 4; ++j) {
         f32 a = A.Elements[j*4 + 0]*v.Elements[0];
         f32 b = A.Elements[j*4 + 1]*v.Elements[1];
         f32 c = A.Elements[j*4 + 2]*v.Elements[2];
         f32 d = A.Elements[j*4 + 3]*v.Elements[3];
         Result.Elements[j] = a + b + c + d;
    }
    return Result;
}
