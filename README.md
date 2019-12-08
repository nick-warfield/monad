# Monadic Iterator

This monadic iterator is a header only library, so running the code is pretty easy. Just include it whatever file you want to use it in, and compile them together. Note that this implementation requires c++17.

Issues:
There aren't any major issues that stop the monad from at least running. But there are several design considerations that have been neglected and should be addressed at some point. First, I am uncertain of which pointer should be used internally. I used raw pointers to simplify things, but I think unique_ptr may be more applicable in this case. Second, the monadic iterators manage a resource, so the rule of 5 likeyly applies. I'll need to verify this at some point, and then implement the rule if it is needed. Thirdly, the interface for the client is not very elegant and I am unsure on how to address that. Feedback on how to clean that up would be appreciated.
