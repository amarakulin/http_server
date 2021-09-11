/* **************************************************************************** */
/*                                                                      .       */
/*   MockHostData.hpp                                                        / V\     */
/*                                                                   / `  /     */
/*   By: tilda      <tilda@student.21-school.ru.fr>                 <<   |      */
/*                                                                  /    |      */
/*   Created: 9/8/21 by tilda                                    /      |      */
/*                                                              /        |      */
/*                                                            /    \  \ /       */
/*                                                           (      ) | |       */
/*                                                   ________|   _/_  | |       */
/*                                                 <__________\______)\__)      */
/* **************************************************************************** */


#ifndef HTTP_SERVER_MOCKHOSTDATA_HPP
#define HTTP_SERVER_MOCKHOSTDATA_HPP

#include "HostTypes.hpp"

class MockHostData{

public:
	MockHostData();
	~MockHostData();
	HostData *createDefaultHostDataNotStatic();
	static HostData *createDefaultHostData();
};


#endif //HTTP_SERVER_MOCKHOSTDATA_HPP
