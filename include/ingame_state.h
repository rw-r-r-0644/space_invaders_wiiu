/*! The ingame state for the Space Invaders game.
 *
 * This is the state where the player(s) actually play the game. Here we allow
 * users to move and fire with the turret so they can prevent the earch from
 * being invaded by the invaders coming from the space.
 */
#ifndef SPACE_INVADERS_INGAME_STATE_H
#define SPACE_INVADERS_INGAME_STATE_H

#include "avatar.h"
#include "avatar_laser.h"
#include "drawable_entity.h"
#include "state.h"
#include "text_entity.h"
#include "alien.h"
#include "flying_saucer.h"
#include "plunger_shot.h"
#include "squiggly_shot.h"
#include "rolling_shot.h"
#include "shield.h"

#include <vector>

namespace space_invaders
{
  class IngameState : public State
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    IngameState() = delete;
    IngameState(const IngameState&) = delete;
    IngameState(IngameState&&) = delete;
    IngameState& operator=(const IngameState&) = delete;
    IngameState& operator=(IngameState&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    IngameState(Game& game);
    virtual ~IngameState() override = default;

    void update(unsigned long dt);
    void render(SDL_Renderer& renderer);

    void onEnter();
    void onExit();

    void onKeyUp(SDL_JoyButtonEvent& event);
    void onKeyDown(SDL_JoyButtonEvent& event);

    const std::vector<AlienPtr>& getAliens() const { return mAliens; }

    const Avatar& getAvatar() const { return mAvatar; }

    const PlungerShot& getPlungerShot() const { return mPlungerShot; }
          PlungerShot& getPlungerShot()       { return mPlungerShot; }

    const SquigglyShot& getSquigglyShot() const { return mSquigglyShot; }
          SquigglyShot& getSquigglyShot()       { return mSquigglyShot; }

    const RollingShot& getRollingShot() const { return mRollingShot; }
          RollingShot& getRollingShot()       { return mRollingShot; }
  private:
    DrawableEntity          mFooterLine;
    Avatar                  mAvatar;
    CollideableEntity       mLeftOobDetector;
    CollideableEntity       mRightOobDetector;
    CollideableEntity       mTopOobDetector;
    AvatarLaser             mAvatarLaser;
    TextEntity              mLifesText;
    DrawableEntity          mLifeSprite1;
    DrawableEntity          mLifeSprite2;
    std::vector<AlienPtr>   mAliens;
    CollideableEntity       mAlienLeftDirector;
    CollideableEntity       mAlienRightDirector;
    TextEntity              mGameOverText;
    TextEntity              mGameOverInstructions;
    FlyingSaucer            mFlyingSaucer;
    PlungerShot             mPlungerShot;
    SquigglyShot            mSquigglyShot;
    RollingShot             mRollingShot;
    std::vector<ShieldPtr>  mShields;
  }; 
}

#endif
