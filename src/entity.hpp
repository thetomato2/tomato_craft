#ifndef TOMATO_ENTITY_HPP_
#define TOMATO_ENTITY_HPP_

#include "common.hpp"
#include "opengl.hpp"
#include "model.hpp"

namespace tom
{
class entity
{
public:
    v3 pos;

    entity();

    const char get_name() const { return _name; }

private:
    const char *_name;
    model _model;
};

}  // namespace tom

#endif  // !TOMATO_ENTITY_HPP_