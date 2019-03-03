#include "submodule_application.hpp"

#include <glm/glm.hpp>

#include "main/application.hpp"

#include "core/log.hpp"
#include "core/contracts/contracts.hpp"
#include "core/math/math.hpp"
#include "core/math/transform_2d.hpp"
#include "core/math/transform_3d.hpp"
#include "python/submodules/macro_def_member.hpp"

namespace shake {
namespace python {


//----------------------------------------------------------------
void register_application( pybind11::module& shake_module )
{
#define DEF_APPLICATION_MEMBER( member_name ) \
    DEF_MEMBER( Application, member_name )

    //----------------------------------------------------------------
	pybind11::class_< Application >( shake_module, "Application" )
		DEF_CTOR( const size_t, const size_t, const std::string& )
        DEF_APPLICATION_MEMBER( run )
        DEF_APPLICATION_MEMBER( update )
        DEF_APPLICATION_MEMBER( get_current_frame_time )
        .def( 
            "window", 
            pybind11::overload_cast<>( &Application::window ), 
            pybind11::return_value_policy::reference 
        )
    ;

#undef DEF_APPLICATION_MEMBER
}


} // namespace python
} // namespace shake