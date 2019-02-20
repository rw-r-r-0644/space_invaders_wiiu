#include "scene.h"
#include "game.h"
#include "player_context.h"
#include "text_entity.h"
#include "welcome_state.h"

using namespace space_invaders;

inline std::string toScoreString(int score) {
  auto result = std::to_string(score);
  auto difference = (4 - result.size());
  if (difference >= 0) {
    result = "0000" + result;
  }
  return result.substr(result.length() - 4, 4);
}

Scene::Scene(Game& game) : mGame(game),
  mState(std::make_shared<WelcomeState>(game)),
  mScore1Caption(std::make_shared<TextEntity>(game)),
  mHiScoreCaption(std::make_shared<TextEntity>(game)),
  mScore2Caption(std::make_shared<TextEntity>(game)),
  mScore1Text(std::make_shared<TextEntity>(game)),
  mHiScoreText(std::make_shared<TextEntity>(game)),
  mScore2Text(std::make_shared<TextEntity>(game))
{
  // initialize the static caption for the 1st player score.
  mScore1Caption->setText("SCORE<1>");
  mScore1Caption->setX(125 - (mScore1Caption->getWidth() / 2));
  mScore1Caption->setY(40);

  // initialize the static caption for the high score.
  mHiScoreCaption->setText("HI-SCORE");
  mHiScoreCaption->setX(672 / 2 - (mHiScoreCaption->getWidth() / 2));
  mHiScoreCaption->setY(mScore1Caption->getY());

  // initialize the static caption for the 2nd player score.
  mScore2Caption->setText("SCORE<2>");
  mScore2Caption->setX(672 - 130 - (mScore2Caption->getWidth() / 2));
  mScore2Caption->setY(mScore1Caption->getY());

  // initialize the dynamic score value for the 1st player.
  mScore1Text->setText("0000");
  mScore1Text->setX(125 - (mScore1Text->getWidth() / 2));
  mScore1Text->setY(mScore1Caption->getY() + 35);

  // initialize the dynamic score value for the high score.
  mHiScoreText->setText("0000");
  mHiScoreText->setX(672 / 2 - (mHiScoreText->getWidth() / 2));
  mHiScoreText->setY(mScore1Text->getY());

  // initialize the dynamic score value for the 2nd player.
  mScore2Text->setText("0000");
  mScore2Text->setX(672 - 130 - (mScore2Text->getWidth() / 2));
  mScore2Text->setY(mScore1Text->getY());
}

void Scene::update(unsigned long dt)
{
  // get references to both player context containers.
  const auto& ctx1 = mGame.getPlayerContext1();
  const auto& ctx2 = mGame.getPlayerContext2();

  // ensure that player scores are up-to-date.
  mScore1Text->setText(toScoreString(ctx1.getScore()));
  mScore2Text->setText(toScoreString(ctx2.getScore()));

  // ensure that the hi-score is up-to-date.
  const auto hiScore = mGame.getHiScore();
  mHiScoreText->setText(toScoreString(hiScore));

  mScore1Caption->update(dt);
  mHiScoreCaption->update(dt);
  mScore2Caption->update(dt);

  mScore1Text->update(dt);
  mHiScoreText->update(dt);
  mScore2Text->update(dt);

  mState->update(dt);
}

void Scene::render(SDL_Renderer& renderer)
{
  mScore1Caption->render(renderer);
  mHiScoreCaption->render(renderer);
  mScore2Caption->render(renderer);

  mScore1Text->render(renderer);
  mHiScoreText->render(renderer);
  mScore2Text->render(renderer);

  mState->render(renderer);
}

void Scene::onKeyUp(SDL_JoyButtonEvent& event)
{
  mState->onKeyUp(event);
}

void Scene::onKeyDown(SDL_JoyButtonEvent& event)
{
  mState->onKeyDown(event);
}

void Scene::setState(StatePtr state)
{
  // exit from the old state (if defined).
  if (mState) {
    mState->onExit();
  }

  // assign and enter the new state (if not null)
  mState = state;
  if (mState) {
    mState->onEnter();
  }
}
