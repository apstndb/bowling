#include "bowlingScore.h"
//#include "util.h"
#include <boost/format.hpp>
#include <iostream>
using namespace std;
using namespace boost;
namespace bowling
{
  Frame::Frame(Frame* nextFrame)
    :throwed_(0),ball1_(0),ball2_(0),nextFrame_(nextFrame)
  {
  }
  Frame::~Frame()
  {
  }
  bool Frame::isOver() const
  {
    return isStrike(ball1_) || throwed_ == 2;
  }
  char Frame::letterBall1(unsigned int ball1) const
  {
    if(throwed_ == 0) return ' ';
    else if(isStrike(ball1)) return 'X';
    else if(ball1 == 0) return 'G';
    else return '0'+ball1;
  }
  char Frame::letterBall2(unsigned int ball1, unsigned int ball2) const
  {
    if(throwed_ < 2) return ' ';
    else return letterBall2Impl(ball1, ball2);
  }
  char TenthFrame::letterBall2(unsigned int ball1, unsigned int ball2) const
  {
    if(throwed_ < 2) return ' ';
    else if(isStrike(ball1)) {
      return letterBall1(ball2);
    }
    else return letterBall2Impl(ball1, ball2);
  }
  char Frame::letterBall2Impl(unsigned int ball1, unsigned int ball2) const
  {
    if(isSpare(ball1, ball2)) return '/';
    else if(isStrike(ball1)) return ' ';
    else if(ball2 == 0) return 'G';
    else return '0'+ball2;
  }
  char TenthFrame::letterBall3(unsigned int ball1, unsigned int ball2, unsigned int ball3) const
  {
    if(throwed_ != 3) return ' ';
    else if(isStrike(ball1)) {
      if(isStrike(ball2)) return letterBall1(ball3);
      else return letterBall2Impl(ball2, ball3);
}
    else {
      if(isSpare(ball1,ball2)) return letterBall1(ball3);
      else {
        if(ball3) throw 3;
        return '-';
      }
    }
  }
  void Frame::print(std::ostream& os) const
  {
    cout << letterBall1(ball1_) << letterBall2(ball1_,ball2_);
  }
  bool Frame::anyPinIsStanding() const
  {
    return ball1_+ball2_ != 10;
  }
  void TenthFrame::print(std::ostream& os) const
  {
    cout << letterBall1(ball1_) << letterBall2(ball1_,ball2_)
      << letterBall3(ball1_, ball2_, ball3_);
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
        result = !isStrike(ball1_);
        break;
      case 2:
        result = isStrike(ball1_)?!isStrike(ball2_):!isSpare(ball1_,ball2_);
        break;
      case 3:
        result = isStrike(ball1_)&&isStrike(ball2_)?
          !isStrike(ball3_):!isSpare(ball2_,ball3_);
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
  unsigned int Frame::calcScore() const
  {
    return ball1_+ball2_;
  }
  unsigned int Frame::calcTotalScore() const
  {
    unsigned int score = calcScore();
    if(isStrike(ball1_) || isSpare(ball1_, ball2_)) {
      if(nextFrame_) {
        score += nextFrame_->ball1_;
        if(isStrike(ball1_)) {
          if(isStrike(nextFrame_->ball1_)&&nextFrame_->nextFrame_) {
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
  bool TenthFrame::isOver() const
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
  unsigned int TenthFrame::calcScore() const
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
  bool Game::isOver() const
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
  unsigned int Game::getCurrentFrame() const
  {
    return currentFrame_+1;
  }
  unsigned int Game::calcTotalScore() const
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

  unsigned int Game::getCurrentBall() const
  {
    if(currentFrame_>= 10) throw 1;
    return frames_[currentFrame_]->throwed_+1;
  }
    
  unsigned int Game::getFrameScore(size_t frame) const
  {
    return frames_[frame]->calcTotalScore();
  }

  unsigned int Game::getScoreOfPoint(size_t frame) const
  {
    unsigned int sum(0);
    do {
      sum += getFrameScore(frame);
    } while(frame--);
    return sum;
  }

  void Game::print(std::ostream& os) const
  {
    for(size_t i = 0; i < 10; ++i) {
      os << boost::format(i!=9?"%||\t":"%||") % *frames_[i];
    }
    os << '\n';
    for(size_t i = 0; i < 10; ++i) {
      os << boost::format(i!=9?"%||\t":"%||") % getScoreOfPoint(i);
    }

  }
  bool Game::anyPinIsStanding() const
  {
    return frames_[currentFrame_]->anyPinIsStanding();
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

