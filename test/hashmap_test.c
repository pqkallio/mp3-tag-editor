#include <CUnit/CUnit.h>
#include "hashmap_test.h"
#include "src/dstructs/hashmap.h"
#include "src/mem/mem.h"

void test_get_set_and_remove(HashMap *map)
{
    char *a = "a";
    char *b = "b";
    char *c = "c";

    map->set(map, a, a);

    CU_ASSERT_EQUAL(map->size, 1);
    CU_ASSERT_PTR_EQUAL(map->get(map, a), a);

    CU_ASSERT(map->set(map, b, b));
    CU_ASSERT(!map->set(map, b, a));

    CU_ASSERT_EQUAL(map->size, 2);
    CU_ASSERT_PTR_EQUAL(map->get(map, a), a);
    CU_ASSERT_PTR_EQUAL(map->get(map, b), b);

    CU_ASSERT_PTR_NULL(map->get(map, c));

    CU_ASSERT_PTR_EQUAL(map->remove(map, a), a);
    CU_ASSERT_PTR_NULL(map->remove(map, a));

    CU_ASSERT_EQUAL(map->size, 1);
    CU_ASSERT_PTR_NULL(map->get(map, a));
    CU_ASSERT_PTR_EQUAL(map->get(map, b), b);
}

void test_hashmap()
{
    HashMap *map = new_hashmap(&DEFAULT_MEMMAP);

    CU_ASSERT_EQUAL(100, map->n_slots);
    CU_ASSERT_EQUAL(0, map->size);

    test_get_set_and_remove(map);

    delete_hashmap(map);
}

void test_hashmap_with_size()
{
    HashMap *map = new_hashmap_with_size(&DEFAULT_MEMMAP, 42);

    CU_ASSERT_EQUAL(42, map->n_slots);
    CU_ASSERT_EQUAL(0, map->size);

    test_get_set_and_remove(map);

    delete_hashmap(map);
}

void test_hashmap_funcs_with_null_pointers()
{
    HashMap *map = new_hashmap(&DEFAULT_MEMMAP);
    void *value = (void *)-1;

    CU_ASSERT_PTR_NULL(map->remove(NULL, "key"));
    CU_ASSERT_PTR_NULL(map->remove(map, NULL));
    CU_ASSERT_PTR_NULL(map->remove(map, "key"));

    CU_ASSERT_PTR_NULL(map->get(NULL, "key"));
    CU_ASSERT_PTR_NULL(map->get(map, NULL));

    CU_ASSERT(!map->set(NULL, "key", value));
    CU_ASSERT(!map->set(map, NULL, value));
    CU_ASSERT(!map->set(map, "key", NULL));

    delete_hashmap(NULL);
    delete_hashmap(map);
}

const void *items[4] = {0};
int i = 0;

void mock_callback(const void *item)
{
    items[i] = item;
    i++;
}

void test_hashmap_foreach()
{
    HashMap *map = new_hashmap(&DEFAULT_MEMMAP);
    int handled[4] = {0};
    int j;

    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;

    CU_ASSERT_FATAL(map->set(map, "one", &one));
    CU_ASSERT_FATAL(map->set(map, "two", &two));
    CU_ASSERT_FATAL(map->set(map, "three", &three));
    CU_ASSERT_FATAL(map->set(map, "four", &four));

    for (j = 0; j < 4; j++)
    {
        CU_ASSERT_PTR_NULL_FATAL(items[j]);
    }

    for (j = 0; j < 4; j++)
    {
        CU_ASSERT_EQUAL_FATAL(handled[j], 0);
    }

    map->foreach (map, mock_callback);

    for (i = 0; i < 4; i++)
    {
        const void *item = items[i];

        if (item == &one)
        {
            handled[0] = 1;
        }
        else if (item == &two)
        {
            handled[1] = 1;
        }
        else if (item == &three)
        {
            handled[2] = 1;
        }
        else if (item == &four)
        {
            handled[3] = 1;
        }
    }

    for (j = 0; j < 4; j++)
    {
        CU_ASSERT_EQUAL_FATAL(handled[j], 1);
    }

    map->foreach (NULL, mock_callback);
    map->foreach (map, NULL);

    delete_hashmap(map);
}
