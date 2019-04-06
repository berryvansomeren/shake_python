#include "submodule_content.hpp"

#include "shake/content/content_manager.hpp"

#include "macro_def_member.hpp"

namespace shake {
namespace python {

//----------------------------------------------------------------
void register_content
( 
    pybind11::module& shake_module 
)
{
    using namespace shake::content;

    auto content_module = shake_module.def_submodule( "content" );

    DEF_CLASS( content_module, ContentManager ) 
    ;
}

} // namespace python
} // namespace shake