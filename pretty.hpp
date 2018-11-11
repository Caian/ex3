/*
 * Copyright (C) 2018 Caian Benedicto <caianbene@gmail.com>
 *
 * This file is part of ex3.
 *
 * ex3 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * ex3 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Make; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#pragma once

#include <ostream>
#include <iterator>
#include <string>

namespace ex3 {

/**
 * @brief Helper class that encapsulates a container and
 * exposes an override for printing the container to an
 * std::ostream as values separated by a custom separator
 * and trailing string.
 *
 * @tparam Container The type of the container.
 */
template <class Container>
struct pretty_container
{
    Container values;
    std::string sep;
    std::string end;

    /**
     * @brief Construct a new pretty_container object from
     * an existing container and a separator.
     *
     * @param values The container with the values to store.
     * @param sep The separator used when printing the
     * elements of the container.
     * @param end The string to put after all elements have
     * been printed.
     */
    pretty_container(
        const Container& values,
        const std::string& sep=",",
        const std::string& end=""
    ) :
        values(values),
        sep(sep),
        end(end)
    {
    }

    /**
     * @brief Print a sequence of values with a custom separator.
     *
     * @tparam IT The type of the iterator.
     *
     * @param begin The iterator pointing to the first element
     * in the sequence to print.
     * @param end The iterator past-the-last element in the
     * sequence to print.
     * @param stream The output stream.
     * @param sep The separator to put between elements.
     * @param send The string to put after all elements have
     * been printed.
     */
    template <typename IT>
    static void print(
        IT begin,
        IT end,
        std::ostream& stream,
        const std::string& sep,
        const std::string& send
    )
    {
        if (begin == end)
            return;

        stream << *begin;
        begin++;

        for ( ; begin != end; begin++) {
            stream << sep << *begin;
        }

        if (send.size() > 0) {
            stream << send;
        }
    }

    /**
     * @brief Override behavior for std::ostream operator <<.
     *
     * @param stream The output stream.
     * @param pc A constant reference to the pretty_container
     * object being printed.
     * @return std::ostream& The output stream passes as input.
     */
    friend std::ostream& operator<< (
        std::ostream& stream,
        const pretty_container& pc
    )
    {
        print(pc.values.begin(), pc.values.end(),
            stream, pc.sep, pc.end);

        return stream;
    }
};

}
