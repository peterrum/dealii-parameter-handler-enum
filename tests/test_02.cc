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

// Test new operators of better enum.

#include <deal.II/base/patterns_enum.h>

using namespace dealii;

BETTER_ENUM(PreconditionerType, char, Identity, AMG, Jacobi, BlockJacobi)

int
main()
{
  PreconditionerType preconditioner = PreconditionerType::Identity;

  if (preconditioner == PreconditionerType::Identity)
    std::cout
      << "PreconditionerType::Identity == PreconditionerType::Identity: passed!"
      << std::endl;
  else
    std::cout << "" << std::endl;

  if (preconditioner == PreconditionerType::Jacobi)
    std::cout << "" << std::endl;
  else
    std::cout
      << "PreconditionerType::Identity == PreconditionerType::Jacobi: passed!"
      << std::endl;

  if (preconditioner != PreconditionerType::Identity)
    std::cout << "" << std::endl;
  else
    std::cout
      << "PreconditionerType::Identity != PreconditionerType::Identity: passed!"
      << std::endl;

  if (preconditioner != PreconditionerType::Jacobi)
    std::cout
      << "PreconditionerType::Identity != PreconditionerType::Jacobi: passed!"
      << std::endl;
  else
    std::cout << "" << std::endl;
}
