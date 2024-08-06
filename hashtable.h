/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pablo Escobar <sataniv.rider@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:52:51 by Pablo Escob       #+#    #+#             */
/*   Updated: 2024/08/06 20:13:28 by Pablo Escob      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

template<typename t_val>
class   HashTable
{
	const int		sizescale = 2;
	const float		rehash = 0.75;
	int				realsize;
	int             arrsize;
	int             sizewithdelete;
	struct			Node
	{
		bool    state;
		t_val    *val;
		Node(char *val_ = NULL) : val(val_), state(true) {};
	};
	Node			**hashtable;
	int             f_hash(const char *str, int tabsize);
	void            rehash();
public:
	HashTable(int size_ = 0);
	HashTable(const HashTable<t_val> &obj);
	~HashTable();
	HashTable	&operator=(const HashTable<t_val> &obj);
	int			add(const char *name, t_val *val);
	int			remove(const char *name);
	char		*find(const char *name);
};