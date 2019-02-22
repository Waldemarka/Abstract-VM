/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:40:59 by vomelchu          #+#    #+#             */
/*   Updated: 2019/02/06 17:41:00 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include "AvmException.hpp"

enum instruction
{
	PUSH = 1,
	ASSERT = 2,
	ADD = 3,
	POP = 4,
	DUMP = 5,
	SUB = 6,
	MUL = 7,
	DIV = 8,
	MOD = 9,
	PRINT = 10,
	EXIT = 11,
	MORE = 12,
	LESS = 13,
	LASTPRINT
};

struct	Data
{
	int	 		command;
	std::string	value;
	int			type;
};

class Lexer
{
public:
	Lexer();
	~Lexer();
	Lexer(int argc, char** argv);
	Lexer(const Lexer&);
	const Lexer& 		operator=(const Lexer&);
	std::vector<Data>	get_lexer() const;

private:
	class LexerException : public AvmException
	{
		public:
			LexerException();
			LexerException(std::string message){_msg = message;};
			LexerException(LexerException const &);
			~LexerException() throw(){};
			virtual const char* what() const throw () {
				return _msg.c_str();}
		private:
			std::string	_msg;
	};
	std::vector<struct Data> _lexer;
	int					ret_command(char *str);
	Data				make_data(int com, int val1, char *val2);
	int					make_token(char *str);
	void				do_lexer(const char *arg);
	void				without_argv();
	bool				check_with_regex(const char *arg);

};

#endif