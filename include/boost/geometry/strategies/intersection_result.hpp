// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_INTERSECTION_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_INTERSECTION_RESULT_HPP

#if defined(HAVE_MATRIX_AS_STRING)
#include <string>
#endif

#include <cstddef>



namespace boost { namespace geometry
{

// TODO - This struct is not used in the library. For now commented out because
//        it interferes with the newly added de9im namespace/functionality.
//        Remove it later if not needed.

/*!
    \brief Dimensionally Extended 9 Intersection Matrix
    \details
    \ingroup overlay
    \see http://gis.hsr.ch/wiki/images/3/3d/9dem_springer.pdf
*/
/*struct de9im
{
    int ii, ib, ie,
        bi, bb, be,
        ei, eb, ee;

    inline de9im()
        : ii(-1), ib(-1), ie(-1)
        , bi(-1), bb(-1), be(-1)
        , ei(-1), eb(-1), ee(-1)
    {
    }

    inline de9im(int ii0, int ib0, int ie0,
        int bi0, int bb0, int be0,
        int ei0, int eb0, int ee0)
        : ii(ii0), ib(ib0), ie(ie0)
        , bi(bi0), bb(bb0), be(be0)
        , ei(ei0), eb(eb0), ee(ee0)
    {}

    inline bool equals() const
    {
        return ii >= 0 && ie < 0 && be < 0 && ei < 0 && eb < 0;
    }

    inline bool disjoint() const
    {
        return ii < 0 && ib < 0 && bi < 0 && bb < 0;
    }

    inline bool intersects() const
    {
        return ii >= 0 || bb >= 0 || bi >= 0 || ib >= 0;
    }

    inline bool touches() const
    {
        return ii < 0 && (bb >= 0 || bi >= 0 || ib >= 0);
    }

    inline bool crosses() const
    {
        return (ii >= 0 && ie >= 0) || (ii == 0);
    }

    inline bool overlaps() const
    {
        return ii >= 0 && ie >= 0 && ei >= 0;
    }

    inline bool within() const
    {
        return ii >= 0 && ie < 0 && be < 0;
    }

    inline bool contains() const
    {
        return ii >= 0 && ei < 0 && eb < 0;
    }


    static inline char as_char(int v)
    {
        return v >= 0 && v < 10 ? static_cast<char>('0' + v) : '-';
    }

#if defined(HAVE_MATRIX_AS_STRING)
    inline std::string matrix_as_string(std::string const& tab, std::string const& nl) const
    {
        std::string ret;
        ret.reserve(9 + tab.length() * 3 + nl.length() * 3);
        ret += tab; ret += as_char(ii); ret += as_char(ib); ret += as_char(ie); ret += nl;
        ret += tab; ret += as_char(bi); ret += as_char(bb); ret += as_char(be); ret += nl;
        ret += tab; ret += as_char(ei); ret += as_char(eb); ret += as_char(ee);
        return ret;
    }

    inline std::string matrix_as_string() const
    {
        return matrix_as_string("", "");
    }
#endif

};

struct de9im_segment : public de9im
{
    bool collinear; // true if segments are aligned (for equal,overlap,touch)
    bool opposite; // true if direction is reversed (for equal,overlap,touch)
    bool parallel;  // true if disjoint but parallel
    bool degenerate; // true for segment(s) of zero length

    double ra, rb; // temp

    inline de9im_segment()
        : de9im()
        , collinear(false)
        , opposite(false)
        , parallel(false)
        , degenerate(false)
    {}

    inline de9im_segment(double a, double b,
        int ii0, int ib0, int ie0,
        int bi0, int bb0, int be0,
        int ei0, int eb0, int ee0,
        bool c = false, bool o = false, bool p = false, bool d = false)
        : de9im(ii0, ib0, ie0, bi0, bb0, be0, ei0, eb0, ee0)
        , collinear(c)
        , opposite(o)
        , parallel(p)
        , degenerate(d)
        , ra(a), rb(b)
    {}


#if defined(HAVE_MATRIX_AS_STRING)
    inline std::string as_string() const
    {
        std::string ret = matrix_as_string();
        ret += collinear ? "c" : "-";
        ret += opposite ? "o" : "-";
        return ret;
    }
#endif
};*/

template <typename SegmentRatio>
struct fraction_type
{
    SegmentRatio robust_ra; // TODO this can be renamed now to "ra"
    SegmentRatio robust_rb;

    bool initialized;
    inline fraction_type()
        : initialized(false)
    {}

    template <typename Info>
    inline void assign(Info const& info)
    {
        initialized = true;
        robust_ra = info.robust_ra;
        robust_rb = info.robust_rb;
    }

    inline void assign(SegmentRatio const& a, SegmentRatio const& b)
    {
        initialized = true;
        robust_ra = a;
        robust_rb = b;
    }

};

//
/*!
\brief return-type for segment-intersection
\note Set in intersection_points.hpp, from segment_intersection_info
*/
template <typename Point, typename SegmentRatio>
struct segment_intersection_points
{
    std::size_t count; // The number of intersection points

    // TODO: combine intersections and fractions in one struct
    Point intersections[2];
    fraction_type<SegmentRatio> fractions[2];
    typedef Point point_type;

    segment_intersection_points()
        : count(0)
    {}
};

// All assigned in cart_intersect, passed to intersection_points
template <typename CoordinateType, typename PromotedType, typename SegmentRatio>
struct segment_intersection_info
{
    typedef PromotedType promoted_type;

    CoordinateType dx_a, dy_a;
    CoordinateType dx_b, dy_b; // TODO b can be removed
    SegmentRatio robust_ra;
    SegmentRatio robust_rb;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_INTERSECTION_RESULT_HPP
