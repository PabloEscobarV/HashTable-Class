/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pablo Escobar <sataniv.rider@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:52:51 by Pablo Escob       #+#    #+#             */
/*   Updated: 2024/08/16 17:44:46 by Pablo Escob      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cstdint>

using t_ulong = unsigned long;

using std::string;

using t_fhash = uint32_t (*)(const char*, size_t, uint32_t);

class   HashTable
{
	const int		k_sizescale = 2;
	const float		k_rehash = 2.0;
	int				nodecount;
	int             valcount;
	int				tablesize;
	struct			Node
	{
		bool    	state;
		string		val;
		string		name;
		Node() : state(true) {};
	};
	Node			**hashtable;
	void			freehashtable(Node** hashtable, int size);
	// t_ulong			f_hash(string &str, int tabsize, int kef = 31);
	t_ulong			f_hashprimar(string &str, t_fhash hash_f);
	t_ulong			f_hashstep(string &str, t_fhash hash_f);
	void			rehash(t_fhash);
	void			resize(t_fhash);
public:
	HashTable(int size_ = 0);
	HashTable(const HashTable &obj);
	~HashTable();
	HashTable	&operator=(const HashTable &obj);
	int			add(string &name, string &val, t_fhash hash_f);
	int			remove(string &name, t_fhash f_hash);
	string		find(string &name, t_fhash hash_f);
};