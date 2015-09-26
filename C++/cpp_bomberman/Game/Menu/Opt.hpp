//
// Opt.hpp for bomberman in /home/arthur/rendu/cpp_bomberman/Game/config
// 
// Made by Arthur Le Meur
// Login   <le-meu_a@epitech.net>
// 
// Started on  Sat Jun 13 17:08:44 2015 Arthur Le Meur
// Last update Sat Jun 13 17:47:45 2015 Arthur Le Meur
//

#ifndef OPT_HPP_
# define OPT_HPP_

# include <string>
# include <fstream>
# include <vector>

class	Opts
{
public:
  Opts(std::string file);
  ~Opts();

  int	getNbIa() const;
  int	getLevelIa() const;
  void	debug() const;

private:
  std::ifstream	m_file;
  int		m_nbIa;
  int		m_levelIa;
  std::vector<std::string> m_content;

  std::vector<std::string>	split(std::string str, char delimiter);
};

#endif // !OPT_HPP_
