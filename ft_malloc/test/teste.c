
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void *allocator_handle = NULL;
static void *(*ft_malloc)(size_t) = NULL;
static void (*ft_free)(void *) = NULL;
static void *(*ft_realloc)(void *, size_t) = NULL;
static void *(*ft_calloc)(size_t, size_t) = NULL;
static void *(*ft_show_alloc_mem)(void) = NULL;

int load_allocator(const char *lib_path)
{
    allocator_handle = dlopen(lib_path, RTLD_LAZY);
    if (!allocator_handle)
    {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    ft_malloc = dlsym(allocator_handle, "malloc");
    ft_free = dlsym(allocator_handle, "free");
    ft_realloc = dlsym(allocator_handle, "realloc");
    ft_calloc = dlsym(allocator_handle, "calloc");
    ft_show_alloc_mem = dlsym(allocator_handle, "show_alloc_mem");

    if (!ft_malloc || !ft_free || !ft_realloc || !ft_calloc || !ft_show_alloc_mem)
    {
        fprintf(stderr, "Error resolving symbols: %s\n", dlerror());
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

char *str_dup(const char *str)
{
    size_t len = strlen(str);
    char *dup = ft_calloc(len + 1, sizeof(char));
    if (dup)
    {
        memcpy(dup, str, len + 1);
    }
    else
    {
        printf("Erro ao alocar memória.\n");
    }
    return dup;
}

void teste_ft()
{
    printf("=== Teste de malloc ===\n");
    char *ptr1 = ft_malloc(64);
    char *ptr2 = ft_malloc(128);
    char *ptr3 = ft_calloc(2000, sizeof(char));

    if (ptr1 && ptr2 && ptr3)
    {
        printf("Alocações realizadas com sucesso.\n");
    }
    else
    {
        printf("Erro ao alocar memória.\n");
    }

    printf("\n=== Teste de realloc ===\n");
    ptr2 = ft_realloc(ptr2, 256);
    if (ptr2)
    {
        printf("Realloc realizado com sucesso.\n");
    }
    else
    {
        printf("Erro ao realizar realloc.\n");
    }

    printf("\n=== Teste de free ===\n");
    ft_show_alloc_mem();
    ft_free(ptr1);
    ft_free(ptr2);
    ft_free(ptr3);
}

void teste_malloc()
{
    printf("=== Teste de malloc ===\n");
    char *ptr1 = malloc(64);
    char *ptr2 = malloc(128);
    char *ptr3 = malloc(2000);

    if (ptr1 && ptr2 && ptr3)
    {
        printf("Alocações realizadas com sucesso.\n");
    }
    else
    {
        printf("Erro ao alocar memória.\n");
    }

    printf("\n=== Teste de realloc ===\n");
    ptr2 = realloc(ptr2, 256);
    if (ptr2)
    {
        printf("Realloc realizado com sucesso.\n");
    }
    else
    {
        printf("Erro ao realizar realloc.\n");
    }

    printf("\n=== Teste de free ===\n");
    free(ptr1);
    free(ptr2);
    free(ptr3);
}

// Função para medir o tempo de execução
double measure_time(void (*test_func)(size_t, size_t), size_t iterations, size_t alloc_size)
{
    clock_t start = clock();
    test_func(iterations, alloc_size);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

void test_ft_malloc(size_t iterations, size_t alloc_size)
{
    for (size_t i = 0; i < iterations; i++)
    {
        void *ptr = ft_malloc(alloc_size);
        if (ptr)
        {
            memset(ptr, 0, alloc_size);
            ft_free(ptr);
        }
    }
}

void test_sys_malloc(size_t iterations, size_t alloc_size)
{
    for (size_t i = 0; i < iterations; i++)
    {
        void *ptr = malloc(alloc_size);
        if (ptr)
        {
            memset(ptr, 0, alloc_size);
            free(ptr);
        }
    }
}

void test(size_t iterations, size_t alloc_size)
{

    printf("Running performance test with %zu iterations and %zu bytes\n", iterations, alloc_size);
    double ft_time = measure_time(test_ft_malloc, iterations, alloc_size);
    printf("Custom ft_malloc time: %f seconds\n", ft_time);

    double sys_time = measure_time(test_sys_malloc, iterations, alloc_size);
    printf("System malloc time: %f seconds\n", sys_time);

    printf("\nPerformance comparison:\n");
    printf("ft_malloc is %.2f%% %s than system malloc\n",
           (ft_time / sys_time) * 100.0,
           (ft_time > sys_time) ? "slower" : "faster");
}

// Function to print memory allocation stats
void print_alloc_stats(void *ptr, size_t size)
{
    if (ptr)
    {
        printf("Successfully allocated %zu bytes at %p\n", size, ptr);
    }
    else
    {
        printf("Failed to allocate %zu bytes\n", size);
    }
}

int stress_test()
{
    printf("Starting malloc test program...\n\n");

    // Test 1: TINY allocations
    printf("Testing TINY allocations...\n");
    void *ptr1 = ft_malloc(32); // TINY allocation
    print_alloc_stats(ptr1, 32);

    void *ptr2 = ft_malloc(64); // TINY allocation
    print_alloc_stats(ptr2, 64);

    // Test 2: SMALL allocations
    printf("\nTesting SMALL allocations...\n");
    void *ptr3 = ft_malloc(256); // SMALL allocation
    print_alloc_stats(ptr3, 256);

    void *ptr4 = ft_malloc(512); // SMALL allocation
    print_alloc_stats(ptr4, 512);

    // Test 3: LARGE allocations
    printf("\nTesting LARGE allocations...\n");
    void *ptr5 = ft_malloc(1024); // LARGE allocation
    print_alloc_stats(ptr5, 1024);

    void *ptr6 = ft_malloc(4088); // LARGE allocation
    print_alloc_stats(ptr6, 2048);

    // Test 4: Test writing to allocated memory
    printf("\nTesting memory writing...\n");
    char *str = (char *)ft_malloc(64);
    if (str)
    {
        strcpy(str, "Hello, custom malloc!");
        printf("Written string: %s\n", str);
    }

    // Test 5: Test realloc
    printf("\nTesting realloc...\n");
    str = ft_realloc(str, 128);
    if (str)
    {
        strcat(str, " Extended with realloc!");
        printf("Extended string: %s\n", str);
    }

    // Test 6: Test calloc
    printf("\nTesting calloc...\n");
    int *numbers = ft_calloc(5, sizeof(int));
    if (numbers)
    {
        printf("Calloc array (should be all zeros): ");
        for (int i = 0; i < 5; i++)
        {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    // Test 7: Free everything
    printf("\nFreeing all allocated memory...\n");
    printf("free ptr1\n");
    ft_free(ptr1);
    printf("free ptr2\n");
    ft_free(ptr2);
    printf("free ptr3\n");
    ft_free(ptr3);
    printf("free ptr4\n");
    ft_free(ptr4);
    printf("free ptr5\n");
    ft_free(ptr5);
    printf("free ptr6\n");
    ft_free(ptr6);
    printf("free str\n");
    ft_free(str);
    printf("free numbers\n");
    ft_free(numbers);

   
    printf("\nPerforming stress test...\n");

    for (int i = 4; i < 4048; i++)
    {
        void *ptr = ft_malloc(i *32);
        if (!ptr)
        {
            printf("Stress test: Failed to allocate at iteration %d\n", i);
            break;
        }
        ft_free(ptr);
    }

    #define STRESS_TEST_COUNT 1000
    void *pointers[STRESS_TEST_COUNT];

    for (int i = 0; i < STRESS_TEST_COUNT; i++)
    {
        size_t size = 10 + i % 1000;
        pointers[i] = ft_malloc(size);
        if (!pointers[i])
        {
            printf("Stress test: Failed to allocate at iteration %d\n", i);
            break;
        }
        memset(pointers[i], i % 256, size);
    }

    for (int i = 0; i < STRESS_TEST_COUNT; i++)
    {
        if (pointers[i])
        {

           ft_free(pointers[i]);
        }
    }

    printf("\nAll tests completed successfully!\n");
    return 0;
}
int main()
{
    if (load_allocator("../libft_malloc.so") != EXIT_SUCCESS)
    {
        printf("Error loading allocator library.\n");
        return 1;
    }

   // teste_malloc();

   // teste_ft();

    // const size_t iterations = 1000;

    // test(iterations, 8);
    // test(iterations, 32);
    // test(iterations, 64);
    // test(iterations, 128);
    // test(iterations, 256);
    // test(iterations, 512);
    // test(iterations, 1024);
    // test(iterations, 2048);
    // test(iterations, 4096);
    // test(iterations, 8192);
    // test(iterations, 16384);
    // test(iterations, 32768);
    // test(iterations, 65536);
    // test(iterations, 131072);
    // test(iterations, 262144);
    // test(iterations, 524288);
    // test(iterations, 1048576);
    // test(iterations, 2097152);
    // test(iterations, 4194304);
    // test(iterations, 8388608);
    // test(iterations, 16777216);
    // test(iterations, 33554432);
    // test(iterations, 67108864);
    // test(iterations, 134217728);
    // test(iterations, 268435456);

   stress_test();

    void *ptr1 = ft_malloc(32); // TINY allocation
   // print_alloc_stats(ptr1, 32);
    ft_free(ptr1);


   ptr1 = ft_malloc(32); // TINY allocation
   // print_alloc_stats(ptr1, 32);
    ft_free(ptr1);


    ft_show_alloc_mem();

    unload_allocator();
    return 0;
}
