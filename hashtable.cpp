/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pablo Escobar <sataniv.rider@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:48:50 by Pablo Escob       #+#    #+#             */
/*   Updated: 2024/08/06 20:10:49 by Pablo Escob      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

template <typename t_val>
HashTable<t_val>::HashTable(int size_) :
	arrsize(size_),
	realsize(0),
	sizewithdelete(0)
{
	hashtable = new Node*[arrsize];
	for (int i = 0; i < arrsize; ++i)
		hashtable[i] = nullptr;
}

template <typename t_val>
HashTable<t_val>::HashTable(const HashTable& obj)
{
	realsize = obj.realsize;
	arrsize = obj.arrsize;
	sizewithdelete = obj.sizewithdelete;
	hashtable = new Node*[arrsize];
	for (int i = 0; i < arrsize; ++i)
		hashtable[i] = nullptr;
}

template <typename t_val>
HashTable<t_val>::~HashTable()
{
	for (int i = 0; i < arrsize; ++i)
		delete hashtable[i];
	delete [] hashtable;
}

template <typename t_val>
HashTable<t_val>	&HashTable<t_val>::operator=(const HashTable<t_val> &obj)
{

}
