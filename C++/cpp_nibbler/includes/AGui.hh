
//
// AGui.hh for nibbler in /home/menich_a/bkp_nib4
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Sun Apr  5 10:02:31 2015 Anatole Menichetti
// Last update Sun Apr  5 17:45:30 2015 Anatole Menichetti
//

#ifndef AGUI_HH_
# define AGUI_HH_

# include <iostream>
# include "Nibbler.hh"

class			AGui
{
protected:
  Nibbler		&m_nibbler; // Nibbler - containing all the game informations.
  bool			m_state; // State of the GUI.

public:
  AGui(Nibbler &); // Init window & set score to 0.
  virtual ~AGui(); // Display score & destroy window.

  virtual void		handleEvents() = 0; // Handle events
  virtual void		dump() = 0; // Display the map.

  bool			isActive() const; // Return the state of the map.
  bool			gaming() const; // Return the state of the nibbler.

  virtual bool		getEvent() const; // Return the event handler capability.
};

#endif /* !AGUI_HH_ */
