#include "Chat.hpp"

Chat::Chat()
{
}

Chat::~Chat()
{
}

bool	Chat::LogIn(std::string login, std::string passwd)
{
  _user = new Contact(login);
  return true;
}
