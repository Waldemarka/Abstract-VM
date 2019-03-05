/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:57:07 by vomelchu          #+#    #+#             */
/*   Updated: 2019/02/11 16:57:08 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "IOperand.hpp"
#include "Lexer.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

template <typename T>
class Operand : public IOperand
{
private:
	T 				_value;
	eOperandType 	_type;
	std::string		_str;
	Operand();

public:
	Operand(T value, eOperandType type);
	~Operand();
	Operand(Operand const &rhs);
	IOperand &operator=(Operand const &rhs);

	int getPrecision( void ) const;
	eOperandType getType( void ) const;
	IOperand const * operator+( IOperand const & rhs ) const;
	IOperand const * operator-( IOperand const & rhs ) const;
	IOperand const * operator*( IOperand const & rhs ) const;
	IOperand const * operator/( IOperand const & rhs ) const;
	IOperand const * operator%( IOperand const & rhs ) const;
	std::string const & toString( void ) const;
	
};

#endif
