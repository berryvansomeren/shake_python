#ifndef MACRO_DEF_MEMBER_HPP
#define MACRO_DEF_MEMBER_HPP

//----------------------------------------------------------------
#define DEF_CTOR( ... ) \
    .def( pybind11::init<__VA_ARGS__>() )

//----------------------------------------------------------------
// Use this to disambiguate between overloads

// Use this version if no overloads exist
#define DEF_MEMBER( classname, member_name ) \
    .def( #member_name, &classname::member_name )

// Use this version to disambiguate overloads based on arguments
#define DEF_MEMBER_OVERLOAD( classname, member_name, /* member_argument_types */ ... ) \
    .def( #member_name, pybind11::overload_cast<__VA_ARGS__>( &classname::member_name ) )

// Use this version to disambiguate overloads based on constness
#define DEF_MEMBER_OVERLOAD_CONST( classname, member_name, /* member_argument_types */ ... ) \
    .def( #member_name, pybind11::overload_cast<__VA_ARGS__>( &classname::member_name, pybind11::const_ ) )

//----------------------------------------------------------------
// Use with template functions, unless you can disamiguate on parameters alone! Then use the above!
// The template type will be postfixed to the name of the function.

// Use this version if no overloads exist
#define DEF_TEMPLATE_MEMBER( classname, member_name, template_type, template_type_name ) \
    .def( ( std::string( #member_name ) + "__" + template_type_name ).c_str(), &classname::member_name<template_type> )

// Use this version to disambiguate overloads based on arguments
#define DEF_TEMPLATE_MEMBER_OVERLOAD( classname, member_name, template_type, template_type_name, ... ) \
    .def( ( std::string( #member_name ) + "__" + template_type_name ).c_str(), \
    pybind11::overload_cast<__VA_ARGS__>( &classname::member_name<template_type> ) )

// Use this version to disambiguate overloads based on constness
#define DEF_TEMPLATE_MEMBER_OVERLOAD_CONST( classname, member_name, template_type, template_type_name, ... ) \
    .def( ( std::string( #member_name ) + "__" + template_type_name ).c_str(), \
    pybind11::overload_cast<__VA_ARGS__>( &classname::member_name<template_type>, pybind11::const_ ) )

#endif // MACRO_DEF_MEMBER_HPP
