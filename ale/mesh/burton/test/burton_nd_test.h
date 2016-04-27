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
 * \file burton_test.h
 * 
 * \brief Defines a test fixture.
 *
 ******************************************************************************/
#pragma once

//! test include
#include "burton_test_base.h"

// some general using statements
using std::size_t;
using std::vector;


////////////////////////////////////////////////////////////////////////////////
//! \brief test fixture for creating the mesh
////////////////////////////////////////////////////////////////////////////////
class burton_2d : public burton_test_base {
public: 

  //---------------------------------------------------------------------------
  // Types From Mesh
  //---------------------------------------------------------------------------

  //! \brief the mesh type
  using mesh_t = mesh_2d_t;

  //! \brief the mesh float type
  using real_t   = typename mesh_t::real_t;
  //! \brief the mesh int type
  using integer_t= typename mesh_t::integer_t;
  //! \brief the mesh dimensions
  static constexpr size_t dimensions = mesh_t::num_dimensions();

  //! \brief the point
  using point_t  = typename mesh_t::point_t;
  //! \brief the vector type
  using vector_t = typename mesh_t::vector_t;
  //! \brief the vertex type
  using vertex_t = typename mesh_t::vertex_t;
  //! \brief the vertex type
  using edge_t   = typename mesh_t::edge_t;
  //! \brief the cell type
  using cell_t   = typename mesh_t::cell_t;


  //---------------------------------------------------------------------------
  // Types
  //---------------------------------------------------------------------------
  
  //! \brief number of cells wide
  static constexpr size_t width = 2;
  //! \brief number of cells high
  static constexpr size_t height = 2;

  //! \brief some test tolerance
  static constexpr real_t test_tolerance = ale::common::test_tolerance;



protected:
  
  //---------------------------------------------------------------------------
  //! \brief the test setup function
  //! \remark this function is called before each test
  //---------------------------------------------------------------------------
  virtual void SetUp() {
    auto   width1 = width + 1;
    auto  height1 = height + 1;

    auto num_vert = width1 * height1;
    mesh_.init_parameters( num_vert );

    vector<vertex_t*> vs;
    vs.reserve( num_vert );

    for(size_t j = 0; j < height + 1; ++j){
      for(size_t i = 0; i < width + 1; ++i){
        auto v = mesh_.create_vertex({ i, j });
        vs.push_back(v);
      } // for
    } // for

    for(size_t j = 0; j < height; ++j){
      for(size_t i = 0; i < width; ++i){
        // go over vertices counter clockwise to define cell
        auto c = mesh_.create_cell( {
            vs[i + j * width1],
            vs[i + 1 + j * width1],
            vs[i + 1 + (j + 1) * width1],
            vs[i + (j + 1) * width1] } );
      } // for
    } // for

    mesh_.init();

  } // SetUp

  //---------------------------------------------------------------------------
  //! \brief the test teardown function
  //! \remark this function is called after each test
  //---------------------------------------------------------------------------
  virtual void TearDown() { }



public:


  //---------------------------------------------------------------------------
  //! \brief Determine the cell-cell adjacency information
  //!  
  //! \param[out] cell_idx   The cell-cell adjacency starting index for each cell
  //! \param[out] cell_neigh The cell-cell adjacency information
  //---------------------------------------------------------------------------
  
  template < typename E >
  decltype(auto) get_cell_neighbors( E cell ) {

    vector<E> neighbors;

    for ( auto e : mesh_.edges(cell) ) 
      for ( auto neigh : mesh_.cells(e) ) 
        if ( neigh != cell ) 
          neighbors.push_back( neigh );
      
    return neighbors;
  }


  //---------------------------------------------------------------------------
  // Data members
  //---------------------------------------------------------------------------

  //! \brief the actual mesh object
  mesh_t mesh_;

};


////////////////////////////////////////////////////////////////////////////////
//! \brief test fixture for creating the mesh
////////////////////////////////////////////////////////////////////////////////
class burton_3d : public burton_test_base {
public: 

  //---------------------------------------------------------------------------
  // Types From Mesh
  //---------------------------------------------------------------------------

  //! \brief the mesh type
  using mesh_t = mesh_3d_t;

  //! \brief the mesh float type
  using real_t   = typename mesh_t::real_t;
  //! \brief the mesh int type
  using integer_t= typename mesh_t::integer_t;
  //! \brief the mesh dimensions
  static constexpr size_t dimensions = mesh_t::num_dimensions();

