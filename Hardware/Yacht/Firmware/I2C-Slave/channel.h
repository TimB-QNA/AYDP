class channel
{
  public:
    unsigned int lowLimit;
    unsigned int highLimit;
    unsigned int setPoint;
    bool changed;

    channel();
    void set(unsigned int val);
    unsigned int value();
};
