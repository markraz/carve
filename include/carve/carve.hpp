// Begin License:
// Copyright (C) 2006-2008 Tobias Sargeant (tobias.sargeant@gmail.com).
// All rights reserved.
//
// This file is part of the Carve CSG Library (http://carve-csg.com/)
//
// This file may be used under the terms of the GNU General Public
// License version 2.0 as published by the Free Software Foundation
// and appearing in the file LICENSE.GPL2 included in the packaging of
// this file.
//
// This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
// INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE.
// End:

#pragma once

#if defined(_MSC_VER)
#  include <carve/vcpp_config.h>
#else
#  include <carve/config.h>
#endif

#if defined(WIN32)
#  include <carve/win32.h>
#elif defined(__GNUC__)
#  include <carve/gnu_cxx.h>
#endif

#include <math.h>

#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <sstream>
#include <iomanip>

#include <carve/collection.hpp>
#include <carve/util.hpp>

#include <stdarg.h>

#define STR(x) #x
#define XSTR(x) STR(x)

/**
 * \brief Top level Carve namespace.
 */
namespace carve {
  static struct noinit_t {} NOINIT;

  inline std::string fmtstring(const char *fmt, ...);

  /**
   * \brief Base class for all Carve exceptions.
   */
  struct exception {
  private:
    mutable std::string err;
    mutable std::ostringstream accum;

  public:
    exception(const std::string &e) : err(e), accum() { }
    exception() : err(), accum() { }
    exception(const exception &e) : err(e.str()), accum() { }

    const std::string &str() const {
      if (accum.tellp()) {
        err = accum.str();
        accum.str("");
      }
      return err;
    }

    template<typename T>
    exception &operator<<(const T &t) {
      accum << t;
      return *this;
    }
  };

  template<typename T>
  struct index_sort {
    const T &vals;
    index_sort(const T &_vals) : vals(_vals) {}
    template<typename U>
    bool operator()(const U &a, const U &b) {
      return vals[a] < vals[b];
    }
  };

  enum RayIntersectionClass {
    RR_DEGENERATE = -2,
    RR_PARALLEL = -1,
    RR_NO_INTERSECTION = 0,
    RR_INTERSECTION = 1
  };

  enum LineIntersectionClass {
    COLINEAR        = -1,
    NO_INTERSECTION = 0,
    INTERSECTION_LL = 1,
    INTERSECTION_PL = 2,
    INTERSECTION_LP = 3,
    INTERSECTION_PP = 4
  };

  enum PointClass {
    POINT_UNK = -2,
    POINT_OUT = -1,
    POINT_ON = 0,
    POINT_IN = 1,
    POINT_VERTEX = 2,
    POINT_EDGE = 3
  };

  enum IntersectionClass {
    INTERSECT_BAD = -1,
    INTERSECT_NONE = 0,
    INTERSECT_FACE = 1,
    INTERSECT_VERTEX = 2,
    INTERSECT_EDGE = 3,
    INTERSECT_PLANE = 4,
  };

  extern double EPSILON;
  extern double EPSILON2;

  static inline void setEpsilon(double ep) { EPSILON = ep; EPSILON2 = ep * ep; }

  template<typename T>
  struct identity_t {
    typedef T argument_type;
    typedef T result_type;
    const T &operator()(const T &t) const { return t; }
  };
}


#define ASSERT(x) do { if (!(x)) throw carve::exception() << __FILE__ << ":" << __LINE__ << "  " << #x; } while(0)
