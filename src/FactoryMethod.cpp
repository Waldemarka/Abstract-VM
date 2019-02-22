/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FactoryMethod.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 15:29:04 by vomelchu          #+#    #+#             */
/*   Updated: 2019/02/12 15:29:05 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FactoryMethod.hpp"
#include <cfloat>

Factory::Factory(){}
Factory::~Factory(){}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const
{
	if (type == Int32) return (createInt32(value));
	else if (type == Int16) return (createInt16(value));
	else if (type == Int8) return (createInt8(value));
	else if (type == Float) return (createFloat(value));
	else if (type == Double) return (createDouble(value));
	else throw ("bad type:(");
}

IOperand const * Factory::createInt32( std::string const & value ) const
{
	try{
		int a = std::stoi(value.c_str());
		if (a >= -2147483648 && a <= 2147483647)
			return(new Operand<int32_t>(a, static_cast<eOperandType>(Int32)));
		else
		{
			std::cout << "overflow int 32" << std::endl;
			return (0);
		}
	}
	catch (std::exception & e)
	{
		std::cout << "overflow int 32" << std::endl;
		return (0);
	}
}

IOperand const * Factory::createInt8( std::string const & value ) const
{
	try{
		int a = std::stoi(value.c_str());
		if (a  < 128 && a >= -128)
			return(new Operand<int8_t>(a, static_cast<eOperandType>(Int8)));
		else
		{
			std::cout << "overflow int 8" << std::endl;
			return (0);
		}
	}
	catch (std::exception & e)
	{
		std::cout << "overflow int 8" << std::endl;
		return (0);
	}
}

IOperand const * Factory::createInt16( std::string const & value ) const
{
	try{
		int a = std::stoi(value.c_str());
		if (a < 32768 && a >= -32768)
			return(new Operand<int16_t>(a, static_cast<eOperandType>(Int16)));
		else
		{
			std::cout << "overflow int 16" << std::endl;
			return (0);
		}
	}
	catch (std::exception & e)
	{
		std::cout << "overflow int 16" << std::endl;
		return (0);
	}
}

IOperand const * Factory::createFloat( std::string const & value ) const
{
	try{
		int a = std::stof(value.c_str());
		if (a >= -FLT_MAX && a <= FLT_MAX)
			return(new Operand<float>(a, static_cast<eOperandType>(Float)));
		else
		{
			std::cout << "overflow int float" << std::endl;
			return (0);
		}
	}
	catch (std::exception & e)
	{
		std::cout << "overflow int float" << std::endl;
		return (0);
	}
}

IOperand const * Factory::createDouble( std::string const & value ) const
{
	try{
		int a = std::stod(value.c_str());
		if (a >= -DBL_MAX && a <= DBL_MAX)
			return(new Operand<double>(a, static_cast<eOperandType>(Double)));
		else
		{
			std::cout << "overflow int double" << std::endl;
			return (0);
		}
	}
	catch (std::exception & e)
	{
		std::cout << "overflow int double" << std::endl;
		return (0);
	}
}