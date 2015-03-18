#ifndef __LOBBY_HH__
#define __LOBBY_HH__

#include "RakPeerInterface.h"

class Lobby
{
private:
  bool mIsServer;
  RakNet::SocketDescriptor mSocket;
  RakNet::RakPeerInterface *mPeer;

  void searchForLobby();
  void waitForClient();

public:
  explicit Lobby(bool isServer = false);
  ~Lobby();
  void	start();
};

#endif
