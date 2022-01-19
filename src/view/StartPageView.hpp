#ifndef START_PAGE_VIEW_H
#define START_PAGE_VIEW_H

#include <string>
#include "../utils/user.hpp"

enum class Login;

class StartPage
{
public:
  StartPage();
  user_t getLoginUser();
  void setResponse(Login response);

private:
  std::string username{};
  std::string password{};
  const char *resultMsg;
  int focus{};

  void show() const;
  void showError() const;
  bool handle(const SDL_Event &event);
};

#endif// START_PAGE_VIEW_H
