#include "texture.hpp"

#include <stb_image.h>

namespace tom
{
texture::texture() : _active(false)
{
}

texture::texture(texture::type type, GLenum texture_target, const char *path,
                 ogl::wgl_func_ptrs gfx)
{
    _type       = type;
    _tex_target = texture_target;
    _path       = path;
    _gfx        = gfx;

    // texture 1
    // ---------
    ogl::gen_tex(1, &_tex_obj);
    ogl::bind_tex(_tex_target, _tex_obj);
    // set the texture wrapping parameters
    ogl::tex_params_s32(_tex_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    ogl::tex_params_s32(_tex_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    ogl::tex_params_s32(_tex_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    ogl::tex_params_s32(_tex_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    s32 width, height, n_channels;
    stbi_set_flip_vertically_on_load(true);
    byt *data = stbi_load(_path, &width, &height, &n_channels, 0);
    if (data) {
        ogl::tex_img_2d(_tex_target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        _gfx.gen_mipmap(_tex_target);
    } else {
        printf("ERROR-> Failed to load texture! - %s\n", _path);
        INVALID_CODE_PATH;
    }
    stbi_image_free(data);

    _active = true;
}

void texture::bind(GLenum tex_unit)
{
    _gfx.active_tex(tex_unit);
    ogl::bind_tex(_tex_target, _tex_obj);
}

}  // namespace tom
