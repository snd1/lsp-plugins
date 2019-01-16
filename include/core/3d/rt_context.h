/*
 * RTContext.h
 *
 *  Created on: 15 янв. 2019 г.
 *      Author: sadko
 */

#ifndef INCLUDE_CORE_3D_RT_CONTEXT_H_
#define INCLUDE_CORE_3D_RT_CONTEXT_H_

#include <core/3d/common.h>
#include <core/3d/Allocator3D.h>
#include <core/3d/Scene3D.h>
#include <core/3d/View3D.h>
#include <data/cstorage.h>

namespace lsp
{
    typedef struct rt_shared_t
    {
        cstorage<v_triangle3d_t>    matched;    // List of matched triangles (for debug)
        cstorage<v_triangle3d_t>    ignored;    // List of ignored triangles (for debug)
        ssize_t                     step;       // Trace step
        ssize_t                     breakpoint; // Trace breakpoint
        Scene3D                    *scene;
        View3D                     *view;
    } rt_shared_t;

    enum rt_context_state_t
    {
        S_SCAN_OBJECTS,
        S_CULL_VIEW,
        S_PARTITION
    };

    typedef struct rt_context_t
    {
        rt_view_t                   view;       // Ray tracing point of view
        rt_shared_t                *shared;     // Shared settings
        rt_context_state_t          state;      // Context state
        size_t                      index;      // Plane index

        Allocator3D<rt_vertex_t>    vertex;     // Collection of vertexes
        Allocator3D<rt_edge_t>      edge;       // Collection of edges
        Allocator3D<rt_triangle_t>  triangle;   // Collection of triangles

        // Construction/destruction
        explicit rt_context_t(rt_shared_t *shared);
        ~rt_context_t();

        // Methods
        /**
         * Swap internal mesh contents with another context
         * @param src source context to perform swap
         */
        void swap(rt_context_t *src);
    } rt_context_t;

} /* namespace mtest */

#endif /* INCLUDE_CORE_3D_RT_CONTEXT_H_ */
