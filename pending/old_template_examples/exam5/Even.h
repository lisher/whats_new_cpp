template <typename T>
class Even
{
    public:
        Even(T arg);

        T getValue();
    private:
        T value;
};

template <typename T>
Even<T>::Even(T arg)
{
    value = arg % 2 ? arg + 1 : arg;
}

template <typename T>
T Even<T>::getValue()
{
    return value;
}
