// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    29.05.2012 15:01:57 CEST
// File:    bit_vector_class.hpp

#ifndef __BIT_VECTOR_CLASS_HEADER
#define __BIT_VECTOR_CLASS_HEADER

typedef long unsigned int luint;

class proxy
{
public:
	inline proxy(unsigned int const & index, luint & val): val_(&val), ind_(index) {}
	
	inline operator bool()
	{
		return ((*val_) & (1lu << ind_));
	}
	
	inline void operator=(bool const & rhs)
	{
		luint r = rhs;
		(*val_) &= ~(1lu << ind_); //delete bit
		(*val_) |= (r << ind_); //set it new
	}
private:
	luint *val_;
	unsigned int ind_;
};

class bit_vector_class
{
public:
	inline bit_vector_class(): key_(0) {};
	inline bit_vector_class(luint const & val): key_(val) {};
	inline bit_vector_class(bit_vector_class const & rhs): key_(rhs.key_) {};
	
	inline void set_bit(unsigned int const & index, bool const & state)
	{
		luint r = state;
		key_ &= ~(1lu << index); //delete bit
		key_ |= (r << index); //set it new
	}
	
	inline proxy operator[](unsigned int const & index)
	{
		return proxy(index, key_);
	}
	inline luint get() const
	{
		return key_;
	}
	
private:
	luint key_;
};

inline luint operator&(bit_vector_class const & a, bit_vector_class const & b)
{
	return a.get() & b.get();
}
#endif //__BIT_VECTOR_CLASS_HEADER
