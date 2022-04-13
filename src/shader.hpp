#ifndef TOMATO_SHADER_HPP_
#define TOMATO_SHADER_HPP_

#include "common.hpp"
#include "math.hpp"

// TODO: phase these out
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

namespace tom
{
class shader
{
public:
    enum class type
    {
        vertex,
        fragment,
    };

public:
    shader(const std::string &vert_path, const std::string &frag_path);
    ~shader();

    u32 get_id() const { return _id; }
    std::string get_vert_code() const { return _vert_code; }
    std::string get_frag_code() const { return _frag_code; }

    void use();
    void set_b32(const char *name, b32 val) const;
    void set_s32(const char *name, s32 val) const;
    void set_f32(const char *name, f32 val) const;
    void set_vec4(const char *name, v4) const;
    void set_mat4(const char *name, m4) const;

private:
    u32 _id;
    std::string _vert_code;
    std::string _frag_code;

    void check_shader_compile_errors(u32 shader_id, shader::type type);
    std::string read_shader_code(const std::string &path);
};

}  // namespace tom

#endif