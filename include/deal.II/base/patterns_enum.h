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

#ifndef dealii_base_petterns_enum_h
#define dealii_base_petterns_enum_h

#include <deal.II/base/better_enum.h>
#include <deal.II/base/parameter_handler.h>
#include <deal.II/base/patterns.h>

#include <boost/algorithm/string/join.hpp>

#include <sstream>
#include <string>

using namespace dealii;

namespace dealii
{
  namespace Patterns
  {
    namespace Tools
    {
      /**
       * Check for T::has_values()
       */
      template <typename T>
      struct has_values
      {
      private:
        static void
        detect(...);

        template <typename U>
        static decltype(std::declval<U const>()._values())
        detect(const U &);

      public:
        static const bool value =
          !std::is_same<void, decltype(detect(std::declval<T>()))>::value;
      };

      /**
       * Check for T::_to_string()
       */
      template <typename T>
      struct has_to_string
      {
      private:
        static void
        detect(...);

        template <typename U>
        static decltype(std::declval<U const>()._to_string())
        detect(const U &);

      public:
        static const bool value =
          !std::is_same<void, decltype(detect(std::declval<T>()))>::value;
      };


      /**
       * Check for T::_from_string()
       */
      template <typename T>
      struct has_from_string
      {
      private:
        static void
        detect(...);

        template <typename U>
        static decltype(std::declval<U const>()._from_string(0))
        detect(const U &);

      public:
        static const bool value =
          !std::is_same<void, decltype(detect(std::declval<T>()))>::value;
      };

      /**
       * Check if T::has_values(), T::_to_string(), and T::_from_string() is
       * defined. If yes, we can simply convert it.
       */
      template <typename T>
      struct is_convertible
      {
        static const bool value = has_values<T>::value &&
                                  has_to_string<T>::value &&
                                  has_from_string<T>::value;
      };

      /**
       * Converter class for structs of type T that fulfill is_convertible<T>.
       */
      template <class T>
      struct Convert<T, typename std::enable_if<is_convertible<T>::value>::type>
      {
        /**
         * Convert to pattern.
         */
        static std::unique_ptr<Patterns::PatternBase>
        to_pattern()
        {
          std::vector<std::string> values;

          for (const auto i : T::_values())
            values.push_back(i._to_string());

          return std::make_unique<Patterns::Selection>(
            boost::algorithm::join(values, "|"));
        }

        /**
         * Convert value to string.
         */
        static std::string
        to_string(const T &t,
                  const Patterns::PatternBase & = *Convert<T>::to_pattern())
        {
          return t._to_string();
        }

        /**
         * Convert string to value.
         */
        static T
        to_value(const std::string &s,
                 const Patterns::PatternBase & = *Convert<T>::to_pattern())
        {
          return T::_from_string(s.c_str());
        }
      };

    } // namespace Tools
  }   // namespace Patterns
} // namespace dealii

#endif
