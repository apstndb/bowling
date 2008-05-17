#ifndef BOWLING_SCORE_H
#define BOWLING_SCORE_H

#include <iosfwd>

namespace bowling
{
  struct Frame {
    unsigned int throwed_;
    unsigned int ball1_, ball2_;
    Frame* nextFrame_;
    Frame(Frame* nextFrame);
    virtual ~Frame();
    virtual bool put(unsigned int pins);
    virtual bool isOver();
    virtual unsigned int calcScore();
    unsigned int calcTotalScore();
    bool isStrike() const;
    bool isSpare() const;
    virtual bool anyPinIsStanding() const;
    virtual void print(std::ostream& os) const;
  };

  struct TenthFrame : public Frame
  {
    unsigned int ball3_;
    TenthFrame(Frame* nextFrame);
    virtual ~TenthFrame();
    virtual bool put(unsigned int pins);
    virtual bool isOver();
    virtual unsigned int calcScore();
    unsigned int calcTotalScore();
    virtual void print(std::ostream& os) const;
    virtual bool anyPinIsStanding() const;
  };

  class Game
  {
    private:
    unsigned int currentFrame_;
    Frame* frames_[10];
    public:
    Game();
    ~Game();
    unsigned int getFrameScore(size_t frame);
    unsigned int getScoreOfPoint(size_t frame);
    unsigned int calcTotalScore();
    unsigned int getCurrentFrame();
    unsigned int getCurrentBall();
    bool put(unsigned int pins);
    bool anyPinIsStanding() const;
    void print(std::ostream& os) const;
    bool isOver();
  };

  std::ostream& operator<<(std::ostream& os, const Game& rhs);
  std::ostream& operator<<(std::ostream& os, const Frame& rhs);
}
#endif
