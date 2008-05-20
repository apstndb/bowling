#ifndef BOWLING_SCORE_H
#define BOWLING_SCORE_H

#include <iosfwd>
#include <string>

namespace bowling
{
  inline bool isStrike(unsigned int ball1)
  {
    if(ball1 > 10) throw 1;
    return ball1 == 10;
  }
  inline bool isStrikeOrSpare(unsigned int ball1, unsigned int ball2)
  {
    if(ball1 + ball2 > 10) throw 2;
    return ball1+ball2 == 10;
  }
  inline bool isSpare(unsigned int ball1, unsigned int ball2)
  {
    return isStrikeOrSpare(ball1, ball2) && !isStrike(ball1);
  }
  struct Frame {
    unsigned int throwed_;
    unsigned int ball1_, ball2_;
    Frame* nextFrame_;
    Frame(Frame* nextFrame);
    virtual ~Frame();
    virtual bool put(unsigned int pins);
    virtual bool isOver() const;
    virtual unsigned int calcScore()const;
    unsigned int calcTotalScore()const;
    wchar_t letterBall1(unsigned int ball1) const;
    virtual wchar_t letterBall2(unsigned int ball1, unsigned int ball2) const;
    wchar_t letterBall2Impl(unsigned int ball1, unsigned int ball2) const;
    virtual bool anyPinIsStanding() const;
    virtual void print(std::wostream& os) const;
    virtual std::wstring str() const;
  };

  struct TenthFrame : public Frame
  {
    unsigned int ball3_;
    TenthFrame(Frame* nextFrame);
    virtual ~TenthFrame();
    virtual bool put(unsigned int pins);
    virtual bool isOver() const;
    virtual unsigned int calcScore() const;
    unsigned int calcTotalScore() const;
    virtual void print(std::wostream& os) const;
    virtual bool anyPinIsStanding() const;
    virtual wchar_t letterBall2(unsigned int ball1, unsigned int ball2) const;
    virtual std::wstring str() const;
    wchar_t letterBall3(unsigned int ball1, unsigned int ball2,
        unsigned int ball3) const;
  };

  class Game
  {
    private:
    unsigned int currentFrame_;
    Frame* frames_[10];
    public:
    Game();
    ~Game();
    unsigned int getFrameScore(size_t frame) const;
    unsigned int getScoreOfPoint(size_t frame) const;
    unsigned int calcTotalScore() const;
    unsigned int getCurrentFrame() const;
    unsigned int getCurrentBall() const;
    bool put(unsigned int pins);
    bool anyPinIsStanding() const;
    void print(std::wostream& os) const;
    std::wstring str1() const;
    std::wstring str2() const;
    bool isOver() const;
  };

  /*std::wostream& operator<<(std::ostream& os, const Game& rhs);
  std::wostream& operator<<(std::ostream& os, const Frame& rhs);*/
  template<class _CharT, class _Traits>
  std::basic_ostream<_CharT, _Traits>& operator<<(std::basic_ostream<_CharT, _Traits>& os, const Game& rhs)
  {
    rhs.print(os);
    return os;
  }

  template<class _CharT, class _Traits>
 std::basic_ostream<_CharT, _Traits>& operator<<(std::basic_ostream<_CharT, _Traits>& os, const Frame& rhs)
  {
    rhs.print(os);
    return os;
  }
}
#endif
