#include <SDL2/SDL.h>
#include <cctype>
#include "StartPageView.hpp"
#include "TextRenderer.hpp"
#include "../utils/Constants.hpp"

#define MS_PER_UPDATE 50

#define RESIZE 1.5f
#define TEXT_BUTTON_X 28
#define USER_BUTTON_Y 78
#define PASS_BUTTON_Y 118
#define DONE_BUTTON_X 112
#define DONE_BUTTON_WIDTH static_cast<int>(((7 + 2) * 4 + 1) * RESIZE)
#define DONE_BUTTON_Y 168

#define TEXT_BUTTON_WIDTH static_cast<int>(((7 + 2) * 10 + 2) * RESIZE)
#define BUTTON_HEIGHT static_cast<int>((7 + 4) * RESIZE)

#define ERROR_MSG_X 74
#define ERROR_MSG_Y 138

extern bool quitRequested;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

static constexpr char USERNAME[] = "USERNAME";
static constexpr char PASSWORD[] = "PASSWORD";
static constexpr char DONE[] = "DONE";

static constexpr char MSG_OK[] = "OK";
static constexpr char MSG_ABORTED[] = "SERVER DISCONNECTED";
static constexpr char MSG_INVALID_USER[] = "INVALID USER";
static constexpr char MSG_INVALID_PASS[] = "INVALID PASSWORD";
static constexpr char MSG_USER_ALREADY_CONNECTED[] = "USER ALREADY CONNECTED";
static constexpr char MSG_MAX_USERS_CONNECTED[] = "MAX USERS CONNECTED";

static constexpr SDL_Rect usernameRect = { TEXT_BUTTON_X,
  USER_BUTTON_Y,
  TEXT_BUTTON_WIDTH,
  BUTTON_HEIGHT };

static constexpr SDL_Rect passwordRect = { TEXT_BUTTON_X,
  PASS_BUTTON_Y,
  TEXT_BUTTON_WIDTH,
  BUTTON_HEIGHT };

static constexpr SDL_Rect doneRect = { DONE_BUTTON_X,
  DONE_BUTTON_Y,
  DONE_BUTTON_WIDTH,
  BUTTON_HEIGHT };

static int setFocusColor(int focus)
{
  return SDL_SetRenderDrawColor(
    renderer, 128 + focus * 127, (1 - focus) * 128, (1 - focus) * 128, 255);
}

namespace {
constexpr bool mouseOnUsernameButton(int x, int y)
{
  return usernameRect.y <= y && y <= usernameRect.y + usernameRect.h
         && usernameRect.x <= x && x <= usernameRect.x + usernameRect.w;
}

constexpr bool mouseOnPasswordButton(int x, int y)
{
  return passwordRect.y <= y && y <= passwordRect.y + passwordRect.h
         && passwordRect.x <= x && x <= passwordRect.x + passwordRect.w;
}

constexpr bool mouseOnDoneButton(int x, int y)
{
  return doneRect.y <= y && y <= doneRect.y + doneRect.h && doneRect.x <= x
         && x <= doneRect.x + doneRect.w;
}
}// namespace

StartPage::StartPage() : resultMsg{ "" } {}

user_t StartPage::getLoginUser()
{
  SDL_StartTextInput();

  bool loginDone = false;
  SDL_Event event;

  int inicio, fin;

  while (!loginDone && !quitRequested) {
    inicio = SDL_GetTicks();

    while (!loginDone && SDL_PollEvent(&event))
      if (event.type == SDL_QUIT)
        quitRequested = true;
      else if (event.type != SDL_MOUSEMOTION)
        loginDone = handle(event);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    show();
    SDL_RenderPresent(renderer);

    fin = SDL_GetTicks();
    SDL_Delay(std::max(MS_PER_UPDATE - (fin - inicio), 0));
  }

  SDL_StopTextInput();

  user_t user{};
  memcpy(user.username, username.c_str(), sizeof user.username);
  memcpy(user.password, password.c_str(), sizeof user.password);

  return user;
}

void StartPage::show() const
{
  SDL_RenderClear(renderer);

  punto<int> pos;
  pos.x = TEXT_BUTTON_X + 2 * RESIZE;
  pos.y = 58 + 2 * RESIZE;
  TextRenderer::renderText(pos, USERNAME, RESIZE);

  pos.y += 20;
  TextRenderer::renderText(pos, username.c_str(), RESIZE);
  setFocusColor(focus == 0);
  SDL_RenderDrawRect(renderer, &usernameRect);

  pos.y += 20;
  TextRenderer::renderText(pos, PASSWORD, RESIZE);

  pos.y += 20;
  TextRenderer::renderText(pos, password.c_str(), RESIZE);
  setFocusColor(focus == 1);
  SDL_RenderDrawRect(renderer, &passwordRect);

  pos.x = DONE_BUTTON_X + 2 * RESIZE;
  pos.y = DONE_BUTTON_Y + 2 * RESIZE;
  TextRenderer::renderText(pos, DONE, RESIZE);
  setFocusColor(focus == 2);
  SDL_RenderDrawRect(renderer, &doneRect);

  showError();
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void StartPage::showError() const
{
  const punto<int> pos{ TEXT_BUTTON_X + static_cast<int>(2 * RESIZE),
    ERROR_MSG_Y };
  TextRenderer::renderText(pos, resultMsg, 1, Color::RED);
}

bool StartPage::handle(const SDL_Event &event)
{
  if (event.type == SDL_MOUSEBUTTONDOWN
      && event.button.button == SDL_BUTTON_LEFT) {
    int x = event.button.x;
    int y = event.button.y;

    if (mouseOnUsernameButton(x, y))
      focus = 0;
    else if (mouseOnPasswordButton(x, y))
      focus = 1;
    else if (mouseOnDoneButton(x, y)) {
      return true;
    }
  } else if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
    case SDLK_BACKSPACE:
      if (focus == 0 && !username.empty())
        username.pop_back();
      else if (focus == 1 && !password.empty())
        password.pop_back();
      break;
    case SDLK_KP_ENTER:
    case SDLK_RETURN:
      if (focus) return true;
      [[fallthrough]];
    case SDLK_TAB:
      focus = (focus + 1) % 3;
      break;
    default:
      break;
    }
  } else if (event.type == SDL_TEXTINPUT) {
    char in = toupper(*event.text.text);
    if (TextRenderer::includesCharacter(in))
      if (focus == 0 && username.size() < 10)
        username += in;
      else if (focus == 1 && password.size() < 10)
        password += in;
  }
  return false;
}

void StartPage::setResponse(Login response)
{
  switch (response) {
  case Login::INVALID_USER_PASS:
    this->resultMsg = MSG_INVALID_PASS;
    break;
  case Login::USER_ALREADY_CONNECTED:
    this->resultMsg = MSG_USER_ALREADY_CONNECTED;
    break;
  case Login::MAX_USERS_CONNECTED:
    this->resultMsg = MSG_MAX_USERS_CONNECTED;
    break;
  case Login::INVALID_USER:
    this->resultMsg = MSG_INVALID_USER;
    break;
  default:
    break;
  }
}
