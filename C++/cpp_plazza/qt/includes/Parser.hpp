//
// Parser.hpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/includes
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed Apr 15 18:19:56 2015 Anatole Menichetti
// Last update Thu Apr 16 15:31:30 2015 Anatole Menichetti
//

#ifndef PARSER_HPP_
# define PARSER_HPP_

# include <iostream>

# define PARAMS_NBR	(4)

class	Parser
{
  double	_multiplier;
  size_t	_cooksNbr;
  size_t	_replaceTime;
  
public:
  Parser(int, char **);
  ~Parser();

  double	getMultiplier() const;
  size_t	getCooksNbr() const;
  size_t	getReplaceTime() const;

private:
  double	getDouble(std::string const &) const;
  size_t	getInteger(std::string const &) const;
};

#endif /* !PARSER_HPP_ */
