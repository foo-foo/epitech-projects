//
// DLLoader.cpp for nibbler in /home/menich_a/rendu/cpp_nibbler
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Fri Apr  3 10:31:51 2015 Anatole Menichetti
// Last update Sun Apr  5 17:08:16 2015 Anatole Menichetti
//

#include <dlfcn.h>
#include "../includes/DLLoader.hh"
#include "../includes/NibError.hh"

DLLoader::DLLoader(std::string const &libname, Nibbler const &nibbler)
{
  AGui	*(*create)(Nibbler const &);
  char	*error;

  handle = dlopen(libname.c_str(), RTLD_LAZY);
  if (!handle)
    throw (NibError("download", dlerror()));

  dlerror();

  create = reinterpret_cast<AGui*(*)(Nibbler const &)>(dlsym(handle, "create"));
  error = dlerror();
  if (error)
    throw (NibError("download", error));

  instance = create(nibbler);
}

DLLoader::~DLLoader()
{
  if (dlclose(handle))
    throw (NibError("download", dlerror()));
}

AGui	*DLLoader::getInstance() const
{
  return (instance);
}
