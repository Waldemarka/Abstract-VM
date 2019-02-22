/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 17:18:14 by vomelchu          #+#    #+#             */
/*   Updated: 2019/02/11 17:18:15 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

//#include "AvmException.hpp"
#include "IOperand.hpp"
#include "FactoryMethod.hpp"

class Parser
{
private:
	class ParserException : public AvmException
	{
		public:
			ParserException();
			ParserException(std::string message){_msg = message;};
			ParserException(ParserException const &);
			~ParserException() throw(){};
			virtual const char* what() const throw () {
				return _msg.c_str();}
		private:
			std::string	_msg;
	};
	std::vector<Data>::iterator			iter;
	std::vector<Data>::iterator			end;
	std::vector<Data>					data;
	std::vector<IOperand const *>		operand;
	Factory 							_factory;
public:
	Parser();
	Parser(std::vector<Data> d);
	~Parser();
	//void			command(std::vector<Data>::iterator	iter);
	void			add();
	void			pop();
	void			sub();
	void			mul();
	void			div();
	void			mod();
	void			dump();
	void			print();
	void			more();
	void			less();
	void			lastprint();
	void			assert(std::vector<Data>::iterator	iter);
	void			push(std::vector<Data>::iterator iter);
	bool			check_exit();
	eOperandType	return_type(int type);
};

#endif
