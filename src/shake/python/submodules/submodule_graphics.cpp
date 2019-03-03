#include "submodule_graphics.hpp"


#include <pybind11/stl.h>

#include "content/content_manager.hpp"
#include "core/log.hpp"
#include "core/contracts/contracts.hpp"
#include "graphics/camera.hpp"
#include "graphics/context.hpp"
#include "graphics/gl.hpp"
#include "graphics/render_pack.hpp"
#include "graphics/geometry/voxel_grid.hpp"
#include "graphics/material/material.hpp"
#include "io/path.hpp"
#include "python/submodules/macro_def_member.hpp"


namespace shake {
namespace python {


//----------------------------------------------------------------
void register_graphics( pybind11::module& shake_module )
{
    using namespace shake::content;
    using namespace shake::graphics;
    using namespace shake::io;

    auto graphics_module = shake_module.def_submodule( "graphics" );

    //----------------------------------------------------------------
	pybind11::class_<Camera, std::shared_ptr<Camera>>( graphics_module, "Camera" )
		DEF_CTOR( size_t, size_t )
        DEF_MEMBER( Camera, update );

    graphics_module.def( "set_current_camera", &set_current_camera );

    //----------------------------------------------------------------
    pybind11::enum_<gl::PolygonMode>( graphics_module, "PolygonMode" )
        .value( "Fill", gl::PolygonMode::Fill )
        .value( "Line", gl::PolygonMode::Line );

    pybind11::enum_<gl::FramebufferBitFlag>( graphics_module, "FrameBufferBitFlag" )
        .value( "Color", gl::FramebufferBitFlag::Color )
        .value( "Depth", gl::FramebufferBitFlag::Depth );

    graphics_module.def( "get_current_polygon_mode", &gl::get_current_polygon_mode );
    graphics_module.def( "set_current_polygon_mode", &gl::set_current_polygon_mode );

    graphics_module.def( "clear", &gl::clear );

    //----------------------------------------------------------------
#define REGISTER_TEMPLATE_MAKE_RENDERPACK( render_pack_type, render_pack_type_name, geometry_type, geometry_type_name, default_material_path ) \
    graphics_module.def( ( std::string( "make_") + render_pack_type_name + "__" + geometry_type_name ).c_str(), [] \
    ( \
        const std::string& geometry_path, \
        const std::string& material_path \
    ) \
        -> render_pack_type \
    { \
        auto& content_manager = ContentManager::get_instance(); \
        \
        return render_pack_type \
        { \
            content_manager.get_or_load<geometry_type>( Path{ geometry_path } ), \
            content_manager.get_or_load<Material>( Path{ material_path } ) \
        }; \
    }, \
    pybind11::arg( "geometry_path" ), \
    pybind11::arg( "material_path" ) = default_material_path \
    );

#define REGISTER_TEMPLATE_MAKE_RENDERPACK_2D( geometry_type, geometry_type_name, default_material_path ) \
    REGISTER_TEMPLATE_MAKE_RENDERPACK( RenderPack2D, "render_pack_2d", geometry_type, geometry_type_name, default_material_path )

#define REGISTER_TEMPLATE_MAKE_RENDERPACK_3D( geometry_type, geometry_type_name, default_material_path ) \
    REGISTER_TEMPLATE_MAKE_RENDERPACK( RenderPack3D, "render_pack_3d", geometry_type, geometry_type_name, default_material_path )
//----------------------------------------------------------------

        pybind11::class_< RenderPack2D >( graphics_module, "RenderPack2D" );
        pybind11::class_< RenderPack3D >( graphics_module, "RenderPack3D" );

        REGISTER_TEMPLATE_MAKE_RENDERPACK_3D( VoxelGrid, "voxel_grid", "materials/default_voxel_material.json" )

            //----------------------------------------------------------------
#undef REGISTER_TEMPLATE_MAKE_RENDERPACK
#undef REGISTER_TEMPLATE_MAKE_RENDERPACK_2D
#undef REGISTER_TEMPLATE_MAKE_RENDERPACK_3D
        }

    } // namespace python
} // namespace shake