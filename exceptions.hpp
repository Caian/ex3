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
 * along with ex3.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <string>

#include <boost/exception/all.hpp>

#if !defined(EX3_NO_STACKTRACE)

#include <boost/stacktrace.hpp>

/**
 * @brief Macro for throwing an exception with stacktrace.
 *
 */
#define EX3_THROW(ExeptInstance) \
    BOOST_THROW_EXCEPTION(ExeptInstance \
        << ex3::traced(boost::stacktrace::stacktrace()))

#else

/**
 * @brief Macro for throwing an exception without stacktrace.
 *
 */
#define EX3_THROW(ExeptInstance) \
    BOOST_THROW_EXCEPTION(ExeptInstance)

#endif

/**
 * @brief Macro for rethrowing an exception.
 *
 */
#define EX3_RETHROW(ExeptInstance) \
    BOOST_THROW_EXCEPTION(ExeptInstance)

/**
 * @brief Macro for throwing non-boost exceptions with info.
 *
 */
#define EX3_ENABLE(ExeptInstance) \
    boost::enable_error_info(ExeptInstance)

namespace ex3 {

#if !defined(EX3_NO_STACKTRACE)

    /** Tag for stacktrace information included in an exception. */
    typedef boost::error_info<struct tag_stacktrace, boost::stacktrace::stacktrace> traced;

#endif

    /**
     * @brief Base class when creating exceptions
     * compatible with boost and std.
     *
     */
    struct exception_base :
        virtual std::exception,
        virtual boost::exception
    {
        exception_base()
        {
        }

        virtual ~exception_base() throw()
        {
        }
    };
}
