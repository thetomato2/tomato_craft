#ifndef TOMATO_MATH_HPP_
#define TOMATO_MATH_HPP_

#include "common.hpp"
#include "intrinsic.hpp"

namespace tom
{

// ===============================================================================================
// #FREE_FUNCS
// ===============================================================================================
namespace math
{
global_var constexpr f32 eps_f32 = 0.0001f;
global_var constexpr f32 pi      = 3.14159265;

f32 to_radian(f32 val)
{
    return (val * pi) / 180.0f;
}

f32 to_degree(f32 val)
{
    return (val * 180.0f) / pi;
}

template<typename T>
T square(const T val)
{
    return val * val;
}

// Returns min or max if input is not in between
template<typename T>
T bounds(const T in, const T min, const T max)
{
    T res = in;

    if (in < min)
        res = min;
    else if (in > max)
        res = max;

    return res;
}

template<typename T>
T max(const T a, const T b)
{
    T res;
    a > b ? res = a : res = b;
    return res;
}

template<typename T>
T min(const T a, const T b)
{
    T res;
    a < b ? res = a : res = b;
    return res;
}
}  // namespace math

// ===============================================================================================
// #VECTOR 2
// ===============================================================================================
union v2
{
    struct
    {
        f32 x, y;
    };
    struct
    {
        f32 u, v;
    };
    f32 e[2];
};

inline v2 operator+(v2 lhs, v2 rhs)
{
    v2 res;

    res.x = lhs.x + rhs.x;
    res.y = lhs.y + rhs.y;

    return res;
}

inline v2 operator+(v2 lhs, f32 rhs)
{
    v2 res;

    res.x = lhs.x + rhs;
    res.y = lhs.y + rhs;

    return res;
}

inline v2 &operator+=(v2 &lhs, v2 rhs)
{
    lhs = lhs + rhs;

    return lhs;
}

inline v2 &operator+=(v2 &lhs, f32 rhs)
{
    lhs.x += rhs;
    lhs.y += rhs;

    return lhs;
}

inline v2 operator-(v2 lhs)
{
    v2 res;

    res.x = -lhs.x;
    res.y = -lhs.y;

    return res;
}
inline v2 operator-(v2 lhs, v2 rhs)
{
    v2 res;

    res.x = lhs.x - rhs.x;
    res.y = lhs.y - rhs.y;

    return res;
}

inline v2 operator-(v2 lhs, f32 rhs)
{
    v2 res;

    res.x = lhs.x - rhs;
    res.y = lhs.y - rhs;

    return res;
}

inline v2 &operator-=(v2 &lhs, v2 rhs)
{
    lhs = lhs - rhs;

    return lhs;
}

inline v2 &operator-=(v2 &lhs, f32 rhs)
{
    lhs = lhs - rhs;

    return lhs;
}

inline v2 operator*(f32 lhs, v2 rhs)
{
    v2 res;

    res.x = lhs * rhs.x;
    res.y = lhs * rhs.y;

    return res;
}

inline v2 operator*(v2 lhs, f32 rhs)
{
    v2 res;

    res.x = lhs.x * rhs;
    res.y = lhs.y * rhs;

    return res;
}

inline v2 &operator*=(v2 &lhs, f32 rhs)
{
    lhs.x *= rhs;
    lhs.y *= rhs;

    return lhs;
}

inline v2 operator/(v2 lhs, f32 rhs)
{
    v2 res;

    res.x = lhs.x / rhs;
    res.y = lhs.y / rhs;

    return res;
}

inline v2 &operator/=(v2 &lhs, f32 rhs)
{
    lhs.x /= rhs;
    lhs.y /= rhs;

    return lhs;
}

inline bool operator==(v2 &lhs, v2 &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator!=(v2 &lhs, v2 &rhs)
{
    return !(lhs == rhs);
}

// ===============================================================================================
// #VECTOR 3
// ===============================================================================================
union v3
{
    struct
    {
        f32 x, y, z;
    };
    struct
    {
        f32 r, g, b;
    };
    struct
    {
        v2 xy;
        f32 _ignored0;
    };
    f32 e[3];
};
inline v3 v3_init(f32 x, f32 y, f32 z)
{
    v3 res;

    res.x = x;
    res.y = y;
    res.z = z;

    return res;
}

inline v3 v3_init(v2 a, f32 z = 0.f)
{
    v3 res;

    res.x = a.x;
    res.y = a.y;
    res.z = z;

    return res;
}

inline v3 operator+(v3 lhs, v3 rhs)
{
    v3 res;

    res.x = lhs.x + rhs.x;
    res.y = lhs.y + rhs.y;
    res.z = lhs.z + rhs.z;

    return res;
}

inline v3 operator+(v3 lhs, f32 rhs)
{
    v3 res;

    res.x = lhs.x + rhs;
    res.y = lhs.y + rhs;
    res.z = lhs.z + rhs;

    return res;
}

inline v3 &operator+=(v3 &lhs, v3 rhs)
{
    lhs = lhs + rhs;

    return lhs;
}

inline v3 &operator+=(v3 &lhs, f32 rhs)
{
    lhs = lhs + rhs;

    return lhs;
}

inline v3 operator-(v3 lhs)
{
    v3 res;

    res.x = -lhs.x;
    res.y = -lhs.y;
    res.z = -lhs.z;

    return res;
}
inline v3 operator-(v3 lhs, v3 rhs)
{
    v3 res;

    res.x = lhs.x - rhs.x;
    res.y = lhs.y - rhs.y;
    res.z = lhs.z - rhs.z;

    return res;
}

inline v3 operator-(v3 lhs, f32 rhs)
{
    v3 res;

    res.x = lhs.x - rhs;
    res.y = lhs.y - rhs;
    res.z = lhs.z - rhs;

    return res;
}

inline v3 &operator-=(v3 &lhs, v3 rhs)
{
    lhs = lhs - rhs;

    return lhs;
}

inline v3 &operator-=(v3 &lhs, f32 rhs)
{
    lhs = lhs - rhs;

    return lhs;
}

inline v3 operator*(f32 lhs, v3 rhs)
{
    v3 res;

    res.x = lhs * rhs.x;
    res.y = lhs * rhs.y;
    res.z = lhs * rhs.z;

    return res;
}

inline v3 operator*(v3 lhs, f32 rhs)
{
    v3 res;

    res.x = lhs.x * rhs;
    res.y = lhs.y * rhs;
    res.z = lhs.z * rhs;

    return res;
}

inline v3 &operator*=(v3 &lhs, f32 rhs)
{
    lhs = lhs * rhs;

    return lhs;
}

inline v3 operator/(v3 lhs, f32 rhs)
{
    v3 res;

    res.x = lhs.x / rhs;
    res.y = lhs.y / rhs;
    res.z = lhs.z / rhs;

    return res;
}

inline v3 &operator/=(v3 &lhs, f32 rhs)
{
    lhs = lhs / rhs;

    return lhs;
}

inline bool operator==(v3 &lhs, v3 &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

inline bool operator!=(v3 &lhs, v3 &rhs)
{
    return !(lhs == rhs);
}

// ===============================================================================================
// #VECTOR 4
// ===============================================================================================
union v4
{
    struct
    {
        f32 x, y, z, w;
    };
    struct
    {
        f32 r, g, b, a;
    };
    struct
    {
        v3 xyz;
        f32 _ignored0;
    };
    struct
    {
        v3 rgb;
        f32 _ignored1;
    };
    f32 e[4];
};

inline v4 v4_init(f32 x, f32 y, f32 z, f32 w)
{
    v4 res;

    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;

    return res;
}

inline v4 v4_init(v2 a, f32 z = 0.f, f32 w = 0.0f)
{
    v4 res;
    res.x = a.x;
    res.y = a.y;
    res.z = z;
    res.w = w;

    return res;
}

inline v4 v4_init(v3 a, f32 w = 0.0f)
{
    v4 res;
    res.x = a.x;
    res.y = a.y;
    res.z = a.z;
    res.w = w;

    return res;
}

inline v4 operator+(v4 lhs, v4 rhs)
{
    v4 res;

    res.x = lhs.x + rhs.x;
    res.y = lhs.y + rhs.y;
    res.z = lhs.z + rhs.z;
    res.w = lhs.w + rhs.w;

    return res;
}

inline v4 operator+(v4 lhs, f32 rhs)
{
    v4 res;

    res.x = lhs.x + rhs;
    res.y = lhs.y + rhs;
    res.z = lhs.z + rhs;
    res.w = lhs.w + rhs;

    return res;
}

inline v4 &operator+=(v4 &lhs, v4 rhs)
{
    lhs = lhs + rhs;

    return lhs;
}

inline v4 &operator+=(v4 &lhs, f32 rhs)
{
    lhs = lhs + rhs;

    return lhs;
}

inline v4 operator-(v4 lhs)
{
    v4 res;

    res.x = -lhs.x;
    res.y = -lhs.y;
    res.z = -lhs.z;
    res.w = -lhs.w;

    return res;
}
inline v4 operator-(v4 lhs, v4 rhs)
{
    v4 res;

    res.x = lhs.x - rhs.x;
    res.y = lhs.y - rhs.y;
    res.z = lhs.z - rhs.z;
    res.w = lhs.w - rhs.w;

    return res;
}

inline v4 operator-(v4 lhs, f32 rhs)
{
    v4 res;

    res.x = lhs.x - rhs;
    res.y = lhs.y - rhs;
    res.z = lhs.z - rhs;
    res.w = lhs.w - rhs;

    return res;
}

inline v4 &operator-=(v4 &lhs, v4 rhs)
{
    lhs = lhs - rhs;

    return lhs;
}

inline v4 &operator-=(v4 &lhs, f32 rhs)
{
    lhs = lhs - rhs;

    return lhs;
}

inline v4 operator*(f32 lhs, v4 rhs)
{
    v4 res;

    res.x = lhs * rhs.x;
    res.y = lhs * rhs.y;
    res.z = lhs * rhs.z;
    res.w = lhs * rhs.w;

    return res;
}

inline v4 operator*(v4 lhs, f32 rhs)
{
    v4 res;

    res.x = lhs.x * rhs;
    res.y = lhs.y * rhs;
    res.z = lhs.z * rhs;
    res.w = lhs.w * rhs;

    return res;
}

inline v4 &operator*=(v4 &lhs, f32 rhs)
{
    lhs = lhs * rhs;

    return lhs;
}

inline v4 operator*(v4 lhs, v3 rhs)
{
    v4 res;

    res.w = (lhs.x * rhs.x) - (lhs.y * rhs.y) - (lhs.z * rhs.z);
    res.x = (lhs.w * rhs.x) + (lhs.y * rhs.z) - (lhs.z * rhs.y);
    res.y = (lhs.w * rhs.y) + (lhs.z * rhs.x) - (lhs.x * rhs.z);
    res.z = (lhs.w * rhs.z) + (lhs.x * rhs.y) - (lhs.y * rhs.x);

    return res;
}

inline v4 operator*=(v4 &lhs, v3 rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

inline v4 operator*(v4 lhs, v4 rhs)
{
    v4 res;

    res.w = (lhs.w * rhs.w) - (lhs.x * rhs.x) - (lhs.y * rhs.y) - (lhs.z * rhs.z);
    res.x = (lhs.x * rhs.w) + (lhs.w * rhs.x) + (lhs.y * rhs.z) - (lhs.z * rhs.y);
    res.y = (lhs.y * rhs.w) + (lhs.w * rhs.y) + (lhs.z * rhs.x) - (lhs.x * rhs.z);
    res.z = (lhs.z * rhs.w) + (lhs.w * rhs.z) + (lhs.x * rhs.y) - (lhs.y * rhs.x);

    return res;
}

inline v4 operator*=(v4 &lhs, v4 rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

inline v4 operator/(v4 lhs, f32 rhs)
{
    v4 res;

    res.x = lhs.x / rhs;
    res.y = lhs.y / rhs;
    res.z = lhs.z / rhs;
    res.w = lhs.w / rhs;

    return res;
}

inline v4 &operator/=(v4 &lhs, f32 rhs)
{
    lhs = lhs / rhs;

    return lhs;
}

inline bool operator==(v4 &lhs, v4 &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

inline bool operator!=(v4 &lhs, v4 &rhs)
{
    return !(lhs == rhs);
}

// ===============================================================================================
// #VECTOR FUNCS
// ===============================================================================================
namespace vec
{

// NOTE: inner product or dot product
inline f32 inner(const v2 a, const v2 b)
{
    f32 res = a.x * b.x + a.y * b.y;
    return res;
};

inline f32 inner(const v3 a, const v3 b)
{
    f32 res = a.x * b.x + a.y * b.y + a.z * b.z;
    return res;
};

inline f32 inner(const v4 a, const v4 b)
{
    f32 res = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    return res;
};

inline f32 dot(const v2 a, const v2 b)
{
    return inner(a, b);
}

inline f32 dot(const v3 a, const v3 b)
{
    return inner(a, b);
}

inline f32 dot(const v4 a, const v4 b)
{
    return inner(a, b);
}

inline v3 cross(const v3 a, const v3 b)
{
    v3 res;

    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;

    return res;
}

inline v2 hadamard(const v2 a, const v2 b)
{
    v2 res;

    res.x = a.x * b.x;
    res.y = a.y * b.y;

    return res;
}

inline v3 hadamard(const v3 a, const v3 b)
{
    v3 res;

    res.x = a.x * b.x;
    res.y = a.y * b.y;
    res.z = a.z * b.z;

    return res;
}

inline v4 hadamard(const v4 a, const v4 b)
{
    v4 res;

    res.x = a.x * b.x;
    res.y = a.y * b.y;
    res.z = a.z * b.z;
    res.w = a.w * b.w;

    return res;
}

inline f32 length_sq(const v2 a)
{
    f32 res = inner(a, a);
    return res;
}

inline f32 length_sq(const v3 a)
{
    f32 res = inner(a, a);
    return res;
}

inline f32 length_sq(const v4 a)
{
    f32 res = inner(a, a);
    return res;
}

inline f32 length(const v2 a)
{
    f32 res = math::sqrt_f32(length_sq(a));
    return res;
}

inline f32 length(const v3 a)
{
    f32 res = math::sqrt_f32(length_sq(a));
    return res;
}

inline f32 length(const v4 a)
{
    f32 res = math::sqrt_f32(length_sq(a));
    return res;
}

inline v3 normalize(const v3 a)
{
    f32 len = length(a);
    TOM_ASSERT(len != 0.0f);

    v3 res;

    res.x = a.x / len;
    res.y = a.y / len;
    res.z = a.z / len;

    return res;
}
inline f32 distance(const v3 a, const v3 b)
{
    v3 dis = a - b;
    dis.x  = abs(dis.x);
    dis.y  = abs(dis.y);
    dis.z  = abs(dis.z);

    f32 res = length(dis);

    return res;
}

}  // namespace vec

// ===============================================================================================
// #Quaternion
// ===============================================================================================

using quat = v4;  // Quaternion
namespace qua
{

inline quat to_quat(v3 v, f32 a)
{
    f32 half_angle_rad = math::to_radian(a / 2.0f);
    f32 sin_half_angle = sinf(half_angle_rad);
    f32 cos_half_angle = cosf(half_angle_rad);

    quat res;

    res.x = v.x * sin_half_angle;
    res.y = v.y * sin_half_angle;
    res.z = v.z * sin_half_angle;
    res.w = cos_half_angle;

    return res;
}

inline f32 norm(quat a)
{
    f32 i   = vec::inner(a.xyz, a.xyz);
    f32 s   = math::square(a.w);
    f32 res = math::sqrt_f32(i + s);

    return res;
}

inline quat unit_norm(quat a)
{
    f32 half_angle_rad = math::to_radian(a.w / 2.0f);
    f32 sin_half_angle = sinf(half_angle_rad);
    f32 cos_half_angle = cosf(half_angle_rad);

    a.w   = cos_half_angle;
    a.xyz = vec::normalize(a.xyz);
    a.xyz = a.xyz * sin_half_angle;

    return a;
}
inline quat conjuate(quat q)
{
    quat res;
    res.x = -q.x;
    res.y = -q.y;
    res.z = -q.z;
    res.w = q.w;

    return res;
}

inline quat inverse(quat a)
{
    f32 abs   = 1 / (math::square(norm(a)));
    quat conj = conjuate(a);
    f32 s     = conj.w * abs;
    v3 i      = conj.xyz * abs;

    quat res;
    res.xyz = i;
    res.w   = s;

    return res;
}

inline v3 rotate(v3 v, v3 u, f32 a)
{
    quat p   = { v.x, v.y, v.z, 0.0f };
    u        = vec::normalize(u);
    quat q   = unit_norm({ u.x, u.y, u.z, a });
    quat q_i = inverse(q);

    quat res = q * p * q_i;

    return res.xyz;
}
}  // namespace qua

// ===============================================================================================
// #Matrix 4x4
// ===============================================================================================
struct m4
{
    // NOTE: row major
    f32 e[4][4];
};

inline m4 operator*(m4 a, m4 b)
{
    m4 res = {};

    // NOTE: this should unroll but...
    // TODO: unroll this and use simd
    for (s32 r = 0; r < 4; ++r) {
        for (s32 c = 0; c < 4; ++c) {
            for (s32 i = 0; i < 4; ++i) {
                res.e[r][c] += a.e[r][i] * b.e[i][c];
            }
        }
    }

    return res;
}

inline v3 transform(m4 a, v3 p, f32 Pw = 1.0f)
{
    v3 res = {};

    res.x = p.x * a.e[0][0] + p.y * a.e[0][1] + p.z * a.e[0][2] + Pw * a.e[0][3];
    res.y = p.x * a.e[1][0] + p.y * a.e[1][1] + p.z * a.e[1][2] + Pw * a.e[1][3];
    res.z = p.x * a.e[2][0] + p.y * a.e[2][1] + p.z * a.e[2][2] + Pw * a.e[2][3];

    return res;
}

inline v3 operator*(m4 a, v3 p)
{
    v3 res = transform(a, p, 1.0f);

    return res;
}

namespace mat
{
inline m4 identity(f32 a = 1.0f)
{
    m4 res = { { { a, 0.0f, 0.0f, 0.0f },
                 { 0.0f, a, 0.0f, 0.0f },
                 { 0.0f, 0.0f, a, 0.0f },
                 { 0.0f, 0.0f, 0.0f, 1.0f } } };

    return res;
}

inline m4 rot_x(f32 a)
{
    f32 c = cos(a);
    f32 s = sin(a);

    m4 res = { { { 1.0f, 0.0f, 0.0f, 0.0f },
                 { 0.0f, c, -s, 0.0f },
                 { 0.0f, s, c, 0.0f },
                 { 0.0f, 0.0f, 0.0f, 1.0f } } };

    return res;
}

inline m4 rot_x(m4 a, f32 b)
{
    return a * rot_x(b);
}

inline m4 rot_y(f32 a)
{
    f32 c = cos(a);
    f32 s = sin(a);

    m4 res = { { { c, 0.0f, s, 0.0f },
                 { 0.0f, 1.0f, 0.0f, 0.0f },
                 { -s, 0.0f, c, 0.0f },
                 { 0.0f, 0.0f, 0.0f, 1.0f } } };

    return res;
}

inline m4 rot_y(m4 a, f32 b)
{
    return a * rot_y(b);
}

inline m4 rot_z(f32 a)
{
    f32 c = cos(a);
    f32 s = sin(a);

    m4 res = { { { c, -s, 0.0f, 0.0f },
                 { s, c, 0.0f, 0.0f },
                 { 0.0f, 0.0f, 1.0f, 0.0f },
                 { 0.0f, 0.0f, 0.0f, 1.0f } } };

    return res;
}

inline m4 rot_z(m4 a, f32 b)
{
    return a * rot_z(b);
}
// u = arbitrary axis, a = angle
inline m4 rotate(const v3 u, f32 a)
{
    a       = math::to_radian(a);
    f32 c   = cos(a);
    f32 l_c = 1 - c;
    f32 s   = sin(a);

    m4 res = { { { u.x * u.x + (1 - u.x * u.x) * c, u.x * u.y * l_c + u.z * s,
                   u.x * u.z * l_c - u.y * s, 0 },
                 { u.x * u.y * l_c - u.z * s, u.y * u.y + (1 - u.y * u.y) * c,
                   u.y * u.z * l_c + u.x * s, 0 },
                 { u.x * u.z * l_c + u.y * s, u.y * u.z * l_c - u.x * s,
                   u.z * u.z + (1 - u.z * u.z) * c, 0 },
                 { 0, 0, 0, 1 } } };
    return res;
}

inline m4 rotate(m4 m, const v3 u, f32 a)
{
    m4 res = m * rotate(u, a);

    return res;
}

inline m4 scale(const m4 a, const f32 b)
{
    m4 res = mat::identity(b);

    res = a * res;

    return res;
}

inline m4 transpose(m4 a)
{
    m4 res;

    for (s32 i = 0; i < 4; ++i) {
        for (s32 j = 0; j < 4; ++j) {
            res.e[i][j] = a.e[j][i];
        }
    }

    return res;
}

inline m4 proj_persp(f32 aspect_ratio, f32 focal_len)
{
    f32 a = 1.0f;
    f32 b = aspect_ratio;
    // f32 c = (1.0f / focal_len);
    f32 c = focal_len;

    f32 n = 0.1f;     // near clip
    f32 f = 1000.0f;  // far clip

    // ortho
#if 1
    f32 d = (n + f) / (n - f);
    f32 e = (2.0f * f * n) / (n - f);
#else
    f32 d = 2.0f / (n - f);
    f32 e = (n + f) / (n - f);
#endif

    m4 res = { { { a * c, 0.0f, 0.0f, 0.0f },
                 { 0.0f, b * c, 0.0f, 0.0f },
                 { 0.0f, 0.0f, d, e },
                 { 0.0f, 0.0f, -1.0f, 0.0f } } };

    return res;
}

inline m4 proj_ortho(f32 aspect_ratio)
{
    f32 a = 1.0f;
    f32 b = aspect_ratio;

    m4 res = { { { a, 0.0f, 0.0f, 0.0f },
                 { 0.0f, b, 0.0f, 0.0f },
                 { 0.0f, 0.0f, 1.0f, 0.0f },
                 { 0.0f, 0.0f, 0.0f, 1.0f } } };

    return res;
}

inline m4 col_3x3(v3 x, v3 y, v3 z)
{
    m4 res = { { { x.x, y.x, z.x, 0.0f },
                 { x.y, y.y, z.y, 0.0f },
                 { x.z, y.z, z.z, 0.0f },
                 { 0.0f, 0.0f, 0.0f, 1.0f } } };

    return res;
}

inline m4 row_3x3(v3 x, v3 y, v3 z)
{
    m4 res = { { { x.x, x.y, x.z, 0.0f },
                 { y.x, y.y, y.z, 0.0f },
                 { z.x, z.y, z.z, 0.0f },
                 { 0.0f, 0.0f, 0.0f, 1.0f } } };

    return res;
}
inline m4 translate(v3 t)
{
    m4 res = mat::identity();

    res.e[0][3] = t.x;
    res.e[1][3] = t.y;
    res.e[2][3] = t.z;

    return res;
}

inline m4 translate(m4 a, v3 t)
{
    m4 res = a;

    res.e[0][3] = t.x;
    res.e[1][3] = t.y;
    res.e[2][3] = t.z;

    return res;
}

inline v3 get_col(m4 a, u32 c)
{
    v3 res = { a.e[0][c], a.e[1][c], a.e[2][c] };

    return res;
}

inline v3 get_row(m4 a, u32 r)
{
    v3 res = { a.e[r][0], a.e[r][1], a.e[r][2] };

    return res;
}

inline m4 uvn_to_m4(v3 pos, v3 u, v3 v, v3 n)
{
    m4 res = { { { u.x, u.y, u.z, -pos.x },
                 { v.x, v.y, v.z, -pos.y },
                 { n.x, n.y, n.z, -pos.z },
                 { 0.0f, 0.0f, 0.0f, 1.0f } } };

    return res;
}

inline m4 loot_at(v3 from, v3 to)
{
    v3 t       = { 0.0f, 1.0f, 0.0f };
    v3 forward = vec::normalize(from - to);
    v3 right   = vec::cross(vec::normalize(t), forward);
    v3 up      = vec::cross(forward, right);

    m4 res = { { { right.x, right.y, right.z, 0.0f },
                 { up.x, up.y, up.z, 0.0f },
                 { forward.x, forward.y, forward.z, 0.0f },
                 { from.x, from.y, from.z, 1.0f } } };

    return res;
}

// TODO: ifdef stdio.h?
inline void print_m4(m4 a)
{
    for (s32 i = 0; i < 4; ++i) {
        printf("%f, %f, %f, %f\n", a.e[i][0], a.e[i][1], a.e[i][2], a.e[i][3]);
    }
}

}  // namespace mat

// ===============================================================================================
// #RECTANGLE 2
// ===============================================================================================

struct rect2
{
    v2 min;
    v2 max;
};

// =================================================kkkk==============================================
// #RECTANGLE 3
// ===============================================================================================

struct rect3
{
    v3 min;
    v3 max;
};

inline rect3 rect3_init(rect2 a)
{
    rect3 res;

    res.min = v3_init(a.min);
    res.max = v3_init(a.max);

    return res;
}

// ===============================================================================================
// #RECTANGLE FUNCS
// ===============================================================================================

namespace rec
{

inline v2 max_corner(rect2 a)
{
    v2 res = a.max;
    return res;
}

inline v3 max_corner(rect3 a)
{
    v3 res = a.max;
    return res;
}

inline v2 min_corner(rect2 a)
{
    v2 res = a.min;
    return res;
}

inline v3 min_corner(rect3 a)
{
    v3 res = a.min;
    return res;
}

inline rect2 min_max(v2 min, v2 max)
{
    rect2 res;

    res.min = min;
    res.max = max;

    return res;
}

inline rect3 min_max(v3 min, v3 max)
{
    rect3 res;

    res.min = min;
    res.max = max;

    return res;
}

inline rect2 min_dim(v2 min, v2 dim)
{
    rect2 res;

    res.min = min;
    res.max = min + dim;

    return res;
}

inline rect3 min_dim(v3 min, v3 dim)
{
    rect3 res;

    res.min = min;
    res.max = min + dim;

    return res;
}

inline rect2 center_half_dim(v2 center, v2 half_dim)
{
    rect2 res;

    res.min = center - half_dim;
    res.max = center + half_dim;

    return res;
}

inline rect3 center_half_dim(v3 center, v3 half_dim)
{
    rect3 res;

    res.min = center - half_dim;
    res.max = center + half_dim;

    return res;
}

inline rect2 center_dim(v2 center, v2 dim)
{
    rect2 res = center_half_dim(center, dim * 0.5f);

    return res;
}

inline rect3 center_dim(v3 center, v3 dim)
{
    rect3 res = center_half_dim(center, dim * 0.5f);

    return res;
}

inline v2 center(rect2 a)
{
    v2 res = 0.5f * (a.min + a.max);

    return res;
}

inline v3 center(rect3 a)
{
    v3 res = 0.5f * (a.min + a.max);

    return res;
}

inline bool is_inside(rect2 a, v2 test)
{
    bool res = test.x >= a.min.x && test.y >= a.min.y && test.x <= a.max.x && test.y <= a.max.y;
    return res;
}

inline bool is_inside(rect3 a, v3 test)
{
    bool res = test.x >= a.min.x && test.y >= a.min.y && test.x <= a.max.x && test.y <= a.max.y &&
               test.z >= a.min.z && test.z <= a.max.z;
    return res;
}

inline rect2 add_dim(rect2 a, v2 dim)
{
    rect2 res;

    res.min = a.min - dim;
    res.max = a.max + dim;

    return res;
}

inline rect3 add_dim(rect3 a, v3 dim)
{
    rect3 res;

    res.min = a.min - dim;
    res.max = a.max + dim;

    return res;
}

inline rect2 add_radius(rect2 a, f32 r)
{
    v2 r_ = { r, r };
    return add_dim(a, r_);
}

inline rect3 add_radius(rect3 a, f32 r)
{
    v3 r_ = { r, r, r };
    return add_dim(a, r_);
}
inline bool intersect(rect2 a, rect2 b)
{
    bool res = !(b.max.x < a.min.x || b.min.x > a.max.x || b.max.y < a.min.y || b.min.y > a.max.y);

    return res;
}

inline bool intersect(rect3 a, rect3 b)
{
    bool res = !(b.max.x < a.min.x || b.min.x > a.max.x || b.max.y < a.min.y || b.min.y > a.max.y ||
                 b.max.z < a.min.z || b.min.z > a.max.z);

    return res;
}

}  // namespace rec

}  // namespace tom
#endif  // TOMATO_MATH_HPP_
