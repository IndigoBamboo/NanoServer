#include <iostream>
#include "RakPeerInterface.h"

#include "Lobby.hh"

int	main(int argc, char **argv)
{
  bool isServer = false;
  if (argc >= 2)
    {
      // Parse arguments to see if there is the server option
      isServer = true;
    }
  Lobby lobby(isServer);

  lobby.start();
  return 0;
}
