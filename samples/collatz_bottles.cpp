#include <iostream>
#include <string>

int main() {
    std::cout << std::endl;
    std::cout << "                  {}" << std::endl;
    std::cout << "                  ||" << std::endl;
    std::cout << "  ___    ___      )(" << std::endl;
    std::cout << "  \\ /    \\ /     |__|" << std::endl;
    std::cout << "   Y      Y      |  |" << std::endl;
    std::cout << "  _|_    _|_     |__|" << std::endl << std::endl;
    std::cout << "So, you want to know what happened? I'll help you remember." << std::endl;
    std::cout << "How many bottles did we order in the beginning?" << std::endl;
    int bottles;
    std::cin >> bottles;
    if (bottles <= 0) {
        std::cout << "You are still too drunk, my friend..." << std::endl;
        return 0;
    }
    if (bottles == 1) {
        std::cout << "Yes, and you drank it all by yourself! Shame on you!" << std::endl;
        return 0;
    }
    while (1) {
        // we don't have else blocks for ifs
        // and int is used instead of bool
        int is_even;
        is_even = bottles % 2 == 0;
        if (is_even) {
            bottles = bottles / 2;
            std::cout << "In the blink of an eye the count went down to " << bottles << "...";
        }
        if (!is_even) {
            int more;
            more = 2 * bottles + 1;
            std::cout << "We knew it was not enough, so we ordered " << more << " more...";
            bottles = bottles + more;
        }
        std::cout << " Do I even need to continue? Yes or no?" << std::endl;
        std::string answer;
        std::cin >> answer;
        // let's have some fun, shall we?
        int normal_yes;
        normal_yes = answer == "yes"  || answer == "Yes"  || answer == "y" || answer == "Y";
        int yell_yes;
        yell_yes = answer == "YES";
        int drunk_yes;
        drunk_yes = answer == "yES";
        int binary_yes;
        binary_yes = answer == "1";
        int yes;
        yes = normal_yes || yell_yes || binary_yes;
        if (normal_yes) {
            std::cout << "All right, then.";
        }
        if (yell_yes) {
            std::cout << "OK, OK, STOP YELLING!";
        }
        if (drunk_yes) {
            std::cout << "All right, th... wait, are you drinking again right now? Are you?" << std::endl;
            return 0;
        }
        if (binary_yes) {
            std::cout << "[pr0c33din9 2 inf0rm]>_";
        }
        if (!yes) {
            answer = "\"" + answer + "\"";
            std::cout << "So you say " << answer << ", huh. I guess you've heard enough." << std::endl;
            return 0;
        }
        if (bottles == 1) {
            std::cout << " So we have now only one last bottle, and then you drank it all by yourself!" << std::endl;
            return 0;
        }
        std::cout << " So we have now " << bottles << " bottles now." << std::endl;
    }
}
