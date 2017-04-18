#ifndef BOOST_GEOMETRY_PROJECTIONS_DENOY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_DENOY_HPP

// Boost.Geometry - extensions-gis-projections (based on PROJ4)
// This file is automatically generated. DO NOT EDIT.

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels

// Last updated version of proj: 4.9.1

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <boost/geometry/extensions/gis/projections/impl/base_static.hpp>
#include <boost/geometry/extensions/gis/projections/impl/base_dynamic.hpp>
#include <boost/geometry/extensions/gis/projections/impl/projects.hpp>
#include <boost/geometry/extensions/gis/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry { namespace projections
{
    struct denoy {};

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {
        namespace denoy
        {

            static const double C0 = 0.95;
            static const double C1 = -.08333333333333333333;
            static const double C3 = .00166666666666666666;
            static const double D1 = 0.9;
            static const double D5 = 0.03;

            // template class, using CRTP to implement forward/inverse
            template <typename Geographic, typename Cartesian, typename Parameters>
            struct base_denoy_spheroid : public base_t_f<base_denoy_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>
            {

                 typedef double geographic_type;
                 typedef double cartesian_type;


                inline base_denoy_spheroid(const Parameters& par)
                    : base_t_f<base_denoy_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>(*this, par) {}

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(geographic_type& lp_lon, geographic_type& lp_lat, cartesian_type& xy_x, cartesian_type& xy_y) const
                {
                    xy_y = lp_lat;
                    xy_x = lp_lon;
                    lp_lon = fabs(lp_lon);
                    xy_x *= cos((C0 + lp_lon * (C1 + lp_lon * lp_lon * C3)) *
                        (lp_lat * (D1 + D5 * lp_lat * lp_lat * lp_lat * lp_lat)));
                }

                static inline std::string get_name()
                {
                    return "denoy_spheroid";
                }

            };

            // Denoyer Semi-Elliptical
            template <typename Parameters>
            void setup_denoy(Parameters& par)
            {
                par.es = 0.;
            }

        } // namespace denoy

        /*!
            \brief Denoyer Semi-Elliptical projection
            \ingroup projections
            \tparam Geographic latlong point type
            \tparam Cartesian xy point type
            \tparam Parameters parameter type
            \par Projection characteristics
             - Pseudocylindrical
             - no inverse
             - Spheroid
            \par Example
            \image html ex_denoy.gif
        */
        template <typename Geographic, typename Cartesian, typename Parameters = parameters>
        struct denoy_spheroid : public detail::denoy::base_denoy_spheroid<Geographic, Cartesian, Parameters>
        {
            inline denoy_spheroid(const Parameters& par) : detail::denoy::base_denoy_spheroid<Geographic, Cartesian, Parameters>(par)
            {
                detail::denoy::setup_denoy(this->m_par);
            }
        };

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION(projections::denoy, denoy_spheroid, denoy_spheroid)

        // Factory entry(s)
        template <typename Geographic, typename Cartesian, typename Parameters>
        class denoy_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual base_v<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_f<denoy_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        inline void denoy_init(detail::base_factory<Geographic, Cartesian, Parameters>& factory)
        {
            factory.add_to_factory("denoy", new denoy_entry<Geographic, Cartesian, Parameters>);
        }

    } // namespace detail
    #endif // doxygen

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_DENOY_HPP

