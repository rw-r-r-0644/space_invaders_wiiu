/*! A welcome state for the Space Invaders game.
 *
 * This state contains the definitions required to show the welcoming message
 * to the user(s). It contains the game name along with the score instructions
 * and an instruction how to start the game. It does not however contain a
 * complex ste of game logics as the actual game simulation is not required.
 */
#ifndef SPACE_INVADERS_WELCOME_STATE_H
#define SPACE_INVADERS_WELCOME_STATE_H

#include "state.h"
#include "text_entity.h"
#include "drawable_entity.h"

namespace space_invaders
{
  class WelcomeState : public State
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    WelcomeState() = delete;
    WelcomeState(const WelcomeState&) = delete;
    WelcomeState(WelcomeState&&) = delete;
    WelcomeState& operator=(const WelcomeState&) = delete;
    WelcomeState& operator=(WelcomeState&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    WelcomeState(Game& game);
    virtual ~WelcomeState() override = default;

    void update(unsigned long dt);
    void render(SDL_Renderer& renderer);

    void onEnter();
    void onExit();

    void onKeyUp(SDL_JoyButtonEvent& event);
    void onKeyDown(SDL_JoyButtonEvent& event);
  private:
    TextEntity mPlayText;
    TextEntity mNameText;
    TextEntity mSinglePlayerText;
    TextEntity mMultiPlayerText;
    TextEntity mControlsText;
    TextEntity mTableCaptionText;
    TextEntity mTableRow1Text;
    TextEntity mTableRow2Text;
    TextEntity mTableRow3Text;
    TextEntity mTableRow4Text;

    DrawableEntity mTableRow1Sprite;
    DrawableEntity mTableRow2Sprite;
    DrawableEntity mTableRow3Sprite;
    DrawableEntity mTableRow4Sprite;
  };
}

#endif
