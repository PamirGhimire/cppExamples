// Rule of Five: if a class needs a custom destructor, copy constructor, copy assignment, move constructor, or move assignment, consider defining all five to manage its resources correctly.
#include <iostream>


class Buffer
{
/*
This class holds an int buffer 
the client instantiates the buffer of a certain size during construction
the buffer can be copied and moved
*/
public:
    explicit Buffer() = delete;
    Buffer(const size_t& buffer_size): num_elements_(buffer_size) 
    {
        // {} zero-initializes every int, so all elements are safe to read.
        // If new throws, construction fails; no array needs freeing.
        data_ = new int[num_elements_]{};
    }

    // copy constructor
    Buffer(const Buffer& other)
    {
        // A new object has no old array to delete (data_ starts as nullptr).
        num_elements_ = other.get_size();
        data_ = new int[num_elements_];
        for (size_t i = 0; i < num_elements_; ++i)
            data_[i] = other[i];
    }

    //copy assignment operator
    Buffer& operator = (const Buffer& other)
    {
        // Compare object addresses for self-assignment, not element values.
        if (this == &other)
            return *this;

        // Allocate and copy before deleting: if new throws, *this is unchanged.
        // Copying ints cannot throw; this gives the strong exception guarantee.
        int* new_data = new int[other.get_size()];
        for (size_t i = 0; i < other.get_size(); ++i)
            new_data[i] = other[i];
        delete [] data_;
        data_ = new_data;
        num_elements_ = other.get_size();
        return *this; // Allows chaining: a = b = c.
    }

    //move constructor
    Buffer(Buffer&& other) noexcept
    {
        // Transfer ownership without allocation or element copies (cannot throw).
        // Member functions can access private fields of any Buffer instance.
        num_elements_ = other.get_size();
        data_ = other.data_;
        // Leave the source empty so its destructor cannot free our array.
        // Transfer the pointer directly: indexing [0] would fail for empty buffers.
        other.data_ = nullptr;
        other.num_elements_ = 0;
    }

    //move assignment operator
    Buffer& operator = (Buffer&& other) noexcept
    {
        // Protect the allocation when assigning an object to itself via std::move.
        if (this == &other)
            return *this;

        // Assignment replaces an existing object, so release its old allocation.
        delete [] data_;
        num_elements_ = other.get_size();
        data_ = other.data_;
        other.data_ = nullptr;
        other.num_elements_ = 0;
        return *this;
    }

    int& operator [] (size_t pos)
    {
        // A reference permits writes such as buffer[i] = 5. Index is unchecked.
        return data_[pos];
    }

    const int& operator [] (size_t pos) const
    {
        // Const buffers (including copy sources) allow reads, but not writes.
        return data_[pos];
    }

    size_t get_size() const
    {
        return num_elements_;
    }

    void print()
    {
        for (size_t i = 0; i < num_elements_; ++i)
            std::cout << data_[i] << " ";
        std::cout << std::endl;
    }

    bool operator == (const Buffer& other) const
    {
        // Equality compares contents; independent deep copies can still be equal.
        if (other.get_size() != num_elements_)
            return false;
        for (size_t i = 0; i < num_elements_; ++i)
            if (data_[i] != other[i])
                return false;
        return true;
    }

    ~Buffer() 
    {
        // Public so scope exit can destroy buffers. delete[] nullptr is safe.
        delete [] data_;
    }

private:
    // Owning raw pointer: destructor, copy, and move operations must agree
    // on ownership (Rule of Five). An empty moved-from buffer uses {0, nullptr}.
    size_t num_elements_{0};
    int* data_{nullptr};
};

int main()
{
    Buffer bc = Buffer(10);
    bc[5] = 5;
    bc.print();

    auto bc_copy = bc; //copy
    bc_copy.print();
    
}
