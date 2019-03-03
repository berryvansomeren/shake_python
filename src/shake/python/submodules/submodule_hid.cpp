#include "submodule_hid.hpp"


#include "hid/keyboard.hpp"
#include "hid/mouse.hpp"
#include "hid/window.hpp"

#include "macro_def_member.hpp"


namespace shake {
namespace python {

namespace { // anonymous


//----------------------------------------------------------------
void register_keyboard
( 
    pybind11::module& hid_module 
)
{
    auto keyboard_module = hid_module.def_submodule( "Keyboard" );
	
    keyboard_module.def
    (
        "is_up", 
        []( const Keyboard::Key& key ) 
        { return Keyboard::get_instance().is_up( key ); }
    );

	keyboard_module.def
    (
        "is_down", 
        []( const Keyboard::Key& key ) 
        { return Keyboard::get_instance().is_down( key ); }
    );

	pybind11::enum_<Keyboard::Key>( keyboard_module, "Key" )
		.value( "A", Keyboard::Key::A )
		.value( "B", Keyboard::Key::B )
		.value( "C", Keyboard::Key::C )
		.value( "D", Keyboard::Key::D )
		.value( "E", Keyboard::Key::E )
		.value( "F", Keyboard::Key::F )
		.value( "G", Keyboard::Key::G )
		.value( "H", Keyboard::Key::H )
		.value( "I", Keyboard::Key::I )
		.value( "J", Keyboard::Key::J )
		.value( "K", Keyboard::Key::K )
		.value( "L", Keyboard::Key::L )
		.value( "M", Keyboard::Key::M )
		.value( "N", Keyboard::Key::N )
		.value( "O", Keyboard::Key::O )
		.value( "P", Keyboard::Key::P )
		.value( "Q", Keyboard::Key::Q )
		.value( "R", Keyboard::Key::R )
		.value( "S", Keyboard::Key::S )
		.value( "T", Keyboard::Key::T )
		.value( "U", Keyboard::Key::U )
		.value( "V", Keyboard::Key::V )
		.value( "W", Keyboard::Key::W )
		.value( "X", Keyboard::Key::X )
		.value( "Y", Keyboard::Key::Y )
		.value( "Z", Keyboard::Key::Z );
}

//----------------------------------------------------------------
void register_mouse
( 
    pybind11::module& hid_module 
)
{
    auto mouse_module = hid_module.def_submodule( "Mouse" );

	pybind11::enum_<Mouse::Key>( mouse_module, "Key" )
		.value( "Left",  Mouse::Key::Left  )
		.value( "Right", Mouse::Key::Right )
		.value( "Alt_1", Mouse::Key::Alt_1 )
		.value( "Alt_2", Mouse::Key::Alt_2 )
		.value( "Alt_3", Mouse::Key::Alt_3 )
		.value( "Alt_4", Mouse::Key::Alt_4 )
		.value( "Alt_5", Mouse::Key::Alt_5 )
		.value( "Alt_6", Mouse::Key::Alt_6 );

	mouse_module.def
    ( 
        "is_up",   
        []( const Mouse::Key& key ) 
        { return Mouse::get_instance().is_up( key ); }
    );

	mouse_module.def
    ( 
        "is_down", 
        []( const Mouse::Key& key ) 
        { return Mouse::get_instance().is_down( key ); }
    );
}

//----------------------------------------------------------------
void register_window
( 
    pybind11::module& hid_module 
)
{
    using namespace shake;

#define DEF_WINDOW_MEMBER( member_name ) \
    DEF_MEMBER( Window, member_name )

	pybind11::class_< Window >( hid_module, "Window" )
        DEF_WINDOW_MEMBER( swap_buffers )
    ;

#undef DEF_WINDOW_MEMBER
}

} // namespace anonymous


//----------------------------------------------------------------
void register_hid
( 
    pybind11::module& shake_module 
)
{
    auto hid_module = shake_module.def_submodule( "hid" );

	register_keyboard   ( hid_module );
    register_mouse      ( hid_module );
    register_window     ( hid_module );
}


} // namespace python
} // namespace shake