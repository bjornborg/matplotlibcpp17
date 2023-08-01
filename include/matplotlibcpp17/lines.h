/**
 * @file lines.h
 * @brief corresponding header for matplotlib.lines
 **/
#pragma once

#include <matplotlibcpp17/common.h>

#include <pybind11/pybind11.h>

/**
 * @brief A wrapper class for matplotlib.lines.line2d
 **/

namespace matplotlibcpp17::lines {

struct DECL_STRUCT_ATTR Line2D : public BaseWrapper {
public:
  Line2D() {}
  Line2D(const pybind11::object &obj) {
    self = obj;
    load_attrs();
  }
  Line2D(pybind11::object &&obj) {
    self = std::move(obj);
    load_attrs();
  }

  ObjectWrapper set_xdata(const pybind11::tuple &args = pybind11::tuple());

private:
  void load_attrs() { LOAD_FUNC_ATTR(set_xdata, self); }
  pybind11::object set_xdata_attr;
};

inline ObjectWrapper Line2D::set_xdata(const pybind11::tuple &args) {
  pybind11::object ret = set_xdata_attr(*args);
  return ObjectWrapper(std::move(ret));
}

} // namespace matplotlibcpp17::lines
