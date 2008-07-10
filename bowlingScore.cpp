#include "bowlingScore.h"
#include <boost/format.hpp>
#include <string>
#include <iostream>
using namespace std;
using boost::wformat;

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
  wchar_t Frame::letterBall1(unsigned int ball1) const
  {
    if(throwed_ == 0) return L' ';
    else if(isStrike(ball1)) return L'X';
    else if(ball1 == 0) return L'G';
    else return L'0'+ball1;
  }
  wchar_t Frame::letterBall2(unsigned int ball1, unsigned int ball2) const
  {
    if(throwed_ < 2) return L' ';
    else return letterBall2Impl(ball1, ball2);
  }
  wchar_t TenthFrame::letterBall2(unsigned int ball1, unsigned int ball2) const
  {
    if(throwed_ < 2) return L' ';
    else if(isStrike(ball1)) {
      return letterBall1(ball2);
    }
    else return letterBall2Impl(ball1, ball2);
  }
  wchar_t Frame::letterBall2Impl(unsigned int ball1, unsigned int ball2) const
  {
    if(isSpare(ball1, ball2)) return L'/';
    else if(isStrike(ball1)) return L' ';
    else if(ball2 == 0) return L'G';
    else return L'0'+ball2;
  }
  wchar_t TenthFrame::letterBall3(unsigned int ball1, unsigned int ball2, unsigned int ball3) const
  {
    if(throwed_ == 3) {
      if(isStrike(ball1)) {
        if(isStrike(ball2)) return letterBall1(ball3);
        else return letterBall2Impl(ball2, ball3);
      }
      else {
        if(isSpare(ball1,ball2)) return letterBall1(ball3);
        else throw 3;
      }
    }
    else if(isOver()) return L'-';
    else return L' ';
  }
  std::wstring Frame::str() const
  {
    std::wstring str;
    str += L' ';
    str += L' ';
    str += letterBall1(ball1_);
    str += letterBall2(ball1_,ball2_);
    return str;
  }
  void Frame::print(std::wostream& os) const
  {
    std::wstring str;
    str += L' ';
    str += L' ';
    str += letterBall1(ball1_);
    str += letterBall2(ball1_,ball2_);
    os << str;
  }
  bool Frame::anyPinIsStanding() const
  {
    return ball1_+ball2_ != 10;
  }

  std::wstring TenthFrame::str() const
  {
    std::wstring str;
    str += L' ';
    str += letterBall1(ball1_);
    str += letterBall2(ball1_,ball2_);
    str += letterBall3(ball1_, ball2_, ball3_);
    return str;
  }
  void TenthFrame::print(std::wostream& os) const
  {
    std::wstring str;
    str += L' ';
    str += letterBall1(ball1_);
    str += letterBall2(ball1_,ball2_);
    str += letterBall3(ball1_, ball2_, ball3_);
    os << str;
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
        throw "Can't be reach.";
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
  Game::Game(unsigned int num)
    :frames_(num), currentFrame_(0), numberOfFrames_(num)
  {
    Frame* nextFrame(0);

    for(std::size_t i = numberOfFrames(); i;) {
      Frame* frame;
      if(i == numberOfFrames()) {
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
    return currentFrame_ == numberOfFrames();
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
    for(std::size_t i = 0; i < numberOfFrames(); ++i) {
      sum += frames_[i]->calcTotalScore();
    }
    return sum;
  }
  Game::~Game()
  {
    for(std::size_t i = 0; i != numberOfFrames();++i) {
      delete frames_[i];
    }
  }

  unsigned int Game::getCurrentBall() const
  {
    if(currentFrame_>= numberOfFrames()) throw 1;
    return frames_[currentFrame_]->throwed_+1;
  }

  unsigned int Game::getFrameScore(std::size_t frame) const
  {
    return frames_[frame]->calcTotalScore();
  }

  unsigned int Game::getScoreOfPoint(std::size_t frame) const
  {
    unsigned int sum(0);
    do {
      sum += getFrameScore(frame);
    } while(frame--);
    return sum;
  }

  std::wstring Game::str1() const
  {
    wstring str;
    for(std::size_t i = 0; i < numberOfFrames(); ++i) {
      str += frames_[i]->str();
    }
    return str;
  }
  std::wstring Game::str2() const
  {
    wstring str;
    unsigned int n = getCurrentFrame();
    for(std::size_t i = 0; i < numberOfFrames(); ++i) {
      if(i < n) {
        str += boost::str(wformat(L"%|4|") % getScoreOfPoint(i));
      }
      else str +=  L"    ";
    }
    return str;
  }
  void Game::print(std::wostream& os) const
  {
    for(std::size_t i = 0; i < numberOfFrames(); ++i) {
      os << wformat(L"%||") % *frames_[i];
    }
    os << L'\n';
    unsigned int n = getCurrentFrame();
    for(std::size_t i = 0; i < numberOfFrames(); ++i) {
      if(i < n) {
        os << wformat(L"%|4|") % getScoreOfPoint(i);
      }
      else os << L"    ";
    }

  }
  bool Game::anyPinIsStanding() const
  {
    return frames_[currentFrame_]->anyPinIsStanding();
  }
  std::wostream& operator<<(std::wostream& os, const Game& rhs)
  {
    rhs.print(os);
    return os;
  }

  std::wostream& operator<<(std::wostream& os, const Frame& rhs)
  {
    rhs.print(os);
    return os;
  }
}

