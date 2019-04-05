#include "submodule_core.hpp"

#include <glm/glm.hpp>

#include "shake/core/log.hpp"
#include "shake/core/contracts/contracts.hpp"
#include "shake/core/math/math.hpp"
#include "shake/core/math/transform_2d.hpp"
#include "shake/core/math/transform_3d.hpp"
#include "shake/python/submodules/macro_def_member.hpp"

namespace shake {
namespace python {


//----------------------------------------------------------------
void register_core(pybind11::module& shake_module)
{
	auto core_module = shake_module.def_submodule("core");

	core_module.def
    ( 
        "log",     
        []( std::string& s ) 
        { LOG(s); }
    );

	core_module.def
    ( 
        "check",   
        []( bool b, std::string& s ) 
        { CHECK(b, s); } 
    );

	//----------------------------------------------------------------
	pybind11::class_< shake::Transform2D >( core_module, "Transform2D" )
		DEF_CTOR();

	pybind11::class_< shake::Transform3D >( core_module, "Transform3D" )
		DEF_CTOR();
}


} // namespace python
} // namespace shake