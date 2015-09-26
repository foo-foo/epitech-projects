//
// Nibbler.hh for nibbler in /home/menich_a/rendu/cpp_nibbler/includes
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Sun Apr  5 16:58:45 2015 Anatole Menichetti
// Last update Sun Apr  5 17:03:39 2015 Anatole Menichetti
//

#ifndef NIBBLER_HH_
# define NIBBLER_HH_

# include <list>
# include <string>

# define SPEED		(125000)
# define MAX_SPEED	(20000)
# define ACCELERATION	(100)

# define ENABLE		(true)
# define DISABLE	(false)

class		Nibbler
{
  typedef void	(Nibbler::*fptr)(void);

 private:
  std::string	_map;
  size_t	_width;
  size_t	_height;
  int		_dir;
  fptr		_dir_to_go[4];

  size_t	m_score;
  bool		m_state;
  size_t	m_speed;
  size_t	m_moves;
  size_t	m_nbrFruits;
  size_t	m_step;
  bool		m_mutex;
  bool		m_crazy;
  bool		m_boost;

  std::list< std::pair <int, int> > _snake;

  bool		check_coo(int, int);
  void		move(int, int);
  void		go_up();
  void		go_down();
  void		go_left();
  void		go_right();
  void		put_fruit(char);
  
 public:
  Nibbler(size_t, size_t);
  ~Nibbler();

  void		go();

  void		turn_left();
  void		turn_right();

  size_t	getWidth() const;
  size_t	getHeight() const;
  size_t	getScore() const;

  bool		isActive() const; // Return the GUI state.                                                   
  void		disable(); // Set the GUI state to DISABLE.

  size_t	getSpeed() const;
  void		boost();
  void		speed(size_t);

  std::string const	&getMap() const;

  void		retry();
};

#endif /* !NIBBLER_HH_ */
