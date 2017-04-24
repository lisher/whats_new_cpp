template <typename T>
class Even
{
    public:
        Even(T arg)
        {
            value = arg % 2 ? arg + 1 : arg;
        }

        T getValue();
    private:
        T value;
};
