//
// DLLoader.hh for nibbler in /home/menich_a/rendu/cpp_nibbler
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Fri Apr  3 10:29:25 2015 Anatole Menichetti
// Last update Sun Apr  5 17:46:40 2015 Anatole Menichetti
//

#ifndef DLLOADER_HH_
# define DLLOADER_HH_

# include "AGui.hh"
# include "Nibbler.hh"

class	DLLoader
{
  AGui	*instance; // An instance previously loaded.
  void	*handle; // The handler used to load the instance.

public:
  DLLoader(std::string const &, Nibbler const &); // Open library and download instance.
  ~DLLoader(); // Cloase library.

  AGui	*getInstance() const; // Return the instance loaded.
};

#endif /* !DLLOADER_HH_ */
