#include <iostream>
#include <cstring>
#include "MessageIdentifiers.h"
#include "Lobby.hh"

Lobby::Lobby(bool isServer) : mIsServer(isServer),
			      mPeer(RakNet::RakPeerInterface::GetInstance())
{
  if (mIsServer)
    {
      mSocket.port = 4242;
    }
  else
    {
      mSocket.port = 4243;
    }
}

Lobby::~Lobby()
{
  RakNet::RakPeerInterface::DestroyInstance(mPeer);
}

void Lobby::start()
{
  mPeer->Startup(1, &mSocket, 1);
  if (mIsServer)
    {
      mPeer->SetMaximumIncomingConnections(1);
      waitForClient();
    }
  else
    {
      searchForLobby();
    }
}

void Lobby::searchForLobby()
{
  bool foundLobby = false;
  RakNet::Packet *packet;

  while (!foundLobby)
    {
      mPeer->Ping("255.255.255.255", 4242, false);
      for (packet = mPeer->Receive(); packet; mPeer->DeallocatePacket(packet), packet = mPeer->Receive())
	{
	  switch(packet->data[0])
	    {
	    case ID_UNCONNECTED_PONG:
	      std::cout << "Lobby found ! : " << packet->systemAddress.ToString() << std::endl;
	      foundLobby = true;
	      break;
	    default :
	      std::cout << "UnIdentified packet : " << packet->systemAddress.ToString() << std::endl;
	    }
	}
    }
}

void Lobby::waitForClient()
{
  bool foundClient = false;
  RakNet::Packet *packet;

  while (!foundClient)
    {
      for (packet = mPeer->Receive();packet;mPeer->DeallocatePacket(packet), packet = mPeer->Receive())
	{
	  switch(packet->data[0])
	    {
	    case ID_UNCONNECTED_PING:
	      std::cout << "Client found !" << std::endl;
	      foundClient = true;
	      break;
	    default :
	      std::cout << "UnIdentified packet" << std::endl;
	    }
	}
    }
}
