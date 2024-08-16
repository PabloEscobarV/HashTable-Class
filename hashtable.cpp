/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pablo Escobar <sataniv.rider@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:48:50 by Pablo Escob       #+#    #+#             */
/*   Updated: 2024/08/16 18:39:23 by Pablo Escob      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include <string>
#include <iostream>
#include <cstdint>
#include <cstring>

using namespace	std;

HashTable::HashTable(int size_) :
	tablesize(size_),
	valcount(0),
	nodecount(0)
{
	hashtable = new Node*[tablesize];
	for (int i = 0; i < tablesize; ++i)
		hashtable[i] = nullptr;
}

HashTable::HashTable(const HashTable& obj)
{
	valcount = obj.valcount;
	tablesize = obj.tablesize;
	nodecount = obj.nodecount;
	hashtable = new Node*[tablesize];
	for (int i = 0; i < tablesize; ++i)
		hashtable[i] = nullptr;
}

HashTable::~HashTable()
{
	freehashtable(hashtable, tablesize);
}

HashTable	&HashTable::operator=(const HashTable &obj)
{
	if (&obj == this)
		return (*this);
	freehashtable(hashtable, tablesize);
	valcount = obj.valcount;
	tablesize = obj.tablesize;
	nodecount = obj.nodecount;
	hashtable = new Node*[tablesize];
	for (int i = 0; i < tablesize; ++i)
		hashtable[i] = nullptr;
	return (*this);
}

void	HashTable::freehashtable(Node** hashtable, int size)
{
	while (size)
	{
		--size;
		delete hashtable[size];
 	}
	delete[] hashtable;
}

// t_ulong	HashTable::f_hash(string &str, int tabsize, int kef)
// {
// 	t_ulong	hash = 0;

// 	for (char i : str)
// 		hash = (kef * hash + i) % tabsize;
// 	return ((hash * 2 + 1) % tabsize);
// }

t_ulong	HashTable::f_hashprimar(string &str, t_fhash f_hash)
{
	return (f_hash(str.c_str(), str.length(), tablesize) % tablesize);
}

t_ulong	HashTable::f_hashstep(string &str, t_fhash f_hash)
{	
	return (f_hash(str.c_str(), str.length(), tablesize * 31) % (tablesize - 1) + 1);
}

void	HashTable::resize(t_fhash f_hash)
{
	int		tmpsize {tablesize};
	Node**	hashtabletmp {hashtable};

	tablesize *= k_sizescale;
	hashtable = new Node* [tablesize];
	for (int i = 0; i < tablesize; ++i)
		hashtable[i] = nullptr;
	valcount = 0;
	nodecount = 0;
	for (int i = 0; i < tmpsize; ++i)
	{
		if (hashtabletmp[i])
		{
			cout << "TEST. KEY:\t" << hashtabletmp[i]->name << "\tVAR:\t" << hashtabletmp[i]->val << endl;
			add(hashtabletmp[i]->name, hashtabletmp[i]->val, f_hash);
		}
	}
	freehashtable(hashtabletmp, tmpsize);
}

void	HashTable::rehash(t_fhash f_hash)
{
	Node**	hashtabletmp {hashtable};
	
	hashtable = new Node* [tablesize];
	for (int i = 0; i < tablesize; ++i)
		hashtabletmp[i] = nullptr;
	for (int i = 0; i < tablesize; ++i)
		if (hashtabletmp[i] && hashtabletmp[i]->state)
			add(hashtabletmp[i]->name, hashtabletmp[i]->val, f_hash);
	freehashtable(hashtabletmp, tablesize);
	nodecount = valcount;
}

int	HashTable::add(string &name, string &val, t_fhash f_hash)
{
	int		i;
	t_ulong	hash;
	t_ulong	step;
	
	if (nodecount && nodecount >= valcount * (int)k_rehash)
		rehash(f_hash);
	if (nodecount + 1 >= tablesize)
		resize(f_hash);
	hash = f_hashprimar(name, f_hash);
	step = f_hashstep(name, f_hash);
	i = 0;
	while (hashtable[hash] && hashtable[hash]->state && i < tablesize)
	{
		hash = (hash + i * step) % tablesize;
		++i;
	}
	if (hashtable[hash] && hashtable[hash]->state)
		return (1);
	if (!hashtable[hash])
		hashtable[hash] = new Node;
	hashtable[hash]->name = name;
	hashtable[hash]->state =true;
	hashtable[hash]->val = val;
	++valcount;
	++nodecount;
	return (0);
}

string	HashTable::find(string& name, t_fhash f_hash)
{
	string		tmp;
	int			i;
	t_ulong	hash {f_hashprimar(name, f_hash)};
	t_ulong	step {f_hashstep(name, f_hash)};
	
	i = 0;
	while (i < tablesize && hashtable[hash] && hashtable[hash]->name != name)
	{
		hash = (hash + step) % tablesize;
		++i;
	}
	if (i >= tablesize)
		return (nullptr);
	if (hashtable[hash] && hashtable[hash]->state)
		tmp = hashtable[hash]->val;
	return (tmp);
}

int	HashTable::remove(string& name, t_fhash f_hash)
{
	int		i;
	t_ulong	hash {f_hashprimar(name, f_hash)};
	t_ulong	step {f_hashstep(name, f_hash)};
	
	i = 0;
	while (i < tablesize && hashtable[hash] && hashtable[hash]->name != name)
	{
		hash = (hash + step) % tablesize;
		++i;
	}
	if (i >= tablesize)
		return (0);
	hashtable[hash]->state = false;
	--valcount;
	return (0);
}

struct Bucket
{
	string	key;
	string	val;
	Bucket() {}
	Bucket(string key_, string val_) : key(key_), val(val_) {}
};

Bucket	*crtBuckets(int count)
{
	string	val {"5"};
	string	key {"var"};
	Bucket		*buckets;
	
	buckets = new Bucket[count];
	for (int i = 0; i < count; ++i)
	{
		buckets[i].key = key + std::to_string(i);
		buckets[i].val = val + std::to_string(i);
	}
	return (buckets);
}

uint32_t murmur3_32(const char* str, size_t len, uint32_t seed)
{
	uint32_t		k;
	const uint8_t	*key	{reinterpret_cast<const uint8_t*>(str)};
    uint32_t 		h		{seed};
    const uint32_t	c1		{0xcc9e2d51};
    const uint32_t	c2		{0x1b873593};
    const int 		r1		{15};
    const int 		r2		{13};
    const uint32_t 	m		{5};
    const uint32_t 	n		{0xe6546b64};

    for (size_t i = len >> 2; i; i--) {
        k = *reinterpret_cast<const uint32_t*>(key);
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;
        h ^= k;
        h = (h << r2) | (h >> (32 - r2));
        h = h * m + n;
        key += 4;
    }
	k = 0;
    switch (len & 3) {
        case 3: k ^= key[2] << 16;
        case 2: k ^= key[1] << 8;
        case 1: k ^= key[0];
                k *= c1;
                k = (k << r1) | (k >> (32 - r1));
                k *= c2;
                h ^= k;
    }
    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}

int	main()
{
	const int	count = 10;
	Bucket	*buckets;
	string	name{"var"};
	string	val{"ABCDE"};
	HashTable	hashtable{8};

	buckets = crtBuckets(count);
	for (int i = 0; i < count; ++i)
	{
		cout << "KEY:\t" << buckets[i].key << "\tVAR:\t" << buckets[i].val << endl;
		hashtable.add(buckets[i].key, buckets[i].val, murmur3_32);
	}
	for (int i = 0; i < count; ++i)
		cout << "Result of find operation:\n" << hashtable.find(buckets[i].key, murmur3_32) << endl;
	delete [] buckets;
	return (0);
}
