#include "bowlingScore.h"
//#include "util.h"
#include <boost/format.hpp>
using namespace std;
using namespace boost;
namespace bowling
{
  Frame::Frame(Frame* nextFrame)
    :throwed_(0),ball1_(0),ball2_(0),nextFrame_(nextFrame)
  {}
  Frame::~Frame()
  {
  }
  bool Frame::isStrike() const
  {
    return ball1_==10;
  }
  bool Frame::isSpare() const
  {
    return ball1_+ball2_==10&&!isStrike();
  }
  bool Frame::isOver()
  {
    return ball1_==10 || throwed_ == 2;
  }
  void Frame::print(std::ostream& os) const
  {
  }
  bool Frame::anyPinIsStanding() const
  {
    return ball1_+ball2_ != 10;
  }
  void TenthFrame::print(std::ostream& os) const
  {

  }

  bool TenthFrame::anyPinIsStanding() const
  {
    bool result;
    switch(throwed_)
    {
      case 0:
        result = true;
        break;
      case 1:
        result = ball1_ != 10;
        break;
      case 2:
        result = ((ball1_ == 10)?ball2_:ball1_+ball2_) < 10;
        break;
      case 3:
        result = ((ball1_+ball2_ == 20)?ball3_:ball1_+ball2_) < 10;
        break;
      default:
        throw 3;
        break;
    }
    return result;
  }
  bool Frame::put(unsigned int pins)
  {
    if(isOver()) {throw int(1);}
    switch(throwed_)
    {
      case 0:
        ball1_ = pins;
        break;
      case 1:
        ball2_ = pins;
        break;
      default:
        throw int(2);
        break;
    }
    if(calcScore()>10) {throw int(1);}
    ++throwed_;

    return isOver();
  }
  unsigned int Frame::calcScore() {
    return ball1_+ball2_;
  }
  unsigned int Frame::calcTotalScore() {
    unsigned int score = calcScore();
    if(score==10) {
      if(nextFrame_) {
        score += nextFrame_->ball1_;
        if(isStrike()) {
          if(nextFrame_->isStrike()&&nextFrame_->nextFrame_) {
            score += nextFrame_->nextFrame_->ball1_;
          } else {
            score += nextFrame_->ball2_;
          }
        }
      }
    }
    return score;
  }
  TenthFrame::TenthFrame(Frame* nextFrame)
    :Frame(nextFrame), ball3_(0)
  {}
  TenthFrame::~TenthFrame()
  {}
  bool TenthFrame::isOver()
  {
    return (throwed_==2 && ball1_+ball2_<10) || throwed_ ==3;
  }
  bool TenthFrame::put(unsigned int pins)
  {
    if(isOver()) {throw int(1);};
    switch(throwed_)
    {
      case 0:
        ball1_ = pins;
        break;
      case 1:
        ball2_ = pins;
        break;
      case 2:
        ball3_ = pins;
        break;
      default:
        throw int(2);
        break;
    }
    if(calcScore()>30) {throw int(1);}
    ++throwed_;

    return isOver();
  }
  unsigned int TenthFrame::calcScore()
  {
    return ball1_+ball2_+ball3_;
  }
  Game::Game()
    :currentFrame_(0)
  {
    Frame* nextFrame(0);

    for(size_t i = 10; i;) {
      Frame* frame;
      if(i==10) {
        frame = new TenthFrame(nextFrame);
      }
      else {
        frame = new Frame(nextFrame);
      }
      frames_[--i] = nextFrame = frame;
    }
  }
  bool Game::isOver()
  {
    return currentFrame_ == 10;
  }
  bool Game::put(unsigned int pins)
  {
    if(isOver()) {throw int(1);};
    if(frames_[currentFrame_]->put(pins)) {
      ++currentFrame_;
    }
    return isOver();
  }
  unsigned int Game::getCurrentFrame()
  {
    return currentFrame_+1;
  }
  unsigned int Game::calcTotalScore()
  {

    unsigned int sum(0);
    for(size_t i = 0; i < 10; ++i) {
      sum += frames_[i]->calcTotalScore();
    }
    return sum;
  }
  Game::~Game()
  {
    for(size_t i = 0; i!=10;++i) {
      delete frames_[i];
    }
  }

  unsigned int Game::getCurrentBall()
  {
    if(currentFrame_>= 10) throw 1;
    return frames_[currentFrame_]->throwed_+1;
  }
    
  unsigned int Game::getFrameScore(size_t frame)
  {
    return frames_[frame]->calcTotalScore();
  }

  unsigned int Game::getScoreOfPoint(size_t frame)
  {
    unsigned int sum(0);
    /*for(size_t i = 0; i<=frame; ++i) {
      sum += getFrameScore(i);
    }*/
    for(; frame; --frame) {
      sum += getFrameScore(frame);
    }
    return sum;
  }

  void Game::print(std::ostream& os) const
  {
    for(size_t i = 0; i < 10; ++i) {
      os << boost::format("%4s") % *frames_[i];
    }
  }
  bool Game::anyPinIsStanding() const
  {
    return frames_[currentFrame_-1]->anyPinIsStanding();
  }
  std::ostream& operator<<(std::ostream& os, const Game& rhs)
  {
    rhs.print(os);
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const Frame& rhs)
  {
    rhs.print(os);
    return os;
  }
}

