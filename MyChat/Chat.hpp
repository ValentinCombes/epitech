#ifndef	__CHAT_HPP__
# define	__CHAT_HPP__

#include <list>
#include <string>

class		Chat
{
private:
  std::list<Contact *>	_contacts;
  std::list<IChat *>	_chats;
  Contact		*_user;

public:
  Chat();
  ~Chat();

  bool			LogIn(std::string login, std::string passwd);
};

#endif
