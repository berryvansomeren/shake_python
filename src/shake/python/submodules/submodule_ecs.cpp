#include "submodule_ecs.hpp"


#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include "ecs/component/component.hpp"
#include "ecs/system/system.hpp"
#include "ecs/system/python_system.hpp"
#include "ecs/system/render_system.hpp"
#include "ecs/world.hpp"
#include "graphics/render_pack.hpp"
#include "python/submodules/macro_def_member.hpp"


namespace shake {
namespace python {


//----------------------------------------------------------------
void register_ecs( pybind11::module& shake_module )
{
	auto m = shake_module.def_submodule( "ecs" );

	using namespace shake::ecs;
	using namespace shake::graphics;

	//----------------------------------------------------------------
	// ENTITY
	{
		//----------------------------------------------------------------
		pybind11::class_< EntityId >( m, "EntityId" )
			DEF_CTOR( EntityIdInternalType );

        // TODO: Works when running Python, but not when running c++ for some reason.. 
        //pybind11::bind_vector<std::vector<EntityId>>( m, "EntityIdVec" );

	} // ENTITY


//----------------------------------------------------------------
#define DEF_WORLD_MEMBER( member_name ) \
    DEF_MEMBER( World, member_name )

#define DEF_WORLD_TEMPLATE_MEMBERS_COMPONENT( template_type, template_type_name ) \
    DEF_TEMPLATE_MEMBER                 ( World, add_component_to_entity,        template_type, template_type_name ) \
    DEF_TEMPLATE_MEMBER                 ( World, entity_has_component,           template_type, template_type_name ) \
    DEF_TEMPLATE_MEMBER_OVERLOAD        ( World, get_component_from_entity,      template_type, template_type_name, EntityId ) \
    DEF_TEMPLATE_MEMBER_OVERLOAD_CONST  ( World, get_component_from_entity,      template_type, template_type_name, EntityId ) \
    DEF_TEMPLATE_MEMBER                 ( World, destroy_component_from_entity,  template_type, template_type_name )

#define DEF_WORLD_TEMPLATE_MEMBERS_SYSTEM( template_type, template_type_name ) \
    DEF_TEMPLATE_MEMBER( World, add_system, template_type, template_type_name )
//----------------------------------------------------------------

	//----------------------------------------------------------------
	// WORLD
	{
		//----------------------------------------------------------------
		pybind11::class_< World >( m, "World" )
			DEF_CTOR( const std::string& )

			DEF_WORLD_MEMBER( update_systems )

			// entities
			DEF_WORLD_MEMBER( create_entity )
			DEF_WORLD_MEMBER( is_valid_entity )
			DEF_WORLD_MEMBER( destroy_entity )
			DEF_WORLD_MEMBER( get_entity_id_set )

			DEF_WORLD_MEMBER( add_python_system )

			// components
			DEF_WORLD_TEMPLATE_MEMBERS_COMPONENT( RenderComponent2D, "render_component_2d" )
			DEF_WORLD_TEMPLATE_MEMBERS_COMPONENT( RenderComponent3D, "render_component_3d" )
			DEF_WORLD_TEMPLATE_MEMBERS_COMPONENT( TransformComponent2D, "transform_component_2d" )
			DEF_WORLD_TEMPLATE_MEMBERS_COMPONENT( TransformComponent3D, "transform_component_3d" )

			// systems
			// The PythonSystem trampoline should just be interpreted as a System,
			// otherwise the automatic upcasting from Pybind11 will fail.
			DEF_WORLD_TEMPLATE_MEMBERS_SYSTEM( System, "python_system" )
			DEF_WORLD_TEMPLATE_MEMBERS_SYSTEM( RenderSystem, "render_system" )
        ;

	} // WORLD

//----------------------------------------------------------------
#undef DEF_WORLD_MEMBER
#undef DEF_WORLD_TEMPLATE_MEMBERS_COMPONENT
#undef DEF_WORLD_TEMPLATE_MEMBERS_SYSTEM
//----------------------------------------------------------------


	//----------------------------------------------------------------
	// COMPONENTS
	{
		//----------------------------------------------------------------
		pybind11::class_< RenderComponent2D >( m, "RenderComponent2D" )
			DEF_CTOR( const RenderPack2D& );

		pybind11::class_< RenderComponent3D >( m, "RenderComponent3D" )
			DEF_CTOR( const RenderPack3D& );

		pybind11::class_< TransformComponent2D >( m, "TransformComponent2D" )
			DEF_CTOR( const shake::Transform2D& );

		pybind11::class_< TransformComponent3D >( m, "TransformComponent3D" )
			DEF_CTOR( const shake::Transform3D& );

	} // COMPONENTS

	//----------------------------------------------------------------
	// SYSTEMS
	{
		//----------------------------------------------------------------
		// The trampoline class that enables python code to inherit from C++ classes
		pybind11::class_<System, PythonSystem, std::shared_ptr<System> > system( m, "PythonSystem" );
		system
			DEF_CTOR()
			DEF_CTOR( const System& )
			DEF_MEMBER( System, update );


		//----------------------------------------------------------------
		pybind11::class_<RenderSystem, std::shared_ptr<RenderSystem>>( m, "RenderSystem" )
			DEF_CTOR()
			DEF_MEMBER( RenderSystem, update );

		m.def( "call_update", []( System* system ) -> void
		{
			auto vec = std::vector<EntityId> { };
			system->update( 1.3f, nullptr, vec );
		} );

	} // SYSTEMS
}

} // namespace python
} // namespace shake