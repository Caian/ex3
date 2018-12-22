# ex3
Quick wrapper for throwing boost exceptions with stacktrace information

## Introduction

This project is intended to be used with [boost](https://www.boost.org/) to enable transparent, switchable stacktracing when throwing instances of `boost::exception` or derived classes.

## Usage

Please refer to [boost exceptions](https://www.boost.org/doc/libs/1_68_0/libs/exception/doc/boost-exception.html) and [boost stacktrace](https://www.boost.org/doc/libs/1_68_0/doc/html/stacktrace.html) to understand the mechanics of semantic tags and stack traces.

This library provides a custom base class for exceptions that inherits `boost::exception` and `std::exception` as well as providing a constructor with a custom message tied to the `what()` virtual method from `std::exception`.

### Requirements

This library requires linking with `-ldl` because of boost stacktrace and, in order to enable stack tracing with function names, it requires compiling with the `-rdynamic` flag, but be advised that `-rdynamic` may affect performance.

### Namespace

The `exception_base` class and the `traced` typedef used for stacktracing are contained in the `ex3` namespace.

### Throwing exceptions

Use the `EX3_THROW` macro to throw exception as you would normally do with `BOOST_THROW_EXCEPTION`, including adding error information:

```c++
#include <ex3/exceptions.hpp>

typedef boost::error_info<struct tag_filename, std::string> filename_info;

EX3_THROW(my_io_exception
    << filename_info("path/to/the/file")
);
```

### Getting information

```c++
boost::diagnostic_information(exception, verbose);
```

```c++
boost::current_exception_diagnostic_information(verbose);
```

```c++
boost::get_error_info<your_error_info>(exception);
```

### Disabling stack tracing

If the stacktrace library happens to be incompatible with the compiler, then it can be disabled by defining `EX3_NO_STACKTRACE`. This will transparently remove includes, typedefs and macros associated with stacktrace generation. **Warning: user code that grabs the stacktrace information will not compile!**