  //! \brief the point
  using point_t  = typename mesh_t::point_t;
  //! \brief the vector type
  using vector_t = typename mesh_t::vector_t;
  //! \brief the vertex type
  using vertex_t = typename mesh_t::vertex_t;
  //! \brief the vertex type
  using edge_t   = typename mesh_t::edge_t;
  //! \brief the cell type
  using cell_t   = typename mesh_t::cell_t;


  //---------------------------------------------------------------------------
  // Types
  //---------------------------------------------------------------------------
  
  //! \brief number of cells wide
  static constexpr size_t num_cells_x = 2;
  static constexpr size_t num_cells_y = 1;
  static constexpr size_t num_cells_z = 1;


  //! \brief comput the number of vertices in each direction
  static constexpr auto num_vert_x = num_cells_x + 1;
  static constexpr auto num_vert_y = num_cells_y + 1;
  static constexpr auto num_vert_z = num_cells_z + 1;
  static constexpr auto num_vert = num_vert_x * num_vert_y * num_vert_z;

  //! \brief comput the number of faces in each direction
  static constexpr auto num_faces = 
    (num_cells_x+1)* num_cells_y   * num_cells_z +
     num_cells_x   *(num_cells_y+1)* num_cells_z +
     num_cells_x   * num_cells_y   *(num_cells_z+1);

  //! \brief some test tolerance
  static constexpr real_t test_tolerance = ale::common::test_tolerance;



protected:
  
  //---------------------------------------------------------------------------
  //! \brief the test setup function
  //! \remark this function is called before each test
  //---------------------------------------------------------------------------
  virtual void SetUp() {

    mesh_.init_parameters( num_vert );

    vector<vertex_t*> vs;
    vs.reserve( num_vert );

    for( size_t k = 0; k < num_vert_z; ++k )
      for( size_t j = 0; j < num_vert_y; ++j )
        for( size_t i = 0; i < num_vert_x; ++i )
        {
          auto v = mesh_.create_vertex({ i, j, k });
          vs.push_back(v);
        }

    auto stride_x = 1;
    auto stride_y = stride_x * num_vert_x;
    auto stride_z = stride_y * num_vert_y;
    
    auto index = [=](auto i, auto j, auto k) 
      {
        return i*stride_x +  j*stride_y +  k*stride_z;
      };


    for( size_t k = 0; k < num_vert_z; ++k ) 
      for( size_t j = 0; j < num_vert_y; ++j ) 
        for( size_t i = 0; i < num_vert_x; ++i ) {


          // x plane
          if ( j < num_cells_y && k < num_cells_z )
            mesh_.create_face( 
              {
                vs[ index( i  , j  , k  ) ],
                vs[ index( i  , j  , k+1) ],
                vs[ index( i  , j+1, k+1) ],
                vs[ index( i  , j+1, k  ) ]
               } );

          // y plane
          if ( i < num_cells_x && k < num_cells_z )
            mesh_.create_face( 
              {
                vs[ index( i  , j  , k  ) ],
                vs[ index( i+1, j  , k  ) ],
                vs[ index( i+1, j  , k+1) ],
                vs[ index( i  , j  , k+1) ]
               } );

          // z plane
          if ( i < num_cells_x && j < num_cells_y )
            mesh_.create_face( 
              {
                vs[ index( i  , j  , k  ) ],
                vs[ index( i+1, j  , k  ) ],
                vs[ index( i+1, j+1, k  ) ],
                vs[ index( i  , j+1, k  ) ]
               } );

        }
    
    for( size_t k = 0; k < num_cells_z; ++k )
      for( size_t j = 0; j < num_cells_y; ++j )
        for( size_t i = 0; i < num_cells_x; ++i )
          // go over vertices counter clockwise to define cell
          auto c = mesh_.create_cell( 
            {
              vs[ index( i  , j  , k  ) ],
              vs[ index( i+1, j  , k  ) ],
              vs[ index( i+1, j+1, k  ) ],
              vs[ index( i  , j+1, k  ) ],
              vs[ index( i  , j  , k+1) ],
              vs[ index( i+1, j  , k+1) ],
              vs[ index( i+1, j+1, k+1) ],
              vs[ index( i  , j+1, k+1) ],
            } );
    
    mesh_.init();
    

    std::cout << mesh_ << std::endl;

  } // SetUp

  //---------------------------------------------------------------------------
  //! \brief the test teardown function
  //! \remark this function is called after each test
  //---------------------------------------------------------------------------
  virtual void TearDown() { }



public:

  //---------------------------------------------------------------------------
  // Data members
  //---------------------------------------------------------------------------

  //! \brief the actual mesh object
  mesh_t mesh_;

};