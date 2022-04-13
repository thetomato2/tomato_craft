#ifndef TOMATO_MATH_HPP_
#define TOMATO_MATH_HPP_

#include "common.hpp"
#include "intrinsic.hpp"

namespace tom
{
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
        f32 _ignored0;
    };
    f32 e[4];
};

inline v4 v4_init(v2 a, f32 z = 0.f, f32 w = 0.f)
{
    v4 res;
    res.x = a.x;
    res.y = a.y;
    res.z = z;
    res.w = w;

    return res;
}

inline v4 v4_init(v3 a, f32 w = 0.f)
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

    res.x = a.y * b.y - a.z * b.y;
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
    v3 res;

    res.x = a.x / len;
    res.y = a.y / len;
    res.z = a.z / len;

    return res;
}

}  // namespace vec

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

    // NOTE: this should unroll but...

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
inline m4 identity()
{
    // clang-format off
    m4 res = { { { 1, 0, 0, 0 }, 
                 { 0, 1, 0, 0 }, 
                 { 0, 0, 1, 0 }, 
                 { 0, 0, 0, 1 } } };
    // clang-format on

    return res;
}

inline m4 rot_x(f32 a)
{
    f32 c = cos(a);
    f32 s = sin(a);

    // clang-format off
    m4 res = { { { 1, 0, 0, 0 }, 
                 { 0, c,-s, 0 }, 
                 { 0, s, c, 0 }, 
                 { 0, 0, 0, 1 } } };

    // clang-format on

    return res;
}

inline m4 rot_y(f32 a)
{
    f32 c = cos(a);
    f32 s = sin(a);

    // clang-format off
    m4 res = { { { c, 0, s, 0 }, 
                 { 0, 1, 0, 0 }, 
                 {-s, 0, c, 0 }, 
                 { 0, 0, 0, 1 } } };

    // clang-format on

    return res;
}

inline m4 rot_y(m4 a, f32 b)
{
    f32 c = cos(b);
    f32 s = sin(b);

    a.e[0][0] *= c;
    a.e[0][2] *= s;
    a.e[2][0] *= -s;
    a.e[2][3] *= c;

    return a;
}

inline m4 rot_z(f32 a)
{
    f32 c = cos(a);
    f32 s = sin(a);

    // clang-format off
    m4 res = { { { c,-s, 0, 0 }, 
                 { s, c, 0, 0 }, 
                 { 0, 0, 1, 0 }, 
                 { 0, 0, 0, 1 } } };

    // clang-format on

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

    // clang-format off
    m4 res = { { { a * c,     0.0f,  0.0f, 0.0f }, 
                 {     0.0f, b * c,  0.0f, 0.0f }, 
                 {     0.0f,  0.0f,     d,   e }, 
                 {     0.0f,   0.0f, -1.0f, 0.0f } } };
    // clang-format on

    return res;
}

inline m4 proj_ortho(f32 aspect_ratio)
{
    f32 a = 1.0f;
    f32 b = aspect_ratio;

    // clang-format off
    m4 res = { { { a, 0, 0, 0 }, 
                 { 0, b, 0, 0 }, 
                 { 0, 0, 1, 0 }, 
                 { 0, 0, 0, 1 } } };
    // clang-format on

    return res;
}

inline m4 col_3x3(v3 x, v3 y, v3 z)
{
    // clang-format off
    m4 res = { { { x.x, y.x, z.x, 0 }, 
                 { x.y, y.y, z.y, 0 }, 
                 { x.z, y.z, z.z, 0 }, 
                 {   0,   0,   0, 1 } } };
    // clang-format on

    return res;
}

inline m4 row_3x3(v3 x, v3 y, v3 z)
{
    // clang-format off
    m4 res = { { { x.x, x.y, x.z, 0 }, 
                 { y.x, y.y, y.z, 0 }, 
                 { z.x, z.y, z.z, 0 }, 
                 {   0,   0,   0, 1 } } };
    // clang-format on

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

inline m4 cam_transform(v3 x, v3 y, v3 z, v3 p)
{
    m4 res = row_3x3(x, y, z);

    res = translate(res, -(res * p));

    return res;
}

inline m4 loot_at(v3 from, v3 to)
{
    v3 t       = { 0.0f, 1.0f, 0.0f };
    v3 forward = vec::normalize(from - to);
    v3 right   = vec::cross(vec::normalize(t), forward);
    v3 up      = vec::cross(forward, right);

    // clang-format off
    m4 res = { { { right.x,   right.y,    right.z,   0 }, 
                 { up.x,      up.y,       up.z,      0 }, 
                 { forward.x, forward.y,  forward.z, 0 }, 
                 { from.x,    from.y,     from.z,    1 } } };
    // clang-format on

    return res;
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

// ===============================================================================================
// #FREE_FUNCS
// ===============================================================================================
namespace math
{
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

}  // namespace tom
#endif  // TOMATO_MATH_HPP_