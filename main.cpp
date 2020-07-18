#include <iostream>
#include <cstdlib>
#include <ctime>

enum class TypeAttempt
{
    BIGGER,
    LESS,
    EQUAL
};

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1 ) + min);
}

TypeAttempt getAttempt(int necessary_number, int user_number)
{
    if(user_number > necessary_number)
        return TypeAttempt::BIGGER;
    else if (user_number < necessary_number)
        return TypeAttempt::LESS;
    else if (user_number == necessary_number)
        return TypeAttempt::EQUAL;
}

void printResult(TypeAttempt type_attempt)
{
    switch (type_attempt)
    {
        case TypeAttempt::LESS: std::cout   << "Your number is less.\n";   break;
        case TypeAttempt::BIGGER: std::cout << "Your number is bigger.\n"; break;
        case TypeAttempt::EQUAL: std::cout  << "Your number is correct!";  break;
    }
}

bool playAgain()
{
    while(true)
    {
        std::cout << "Would you like to play again?(y/n): ";
        char answer{' '};
        std::cin >> answer;
        std::cin.ignore(INT_MAX, '\n');

        if(answer == 'y')
            return true;
        if(answer == 'n')
            return false;
    }
}

void hiloPlay()
{
    srand(static_cast<unsigned int>(time(0)));
    bool answer;

    do
    {
        // Preparation sreen
        system("cls");
        std::cout << "Let's play. I'm thinking a number. You have 7 attempts to guess what it is.\n";

        int necessary_number{ getRandomNumber(1, 100) };
        int user_number{ 0 };
        TypeAttempt type_attempt;

        for(int attempt = 0; attempt < 7; ++attempt)
        {
            std::cout << "Attempt #" << attempt + 1 << " :";
            std::cin >> user_number;
            std::cin.ignore(INT_MAX, '\n');

            if(std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                --attempt;
                continue;
            }

            type_attempt = getAttempt(necessary_number, user_number);
            printResult(type_attempt);

            if(type_attempt == TypeAttempt::EQUAL)
            {
                std::cout << "You won!\n";
                answer = playAgain();
                break;
            }

            if(attempt == 6)
            {
                std::cout << "You lost. The necessary number is " << necessary_number << '\n';
                answer = playAgain();
            }
        }
    } while(answer == true);

    std::cout << "Thank you for playing.\n";
}

int main()
{
    hiloPlay();
    return 0;
}
