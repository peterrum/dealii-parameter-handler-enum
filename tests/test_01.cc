// ---------------------------------------------------------------------
//
// Copyright (C) 2021 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE.md at
// the top level directory of deal.II.
//
// ---------------------------------------------------------------------

// Test parsing with ParameterHandler.

#include <deal.II/base/parameter_handler.h>
#include <deal.II/base/patterns_enum.h>

using namespace dealii;

BETTER_ENUM(PreconditionerType, char, Identity, AMG, Jacobi, BlockJacobi)

int
main()
{
  ParameterHandler prm;

  PreconditionerType preconditioner = PreconditionerType::Identity;
  prm.add_parameter("preconditioner", preconditioner);

  prm.print_parameters(std::cout, ParameterHandler::OutputStyle::Description);
  std::cout << std::endl;

  prm.print_parameters(std::cout, ParameterHandler::OutputStyle::PRM);
  std::cout << std::endl;

  for (const auto e : PreconditionerType::_values())
    {
      std::istringstream is("{\"preconditioner\" : \"" +
                            std::string(e._to_string()) + "\"}");
      prm.parse_input_from_json(is);
      prm.print_parameters(std::cout, ParameterHandler::OutputStyle::PRM);
      std::cout << std::endl;
    }
}
