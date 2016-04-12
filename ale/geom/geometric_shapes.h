/*~-------------------------------------------------------------------------~~*
 *     _   ______________     ___    __    ______
 *    / | / / ____/ ____/    /   |  / /   / ____/
 *   /  |/ / / __/ /  ______/ /| | / /   / __/   
 *  / /|  / /_/ / /__/_____/ ___ |/ /___/ /___   
 * /_/ |_/\____/\____/    /_/  |_/_____/_____/   
 * 
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
/*!
 *
 * \file geometric_shapes.h
 * 
 * \brief A geometric shapes enum class.
 *
 ******************************************************************************/
#pragma once


namespace ale {
namespace geom {

//////////////////////////////////////////////////////////////////////////////
// the 
//////////////////////////////////////////////////////////////////////////////
enum class geometric_shapes_t 
{
  triangle,
  quadrilateral,
  polygon,
  tetrahedron,
  hexahedron 
};


} // namespace geom
} // namespace ale