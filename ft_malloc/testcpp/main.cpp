#include <new>
#include <iostream>
#include <cstring>
#include <dlfcn.h>

static void *allocator_handle = nullptr;
static void *(*ft_malloc)(size_t) = nullptr;
static void (*ft_free)(void *) = nullptr;
static void *(*ft_realloc)(void *, size_t) = nullptr;
static void *(*ft_calloc)(size_t, size_t) = nullptr;
static void *(*ft_show_alloc_mem)(void) = nullptr;


int load_allocator(const char *lib_path)
{
    allocator_handle = dlopen(lib_path, RTLD_LAZY);
    if (!allocator_handle)
    {
         std::cerr << "Error loading library: " << dlerror() << std::endl;
        return EXIT_FAILURE;
    }

    ft_malloc =(void *(*)(size_t)) dlsym(allocator_handle, "malloc");
    ft_free = (void (*)(void *)) dlsym(allocator_handle, "free");
    ft_realloc = (void *(*)(void *, size_t)) dlsym(allocator_handle, "realloc");
    ft_calloc =  (void *(*)(size_t, size_t)) dlsym(allocator_handle, "calloc");
    ft_show_alloc_mem =  (void *(*)(void)) dlsym(allocator_handle, "show_alloc_mem");

    if (!ft_malloc || !ft_free || !ft_realloc || !ft_calloc || !ft_show_alloc_mem)
    {
        std::cerr << "Error resolving symbols: " << dlerror() << std::endl;
        dlclose(allocator_handle);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void unload_allocator(void)
{
    if (allocator_handle)
    {
        dlclose(allocator_handle);
        allocator_handle = NULL;
        ft_malloc = NULL;
        ft_free = NULL;
        ft_realloc = NULL;
        ft_calloc = NULL;
        ft_show_alloc_mem = NULL;
    }
}


// Redefinição do operador global new
void *operator new(size_t size)
{
    if (!ft_malloc)
    {
        throw std::bad_alloc();
    }

    void *ptr = ft_malloc(size);
    if (!ptr)
    {
        throw std::bad_alloc();
    }
    return ptr;
}

// Redefinição do operador global delete
void operator delete(void *ptr) noexcept
{
    if (ptr && ft_free)
    {
        ft_free(ptr);
    }
}

// Redefinição do operador new[] (para arrays)
void *operator new[](size_t size)
{
    if (!ft_malloc)
    {
        throw std::bad_alloc();
    }

    void *ptr = ft_malloc(size);
    if (!ptr)
    {
        throw std::bad_alloc();
    }
    return ptr;
}

// Redefinição do operador delete[] (para arrays)
void operator delete[](void *ptr) noexcept
{
    if (ptr && ft_free)
    {
        ft_free(ptr);
    }
}

struct Foo
{
    Foo() { std::cout << "Foo constructor called" << std::endl; }
    ~Foo() { std::cout << "Foo destructor called" << std::endl; }
};


// Teste simples
int main()
{
    if (load_allocator("../libft_malloc.so") != EXIT_SUCCESS)
    {
        return 1;
    }

    try
    {
        // Testando new e delete
        std::cout << "Testing new and delete..." << std::endl;
        int *int_ptr = new int(42);
        std::cout << "Allocated int: " << *int_ptr << std::endl;
        delete int_ptr;

        // Testando new[] e delete[]
        std::cout << "Testing new[] and delete[]..." << std::endl;
        char *char_array = new char[10];
        std::strcpy(char_array, "Hello");
        std::cout << "Allocated char array: " << char_array << std::endl;
        delete[] char_array;


        // Testando realloc
        std::cout << "Testing realloc..." << std::endl;
        int *int_array = new int[5];
        std::cout << "Allocated int array: " << int_array << std::endl;
        int_array = (int *)ft_realloc(int_array, 10 * sizeof(int));
        std::cout << "Reallocated int array: " << int_array << std::endl;
        delete[] int_array;


        // Testando calloc
        std::cout << "Testing calloc..." << std::endl;
        int *int_array2 = (int *)ft_calloc(10, sizeof(int));
        std::cout << "Allocated int array: " << int_array2 << std::endl;
        delete[] int_array2;

        std::cout << "Testing Foo constructor and destructor..." << std::endl;
        {

            Foo foo;
        }

        {
            Foo* foo_ptr = new Foo();
            std::cout << "Allocated Foo object: " << foo_ptr << std::endl;
            delete foo_ptr;
        }

    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Allocation failed: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Test completed successfully." << std::endl;
    ft_show_alloc_mem();

    unload_allocator();
    return 0;
}
