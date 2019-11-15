# Monadic Iterator

abstract base class, only hasNext and next abstract
subclass zero
subclass unit, holds item, if item has been accessed
mplus, holds 2 iterators of the same type, walks throughs first then walks the second
bind, holds func A->Iterator<B>, saves iterator<B>
	func(A) then walk over all of the result, then repeat until out of A

