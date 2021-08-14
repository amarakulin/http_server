/* **************************************************************************** */
/*                                                                      .       */
/*   test.cpp.c                                                        / V\     */
/*                                                                   / `  /     */
/*   By: tilda      <tilda@student.21-school.ru.fr>                 <<   |      */
/*                                                                  /    |      */
/*   Created: 8/14/21 by tilda                                    /      |      */
/*                                                              /        |      */
/*                                                            /    \  \ /       */
/*                                                           (      ) | |       */
/*                                                   ________|   _/_  | |       */
/*                                                 <__________\______)\__)      */
/* **************************************************************************** */


#include "acutest.hpp"

void
test_tutorial(void)
{
	void* mem;

	mem = malloc(10);
	TEST_CHECK(mem != NULL);

	mem = realloc(mem, 20);
	TEST_CHECK(mem != NULL);

	free(mem);
}


TEST_LIST = {
		{ "tutorial", test_tutorial },
		{nullptr, nullptr }
};