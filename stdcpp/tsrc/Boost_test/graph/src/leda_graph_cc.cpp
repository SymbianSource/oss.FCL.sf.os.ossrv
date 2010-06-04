//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

/*
 * � Portions copyright (c) 2006-2007 Nokia Corporation.  All rights reserved.
*/

#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/leda_graph.hpp>
#ifdef __SYMBIAN32__
#include "std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__
#endif

int
main(int,char*[])
{
  using namespace boost;
  {
    typedef leda::GRAPH<int,int> Graph;
    typedef graph_traits<Graph>::vertex_descriptor Vertex;
    typedef graph_traits<Graph>::edge_descriptor Edge;
    function_requires< VertexListGraphConcept<Graph> >();
    function_requires< BidirectionalGraphConcept<Graph> >();
    function_requires< AdjacencyGraphConcept<Graph> >();
    function_requires< VertexMutableGraphConcept<Graph> >();
    function_requires< EdgeMutableGraphConcept<Graph> >();
    function_requires< VertexMutablePropertyGraphConcept<Graph> >();
    function_requires< EdgeMutablePropertyGraphConcept<Graph> >();
    function_requires<
      ReadablePropertyGraphConcept<Graph, Vertex, vertex_index_t> >();
    function_requires<
      ReadablePropertyGraphConcept<Graph, Edge, edge_index_t> >();
    function_requires<
      LvaluePropertyGraphConcept<Graph, Vertex, vertex_all_t> >();
    function_requires<
      LvaluePropertyGraphConcept<Graph, Vertex, edge_all_t> >();
  }
   
#ifdef __SYMBIAN32__
std_log(LOG_FILENAME_LINE,"[End Test Case ]");

	testResultXml("leda_graph_cc");
	close_log_file();
#endif
  return 0;
}
