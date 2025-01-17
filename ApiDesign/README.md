# API design 

## This aims to be a summary of best practices on API design

### Resources and inspiration:
- Back to Basics: C++ API Design - Jason Turner - CppCon 2022 - https://www.youtube.com/watch?v=zL-vn_pGGgY

### Best practices:
Motto: make your API hard to use wrong
- try to use your API wrong. Don't only rely on your creativity but fuzz test you API
- use better namings
- use [[nodiscard]] to force caller to use the returned value
- never return a raw pointer
- use 'noexcept' to help indicate the type of error handling
- provide consisten, impossible to ignore, in-band error handling. In-band meaning the error is provided as part of the response of the API call, not as a parallel mechanim (errno)
    examples of good practices: exceptions, std::expected (from C++23 but can be implemented as std::variant<T,Error> or in other ways)
- use stronger types and avoid default conversions
- delete problematic overloads / prevent conversions 
- avoid passing pointers (only to be used for single/optional objects)
- avoid passing smart pointers.
- limit your API as much as possible (remember: it is easy to add but very difficult to remove when a function is provided)