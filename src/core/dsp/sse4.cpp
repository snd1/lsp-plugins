/*
 * sse.cpp
 *
 *  Created on: 04 марта 2016 г.
 *      Author: sadko
 */

#include <core/types.h>
#include <core/debug.h>
#include <core/dsp.h>
#include <core/bits.h>

#include <core/x86/features.h>

#define CORE_X86_SSE4_IMPL
#define CORE_X86_SSE_IMPL

namespace lsp
{
    namespace sse
    {
        #include <core/x86/sse/const.h>
    }
}

#include <core/x86/sse4/3dmath.h>

#undef CORE_X86_SSE_IMPL
#undef CORE_X86_SSE4_IMPL

namespace lsp
{
    namespace sse4
    {
        using namespace x86;
        
        #define EXPORT1(function)                   dsp::function = sse4::function

        void dsp_init(const cpu_features_t *f)
        {
            if (!(f->features & CPU_OPTION_SSE4_1))
                return;

            // Additional xmm registers are available only in 64-bit mode
            lsp_trace("Optimizing DSP for SSE4 instruction set");

            // 3D Math
            EXPORT1(normalize_point);
            EXPORT1(scale_point1);
            EXPORT1(scale_point2);

            EXPORT1(normalize_vector);
            EXPORT1(scale_vector1);
            EXPORT1(scale_vector2);

            EXPORT1(check_point3d_on_triangle_p3p);
            EXPORT1(check_point3d_on_triangle_pvp);
            EXPORT1(check_point3d_on_triangle_tp);

            EXPORT1(find_intersection3d_rt);
        }
        
        #undef EXPORT1
    }

}